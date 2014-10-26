//=================================================================
// Author  : S.R.Manikandasriram
// Guide   : Bharath Bhikkaji
// Company : Control Engineering Lab, IIT Madras
// Program : Code written in RobotC for use in LEGO Mindstorms NXT 2.0 kit.
// This program is used to observe the functioning of the in-built PID
// controller using just one interactive Servo motor and NXT intelligent
// brick. Data is stored using the Datalog feature available in NXT.

// Declare useful constants
#define RUN_TIME 10000                            // in milliseconds
#define DELTA_T 50                                // in milliseconds
#define SPEED_SETPOINT 50                         // on a scale of 100
#define RECORDS RUN_TIME/DELTA_T                  // no. of records to be stored in datalog
#define RECORD_SIZE 8

task main()
{
  nMaxRegulatedSpeedNxt = 500;                    // for consistent speed
  nMotorEncoder[motorB] = 0;                      // Reset the Motor Encoder of Motor B
  /* Note: nMotorEncoder has a range of -32768 to 32767. So it will "wrap" after about ~90
  revolutions. Hence, nMotorEncoder must be reset often enough to avoid any unexpected
  results */
  nMotorPIDSpeedCtrl[motorB] = mtrSpeedReg;       // enable PID speed control
  nSyncedMotors = synchNone;                      // ensure no syncronization between motors (i.e.) motorB is independent

  int motorPIDpower, motorPIDdegrees;
  motor[motorB] = SPEED_SETPOINT;                 // Motor B given a power level of 50/100
  time1[T1] = 0;                                  // arrays to hold the current value of the time in 1ms duration

  nDatalogSize = RECORDS*RECORD_SIZE;             // Allocate memory for datalog

  while (time1[T1] < RUN_TIME) {                  // Run for RUN_TIME sec
    motorPIDdegrees = nMotorEncoder[motorB];      // degrees rotated by motor
    motorPIDpower   = motorPWMLevel[motorB];      // get power given to the motor
    AddToDatalog(1,motorPIDdegrees);              // store value to Datalog
    AddToDatalog(2,motorPIDpower);                // store value to Datalog
    wait1Msec(DELTA_T);                           // log data every DELTA_T ms
  }
  motor[motorB] = 0;                              // Stop the motors
  SaveNxtDatalog();                               // save log file from RAM to Flash memory
}
