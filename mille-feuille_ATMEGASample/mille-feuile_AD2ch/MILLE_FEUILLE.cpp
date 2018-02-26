
#include "MILLE_FEUILLE.h"

const uint8_t myOutPin[NUM_OUTPUT] = {3,5,6,9,7,8};
const uint8_t myInPin[NUM_INPUT] = {2,14,15,16,17};


void getWireSetting(uint8_t myPin[4],sDevInfo *DeviceInfomation){
  int i,j;
  
  for(j=0;j<4;++j){
    DeviceInfomation->IOs[j] = 0;
  }

  if((myPin[0]==myMOSI)&&(myPin[1]==myMISO)&&(myPin[2]==mySCK)){
    //Normal SPI
    //0x07 mSPI1
    DeviceInfomation->typeOfGate = mSPI1;
    
  }else if((myPin[0]==myMOSI)&&(myPin[1]!=myMISO)&&(myPin[2]==mySCK)){
    //SCK SPI
    //0x08mSPI2
    DeviceInfomation->typeOfGate = mSPI2;
    
  }else if((myPin[0]!=myMOSI)&&(myPin[1]!=myMISO)&&(myPin[2]==mySCK)){
    //MOSI SCK SPI
    //0x09mSPI3
    DeviceInfomation->typeOfGate = mSPI3;
  
  }else if(((myPin[0]!=myMOSI)&&(myPin[1]==myMISO)&&(myPin[2]==mySCK))){
    //MISO SCK SPI
    //0x0A mSPI4
    DeviceInfomation->typeOfGate = mSPI4;
    
  }else{
    //Normal IO
    //0x02mOPENALLGATE
    DeviceInfomation->typeOfGate = mOPENALLGATE;    
  }

  //Softserial
  if((myPin[0]==mySoftTX)&&(myPin[1]==mySoftRX)){
    DeviceInfomation->IOs[0]=0x01; 
    DeviceInfomation->IOs[1]=0x11;
  }

  //Normal GPIO
  for(j=0;j<4;++j){
    for(i=1;i<NUM_INPUT;++i){   //myInPin[0] is mySoftRx
      
      if(myPin[j] == myInPin[i]){
        pinMode(myPin[j],INPUT);
        //sPin[j]=i+0x11;
        DeviceInfomation->IOs[j]=i+0x11;
      }
    }
   
    for(i=1;i<NUM_OUTPUT;++i){   //myOutPin[0] is mySoftTx
      if(myPin[j] == myOutPin[i]){
        pinMode(myPin[j],OUTPUT);
        //sPin[j]=i+0x01;
        DeviceInfomation->IOs[j]=i+0x01;
      }
    }
  }
}





/////////////
//select libraly
#define GPIOBOARD_LIB
#define AD2CH_LIB
#define DA1CH_LIB
#define LIGHT_LIB
#define PWM16CH_LIB
#define UNISTEP_LIB
#define HUMIDITY_LIB
#define AIRPRESS_LIB
#define PROXIMITY_LIB
#define DCMOTOR_LIB
#define PIR_LIB
#define MOISTURE_LIB
#define ACC_MMA8451Q_LIB
#define MPU9250_LIB
#define HART_LIB
#define RELAY_LIB
#define TOF_LIB
#define RN4020_LIB

