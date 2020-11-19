#include <Wire.h>
#define IMU_ADDR 0x68
#define IMU_INIT 0x6B

#define GYRO_X_H 0x3B
#define GYRO_X_L 0x44
#define GYRO_Y_H 0x45
#define GYRO_Y_L 0x46
#define GYRO_Z_H 0x47
#define GYRO_Z_L 0x48

double imuXAvg = 0, imuYAvg = 0, imuZAvg = 0;
int sampleSize = 50;


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

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.print("STARTING\n!");
  initIMU();
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

void loop() {
  // put your main code here, to run repeatedly:
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
  
  Serial.print (imuXAvg);
  Serial.print ("     ");
  Serial.print (imuYAvg);
  Serial.print ("     ");
  Serial.println (imuZAvg);
  
  imuXAvg = 0;
  imuYAvg = 0;
  imuZAvg = 0;
}
