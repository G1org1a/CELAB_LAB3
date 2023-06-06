%% Parametri prova
clear

parameters;

load("data/thd_for_estimation.mat")
load("data/picchi_cris.mat")
figure(200);
plot(meas.time, meas.signals.values);
hold on;

%% calcoli

values = meas.signals.values;
time = meas.time;

data_osc = values(5400:7000);
osc_mean = abs(movmean(data_osc, 9));

data_bias = values(7500:end);
bias_mean = mean(data_bias);


%% codice tutor
[bbb,aaa] = butter(2,30/500);
data_filt = filtfilt(bbb,aaa,data_osc);
[peaks_2, locations_2] = findpeaks(abs(data_filt));

figure(1)
plot(abs(data_filt));hold on;
scatter(locations_2, peaks_2);


locations_new = [];
peaks_new = [];

for i = 1:length(locations_2)
    if(i+1 <= length(locations_2))
        if(locations_2(i) + 20 < locations_2(i+1))
            locations_new = [locations_new, locations_2(i)];
            peaks_new = [peaks_new, peaks_2(i)];
        end
    else
            locations_new = [locations_new, locations_2(i)];
            peaks_new = [peaks_new, peaks_2(i)];
    end
end

locations_pos = locations_new(1:2:12);
peaks_pos = peaks_new(1:2:12);

locations_neg = locations_new(2:2:12);
peaks_neg = peaks_new(2:2:12);

figure(2);
plot(osc_mean);
hold on;
scatter(locations_pos, peaks_pos);
hold off;


%% stima 

k = 0:1:length(peaks_pos)-1;

tk = locations_pos;
LAtheta = log(peaks_pos);

PHIK = [-k' ones(size(k))'];
YPSILON = LAtheta';

theta_pos = inv(PHIK'*PHIK)*PHIK'*YPSILON;

csi = theta_pos(1);

delta_pos = csi/ (sqrt(pi^2 + csi^2));

Tk = [locations_pos(1)/1000];
for i = 2:length(locations_pos)
    Tk = [Tk, (locations_pos(i)-locations_pos(i-1))/1000];
end


omegaK = pi./Tk

w_stim = mean(omegaK)

wn_stim = w_stim / sqrt(1-delta_pos^2)

Bbpos = mld.Jb * (2*delta_pos*wn_stim) % 3.4e-3
kpos = mld.Jb*wn_stim^2 % 0.83

%% neg

kneg = 0:1:length(peaks_neg)-1;

tkneg = locations_neg;
LAthetaneg = log(peaks_neg);

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

wn_stimneg = w_stimneg / sqrt(1-delta_neg^2)

Bbneg = mld.Jb * (2*delta_neg*wn_stimneg) % 3.4e-3
kneg = mld.Jb*wn_stimneg^2 % 0.83

%%  media

kf = (kneg+kpos)/2

Bb = (Bbpos + Bbneg)/2
