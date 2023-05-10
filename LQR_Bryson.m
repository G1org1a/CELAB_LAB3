%% LQR BRYSON'S RULE 
s = tf('s');
sysDprime = s*(s*Jeq+Beq)*(mld.Jb*s + mld.Bb)+ mld.k*(s*(Jeq+mld.Jb/gbox.N^2)+(Beq+mld.Bb/gbox.N^2));
sysP = (1/(gbox.N*s))*(drv.dcgain*mot.Kt)*(mld.Jb*s^2 + mld.Bb*s + mld.k)/(Req*sysDprime+mot.Kt*mot.Ke*(mld.Jb*s^2 + mld.Jb*s + mld.k));

%theta_


theta_h = 0.3*50*pi/180;
theta_d = pi/36;
u = 10;

Q = [1/theta_h^2, 0, 0, 0; 0, 1/theta_d^2, 0, 0; 0, 0, 0, 0; 0, 0, 0, 0];
R = 1/u^2;

K = lqr(sysG, Q, R);
