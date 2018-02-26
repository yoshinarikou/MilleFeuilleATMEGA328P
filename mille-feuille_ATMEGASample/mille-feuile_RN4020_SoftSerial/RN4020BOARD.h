#ifndef RN4020BOARD_H
#define RN4020BOARD_H
 
#include "Arduino.h"
#include <inttypes.h>
#include "MILSTRUCT.h"
#include "MILLE.h"

#define RN4020_ADDRESS 0xC0000009
//#define RN4020_ADDRESS 0x80000001
#define TYPEOFWIRE 0x02

#define IO_NUMBER 4



class RN4020BOARD {
public:
   // GPIOBOARD(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3);
    RN4020BOARD(uint8_t pin[2],sDevInfo *DeviceInfomation, uint64_t connectorNumber);
    //void getInfo(sDevInfo *DeviceInfomation,uint64_t connectorNumber);
    void flash(int n);
    int getAddress(int n);
    void testFlush(void);
private:
    uint8_t myPin[2];
  

};
 
#endif
