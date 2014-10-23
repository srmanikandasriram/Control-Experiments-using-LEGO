% Controller Parameters 

% Copyright 2014 S.R.Manikandasriram

% Task Sample Rates
ts1 = 0.004;						% ts1 sample time [sec]

% Low Path Filter Coefficients
a_b = 0.8;							% average battery value
a_d = 0.8;							% suppress velocity noise
a_r = 0.996;						% smooth reference signal

% Velocity control
% H(s) = v(s)/V(s) = 212.4/(s^2+172.3*s+2826);
% v(s)/v_r(s) = Kp*212.4/(s^2+172.3*s+2826+Kp*212.4);
zeta = 1;
w_n = 172.3/(2*zeta);               % natural frequency of velocity control
k_v = (w_n^2-2826)/212.4;
k_gv = w_n^2/(212.4*k_v);

% Load position control
zeta = 1;
cm2phi = 2;
ANGLE_OFFSET = 93;                   % Angle sensor reading at pendnt position
g = 9.81                             % Acceleration due to gravity [m/sec^2]
l = 0.17                             % Pendulum length [m]
w_n1 = sqrt(g/l);
k_z = -2*w_n1;