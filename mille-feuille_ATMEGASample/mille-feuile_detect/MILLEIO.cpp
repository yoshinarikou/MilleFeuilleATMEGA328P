#include "MILLEIO.h"
#include "MILLE_FEUILLE.h"

MILLEIO::MILLEIO(uint64_t Address,uint8_t pin[4],sDevInfo *DeviceInfomation, uint64_t connectorNumber){
  if(connectorNumber==BASEBOARD){
    DeviceInfomation->address = Address;
    DeviceInfomation->location = BASEBOARD;
  }else{
    DeviceInfomation->address = Address + connectorNumber;
  }
  getWire(DeviceInfomation->address, pin, connectorNumber); //Address and conector Number
  getWireSetting(pin,DeviceInfomation);
}
MILLEIO::~MILLEIO(){
  ;
}
MILLEIO::getMyWire(uint64_t Address, uint8_t pin[4], uint64_t connectorNumber){
  getWire((BASE_ADDRESS + Address), pin, connectorNumber); //Address and conector Number
}

