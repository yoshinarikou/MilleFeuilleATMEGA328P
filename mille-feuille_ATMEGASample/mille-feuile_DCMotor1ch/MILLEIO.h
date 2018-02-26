#ifndef MILLEIO_h
#define MILLEIO_h
 
#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"


class MILLEIO {
public:
    MILLEIO(uint64_t Address, uint8_t pin[4],sDevInfo *DeviceInfomation, uint64_t connectorNumber);
    ~MILLEIO();
private:
    
};
 
#endif
