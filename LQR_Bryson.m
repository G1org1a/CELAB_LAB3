%% LQR BRYSON'S RULE 

theta_h = 0.3*50*pi/180;
theta_d = pi/36;
u = 10;

Q = [1/theta_h^2, 0, 0, 0; 0, 1/theta_d^2, 0, 0; 0, 0, 0, 0; 0, 0, 0, 0];
R = 1/u^2;

A = [0, 0, 1, 0; 0, 0, 0, 1; 0, mld.k/(gbox.N^2*Jeq), -1/Jeq*(Beq + mot.Kt*mot.Ke/Req), 0; 0, -mld.k/mld.Jb-mld.k/(gbox.N^2*Jeq), -mld.Bb/mld.Jb+1/Jeq*(Beq + mot.Kt*mot.Ke/Req), -mld.Bb/mld.Jb];
B = [0; 0; (mot.Kt*drv.dcgain)/(gbox.N *Jeq*Req); -(mot.Kt*drv.dcgain)/(gbox.N *Jeq*Req)];
C = [1, 0, 0, 0];
D = 0;

stsp = [A B; C D];
N = stsp\[0; 0; 0; 0; 1];
Nx = N(1:4);
Nu = N(end);

sysG = ss(A, B, C, D);


K = lqr(sysG, Q, R);
Ki = 0;
