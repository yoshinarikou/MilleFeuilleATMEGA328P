#include "MILLEIO.h"
#include "MILLE_FEUILLE.h"

MILLEIO::MILLEIO(uint64_t Address,uint8_t pin[4],sDevInfo *DeviceInfomation, uint64_t connectorNumber){
  DeviceInfomation->address = Address + connectorNumber;    
  getWire(DeviceInfomation->address, pin, connectorNumber); //Address and conector Number
  getWireSetting(pin,DeviceInfomation);
}
MILLEIO::~MILLEIO(){
  ;
}

