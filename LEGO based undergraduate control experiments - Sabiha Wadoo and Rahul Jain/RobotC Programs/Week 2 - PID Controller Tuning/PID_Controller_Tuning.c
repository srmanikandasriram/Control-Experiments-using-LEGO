//=================================================================
// Author  : S.R.Manikandasriram
// Guide   : Bharath Bhikkaji
// Company : Control Engineering Lab, IIT Madras
// Program : Code written in RobotC for use in LEGO Mindstorms NXT 2.0 kit.
// This program is used to employ a custom PID controller for the
// interactive Servo motor. Data is stored using the Datalog feature
// available in NXT.
//
// Objective of this laboratory experiment is to fulfill the system design
// criteria given by maximum percentage overshoot and maximum settling time
// constraints for output.

// Declare useful constants
#define RUN_TIME 10000                            // in milliseconds
#define RECORD_SIZE 4
#define ENCODER_SETPOINT 500                      // Setpoint in degrees

task main()
{
  nMotorEncoder[motorB] = 0;                      // Reset the Motor Encoder of Motor B
  /* Note: nMotorEncoder has a range of -32768 to 32767. So it will "wrap" after about ~90
  revolutions. Hence, nMotorEncoder must be reset often enough to avoid any unexpected
  results */

  nMotorPIDSpeedCtrl[motorB] = mtrNoReg;          // disable PID speed control
  nSyncedMotors = synchNone;                      // ensure no syncronization between motors (i.e.) motorB is independent

  float Kp = 0.454*10.5, Ki = 2.2*0.2, Kd = 0.159*0.2;                  // PID variables. For Lego DC Motor: Ku = 11, Tu = 0.2
  /* Note: PID Tuning methods
  1. Ziegler-Nichols (Z-N) method:
      a. Set Ki and Kd to zero.
      b. Slowly increase Kp to a value Ku at which sustained oscillations - constant amplitude and periodic - are observed.
      c. Note period of oscillation
      d. Refer table below for initial values
      +----------------+----------+----------+----------+
      | Z-N Model      | Kp       | Ki       | Kd       |
      +----------------+----------+----------+----------+
      | P controller   | 0.5*Ku   | 0        | 0        |
      +----------------+----------+----------+----------+
      | PI controller  | 0.455*Ku | 0.833*Tu | 0        |
      +----------------+----------+----------+----------+
      | PID controller | 0.588*Ku | 0.5*Tu   | 0.125*Tu |
      +----------------+----------+----------+----------+
  2. Tyreus-Luyben (T-L) method:
      Since Z-N method usually results in aggressive tuning, alternatively T-L method can be adopted (Refer table below).
      +----------------+----------+--------+----------+
      | T-L Model      | Kp       | Ki     | Kd       |
      +----------------+----------+--------+----------+
      | PI controller  | 0.312*Ku | 2.2*Tu | 0        |
      +----------------+----------+--------+----------+
      | PID controller | 0.454*Ku | 2.2*Tu | 0.159*Tu |
      +----------------+----------+--------+----------+
  */
  float new_err = 0, old_err = 0, sum_err = 0;    // Error variables
  int dt = 20;                                    // in ms
  int motorPIDpower, motorPIDdegrees;

  motor[motorB] = 50;                             // Motor B given a power level of 50/100
  time1[T1] = 0;                                  // arrays to hold the current value of the time in 1ms duration

  nDatalogSize = RECORD_SIZE*RUN_TIME/dt;         // Allocate memory for datalog

  while (time1[T1] < RUN_TIME) {                  // Run for RUN_TIME sec
    motorPIDdegrees = nMotorEncoder[motorB];      // degrees rotated by motor
    new_err = ENCODER_SETPOINT-motorPIDdegrees;   // Calculate current error
    sum_err += new_err*dt/1000;                        // Integral of error ( calculated as a discrete sum of errors)

    // Calculate power to be applied to the motor
    motorPIDpower = Kp*new_err + Ki*sum_err + Kd*(new_err-old_err)*1000/dt;
    old_err = new_err;

    // Ensure power level is between -100 and 100
    if(motorPIDpower >= 100)
      motorPIDpower = 100;
    else if(motorPIDpower <= -100)
      motorPIDpower = -100;

    motor[motorB] = motorPIDpower;                // Apply the calculated power to the motors
    AddToDatalog(1,motorPIDdegrees);              // store value
    wait1Msec(dt);                                // log data every dt ms
  }
  motor[motorB] = 0;                              // Stop the motors
  SaveNxtDatalog();                               // save log file from RAM to Flash memory
}
