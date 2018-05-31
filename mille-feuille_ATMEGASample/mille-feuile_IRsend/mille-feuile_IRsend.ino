#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"
#include "MILLEIO.h"

#define IRS_ADDRESS 0x80000069

uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数
sDevInfo infoIRS;  //define structure for device information.

mille myMille;//mille-feuille contorol instance.
MILLEIO myRELAY(IRS_ADDRESS, myWire,&infoIRS, 0);//AD2CH class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(myMille.detectModule(&infoIRS)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire[0],OUTPUT);
}

void loop() {
  myMille.connect(&infoIRS);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  
  digitalWrite(myWire[0],HIGH);//send
  delay(1000);
  digitalWrite(myWire[0],LOW);//stop
  
  myMille.disconnect(&infoIRS);//別のデバイスに接続する前に接続断をします。
  delay(1000);
}
