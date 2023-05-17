clear;
clc

%% specs

Mp = 0.3;                                               % overshoot
ts_star = 0.85;                                         % settling time

parameters;

%% system tf
s = tf('s');

sysDprime = Jeq*mld.Jb*(s^3) + (Jeq*mld.Bb+mld.Jb*Beq)*(s^2) + (Beq*mld.Bb+mld.k*(Jeq+mld.Jb/(gbox.N^2)))*s + mld.k*(Beq + mld.Bb/(gbox.N^2));
sysP = (1/(gbox.N*s))*(drv.dcgain*mot.Kt)*(mld.Jb*s^2 + mld.Bb*s + mld.k)/(Req*sysDprime+mot.Kt*mot.Ke*(mld.Jb*s^2 + mld.Jb*s + mld.k));

%% scripts

pid_calibration;

%stateSpace_Nominal;

%stateSpace_Integral;

%LQR_design;

%LQR_Bryson;