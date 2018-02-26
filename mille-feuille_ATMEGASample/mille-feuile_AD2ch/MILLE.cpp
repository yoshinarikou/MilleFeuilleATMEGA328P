#include "MILLE.h"

mille::mille(){

  _MOSI = 11;
  _MISO = 12;
  _SCK = 13;
  _ncs = 10;
  _in1 = 14;
  _in2 = 15;
  _in3 = 16;

  pinMode(_in1,INPUT);
  pinMode(_in2,INPUT);
  pinMode(_in3,INPUT);
  //pinMode(_in4,INPUT);

  pinMode(_ncs,OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin();
  digitalWrite(_ncs, HIGH);
 
}

void mille::order(uint32_t const myAddress, uint8_t myData1, uint8_t myData2) {
    
    uint8_t sendData;

    digitalWrite(_ncs, HIGH);
    //SPI.transfer(0x11);
    delayMicroseconds(10);
    digitalWrite(_ncs, LOW);
    delayMicroseconds(10);
    //_ncs = 0;
    sendData = (myAddress>>24)&0xFF;
    SPI.transfer(sendData);
    delayMicroseconds(10);
    SPI.transfer((myAddress>>16)&0xFF);
    delayMicroseconds(10);
    SPI.transfer((myAddress>>8)&0xFF);
    delayMicroseconds(10);
    SPI.transfer(myAddress&0xFF);
    delayMicroseconds(10);
    SPI.transfer(myData1);
    delayMicroseconds(10);
    SPI.transfer(myData2);
    delayMicroseconds(10);

    digitalWrite(_ncs, HIGH);
    delayMicroseconds(100);

}

uint8_t mille::readInputData(void){
    uint8_t flg_error = 0;
    uint8_t location = 0xFF;

    //return (digitalRead(_in3));
    
    if(digitalRead(_in1)==0){
        ++flg_error;
        location = 1;
    }
    
    if(digitalRead(_in2)==0){
        ++flg_error;
        location = 5;
    }
    
    if(digitalRead(_in3)==0){
        ++flg_error;
        location = 9;
    }

  //return flg_error;
    
    if(flg_error==1){
        return location;
    }else{
        return 0xff;
    }
}

uint8_t mille::detectModule(sDevInfo *myDevInfo){
    uint8_t i = 0;
    uint8_t myLocation = 0xff;
    uint64_t myAddress= 0;
    
    //Detect Mode ON
    
    for(i=0;i<3;++i){
        order(BASE_ADDRESS, (1+4*i), (0x12+i));//sift 0x12
        delay(10);
    }
    /*order(BASE_ADDRESS, 0x01, 0x11);
    order(BASE_ADDRESS, 0x05, 0x12);
    order(BASE_ADDRESS, 0x09, 0x13);
    */
    
    //order(myAddress, DETECTMODE_ON, 0x00);
    order(myDevInfo->address, DETECTMODE_ON, 0x00);
    delay(10);
    myLocation = readInputData();
    
    //Detect Mode OFF
    order(myDevInfo->address, DETECTMODE_OFF, 0x00);
    delay(10);
    
    for(i=0;i<3;++i){
        order(BASE_ADDRESS, (1+4*i), 0x00);
        delay(10);
    }
    
    myDevInfo->location = myLocation;
    //printf("myDevInfo->location = %d\r\n",myDevInfo->location);
    if(myDevInfo->location!=255){
        return 0;//find device
    }else{
        return 1;//not find device
    }
}

void mille::connect(sDevInfo *myDevInfo) {
    //uint8_t numIOs = sizeof(myDevInfo->IOs) / sizeof(myDevInfo->IOs[0]);
    uint8_t i;
        
    //for(i=0;i<numIOs;++i){
    for(i=0;i<NORMAL_IONUMBRE;++i){
        order(BASE_ADDRESS, ((myDevInfo->location) + i), myDevInfo->IOs[i]);
        //printf("location = %d : IOs[%d] = %d\r\n",((myDevInfo->location) + i), i, myDevInfo->IOs[i]);
    }
    
    //Open Gate of Module
    
    //order(myDevInfo->address, 0x02, 0x00);
    order(myDevInfo->address, myDevInfo->typeOfGate, 0x00);
    /*
    0x01://close gate
    0x02://open gate normal IOs
    0x03://Detect mode ON
    0x04://Detect mode OFF
    0x05://LED on
    0x06://LED offx06://LED off
    0x07://SPI gate : MOSI MISO SCK CS
    0x08://One way SPI gate : MOSI SCK CS EXtra IO
    0x09://SCK as a clock : SCK Extra IOs
    0x0A://SPI gate : MISO SCK CS
    0x0B://hold mode ON
    0x0C://hold mode OFF
    */
}


void mille::disconnect(sDevInfo *myDevInfo) {
  uint8_t num,i;
  order(myDevInfo->address, mCLOSEGATE, 0x00);
    
  num = sizeof(myDevInfo->IOs)/sizeof(uint8_t);
  for(i=0;i<num;++i){
    order(BASE_ADDRESS, ((myDevInfo->location) + i),0x00);
  }
}

void mille::holdConnect(sDevInfo *myDevInfo) {
    uint8_t i;
    
    order(myDevInfo->address, mHOLD_OFF, 0x00);
        
    for(i=0;i<NORMAL_IONUMBRE;++i){
        order(BASE_ADDRESS, ((myDevInfo->location) + i), myDevInfo->IOs[i]);
        //printf("location = %d : IOs[%d] = %d\r\n",((myDevInfo->location) + i), i, myDevInfo->IOs[i]);
    }
    
    order(myDevInfo->address, myDevInfo->typeOfGate, 0x00);
}

void mille::holdDisconnect(sDevInfo *myDevInfo) {
    uint8_t num,i;

    order(myDevInfo->address, mHOLD_ON, 0x00);
    
    num = sizeof(myDevInfo->IOs)/sizeof(uint8_t);
    for(i=0;i<num;++i){
            order(BASE_ADDRESS, ((myDevInfo->location) + i),0x00);
    }
}