void getWire(uint64_t myAddress, uint8_t *wire, uint8_t connectorNo){
        
    if(myAddress == BASE_ADDRESS){
        ;
#ifdef GPIOBOARD_LIB//OK
    }else if(myAddress == (BASE_ADDRESS+0x01)){//GPIO
      //wire[0]=myMOSI; wire[1]=myOutPin[1]; wire[2]=mySCK; wire[3]=myOutPin[2];
        wire[0]=myOutPin[1]; wire[1]=myOutPin[2]; wire[2]=myOutPin[3]; wire[3]=myOutPin[4];
       // wire[0]=myInPin[1]; wire[1]=myInPin[2]; wire[2]=myInPin[3]; wire[3]=myInPin[4];
        //wire[0]=mySoftTX; wire[1]=mySoftRX; wire[2]=myOutPin[0]; wire[3]=myOutPin[1];
    }else if(myAddress == (BASE_ADDRESS+0x02)){//GPIO
        wire[0]=myOutPin[1]; wire[1]=myOutPin[2]; wire[2]=myOutPin[3]; wire[3]=myOutPin[4];
        //wire[0]=myInPin[1]; wire[1]=myInPin[2]; wire[2]=myInPin[3]; wire[3]=myInPin[4];
        //wire[0]=mySoftTX; wire[1]=mySoftRX; wire[2]=myOutPin[0]; wire[3]=myOutPin[1];
    }else if(myAddress == (BASE_ADDRESS+0x03)){//GPIO
        wire[0]=myOutPin[1]; wire[1]=myOutPin[2]; wire[2]=myOutPin[3]; wire[3]=myOutPin[4];
        //wire[0]=myInPin[1]; wire[1]=myInPin[2]; wire[2]=myInPin[3]; wire[3]=myInPin[4];
        //wire[0]=mySoftTX; wire[1]=mySoftRX; wire[2]=myOutPin[0]; wire[3]=myOutPin[1];
#endif
#ifdef AD2CH_LIB//OK
    }else if((myAddress >= (BASE_ADDRESS+0x05))&&(myAddress <= (BASE_ADDRESS+0x08))){
        wire[0]=myMOSI; wire[1]=myMISO; wire[2]=mySCK; wire[3]=myOutPin[1];
#endif
#ifdef DA1CH_LIB//OK
    }else if((myAddress >= (BASE_ADDRESS+0x09))&&(myAddress <= (BASE_ADDRESS+0x0C))){
        wire[0]=myMOSI; wire[1]=myOutPin[1]; wire[2]=mySCK; wire[3]=myOutPin[2];
#endif
#ifdef LIGHT_LIB//OK
    }else if((myAddress >= (BASE_ADDRESS+0x0D))&&(myAddress <= (BASE_ADDRESS+0x10))){
        wire[0]=myOutPin[1]; wire[1]=myMISO; wire[2]=mySCK; wire[3]=myInPin[1];
#endif
#ifdef PWM16CH_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x15))&&(myAddress <= (BASE_ADDRESS+0x18))){
        wire[0]=mySDA; wire[1]=mySCL;
#endif
#ifdef UNISTEP_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x1D))&&(myAddress <= (BASE_ADDRESS+0x20))){
        wire[0]=myOutPin[1]; wire[1]=myOutPin[2]; wire[2]=myOutPin[3]; wire[3]=myOutPin[4];
#endif
#ifdef HUMIDITY_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x21))&&(myAddress <= (BASE_ADDRESS+0x24))){
        wire[0]=mySDA; wire[1]=mySCL;
#endif
#ifdef AIRPRESS_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x25))&&(myAddress <= (BASE_ADDRESS+0x28))){
        wire[0]=mySDA; wire[1]=mySCL;
#endif
#ifdef PROXIMITY_LIB//OK
    }else if((myAddress >= (BASE_ADDRESS+0x29))&&(myAddress <= (BASE_ADDRESS+0x2C))){
        wire[0]=myOutPin[1]; wire[1]=myInPin[1];
#endif
#ifdef DCMOTOR_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x2D))&&(myAddress <= (BASE_ADDRESS+0x30))){
        wire[0]=myOutPin[1]; wire[1]=myOutPin[2];
#endif
#ifdef MOISTURE_LIB//OK
    }else if((myAddress >= (BASE_ADDRESS+0x31))&&(myAddress <= (BASE_ADDRESS+0x34))){
        wire[0]=myOutPin[1]; wire[1]=myMISO; wire[2]=mySCK; wire[3]=myInPin[1];
#endif
#ifdef PIR_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x35))&&(myAddress <= (BASE_ADDRESS+0x38))){
        wire[0]=myInPin[1];
#endif
#ifdef ACC_MMA8451Q_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x3D))&&(myAddress <= (BASE_ADDRESS+0x40))){
        wire[0]=mySDA; wire[1]=mySCL;
#endif
#ifdef MPU9250_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x41))&&(myAddress <= (BASE_ADDRESS+0x44))){
        wire[0]=mySDA; wire[1]=mySCL;
#endif
#ifdef HART_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x49))&&(myAddress <= (BASE_ADDRESS+0x4C))){
        wire[0]=mySDA; wire[1]=mySCL;
#endif
#ifdef RELAY_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x4D))&&(myAddress <= (BASE_ADDRESS+0x50))){
        wire[0]=myOutPin[1];
#endif
#ifdef TOF_LIB
    }else if((myAddress >= (BASE_ADDRESS+0x51))&&(myAddress <= (BASE_ADDRESS+0x54))){
        wire[0]=mySDA; wire[1]=mySCL;
#endif
#ifdef RN4020_LIB
    }else if((myAddress >= (SPECIAL_ADDRESS+0x09))&&(myAddress <= (SPECIAL_ADDRESS+0x0C))){
        wire[0]=mySoftTX; wire[1]=mySoftRX;
        
#endif

    }else{
        //Serial.begin(115200);
        //Serial.println("IO error");
        ;
    }
}

