#include <Servo.h>

int speedVal = 900;
int potValLeft = 0, potValRight = 0;
int potPinLeft = 2, potPinRight = 1;
int count = 0;
int leftSpeed = 1000;
double propConst = 0.010, integConst = 0.010, derivConst = 10;
Servo myServoLeft;
Servo myServoRight;
const int LEVELPOS = 0;
int maxPos;
double totalError = 0;

#include <Wire.h>
#define IMU_ADDR 0x68
#define IMU_INIT 0x6B

#define GYRO_X_H 0x3B
#define GYRO_X_L 0x44
#define GYRO_Y_H 0x45
#define GYRO_Y_L 0x46
#define GYRO_Z_H 0x47
#define GYRO_Z_L 0x48

int imuXAvg = 0, imuYAvg = 0, imuZAvg = 0;
int sampleSize = 60;


void initIMU()
{
  Wire.begin();
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(IMU_INIT);
  Wire.endTransmission(true);
}

struct imuResult
{
  int16_t gyroX = 0, gyroY = 0, gyroZ = 0;
};

void setMotorSpeedRandom(int potValLeft, int potValRight){
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

void setMotorSpeed(int rightSpeed){
  const double MAXSPEED = 1300, MINSPEED = 900;
  int rightMotorSpeed = rightSpeed * (MAXSPEED - MINSPEED) + MINSPEED; 
  myServoRight.writeMicroseconds(rightMotorSpeed);
  //Serial.print(leftSpeed);
  Serial.print ("      ");
  Serial.print(rightSpeed);
  Serial.println ("      ");
}

int getPIDSpeed ()
{
  Serial.print (imuXAvg);
  Serial.print ("      ");
  Serial.print (imuYAvg);
  Serial.print ("      ");
  Serial.print (imuZAvg);
  int currentError = LEVELPOS - imuYAvg;
  totalError += currentError;
  int propPart = currentError*propConst;
  int integPart = totalError*propConst;
  return propPart + integPart;  
}

struct imuResult readFromIMU()
{
  struct imuResult returnStruct;
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(GYRO_X_H);
  Wire.endTransmission(false);
  Wire.requestFrom(IMU_ADDR, 6, true); //We want to get the next 6 bytes. 
  returnStruct.gyroX = Wire.read() << 8 | Wire.read(); //We get the high and low registers and put them in an int with 16 bits
  returnStruct.gyroY = Wire.read() << 8 | Wire.read();
  returnStruct.gyroZ = Wire.read() << 8 | Wire.read();
  
  return returnStruct;
  
} 

struct imuResult imuData;

void getIMUAverage()
{
    imuXAvg = 0;
    imuYAvg = 0;
    imuZAvg = 0;
    for (int i = 0; i < sampleSize; i++)
    {
      imuData = readFromIMU();
      imuXAvg += imuData.gyroX;
      imuYAvg += imuData.gyroY;
      imuZAvg += imuData.gyroZ;
    }

    imuXAvg = imuXAvg/sampleSize;
    imuYAvg = imuYAvg/sampleSize; 
    imuZAvg = imuZAvg/sampleSize;
}


void setup() {
  myServoLeft.attach(6);
  myServoRight.attach(5);
  Serial.begin(9600);
  Serial.print("STARTING!\n");
  initIMU();
  myServoLeft.writeMicroseconds(1300);
  myServoRight.writeMicroseconds(1300);
  delay(1000);
  myServoLeft.writeMicroseconds(900);
  myServoRight.writeMicroseconds(900);
  getIMUAverage();
  maxPos = imuYAvg;
}

void loop() {
   
  // put your main code here, to run repeatedly:
    //potValLeft = analogRead(potPinLeft);
    //Serial.println(potValLeft);

    getIMUAverage ();
    
    setMotorSpeed (getPIDSpeed());
   // get imu Position, pass to pid
}
