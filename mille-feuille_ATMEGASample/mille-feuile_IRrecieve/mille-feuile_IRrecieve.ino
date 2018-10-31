/*
 * I used test IR data with Android app.
 * https://play.google.com/store/apps/details?id=com.weedle.daikin_ac_remotes
 */

#include "Arduino.h"
#include <inttypes.h>
#include "MILLEIO.h"
#include "MILLE.h"
#include <SoftwareSerial.h> //Include nomally

#define DATA_LENGTH 1024

#define IRR_ADDRESS 0x8000006D  //device board address

uint8_t myIO[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoIRR;  //define structure for device information.

mille myMille; //mille-feuille controller instance.
MILLEIO myIRR(IRR_ADDRESS,myIO,&infoIRR,0); //MILLEIO class instance, connector number on baseboard is zero.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("start");
  if(myMille.detectModule(&infoIRR)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myIO[0],INPUT);
}

void loop() {
  int i;
  myMille.connect(&infoIRR); //wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  uint8_t inputData = digitalRead(myIO[0]);
  boolean dataArray[DATA_LENGTH];
  if(inputData==0){
    while(inputData==0){
      inputData = digitalRead(myIO[0]);
    }
    for(i=0; i<DATA_LENGTH; ++i){
      dataArray[i] = digitalRead(myIO[0]);
      delayMicroseconds(280);
    }
    Serial.write("dataArray = :");
    
    for(i=0; i<DATA_LENGTH; ++i){
      Serial.print(dataArray[i]);
    }
    Serial.write("\r\n");
  }
  myMille.disconnect(&infoIRR);  //別のデバイスに接続する前に接続断をします。
  
}
