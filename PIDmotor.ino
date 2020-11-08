#include <Servo.h>

int speedVal = 900;
int potValProp = 0, potValIntegral = 0, potValDeriv = 0;
int potPinProp = 2, potPinIntegral = 1, potPinDeriv = 0;

Servo myServoLeft;
Servo myServoRight;

void setup() {
  //Set up which pins to connect servos and pots
  myServoLeft.attach(5);
  myServoRight.attach(6);
  
  Serial.begin(9600);
  Serial.print("STARTING!\n");

  //Use this startup so the ECE's work (need to give them a value of 900 at start)
  myServoLeft.writeMicroseconds(1300);
  myServoRight.writeMicroseconds(1300);
  delay(1000);
  myServoLeft.writeMicroseconds(900);
  myServoRight.writeMicroseconds(900);
}

int getPotVal (int potPin)
{
  return analogRead(potPin);
}

void setMotorSpeed(){
  const double MAXSPEED = 1300, MINSPEED = 900;
  potValProp = getPotVal (potPinProp);
  potValIntegral = getPotVal (potPinIntegral);
  potValDeriv = getPotVal (potPinDeriv);

  //Set the speed based on the calculations - TO DO
  int leftMotorSpeed = 0;
  int rightMotorSpeed = 0;
  Serial.print(leftMotorSpeed);
  Serial.print ("      ");
  Serial.println(rightMotorSpeed);
  
  myServoLeft.writeMicroseconds(leftMotorSpeed);
  myServoRight.writeMicroseconds(rightMotorSpeed);  
}

void loop() {
   
  // put your main code here, to run repeatedly:
    setMotorSpeed ();
}
