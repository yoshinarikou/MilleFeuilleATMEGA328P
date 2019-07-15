//reference:
//https://garretlab.web.fc2.com/arduino/make/infrared_sensor_nec_format/index.html

#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"
#include "IRSEND.h"


#define IRS_ADDRESS 0x8000007D

uint8_t myIO[4];  //The wire for device.配線の情報を格納する変数
sDevInfo infoIRS;  //define structure for device information.

mille myMille(IRS_ADDRESS, myIO,&infoIRS, 0);//mille-feuille contorol instance.

IRSEND controller(myIO[0]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  if(myMille.detectModule(&infoIRS)){  //Find the device
    exit(0);    //device conection error
  }
  
  pinMode(myIO[0],OUTPUT);
}

void loop() {
  myMille.connect(&infoIRS);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  controller.sendData(0x1A);//no format
//  controller.sendNECCommand(0x1e, 0x45, 0xbc);//data, command1, command2
  delay(1000);
  myMille.disconnect(&infoIRS);//別のデバイスに接続する前に接続断をします。
}
