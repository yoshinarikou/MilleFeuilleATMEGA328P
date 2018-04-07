#include "RN42BOARD.h"
#include "MILLE_FEUILLE.h"


//GPIOBOARD::GPIOBOARD(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3){
RN42BOARD::RN42BOARD(uint8_t pin[2],sDevInfo *DeviceInfomation, uint64_t connectorNumber){
    uint8_t i,j;
    
    DeviceInfomation->address = RN42_ADDRESS + connectorNumber;;
   
    getWire(DeviceInfomation->address, pin, connectorNumber); //Address and conector Number
  
    myPin[0] = pin[0];
    myPin[1] = pin[1];

    getWireSetting(myPin,DeviceInfomation);

}

