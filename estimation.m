%% Parametri prova
clear

parameters;

load("data/thd_for_estimation.mat")

% delta= 0.05;
% omegaN = 24.4;
% thetaD0 = 30;
% thetaD0prime = 0;
% sigma = -delta*omegaN;

%% calcoli

values = thd.signals.values;
time = thd.time;

%plot(time, values);

data_osc = values(1920:3750);
osc_mean = abs(movmean(data_osc, 9));

data_bias = values(3750:end);
bias_mean = mean(data_bias);

plot(time(1920:3750), abs(osc_mean-bias_mean));

[peaks, locations] = findpeaks(osc_mean);


locations_new = [];
peaks_new = [];

for i = 1:length(locations)
    if(i+1 <= length(locations))
        if(locations(i) + 20 < locations(i+1))
            locations_new = [locations_new, locations(i)];
            peaks_new = [peaks_new, peaks(i)];
        end
    else
            locations_new = [locations_new, locations(i)];
            peaks_new = [peaks_new, peaks(i)];
    end
end

locations_pos = locations_new(1:2:12);
peaks_pos = peaks_new(1:2:12);

locations_neg = locations_new(2:2:12);
peaks_neg = peaks_new(2:2:12);

figure(10);
plot(osc_mean);
hold on;
scatter(locations_neg, peaks_neg);
hold off;

%% codice tutor
[bbb,aaa] = butter(2,30/500);
data_filt = filtfilt(bbb,aaa,data_osc);
[peaks_2, locations_2] = findpeaks(abs(data_filt));

figure(100)
% plot(abs(data_osc)); hold on;
% plot(osc_mean); hold on;
plot(abs(data_filt));hold on;
scatter(locations_2, peaks_2);

%plot(locations, peaks);

%%

% omega = omegaN*sqrt(1-delta^2);
% Phi = atan((sigma*thetaD0-thetaD0prime)/(omega*thetaD0));
% A = sqrt(thetaD0^2 + ((thetaD0prime-sigma*thetaD0)/omega)^2);
% 
% t = 0:0.001:1.5;
% thetaD =A*exp(sigma*t).*cos(omega*t+Phi);

%%plot(t, thetaD);

%% stima 


k = 0:1:length(peaks_pos)-1;

tk = locations_pos;
LAtheta = peaks_pos;

PHIK = [-k' ones(size(k))'];
YPSILON = LAtheta';

theta_pos = inv(PHIK'*PHIK)*PHIK'*YPSILON;
%plot(tk, LAtheta);

csi = theta_pos(1);

delta_pos = csi/ (sqrt(pi^2 + csi^2));

Tk = [locations_pos(1)/1000];
for i = 2:length(locations_pos)
    Tk = [Tk, (locations_pos(i)-locations_pos(i-1))/1000];
end


omegaK = pi./Tk

w_stim = mean(omegaK)

wn_stim = w_stim / sqrt(1-delta_pos)

Bb = mld.Jb * (2*delta_pos*wn_stim) % 3.4e-3
kpos = mld.Jb*wn_stim^2 % 0.83

%% neg

kneg = 0:1:length(peaks_neg)-1;

tkneg = locations_neg;
LAthetaneg = peaks_neg;

PHIKneg = [-kneg' ones(size(kneg))'];
YPSILONneg = LAthetaneg';

theta_neg = inv(PHIKneg'*PHIKneg)*PHIKneg'*YPSILONneg;
%plot(tk, LAtheta);

csineg = theta_neg(1);

delta_neg = csineg/ (sqrt(pi^2 + csineg^2));

Tkneg = [locations_neg(1)/1000];
for i = 2:length(locations_neg)
    Tkneg = [Tkneg, (locations_neg(i)-locations_neg(i-1))/1000];
end


omegaKneg = pi./Tkneg

w_stimneg = mean(omegaKneg)

wn_stimneg = w_stimneg / sqrt(1-delta_neg)

Bbneg = mld.Jb * (2*delta_neg*wn_stimneg) % 3.4e-3
kneg = mld.Jb*wn_stimneg^2 % 0.83

%%  media

kf = (kneg+kpos)/2

Bb = (Bb + Bbneg)/2
