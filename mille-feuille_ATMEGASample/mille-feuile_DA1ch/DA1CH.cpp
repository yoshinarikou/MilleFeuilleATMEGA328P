#include "DA1CH.h"
#include "MILLE_FEUILLE.h"

DA1CH::DA1CH(uint8_t pin0, uint8_t pin1,uint8_t pin2,uint8_t pin3){

  if(pin0!=myMOSI){
    //not spi
    typeOfPWM = 1;
    myPin[0] = pin0;
    
  }else{
    typeOfPWM = 0;
    
    myPin[0] = pin0;
    myPin[1] = pin1;
    myPin[2] = pin2;
    myPin[3] = pin3;
  }
}

void DA1CH::setup(void){

  if(typeOfPWM == 0){
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setDataMode(SPI_MODE0);
    pinMode(myPin[1], OUTPUT);//CS pin
    pinMode(myPin[3], OUTPUT);//LDAC pin
    
    digitalWrite(myPin[1], HIGH);
    digitalWrite(myPin[3], HIGH);
  }
  
}
void DA1CH::write(uint16_t data){

  uint8_t sendData[2];
  
  if(typeOfPWM == 0){
    //Using DA IC
    sendData[0] = 0x30 + ((data >> 8) & 0x0f);
    sendData[1] = data & 0xff;
    
    digitalWrite(myPin[1], HIGH);//CS High
    digitalWrite(myPin[3], HIGH);//LDAC High
    delay(1);
    
    digitalWrite(myPin[1], LOW);//CS Low
  
    SPI.transfer(sendData[0]);
    SPI.transfer(sendData[1]);
    
    digitalWrite(myPin[1], HIGH);//CS High
    delay(1);
    digitalWrite(myPin[3], LOW);//LDAC Low
    delay(1);
    digitalWrite(myPin[3], HIGH);//LDAC High
    
  }else{
    //normal PWM out 
    analogWrite(myPin[0], data>>4); //analogWrite is 8bit data
  }
}

