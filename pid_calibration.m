ts_star = 0.85;
Mp = 0.30;
alpha = 4;

s = tf('s');

sysDprime = s*(s*Jeq+Beq)*(mld.Jb*s + mld.Bb)+ mld.k*(s*(Jeq+mld.Jb/gbox.N^2)+(Beq+mld.Bb/gbox.N^2));
sysP = (1/(gbox.N*s))*(drv.dcgain*mot.Kt)*(mld.Jb*s^2 + mld.Bb*s + mld.k)/(Req*sysDprime+mot.Kt*mot.Ke*(mld.Jb*s^2 + mld.Jb*s + mld.k));

[num,den] = tfdata(sysP, 'v');
sys = tf(num, den);

[Gm,Pm,Wcg,Wcp] = margin(sys);
damping = log(1/Mp)/sqrt(pi^2 + (log(1/Mp)^2));
requested_phase = atan(2*damping/sqrt(sqrt(1+4*damping^4) - 2*damping^2));

w_gc = 3/(damping*ts_star);
Tl = 1/(10*w_gc);
z = freqresp(sys,w_gc);

DeltaK = 1/abs(z);
DeltaPhi = requested_phase - pi - angle(z);

Td = (tan(DeltaPhi) + sqrt((tan(DeltaPhi)^2 + 4/alpha)))/(2*w_gc);
Ti = alpha*Td;

Kp = DeltaK *cos(DeltaPhi);
Kd = Kp*Td;
Ki = Kp/Ti;


Tw = ts_star / 5;
Kw = 4/Tw;


