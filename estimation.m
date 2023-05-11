%% Parametri prova

clear all;

delta= 0.05;
omegaN = 24.4;
thetaD0 = 30;
thetaD0prime = 0;
sigma = -delta*omegaN;

%% calcoli

omega = omegaN*sqrt(1-delta^2);
Phi = atan((sigma*thetaD0-thetaD0prime)/(omega*thetaD0));
A = sqrt(thetaD0^2 + ((thetaD0prime-sigma*thetaD0)/omega)^2);

t = 0:0.001:1.5;
thetaD =A*exp(sigma*t).*cos(omega*t+Phi);

%%plot(t, thetaD);

%% stima 

k = 0:1:12;
tk = (k*pi-Phi)/omega;

LAtheta = log(abs(A*exp(sigma*tk).*cos(omega*tk+Phi)));

PHIK = [-k' ones(size(k))'];
YPSILON = LAtheta';

theta_est = inv(PHIK'*PHIK)*PHIK'*YPSILON;
%plot(tk, LAtheta);

csi = theta_est(1);

delta_est = csi/ (sqrt(pi^2 + csi^2));

Tk =tk(2)-tk(1);
omegaK = pi/Tk;

w_stim = sum(omegaK)/size(omegaK);

wn_stim = w_stim / sqrt(1-delta_est);
