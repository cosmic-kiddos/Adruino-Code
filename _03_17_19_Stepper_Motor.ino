/*
  Cosmic Kiddos Stepper Motor Control


  Five stepper motors are controlled.
  The motors should turn to the angle that is specified in the serial input


  Created 12 Mar. 2019
  by Cody Candler

*/
///*
#include <Stepper.h>
#include <Servo.h>

const int numberSteppers = 5; //change this depending on the number of stepper motors on this arduino



const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution. The number can be used to calibrate for drift
// for your motor

// initialize the steppers on the specified pins:
//Note. Some stepper controllers swap the middle two pins as is the case in this setup.
//Ex. Some kits would use 2,3,4,5 for stepper0
Stepper stepper0(stepsPerRevolution, 2, 4, 3, 5);
Stepper stepper1(stepsPerRevolution, 6, 8, 7, 9);
Stepper stepper2(stepsPerRevolution, 10, 12, 11, 13);
Stepper stepper3(stepsPerRevolution, 14, 16, 15, 17);
Stepper stepper4(stepsPerRevolution, 18, 20, 19, 21);

//build an array of all the stepper motors
Stepper stepperArray[] = {stepper0, stepper1, stepper2, stepper3, stepper4};

//initialize the servos
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
//build array of servos
Servo servoArray[] = {servo0, servo1, servo2, servo3, servo4};

int currentSteps[] = {0, 0, 0, 0, 0}; //track the current steps for each stepper
int desiredSteps[] = {0, 0, 0, 0, 0}; //the steps required to put the stepper to the desired angle
float desiredAngle[] = {36000, 36000, 0, 0, 0}; //input variable. Initialize steppers to pointing straight down
float servoAngle[] = {180, 180, 180, 180, 180}; //input variable. Initialize all arms to being straightened out



//char delimiters[] = "-"; //setup for turning strings from processing into an array of ints
//char* valPosition;       //setup for turning strings from processing into an array of ints


void setup() {
  // set the speed to 4 rpm:
  int speed = 4;

  stepper0.setSpeed(speed);
  stepper1.setSpeed(speed);
  stepper2.setSpeed(speed);
  stepper3.setSpeed(speed);
  stepper4.setSpeed(speed);

  //select pins for servos
  servo0.attach(21);
  servo1.attach(22);
  servo2.attach(23);
  servo3.attach(24);
  servo4.attach(25);


  // initialize the serial port:
  Serial.begin(9600);
}

String message = "";
void loop() {
  // If there is something in the buffer
  if (Serial.available() > 0) {
    message = Serial.readStringUntil('-');
    // 090, 000, 000, 000, 000-
    // val 1 0 - 3
    // val 2 4 - 7
    // val 3 8 - 11
    // val 4 12 - 15
    // val 5 16 - 19
    // message.substring(start, end).toInt() <----- Gets angle
    for (int i = 0; i < numberSteppers; i++) {
      desiredAngle[i] =  message.substring(4 * i, 4 * i + 3).toInt();
      Serial.println(desiredAngle[i]);
    }
  }

  for (int i = 0; i <= 4; i++) {
    desiredSteps[i] = desiredAngle[i] * stepsPerRevolution / 360; //calculate steps from angle
  }
  for (int i = 0; i <= 4; i++) {
    if (currentSteps[i] < desiredSteps[i]) {
      stepperArray[i].step(1); //Step once forward
      currentSteps[i]++; //Remember/track this step
    }
    else if (currentSteps[i] > desiredSteps[i]) {
      stepperArray[i].step(-1); //Step once forward
      currentSteps[i]--; //Remember/track this step
    }

  }

  delay(2);
}





























//*/
/*
  #include <AccelStepper.h>
  #define HALFSTEP 8

  // Motor pin definitions
  #define motorPin1  8     // IN1 on the ULN2003 driver 1
  #define motorPin2  9     // IN2 on the ULN2003 driver 1
  #define motorPin3  10     // IN3 on the ULN2003 driver 1
  #define motorPin4  11     // IN4 on the ULN2003 driver 1
  #define motorPin5  12     // IN1 on the ULN2003 driver 1
  #define motorPin6  13    // IN2 on the ULN2003 driver 1
  #define motorPin7  14     // IN3 on the ULN2003 driver 1
  #define motorPin8  15     // IN4 on the ULN2003 driver 1

  // Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
  AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
  AccelStepper stepper2(HALFSTEP, motorPin5, motorPin6, motorPin7, motorPin8);
  AccelStepper stepperArray[] ={stepper1,stepper2};
  void setup() {
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  stepper1.moveTo(20000);

  }//--(end setup )---

  void loop() {

  //Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepperArray[0].moveTo(-stepper1.currentPosition());
  }
  stepperArray[0].run();
  }
*/
