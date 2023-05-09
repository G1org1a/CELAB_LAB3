%% controller specifics 
delta = (log(1/Mp))/sqrt((pi^2)+(log(1/Mp)^2));         % damping factor
omega_gc = 3/(ts_star*delta);                           % crossover freq.
Tl = 1/(10*omega_gc);                                   % cut-off freq.
alpha = 4;

%% Controller tuning






%%

[PID, info] = pidtune(sysP, 'PIDF', omega_gc);

Tw = ts_star / 5;
Kw = 1 / Tw;


