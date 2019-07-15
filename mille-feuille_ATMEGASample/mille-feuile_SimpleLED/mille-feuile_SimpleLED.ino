#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"

#define SIMPLE_LED_ADDRESS 0x8000005D  //device board address

uint8_t myWire[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoSLED;  //define structure for device information.
mille myMille(SIMPLE_LED_ADDRESS,myWire,&infoSLED,0); //mille-feuille controller instance. Connector No,0.

void setup() {
  // put your setup code here, to run once:
  if(myMille.detectModule(&infoSLED)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire[0],OUTPUT);
  pinMode(myWire[1],OUTPUT);
  pinMode(myWire[2],OUTPUT);
  pinMode(myWire[3],OUTPUT);
  
}

void loop() {  
  myMille.holdConnect(&infoSLED); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  
  digitalWrite(myWire[0], LOW);
  digitalWrite(myWire[1], LOW);
  digitalWrite(myWire[2], LOW);
  digitalWrite(myWire[3], LOW);
  
  for(int i=0;i<=3;++i){
    digitalWrite(myWire[i], HIGH);
    delay(200);
    digitalWrite(myWire[i], LOW);
    delay(200);
  }
    delay(1000);
    digitalWrite(myWire[0], HIGH);
    digitalWrite(myWire[1], HIGH);
    digitalWrite(myWire[2], HIGH);
    digitalWrite(myWire[3], HIGH);
  myMille.holdDisconnect(&infoSLED);  //別のデバイスに接続する前に接続断をします。
  delay(2000);
  
}
