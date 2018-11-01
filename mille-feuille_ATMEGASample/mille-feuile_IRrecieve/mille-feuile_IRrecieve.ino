/*
 * I used test IR data with Android app.
 * https://play.google.com/store/apps/details?id=com.weedle.universal_projector_remote
 * And I chose NEC.
 */

#include "Arduino.h"
#include <inttypes.h>
#include "MILLEIO.h"
#include "MILLE.h"

#define DATA_LENGTH 1024

#define DATA_HALF_UNIT_T 280 //NEC format 562usec
//#define DATA_HALF_UNIT_T 212 //AEHA format 320~500usec(about 425usec)
//#define DATA_HALF_UNIT_T 300 //SONY format 600usec

#define IRR_ADDRESS 0x8000006D  //device board address

uint8_t myIO[4];  //The wires for device.配線の情報を格納する変数
sDevInfo infoIRR;  //define structure for device information.

mille myMille; //mille-feuille controller instance.
MILLEIO myIRR(IRR_ADDRESS,myIO,&infoIRR,0); //MILLEIO class instance, connector number on baseboard is zero.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します

void dataConverter(uint8_t *dataArrayHex){
  int i;
  boolean dataArray[DATA_LENGTH];
  for(i=0; i<DATA_LENGTH; ++i){
    dataArray[i] = digitalRead(myIO[0]);
    delayMicroseconds(DATA_HALF_UNIT_T);
  }
  Serial.write("dataArray = :");
  
  for(i=0; i<DATA_LENGTH; ++i){
    Serial.print(dataArray[i]);
  }
  Serial.write("\r\n"); 
  Serial.write("\r\n"); 


  for(i=0; i<DATA_LENGTH/8; ++i){
    dataArrayHex[i] = 0;    
  }

  int j=0;
  int k=0;
  //data converter
  for(i=0; i<DATA_LENGTH; ++i){
    if((dataArray[i]==0) && (dataArray[i+2]==1) && (dataArray[i+4]==1)){ //data 1
      dataArrayHex[k] = dataArrayHex[k] << 1;
      dataArrayHex[k] = dataArrayHex[k] | 0x01;
      i+=7;
      ++j;
      
    }else if((dataArray[i]==0) && (dataArray[i+2]==1) && (dataArray[i+4]==0)){ //data 0
      dataArrayHex[k] = dataArrayHex[k] << 1;
      //dataArrayHex[k] = dataArrayHex[k] | 0x00;
      i+=3;
      ++j;
    }else{
      ;
    }
    if(j>=8){
      j=0;
      ++k;
    }
  }
  
  for(i=0; i<DATA_LENGTH/8; ++i){
    //Serial.print(i);
    Serial.write(" 0x"); 
    Serial.print(dataArrayHex[i],HEX);
    Serial.write(" "); 
    
  }
}
  



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
  uint8_t dataArrayHex[DATA_LENGTH/8];
  if(inputData==0){
    while(inputData==0){//learder1
      inputData = digitalRead(myIO[0]);
    }
    dataConverter(dataArrayHex);
  }
  myMille.disconnect(&infoIRR);  //別のデバイスに接続する前に接続断をします。
  
}
