#include <inttypes.h>
#include "MILLE.h"

#define PIR_ADDRESS 0x80000035

uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数
sDevInfo infoPIR;  //define structure for device information.

mille myMille(PIR_ADDRESS,myWire,&infoPIR,0);//mille-feuille contorol instance.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  if(myMille.detectModule(&infoPIR)){  //Find the device
    exit(0);    //device conection error
  }
  
  pinMode(myWire[0],INPUT);
  
}

void loop() {
  myMille.connect(&infoPIR);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。

  int data = digitalRead(myWire[0]);
  Serial.write("data = ");
  Serial.print(data);
  Serial.write("\r\n");

  myMille.disconnect(&infoPIR);//別のデバイスに接続する前に接続断をします。
  delay(1000);    
}
