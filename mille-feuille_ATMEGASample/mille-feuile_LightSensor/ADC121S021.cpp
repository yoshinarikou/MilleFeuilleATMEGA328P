#include "ADC121S021.h"
#include "MILLE_FEUILLE.h"

ADC121S021::ADC121S021(uint8_t pin0,uint8_t pin1,uint8_t pin2,uint8_t pin3){
 
    if(pin1!=myMISO){
      //not spi
      typeOfAD = 1;
      myPin[0] = pin0;
      
    }else{
      typeOfAD = 0;
      myPin[0] = pin0;
      myPin[1] = pin1;
      myPin[2] = pin2;
      myPin[3] = pin3;
    }
}

void ADC121S021::setup(void){
  if(typeOfAD==0){
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setDataMode(SPI_MODE0);
    pinMode(myPin[0], OUTPUT);//CS pin
    digitalWrite(myPin[0], HIGH);
  }
}

int ADC121S021::read(void){
  uint16_t myData[2];
  
  if(typeOfAD == 0){
    //Using AD IC
    
    digitalWrite(myPin[0], HIGH);//CS High
    delay(1);
   
    SPI.setClockDivider(SPI_CLOCK_DIV4);//4MHz for 16MHz ATMEGA328P
    digitalWrite(myPin[0], LOW);//CS Low
  
    myData[0] = SPI.transfer(0x00);
    myData[1] = SPI.transfer(0x00);
    
    digitalWrite(myPin[0], HIGH);//CS High
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    return ((myData[0]<<8) + myData[1]);
    
  }else{
    //normal AD pin 
    return (analogRead(myPin[0]));
  }
}

