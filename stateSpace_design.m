%% NOMINAL 

delta = (log(1/Mp))/sqrt((pi^2)+(log(1/Mp)^2));         % damping factor
omega_n = 3/(ts_star*delta);                           % crossover freq.
phi = atan(sqrt(1-delta^2)/delta);

A = [0, 0, 1, 0; 0, 0, 0, 1; 0, mld.k/(gbox.N^2*Jeq), -1/Jeq*(Beq + mot.Kt*mot.Ke/Req), 0; 0, -mld.k/mld.Jb-mld.k/(gbox.N^2*Jeq), -mld.Bb/mld.Jb+1/Jeq*(Beq + mot.Kt*mot.Ke/Req), -mld.Bb/mld.Jb];
B = [0; 0; (mot.Kt*drv.dcgain)/(gbox.N *Jeq*Req); -(mot.Kt*drv.dcgain)/(gbox.N *Jeq*Req)];
C = [1, 0, 0, 0];
D = 0;

eig = [omega_n*exp(i*(-pi+phi)), omega_n*exp(i*(-pi-phi)) , omega_n*exp(i*(-pi+phi/2)), omega_n*exp(i*(-pi-phi/2))];

stsp = [A B; C D];
N = stsp\[0; 0; 0; 0; 1];
Nx = N(1:4);
Nu = N(end);

K = acker(A,B,eig);
Ki = 0;


%% INTEGRAL

delta = (log(1/Mp))/sqrt((pi^2)+(log(1/Mp)^2));         % damping factor
omega_n = 3/(ts_star*delta);                           % crossover freq.
phi = atan(sqrt(1-delta)/delta);

A = [0, 0, 1, 0; 0, 0, 0, 1; 0, mld.k/(gbox.N^2*Jeq), -1/Jeq*(Beq + mot.Kt*mot.Ke/Req), 0; 0, -mld.k/mld.Jb-mld.k/(gbox.N^2*Jeq), -mld.Bb/mld.Jb+1/Jeq*(Beq + mot.Kt*mot.Ke/Req), -mld.Bb/mld.Jb];
B = [0; 0; (mot.Kt*drv.dcgain)/(gbox.N *Jeq*Req); -(mot.Kt*drv.dcgain)/(gbox.N *Jeq*Req)];
C = [1, 0, 0, 0];
D = 0;
Ae = [0 C; zeros(4,1) A];
Be = [0; B];
Ce = [0 C];

eig_robust = [omega_n*exp(i*(-pi+phi)), omega_n*exp(i*(-pi-phi)) , omega_n*exp(i*(-pi+phi/2)), omega_n*exp(i*(-pi-phi/2)), -omega_n];

stsp = [A B; C D];
N = stsp\[0; 0; 0; 0; 1];
Nx = N(1:4);
Nu = N(end);

K = acker(Ae,Be,eig_robust);
Ki = K(1);
K = K(2:end);