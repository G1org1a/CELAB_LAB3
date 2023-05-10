delta = log(1/Mp)/sqrt(pi^2 + (log(1/Mp)^2));
w_gc = 3/(delta*ts_star);
phi_m = atan(2*delta/sqrt(sqrt(1+4*delta^4) - 2*delta^2));

alpha = 15;

s = tf('s');

sysDprime = Jeq*mld.Jb*(s^3) + (Jeq*mld.Bb+mld.Jb*Beq)*(s^2) + (Beq*mld.Bb+mld.k*(Jeq+mld.Jb/(gbox.N^2)))*s + mld.k*(Beq + mld.Bb/(gbox.N^2));
%sysDprime = s*(s*Jeq+Beq)*(mld.Jb*s + mld.Bb)+ mld.k*(s*(Jeq+mld.Jb/gbox.N^2)+(Beq+mld.Bb/gbox.N^2));
sysP = (1/(gbox.N*s))*(drv.dcgain*mot.Kt)*(mld.Jb*s^2 + mld.Bb*s + mld.k)/(Req*sysDprime+mot.Kt*mot.Ke*(mld.Jb*s^2 + mld.Jb*s + mld.k));

% [num,den] = tfdata(sysP, 'v');
% sys = tf(num, den);

%[Gm,Pm,Wcg,Wcp] = margin(sysP);

PID.Tl = 1/(5*w_gc);

z = freqresp(sysP,w_gc); % value of sysP at w_gc

DeltaK = 1/abs(z);
DeltaPhi = phi_m - pi - angle(z);

PID.Td = (tan(DeltaPhi) + sqrt((tan(DeltaPhi)^2 + 4/alpha))) / (2*w_gc);
PID.Ti = alpha * PID.Td;

PID.Kp = DeltaK * cos(DeltaPhi);
PID.Kd = PID.Kp * PID.Td;
PID.Ki = PID.Kp / PID.Ti;


Tw = ts_star / 5;
Kw = 4/Tw;


