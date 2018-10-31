#include "Arduino.h"
#include <inttypes.h>
#include <Wire.h>
#include <VL53L0X.h>
#include "MILLEIO.h"
#include "MILLE.h"

#define ToFB_ADDRESS 0x80000071  //device board address
 
VL53L0X sensor1;
VL53L0X sensor2;

uint8_t myWire1[4];  //The wires for device.配線の情報を格納する変数
uint8_t myWire2[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoToFB1;  //define structure for device information.
sDevInfo infoToFB2;  //define structure for device information.

mille myMille; //mille-feuille controller instance.
MILLEIO myToFB1(ToFB_ADDRESS,myWire1,&infoToFB1,0); //MILLEIO class instance, connector number on baseboard is zero.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します
MILLEIO myToFB2(ToFB_ADDRESS,myWire2,&infoToFB2,1);
  
void setup() {
  // put your setup code here, to run once:
    
  Serial.begin(9600);
  Wire.begin();
  
  if(myMille.detectModule(&infoToFB1)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire1[0],OUTPUT);

  if(myMille.detectModule(&infoToFB2)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire2[0],OUTPUT);

}

void loop() {
  
  Serial.println("start");
  
  myMille.holdConnect(&infoToFB1); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  digitalWrite(myWire1[0], LOW);
  delay(100);
  myMille.holdDisconnect(&infoToFB1);  //別のデバイスに接続する前に接続断をします。
  
  myMille.holdConnect(&infoToFB2); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  digitalWrite(myWire2[0], LOW);
  delay(100);
  myMille.holdDisconnect(&infoToFB2);
  
  delay(1000);
  
  myMille.holdConnect(&infoToFB1); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  digitalWrite(myWire1[0], HIGH);
  delay(150);
  sensor1.init(true);
  delay(100);
  sensor1.setAddress((uint8_t)24);
  sensor1.setTimeout(500);
  myMille.holdDisconnect(&infoToFB1);  //別のデバイスに接続する前に接続断をします。
  
  myMille.holdConnect(&infoToFB2); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  digitalWrite(myWire2[0], HIGH);
  delay(150);
  sensor2.init(true);
  delay(100);
  sensor2.setAddress((uint8_t)25);
  sensor2.setTimeout(500);
  myMille.holdDisconnect(&infoToFB2);

  delay(10);
  sensor1.startContinuous();
  sensor2.startContinuous();

while(1){
  Serial.print("1:");
  Serial.print(sensor1.readRangeContinuousMillimeters());
  Serial.print(" 2:");
  Serial.print(sensor2.readRangeContinuousMillimeters());
  Serial.print("\r\n");
  delay(10);
    
}





  
}
