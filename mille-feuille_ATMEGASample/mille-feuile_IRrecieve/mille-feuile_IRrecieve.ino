#include "Arduino.h"
#include <inttypes.h>
#include "MILLEIO.h"
#include "MILLE.h"

#define IRS_ADDRESS 0x8000006D  //device board address

uint8_t myWire[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoIRS;  //define structure for device information.

mille myMille; //mille-feuille controller instance.
MILLEIO myGpio(IRS_ADDRESS,myWire,&infoIRS,0); //MILLEIO class instance, connector number on baseboard is zero.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(myMille.detectModule(&infoIRS)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire[0],INPUT);
}

void loop() {
  int IRR;
  myMille.connect(&infoIRS); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  IRR = digitalRead(myWire[0]);
  Serial.write("IRR = ");
  Serial.print(IRR);
  Serial.write("\r\n");
  myMille.disconnect(&infoIRS);  //別のデバイスに接続する前に接続断をします。
  
}
