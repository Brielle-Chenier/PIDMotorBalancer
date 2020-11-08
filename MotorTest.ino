#include <Servo.h>

int speedVal = 900;
int potValLeft = 0;
int potValRight = 0;
int potPinLeft = 2;
int potPinRight = 1;

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
  potValLeft = getPotVal (potPinLeft);
  potValRight = getPotVal (potPinRight);

  //Set the appropriate speeds with equal intervals based on pot vals
  int leftSpeed = MINSPEED + (potValLeft*(MAXSPEED-MINSPEED)/1023);
  Serial.print(leftSpeed);
  Serial.print ("      ");
  int rightSpeed = MINSPEED + (potValRight*(MAXSPEED-MINSPEED)/1023);
  Serial.println(rightSpeed);
  
  myServoLeft.writeMicroseconds(leftSpeed);
  myServoRight.writeMicroseconds(rightSpeed);
  
  
}
void loop() {
   
  // put your main code here, to run repeatedly:
    setMotorSpeed ();
}
