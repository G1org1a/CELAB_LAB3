%% controller specifics 
delta = (log(1/Mp))/sqrt((pi^2)+(log(1/Mp)^2));         % damping factor
omega_gc = 3/(ts_star*delta);                           % crossover freq.
Tl = 1/(10*omega_gc);                                   % cut-off freq.
alpha = 4;

%% Controller tuning

s = tf('s');
sysDprime = s*(s*Jeq+Beq)*(mld.Jb*s + mld.Bb)+ mld.k*(s*(Jeq+mld.Jb/gbox.N^2)+(Beq+mld.Bb/gbox.N^2));
sysP = (1/(gbox.N*s))*(drv.dcgain*mot.Kt)*(mld.Jb*s^2 + mld.Bb*s + mld.k)/(Req*sysDprime+mot.Kt*mot.Ke*(mld.Jb*s^2 + mld.Jb*s + mld.k));


[PID, info] = pidtune(sysP, 'PIDF', omega_gc);

Tw = ts_star / 5;
Kw = 1 / Tw;