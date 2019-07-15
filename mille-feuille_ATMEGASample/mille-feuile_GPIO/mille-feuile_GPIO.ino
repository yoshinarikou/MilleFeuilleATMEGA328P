#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"

#define GPIO_ADDRESS 0x80000001  //device board address
 
uint8_t myWire[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoGpio;  //define structure for device information.

mille myMille(GPIO_ADDRESS,myWire,&infoGpio,0); //mille-feuille controller instance.
  
void setup() {
  // put your setup code here, to run once:
  if(myMille.detectModule(&infoGpio)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire[0],OUTPUT);
}

void loop() {  
  myMille.connect(&infoGpio); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  for(int i=0;i<3;++i){
    digitalWrite(myWire[0], HIGH);
    delay(1000);
    digitalWrite(myWire[0], LOW);
    delay(1000);
  }
  myMille.disconnect(&infoGpio);  //別のデバイスに接続する前に接続断をします。
  delay(2000);
  
}
