#include <Wire.h>

#define UINT14_MAX        16383
#define UINT14_MAX_HALF        8191
#define MMA8451ADDRESS 0x1C
uint8_t MMA8451_address;

void I2C_Write_byte(uint8_t reg, uint8_t data){
  
  Wire.beginTransmission(MMA8451_address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t I2C_Read_byte(uint8_t reg){
  uint8_t data;
  Wire.beginTransmission(MMA8451_address);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MMA8451_address, 1);
  while( Wire.available()){
    data = Wire.read();
  }
  return data;
}

int get_acc(uint8_t axis){
  
  uint8_t data[2];
  
  Wire.beginTransmission(MMA8451_address);
  Wire.write(axis);
  Wire.endTransmission(false);
  Wire.requestFrom(MMA8451_address, 2);
  while( Wire.available()){
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  
  int i_acc = (data[0] << 6) | (data[1] >> 2);

  if (i_acc > UINT14_MAX_HALF){
    i_acc = i_acc - UINT14_MAX;
  }
  return i_acc;

}

bool MMA8451_begin(uint8_t i2caddr)
{
  int ID;
  Wire.begin();
  MMA8451_address = i2caddr;
  I2C_Write_byte(0x2A,0x01);
  
  //Who am I?
  ID = I2C_Read_byte(0x0D);
  Serial.write("ID = ");
  Serial.print(ID);
  Serial.write("\r\n");
  return true;   
}


void setup() {
    Serial.begin(9600);
    Serial.println("setup");

    /* i2c通信初期化(MMA8451と通信するものとする */
    if(!MMA8451_begin(MMA8451ADDRESS))  {
      Serial.println("Couldnt start");
       while (1);
    }
    Serial.println("Start");
    /* スケールレンジは Range±2g とする*/
    //MMA8451_setRange(MMA8451_RANGE_2_G);
    //get_acc(0x01);
}

void loop() {
  float acc[3];

  acc[0] = (get_acc(0x01)/4096.0);
  acc[1] = (get_acc(0x03)/4096.0);
  acc[2] = (get_acc(0x05)/4096.0);
  Serial.write("acc[0] = ");
  Serial.print(acc[0]);
  Serial.write(", acc[1] = ");
  Serial.print(acc[1]);
  Serial.write(", acc[2] = ");
  Serial.print(acc[2]);
  Serial.write("\r\n");
  delay(500);
  
}


