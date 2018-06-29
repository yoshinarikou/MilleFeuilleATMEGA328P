#ifndef MILLEIO_H
#define MILLEIO_H
 
#include "Arduino.h"
#include <inttypes.h>
#include "MILLE.h"

class MILLEIO {
public:
    MILLEIO(uint64_t Address, uint8_t pin[4],sDevInfo *DeviceInfomation, uint64_t connectorNumber);
    ~MILLEIO();
    getMyWire(uint64_t Address, uint8_t pin[4], uint64_t connectorNumber);
private:
    
};
 
#endif
