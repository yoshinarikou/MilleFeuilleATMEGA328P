#include "Arduino.h"
#include <inttypes.h>
#include "MILLEIO.h"
#include "MILLE.h"

#define SIMPLE_BUTTON_ADDRESS 0x80000061  //device board address

uint8_t myWire[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoSBT;  //define structure for device information.

mille myMille; //mille-feuille controller instance.
MILLEIO myGpio(SIMPLE_BUTTON_ADDRESS,myWire,&infoSBT,0); //MILLEIO class instance, connector number on baseboard is zero.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(myMille.detectModule(&infoSBT)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire[0],INPUT);
  pinMode(myWire[1],INPUT);
  pinMode(myWire[2],INPUT);
  pinMode(myWire[3],INPUT);
}

void loop() {
  int sw[4];
  myMille.connect(&infoSBT); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  sw[0] = digitalRead(myWire[0]);
  sw[1] = digitalRead(myWire[1]);
  sw[2] = digitalRead(myWire[2]);
  sw[3] = digitalRead(myWire[3]);
  Serial.write("Switch 0:");
  Serial.print(sw[0]);
  Serial.write(" 1:");
  Serial.print(sw[1]);
  Serial.write(" 2:");
  Serial.print(sw[2]);
  Serial.write(" 3:");
  Serial.print(sw[3]);
  Serial.write("\r\n");
  myMille.disconnect(&infoSBT);  //別のデバイスに接続する前に接続断をします。
  
}
