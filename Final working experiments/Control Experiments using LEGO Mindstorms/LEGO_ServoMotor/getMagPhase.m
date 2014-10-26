function [freq, mag, phase ] = getMagPhase( data )
%getMagPhase Magnitude and Phase response of motor
%   Extracts the Magnitude and Phase response from the motor response
% data. The input is a matrix with three columns - Time, Voltage, Theta.
time = data(:,1);
voltage = data(:,2);
theta = data(:,3);
dt = time(2)-time(1);
[voltage_peaks, l_vp] = findpeaks(voltage);

if size(voltage_peaks,1)<2
    error('Data must contain atleast one complete peak-to-peak.')
end

T = mean((l_vp(2:end)-l_vp(1:end-1)).*dt);
freq = 1/T;
[theta_peaks,l_tp] = findpeaks(theta);
[theta_troughs,l_tt] = findpeaks(-theta);
theta_troughs = -theta_troughs;
if size(theta_peaks,1)>size(theta_troughs,1)
    mag = mean(theta_peaks(1:size(theta_troughs,1))-theta_troughs)/2;
else
    mag = mean(theta_peaks-theta_troughs(1:size(theta_peaks,1)))/2;
end
mag = mag/voltage_peaks(1);
if size(theta_peaks,1)>size(voltage_peaks,1)
    phase = mean((l_vp-l_tp(1:size(voltage_peaks,1))).*dt)*freq*2*pi;
else
    phase = mean((l_vp(1:size(theta_peaks,1))-l_tp).*dt)*freq*2*pi;
end
plotyy(time,voltage,time,theta);
phase = wrapToPi(phase);
phase = phase*180/pi;
end

