#include <inttypes.h>
#include "MILLEIO.h"
#include "MILLE.h"
#include "DA1CH.h"

#define DA1CH_ADDRESS 0x80000009

uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数
sDevInfo infoDA1CH;  //define structure for device information.

mille myMille;//mille-feuille contorol instance.
MILLEIO myDA1ch(DA1CH_ADDRESS, myWire, &infoDA1CH,0);//AD2CH class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します

DA1CH myDA0(myWire[0],myWire[1],myWire[2],myWire[3]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  myDA0.setup();
  if(myMille.detectModule(&infoDA1CH)){  //Find the device
    exit(0);    //device conection error
  }
}

void loop() {
  myMille.connect(&infoDA1CH);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。

  Serial.println("analog out");
  myDA0.write(0xfff);
  delay(1000);
  myDA0.write(0xfff/2);
  delay(1000);
  myDA0.write(0x000);
  delay(1500);
  myMille.disconnect(&infoDA1CH);//別のデバイスに接続する前に接続断をします。
  delay(1000);
}
