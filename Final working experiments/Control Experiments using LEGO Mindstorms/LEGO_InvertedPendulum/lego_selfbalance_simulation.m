% Simulation and Virtual Reality Parameters

% Copyright 2011 The MathWorks, Inc.

% Initial Values
PSI0 = 5 * pi / 180;				% initial value of body angle
X1IV = [							% x1 initial value
	0
	PSI0
	0
	0
	];
X2IV = [							% x2 initial value
	0
	0
	];

% Sample Rates
TS = 0.001;							% base sample rate [sec]

% Environments
GYRO0 = 600;						% initial value of gyro sensor
BATTERY = 8000;						% initial value of battery [mV]

% MAP
START_POS = [100, 100];				% initial position ([z, x]) [cm]
