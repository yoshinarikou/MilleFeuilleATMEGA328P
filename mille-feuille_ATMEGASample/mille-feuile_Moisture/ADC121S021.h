#ifndef ___ADC121S021_H___
#define ___ADC121S021_H___
 
#include "Arduino.h"
#include <inttypes.h>
#include "MILSTRUCT.h"
#include "MILLE.h"

class ADC121S021 {
public:
    ADC121S021(uint8_t pin0,uint8_t pin1,uint8_t pin2,uint8_t pin3);
    void setup(void);
    int read(void);
private:
    uint8_t myPin[4];
    uint8_t typeOfAD;//IC or AD pin selector
    
};
 
#endif
