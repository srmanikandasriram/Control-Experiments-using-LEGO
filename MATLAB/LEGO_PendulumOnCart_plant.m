% Parameters and State-Space Matrix Calculation

% Copyright 2014 S.R.Manikandasriram

% Physical Constant
g = 9.81;						% gravity acceleration [m/sec^2]

% PendulumOnCart Parameters
m = 0.015;						% wheel weight [kg]
R = 0.025;						% wheel radius [m]
Jw = m * R^2 / 2;				% wheel inertia moment [kgm^2]

m1 = 0.01;                      % castor wheel weight [kg]
r = 0.015;                      % castor wheel radius [m]
Jcw = m1*r^2/2;                 % castor wheel inertia moment [kgm^2]

M = 0.6;						% body weight [kg]
W = 0.11;						% body width [m]
D = 0.09;						% body depth [m]
L = 0.22;                       % body length [m]

H = 0.19;						% suspension height [m]
l = 0.17;						% pendulum length [m]
Mp = 0.06;                      % bob weight [kg]
Jp = Mp*l^2;                    % bob inertia moment [kgm^2]

fm = 0.0022;					% friction coefficient between body & DC motor
fw = 0;							% friction coefficient between wheel & floor

% DC Motor Parameters			
Jm = 1e-5;						% DC motor inertia moment [kgm^2]
Rm = 6.69;						% DC motor resistance [ƒ¶]
Kb = 0.468;						% DC motor back EMF constant [Vsec/rad]
Kt = 0.317;						% DC motor torque constant [Nm/A]
n = 1;							% gear ratio

% PendulumOnCart State-Space Matrix Calculation
