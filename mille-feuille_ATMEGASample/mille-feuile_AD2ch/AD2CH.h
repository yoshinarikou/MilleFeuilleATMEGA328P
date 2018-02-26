#ifndef GPIOBOARD_H
#define GPIOBOARD_H
 
#include "Arduino.h"
#include <inttypes.h>
#include "MILSTRUCT.h"
#include "MILLE.h"

#define AD2ch_ADDRESS 0x80000005  
//#define TYPEOFWIRE 0x07
//#define IO_NUMBER 4

class AD2CH {
public:
    AD2CH(uint8_t pin0, uint8_t pin1,uint8_t pin2,uint8_t pin3);
    void setup(void);
    int read(uint8_t ch);
    int readSimpleDiff(void);//pseudo-differential pairs 疑似差動入力関数
private:
    int readDiff(uint8_t PN);
    uint8_t myPin[4];
    uint8_t typeOfAD;//MCP3202 or AD pins selector
    
};
 
#endif
