#include <Servo.h>

int speedVal = 900;
int potValLeft = 0;
int potValRight = 0;
int potPinLeft = 2;
int potPinRight = 1;
int count = 0;
int leftSpeed = 1000;
Servo myServoLeft;
Servo myServoRight;

void setup() {
  myServoLeft.attach(5);
  myServoRight.attach(6);
  Serial.begin(9600);
  Serial.print("STARTING!\n");
  myServoLeft.writeMicroseconds(1300);
  myServoRight.writeMicroseconds(1300);
  delay(1000);
  myServoLeft.writeMicroseconds(900);
  myServoRight.writeMicroseconds(900);
}

void setMotorSpeed(int potValLeft, int potValRight){
  const double MAXSPEED = 1300, MINSPEED = 900;
  
  if (count == 100){
    leftSpeed = random(MINSPEED+200, MAXSPEED);
    count = 0;
  }
  Serial.print(leftSpeed);
  Serial.print ("      ");
  myServoLeft.writeMicroseconds(leftSpeed);
  int rightSpeed = MINSPEED + (potValRight*(MAXSPEED-MINSPEED)/1023);
  Serial.print(rightSpeed);
  Serial.print ("      ");
  Serial.println(count);
  
  myServoRight.writeMicroseconds(rightSpeed);
  count++;
  
  
}
void loop() {
   
  // put your main code here, to run repeatedly:
    potValLeft = analogRead(potPinLeft);
    //Serial.println(potValLeft);

    potValRight = analogRead(potPinRight);
   // Serial.println(potValRight);

    setMotorSpeed (potValLeft, potValRight);
}
