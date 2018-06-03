#include "Arduino.h"
#include <inttypes.h>
#include "MILLEIO.h"
#include "MILLE.h"
#include <SoftwareSerial.h> //Include nomally

#define IRR_ADDRESS 0x8000006D  //device board address

uint8_t myIO[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoIRR;  //define structure for device information.

mille myMille; //mille-feuille controller instance.
MILLEIO myIRR(IRR_ADDRESS,myIO,&infoIRR,0); //MILLEIO class instance, connector number on baseboard is zero.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します
SoftwareSerial myIrr(myIO[0], myIO[1]); // RX, TX //mille-feuille has one software serial pin. connector 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myIrr.begin(300);
  if(myMille.detectModule(&infoIRR)){  //Find the device
    exit(0);    //device conection error
  }
}

void loop() {
  int IRR;
  myMille.connect(&infoIRR); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  if(myIrr.available()){
    Serial.write((char)myIrr.read());
  }
  myMille.disconnect(&infoIRR);  //別のデバイスに接続する前に接続断をします。
  
}
