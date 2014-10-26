% Controller Parameters 

% Copyright 2011 The MathWorks, Inc.

% Servo Gain Calculation using Optimal Regulator
A_BAR = [A1, zeros(4, 1); C1(1, :), 0];
B_BAR = [B1; 0, 0];
% QQ = [
% 	1, 0,   0, 0, 0
% 	0, 6e5, 0, 0, 0
% 	0, 0,   1, 0, 0
% 	0, 0,   0, 1, 0
% 	0, 0,   0, 0, 4e2
% 	];
% RR = 1e3 * eye(2);

% KK = lqr(A_BAR, B_BAR, QQ, RR);
% pre-calculated optimal gain matrix
KK = [-0.8351  -34.1896   -1.2935   -2.8141   -0.4472
      -0.8351  -34.1896   -1.2935   -2.8141   -0.4472];

  
k_f = KK(1, 1:4);					% feedback gain
k_i = KK(1, 5);						% integral gain
% suppress velocity gain because it fluctuates robot
k_f(3) = k_f(3) * 0.85;

% Task Sample Rates
ts1 = 0.004;						% ts1 sample time [sec]

% Start Time of balancing and autonomous drive
time_start = 4000;                  % start time of balancing [msec] (= gyro calibration time)

% Parameters of Coulombic & Viscous Friction
pwm_gain = 1;						% pwm gain
pwm_offset = 0;						% pwm offset 

% Low Path Filter Coefficients
a_b = 0.8;							% average battery value
a_d = 0.8;							% suppress velocity noise
a_r = 0.996;						% smooth reference signal
a_gc = 0.8;							% calibrate gyro offset
a_gd = 0.999;						% compensate gyro drift

% User Setting Values
k_thetadot = 0.3 / R;				% speed gain (0.3 [m/sec])
k_phidot = 25;						% rotation speed gain
k_sync = 0.35;						% wheel synchronization gain

% LocalWords:  QQ KK QQ KK msec Coulombic pwm
