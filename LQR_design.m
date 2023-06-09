%% LQR DESIGN

delta = (log(1/Mp))/sqrt((pi^2)+(log(1/Mp)^2));         % damping factor
omega_n = 3/(ts_star*delta);                           % crossover freq.
phi = atan(sqrt(1-delta^2)/delta)-pi;
sigma = -3/ts_star;

A = [0, 0, 1, 0; 0, 0, 0, 1; 0, mld.k/(gbox.N^2*Jeq), -1/Jeq*(Beq + mot.Kt*mot.Ke/Req), 0; 0, -mld.k/mld.Jb-mld.k/(gbox.N^2*Jeq), -mld.Bb/mld.Jb+1/Jeq*(Beq + mot.Kt*mot.Ke/Req), -mld.Bb/mld.Jb];
B = [0; 0; (mot.Kt*drv.dcgain)/(gbox.N *Jeq*Req); -(mot.Kt*drv.dcgain)/(gbox.N *Jeq*Req)];
C = [1, 0, 0, 0];
D = 0;

stsp = [A B; C D];
N = stsp\[0; 0; 0; 0; 1];
Nx = N(1:4);
Nu = N(end);

sysG = ss(A, B, C, 0);
sysGp = ss(-A, -B, C, 0);

rlocus(sysG*sysGp);

figure(1)
hold on

plot([sigma, sigma],[-600, 600], 'k--');
plot([-100, sigma], [-100*phi, sigma*phi], 'k--');
plot([-100, sigma], [100*phi, -sigma*phi], 'k--');

axis([-60 60 -60 60]);

sys_test = 1+4*sysG*sysGp; %prende 2 su 4 zeri significativi
[Z, P, gain] = zpkdata(sys_test);

Z = cell2mat(Z);
plot(Z,"x")


r = 1/5000;
% K = lqr(sysG, transpose(C)*C, r);
K = lqry(sysG, 1, r);
Ki = 0;

