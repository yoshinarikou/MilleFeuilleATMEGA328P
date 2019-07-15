#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"
#include "RN42BOARD.h"
#include <SoftwareSerial.h> //Include nomally

#define DEBUG 1
#define RN42_ADDRESS 0xC000000D

sDevInfo infoRN42;  //define structure for device information.
uint8_t myIO[2];  

mille myMille(RN42_ADDRESS, myIO, &infoRN42,0); //mille-feuille contorol instance.

SoftwareSerial myRN42Serial0(myIO[1], myIO[0]); // RX, TX //mille-feuille has one software serial pin. connector 0

void readSoftSerial(void){
    while(myRN42Serial0.available()){
      Serial.write((char)myRN42Serial0.read());
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myRN42Serial0.begin(9600);
  if(myMille.detectModule(&infoRN42)){  
      exit(0);    //device conection error
  }
}

void loop() {
  
  Serial.write("Start RN42...\r\n");
  myMille.connect(&infoRN42);
  delay(100);
  Serial.write("Connect wires...\r\n");
  myRN42Serial0.begin(9600);
  Serial.write("Ready to connect!\r\n");

  //Read text from RN42--------------------------------
  char inByte = 0;
  int i;

   while(1){

    //myRN42Serial0.println("alive"); 
    for(i=0;i<1000;++i){
      if (myRN42Serial0.available() > 0) {
        myRN42Serial0.print("I received: ");
        // get incoming byte:
        inByte = myRN42Serial0.read();
        myRN42Serial0.println(inByte); 
        Serial.println(inByte); 
        //delay(100);
        break;
      }
    }
    myMille.disconnect(&infoRN42);
    myMille.connect(&infoRN42);
  }
 
}
