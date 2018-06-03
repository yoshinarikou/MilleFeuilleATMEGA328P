#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"
#include "MILLEIO.h"
#include <SoftwareSerial.h> //Include nomally

#define IRS_ADDRESS 0x80000069

uint8_t myIO[4];  //The wire for device.配線の情報を格納する変数
sDevInfo infoIRS;  //define structure for device information.

mille myMille;//mille-feuille contorol instance.
MILLEIO myIRS(IRS_ADDRESS, myIO,&infoIRS, 0);//class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します
SoftwareSerial myIrs(myIO[1], myIO[0]); // RX, TX //mille-feuille has one software serial pin. connector 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myIrs.begin(300);
  
  if(myMille.detectModule(&infoIRS)){  //Find the device
    exit(0);    //device conection error
  }
}

void loop() {
  myMille.connect(&infoIRS);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  myIrs.print('Hello world!');
  delay(1000);
  myMille.disconnect(&infoIRS);//別のデバイスに接続する前に接続断をします。
}
