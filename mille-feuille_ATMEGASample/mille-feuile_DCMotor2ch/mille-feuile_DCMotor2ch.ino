#include <inttypes.h>
#include "MILLEIO.h"
#include "MILLE.h"

#define DCMOTOR2CH_ADDRESS 0x80000059

sDevInfo infoDCMOTOR2CH;  //define structure for device information.
uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数

mille myMille;//mille-feuille contorol instance.
MILLEIO myDCMOTOR2CH(DCMOTOR2CH_ADDRESS, myWire,&infoDCMOTOR2CH,0);//class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(myMille.detectModule(&infoDCMOTOR2CH)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire[0],OUTPUT);
  pinMode(myWire[1],OUTPUT);
  pinMode(myWire[2],OUTPUT);
  pinMode(myWire[3],OUTPUT);
}

void loop() {
  myMille.connect(&infoDCMOTOR2CH);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  
  Serial.println("connect\r\n");

  //forward
  Serial.println("forward\r\n");
  digitalWrite(myWire[0],HIGH);
  digitalWrite(myWire[1],LOW);
  digitalWrite(myWire[2],HIGH);
  digitalWrite(myWire[3],LOW);
  delay(2000);
  
  //brake
  Serial.println("brake\r\n");
  digitalWrite(myWire[0],HIGH);
  digitalWrite(myWire[1],HIGH);
  digitalWrite(myWire[2],HIGH);
  digitalWrite(myWire[3],HIGH);
  delay(200);

  //back
  Serial.println("back\r\n");
  digitalWrite(myWire[0],LOW);
  digitalWrite(myWire[1],HIGH);
  digitalWrite(myWire[2],LOW);
  digitalWrite(myWire[3],HIGH);
  delay(2000);

  //no controll
  Serial.println("non\r\n");
  digitalWrite(myWire[0],HIGH);
  digitalWrite(myWire[1],HIGH);
  digitalWrite(myWire[2],HIGH);
  digitalWrite(myWire[3],HIGH);
  delay(200);
  
  Serial.println("disconnect\r\n");
  
  myMille.disconnect(&infoDCMOTOR2CH);//別のデバイスに接続する前に接続断をします。
  delay(1000);
    
}
