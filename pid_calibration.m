delta = log(1/Mp)/sqrt(pi^2 + (log(1/Mp)^2));
w_gc = 3/(delta*ts_star);
%phi_m = atan(2*delta/sqrt(sqrt(1+4*delta^4) - 2*delta^2));
phi_m = 1.04 - 0.8*Mp;

alpha = 10;


PID.Tl = 1/(10*w_gc);

z = freqresp(sysP,w_gc); % value of sysP at w_gc

DeltaK = 1/abs(z);
DeltaPhi = phi_m - pi - angle(z);

PID.Td = (tan(DeltaPhi) + sqrt((tan(DeltaPhi)^2 + 4/alpha))) / (2*w_gc);
PID.Ti = alpha * PID.Td;

PID.Kp = DeltaK * cos(DeltaPhi);
PID.Kd = PID.Kp * PID.Td;
PID.Ki = PID.Kp / PID.Ti;


Tw = ts_star / 5;
Kw = 1 / Tw;


