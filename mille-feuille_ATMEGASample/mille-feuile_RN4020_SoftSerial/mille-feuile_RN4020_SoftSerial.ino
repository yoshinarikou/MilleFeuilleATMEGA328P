#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"
#include "MILLEIO.h"
#include "RN4020BOARD.h"
#include <SoftwareSerial.h> //Include nomally

#define DEBUG 1
#define RN4020_ADDRESS 0xC0000009

sDevInfo infoRN4020;  //define structure for device information.
uint8_t myIO[2];  

mille myMille; //mille-feuille contorol instance.
MILLEIO myRn4020(RN4020_ADDRESS, myIO, &infoRN4020,0);  //set wire connector number 0

SoftwareSerial myRN4020Serial0(myIO[1], myIO[0]); // RX, TX //mille-feuille has one software serial pin. connector 0

void readSoftSerial(void){
    while(myRN4020Serial0.available()){
      Serial.write((char)myRN4020Serial0.read());
    }
}
void initRN4020(void){
  
    myRN4020Serial0.println("SF,1");
    delay(1000);
    readSoftSerial();
    
    myRN4020Serial0.println("SS,00000001");
    delay(1000);
    readSoftSerial();
    
    myRN4020Serial0.println("SR,24000000");
    delay(1000);
    readSoftSerial();
    
    myRN4020Serial0.println("PZ");
    delay(1000);
    readSoftSerial();
    
    myRN4020Serial0.println("PS,123456789012345678901234567890FF");
    delay(1000);
    readSoftSerial();
    
    myRN4020Serial0.println("PC,12345678901234567890123456789011,1A,0A");
    delay(1000);
    readSoftSerial();
    
    myRN4020Serial0.println("PC,12345678901234567890123456789022,06,02");
    delay(1000);
    readSoftSerial();
    
    myRN4020Serial0.println("R,1");
    delay(1500);
    readSoftSerial();
    delay(100);


    myRN4020Serial0.println("SB,1");
    delay(1000);

    Serial.println("Software Serial Baudrate:9600\n\r");

    myRN4020Serial0.println("R,1");//change Baudrate 9600
    delay(1500);

    myRN4020Serial0.begin(9600);//change Baudrate
    delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myRN4020Serial0.begin(115200);
  if(myMille.detectModule(&infoRN4020)){  
      exit(0);    //device conection error
  }
}

void loop() {
  
  Serial.write("Start Setting RN4020...\r\n");
  myMille.connect(&infoRN4020);
  delay(100);
  Serial.write("Connect wires...\r\n");
  myRN4020Serial0.begin(115200);
  initRN4020();

  Serial.write("Ready to connect!\r\n");
  
  Serial.println("Send \"@\" from smart phone and get \"Hello\" from ATMEGA328P.\r\n");

  //Read text from RN4020--------------------------------
  char temp[2];
  String str;
  int code;
  int codeA,codeB;
  char myChar[20];

   while(1){
    myRN4020Serial0.listen();
    while(myRN4020Serial0.available()){
      temp[1] = (char)myRN4020Serial0.read();
      //Serial.write(temp[1]);
      if((((temp[0] >= '0')&&(temp[0] <= '9'))||((temp[0] >= 'A')&&(temp[0] <= 'F'))) && (((temp[1] >= '0')&&(temp[1] <= '9'))||((temp[1] >= 'A')&&(temp[1] <= 'F')))){
        //change ASCII code
        if(((temp[0] >= 'A')&&(temp[0] <= 'F'))){
          codeA = (int)temp[0]-55;
        }else{
          codeA = (int)temp[0]-48;
        }
        
        if(((temp[1] >= 'A')&&(temp[1] <= 'F'))){
          codeB = (int)temp[1]-55;
        }else{
          codeB = (int)temp[1]-48;
        }
        code = codeA * 16 + codeB;
        if((char)code != '@'){
          Serial.write((char)code);
          
        }else if((char)code == '@'){//when you send '@' from mobile phone or tablet, you can get 'HELLO'
          myRN4020Serial0.write("SHW,000B,48454C4C4F\n");
          //disconnect & connect test----
          //if you need to listen softwareserial Rx, do not disconnect the wire. 
          myMille.holdDisconnect(&infoRN4020);
          delay(100);
          myMille.connect(&infoRN4020);
          delay(100);
          myRN4020Serial0.begin(9600); //baud rate was changed in initialize
          //--------------------
  
        }
        temp[0]=' ';
        temp[1]=' ';
      }
      temp[0] = temp[1];
    }
  }
 
}
