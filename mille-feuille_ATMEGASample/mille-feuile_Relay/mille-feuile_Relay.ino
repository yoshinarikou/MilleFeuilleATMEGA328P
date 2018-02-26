#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"
#include "MILLEIO.h"

#define RELAY_ADDRESS 0x8000004D

uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数
sDevInfo infoRELAY;  //define structure for device information.

mille myMille;//mille-feuille contorol instance.
MILLEIO myRELAY(RELAY_ADDRESS, myWire,&infoRELAY, 0);//AD2CH class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(myMille.detectModule(&infoRELAY)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire[0],OUTPUT);
}

void loop() {
  myMille.connect(&infoRELAY);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  
  digitalWrite(myWire[0],HIGH);
  delay(1000);
  digitalWrite(myWire[0],LOW);
  
  myMille.disconnect(&infoRELAY);//別のデバイスに接続する前に接続断をします。
  delay(1000);
}
