#ifndef IRSEND_H
#define IRSEND_H

#include <inttypes.h>

class IRSEND {
  public:
    // constructor
    IRSEND(uint8_t ledPin);
    void sendNECCommand(uint8_t data, uint8_t custom0, uint8_t custom1);
    void sendData(uint8_t date);
  private:
    uint8_t _ledPin;   // the pin number which the LED is connected
    uint8_t _custom0;  // custom code 
    uint8_t _custom1;  // custom code
    void on(int num);
};
#endif
