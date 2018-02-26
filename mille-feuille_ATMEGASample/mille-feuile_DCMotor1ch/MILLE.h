#ifndef ___MILLE_H___
#define ___MILLE_H___
 
#include "Arduino.h"
#include <inttypes.h>
#include "MILSTRUCT.h"
#include <SPI.h>

#define BASE_ADDRESS 0x80000000
#define SPECIAL_ADDRESS 0xC0000000
#define DETECTMODE_ON 0x03
#define DETECTMODE_OFF 0x04


class mille {
  public:
    mille(void);
    void order(uint32_t const myAddress, uint8_t myData1, uint8_t myData2);
    uint8_t detectModule(sDevInfo *myDevInfo);
    uint8_t readInputData(void);
    void connect(sDevInfo *myDevInfo);
    void disconnect(sDevInfo *myDevInfo);
    void holdConnect(sDevInfo *myDevInfo);
    void holdDisconnect(sDevInfo *myDevInfo);
  private:
    uint8_t _MOSI;
    uint8_t _MISO;
    uint8_t _SCK;
    uint8_t _ncs;
    uint8_t _in1;
    uint8_t _in2;
    uint8_t _in3;
    //uint8_t _in4;
};
 
#endif
