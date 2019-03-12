/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */
///*
#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper stepper0(stepsPerRevolution, 2, 4, 3, 5);
Stepper stepper1(stepsPerRevolution, 6, 8, 7, 9);
//Stepper stepper2(stepsPerRevolution, 9, 11, 10, 12);

Stepper stepper2(stepsPerRevolution, 34, 35, 36, 37);

Stepper stepper3(stepsPerRevolution, 13, 15, 14, 16);
Stepper stepper4(stepsPerRevolution, 17, 19, 18, 20);
Stepper stepperArray[] = {stepper0,stepper1,stepper2,stepper3,stepper4};


Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servoArray[] = {servo0,servo1,servo2,servo3,servo4};

int currentSteps[] = {0,0,0,0,0}; //track the current steps for each stepper
int desiredSteps[] = {0,0,0,0,0}; //the steps required to put the stepper to the desired angle
float desiredAngle[] = {180,180,0,0,0}; //input variable. Initialize steppers to pointing straight down
float servoAngle[] = {180,180,180,180,180};//input variable. Initialize all arms to being straightened out

void setup() {
  // set the speed at 60 rpm:
  int speed = 4;
  
  stepper0.setSpeed(speed);
  stepper1.setSpeed(speed);
  stepper2.setSpeed(speed);
  stepper3.setSpeed(speed);
  stepper4.setSpeed(speed);

  servo0.attach(21);
  servo1.attach(22);
  servo2.attach(23);
  servo3.attach(24);
  servo4.attach(25);

  
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {    // is a character available?
    desiredAngle[0]=Serial.read();
  }
  
  for (int i = 0; i <= 4; i++) {
    desiredSteps[i] = desiredAngle[i]*stepsPerRevolution/360; //calculate steps from angle
  }
  for (int i = 0; i <= 4; i++) {
    if (currentSteps[i] < desiredSteps[i]){ 
      stepperArray[i].step(1); //Step once forward
      currentSteps[i]++; //Remember/track this step
    }
    else if (currentSteps[i] > desiredSteps[i]){
      stepperArray[i].step(-1); //Step once forward
      currentSteps[i]--; //Remember/track this step
    }
   /*
    servoArray[i].write(servoAngle[i]); //set the servo to the desired angle
    servoAngle[i]++;
    Serial.println(servoAngle[i]);
    if (servoAngle [i] > 170){
      servoAngle[i] = 0;
    }
*/
    
    
    if (desiredSteps[i] == currentSteps[i]){
      desiredAngle[i]=desiredAngle[i]+20;
      Serial.println("+20");
      if (desiredAngle[i] >360){
        desiredAngle[i] = 0;
        Serial.println("angle reset");
      }
      

    
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
