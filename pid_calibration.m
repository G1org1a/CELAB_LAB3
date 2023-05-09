%% CALIBRAZIONE DEL NOSTRO MODELLO


settling = 0.5;
Overshoot = 0.30;
alpha = 4000;

R_eq = mot.R + sens.curr.Rs;
B_eq = Beq;

%k_m = (drv.dcgain*mot.Kt)/(R_eq*B_eq + mot.Kt*mot.Ke);

%T_m = R_eq*Jeq/(R_eq*B_eq + mot.Kt*mot.Ke);
 
%% Collocated system for hub
%num = [mld.Jb mld.Bb mld.k];
%den = gbox.N*[Jeq*mld.Jb (Jeq*mld.Bb + mld.Jb*B_eq) (B_eq*mld.Bb + mld.k*(Jeq + mld.Jb/(gbox.N^2))) mld.k*(B_eq + mld.Bb/(mld.Bb/gbox.N^2)) 0];


s = tf('s');

D_prime = Jeq*mld.Jb*s^3 + (Jeq*mld.Bb + mld.Jb*B_eq)*s^2 + (B_eq*mld.Bb + mld.k*(Jeq + mld.Jb/(gbox.N^2)))*s + mld.k*(B_eq + (mld.Bb/gbox.N^2));
Hub_tf =  (1/(gbox.N*s))*(drv.dcgain*mot.Kt*(mld.Jb*s^2 +  mld.Bb*s + mld.k))/(R_eq*D_prime + mot.Kt*mot.Ke*(mld.Jb*s^2 +  mld.Bb*s + mld.k));

[num,den] = tfdata(Hub_tf, 'v');
sys = tf(num, den);


[Gm,Pm,Wcg,Wcp] = margin(sys);
%[z, pphi] = bode(sys, w_gc);
%bode(sys);
%margin(sys);


damping = log(1/Overshoot)/sqrt(pi^2 + (log(1/Overshoot)^2));
requested_phase = atan(2*damping/sqrt(sqrt(1+4*damping^4) - 2*damping^2));

w_gc = 3/(damping*settling);
Tl = 1/(10*w_gc);
z = freqresp(sys,w_gc);

DeltaK = 1/abs(z);
DeltaPhi = requested_phase - pi - angle(z);

Kp = DeltaK *cos(DeltaPhi);
Td = (tan(DeltaPhi) + sqrt((tan(DeltaPhi)^2 + 4/alpha)))/(2*w_gc);
Ti = alpha*Td;

Kd = Kp*Td;
%Kd = DeltaK *sin(DeltaPhi)/w_gc;
Ki = Kp/Ti;


%Kp = Kp;
%Ki = Ki/10;
%Kd = Kd*5;

% Kp = DeltaK *cos(DeltaPhi);
% Ki = -w_gc*DeltaK *sin(DeltaPhi);

%% AntiWindup
Tw = settling/5;
Kw = 3/(25*settling*Ki);
%Kw = 3/Tw;
%Kw = 0;


