/*
 Cosmic Kiddos Stepper Motor Control


 Five servos are controlled.
 The motors should turn to the angle that is specified in the serial input


 Created 12 Mar. 2019
 by Cody Candler

 */
///*

#include <Servo.h>

const int numberServos = 5; //change this depending on the number of stepper motors on this arduino


//initialize the servos
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servoArray[] = {servo0,servo1,servo2,servo3,servo4};


int servoAngle[] = {180,180,180,180,180};//input variable. Initialize all arms to being straightened out


void setup() {
  //choose the servo pins
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
    for(int i = 0; i < numberServos; i++){
      servoAngle[i] =  message.substring(4*i, 4*i+3).toInt();
      Serial.println(servoAngle[i]);
    }
  }
  for(int i = 0; i < numberServos; i++){
    servoArray[i].write(servoAngle[i]); //set the servo to the desired angle
    //servoAngle[i]++;
    Serial.println(servoAngle[i]);
if (servoAngle [i] > 180){
      servoAngle[i] = 180; //our servos do not have mechanical stops. This prevents damage
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
