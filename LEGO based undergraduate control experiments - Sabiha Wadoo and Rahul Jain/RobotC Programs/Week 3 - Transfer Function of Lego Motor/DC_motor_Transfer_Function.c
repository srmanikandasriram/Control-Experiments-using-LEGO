//=================================================================
// Author: S.R.Manikandasriram
// Company: Control Engineering Lab, IIT Madras
// Guide: Bharath Bhikkaji
// Program: Code written in RobotC for use in LEGO Mindstorms NXT 2.0 kit.
// This program is used to determine the transfer function of the LEGO
// DC motor which is present in the interactive Servo motor. Data is stored
// using the Datalog feature available in NXT.
//
// Objective of this laboratory experiment is to find the transfer function
// using experimental modeling approach

// Declare useful constants
#define RUN_TIME 10000                            // in milliseconds
#define RECORD_SIZE 4

task main()
{
//  nMaxRegulatedSpeedNxt = 500;                    // for consistent speed
  nMotorEncoder[motorB] = 0;                      // Reset the Motor Encoder of Motor B
  /* Note: nMotorEncoder has a range of -32768 to 32767. So it will "wrap" after about ~90
  revolutions. Hence, nMotorEncoder must be reset often enough to avoid any unexpected
  results */

  nMotorPIDSpeedCtrl[motorB] = mtrNoReg;          // disable PID speed control
  nSyncedMotors = synchNone;                       // ensure no syncronization between motors (i.e.) motorB is independent

  int motorPIDdegrees, dt = 20;

  motor[motorB] = 100;                            // Motor B given a power level of 50/100
  time1[T1] = 0;                                  // arrays to hold the current value of the time in 1ms duration

  nDatalogSize = RUN_TIME*RECORD_SIZE/dt;         // Allocate memory for datalog

  while (time1[T1] < RUN_TIME) {                  // Run for RUN_TIME sec
    motorPIDdegrees = nMotorEncoder[motorB];      // degrees rotated by motor
    AddToDatalog(1,motorPIDdegrees);              // store value
    wait1Msec(dt);                                // log data every dt ms
  }
  motor[motorB] = 0;                              // Stop the motors
  SaveNxtDatalog();                               // save log file from RAM to Flash memory
}
