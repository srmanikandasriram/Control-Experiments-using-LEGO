#!/usr/bin/env python

'''========================================================================
 Author: S.R.Manikandasriram
 Company: Control Engineering Lab, IIT Madras
 Guide: Bharath Bhikkaji
 Program: Code written in Python to parse the exported CSV file from RobotC
 and plot the performance plot using GNU Plot.
'''

import sys
import os
import csv
import matplotlib.pyplot as plt

if len(sys.argv) < 4:
	sys.exit('Usage: %s <csv-file> <no-of-rows> <sample_time>' % sys.argv[0])

if not os.path.exists(sys.argv[1]):
	sys.exit('ERROR: CSV file %s not found!'% sys.argv[1])

data = []

with open(sys.argv[1], 'rb') as csvfile:
	reader = csv.reader(csvfile, delimiter=',')
	for row in reader:
		data.append(map(int,row))
data = data[1:]
data.sort()

data_length = len(data)
no_of_rows = int(sys.argv[2])
samp_time = float(sys.argv[3])

while(data_length>no_of_rows):
	count = 0
	for d in data[data_length-no_of_rows:data_length]:
		data[count].append(d[1])
		data[count].append((data[count][1]-data[count-1][1])/samp_time)
		data[count][0] = samp_time*(count+1)
		count += 1
	data_length -= no_of_rows
data[0][3] = 0.0
data = data[:no_of_rows]
time_axis = [row[0] for row in data]
pwm_axis = [row[2] for row in data]
speed_axis = [row[3] for row in data]
fig, ax1 = plt.subplots()

ax2 = ax1.twinx()
ax1.plot(time_axis, speed_axis, 'g-')
ax2.plot(time_axis, pwm_axis, 'b-')

ax1.set_xlabel("Time (in seconds)")
ax1.set_ylabel("Speed (in degrees per second)", color='g')
ax2.set_ylabel("PWM (in %)", color='b')

plt.show()