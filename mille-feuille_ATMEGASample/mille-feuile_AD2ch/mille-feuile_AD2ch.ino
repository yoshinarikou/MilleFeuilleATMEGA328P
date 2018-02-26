#include <inttypes.h>
#include "MILLE.h"
#include "MILLEIO.h"
#include "AD2CH.h"

#define AD2ch_ADDRESS 0x80000005  //device board address

uint8_t myWire[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoAD2CH;  //define structure for device information.

mille myMille;//mille-feuille contorol instance.
MILLEIO myAD2ch(AD2ch_ADDRESS, myWire,&infoAD2CH,0);//AD2CH class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します

AD2CH myAD0(myWire[0],myWire[1],myWire[2],myWire[3]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  myAD0.setup();
  if(myMille.detectModule(&infoAD2CH)){  //Find the device
    exit(0);    //device conection error
  }
}

void loop() {
  myMille.connect(&infoAD2CH);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  int readData[3];
  readData[0] = myAD0.read(0);  //0ch
  readData[1] = myAD0.read(1);  //1ch
  readData[2] = myAD0.readSimpleDiff(); //pseudo-differential pairs 疑似差動入力関数
  
  Serial.write("AD 0ch = ");
  Serial.print(readData[0]);
  Serial.write(" 1ch = ");
  Serial.print(readData[1]);
  Serial.write(" Diff = ");
  Serial.print(readData[2]);//pseudo-differential 疑似差動入力
  Serial.write("\r\n");
  
  myMille.disconnect(&infoAD2CH);//別のデバイスに接続する前に接続断をします。
  delay(1000);
}
