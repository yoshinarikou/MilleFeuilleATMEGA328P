#ifndef GPIOBOARD_H
#define GPIOBOARD_H
 
#include "Arduino.h"
#include <inttypes.h>
#include "MILSTRUCT.h"
#include "MILLE.h"

#define DA1CH_ADDRESS 0x80000009
//#define TYPEOFWIRE 0x08
#define IO_NUMBER 4

class DA1CH {
public:
    DA1CH(uint8_t pin0, uint8_t pin1,uint8_t pin2,uint8_t pin3);
    void setup(void);
    void write(uint16_t data);
private:
    uint8_t myPin[4];
    uint8_t typeOfPWM;//IC or PWM pins selector
    
};
 
#endif
