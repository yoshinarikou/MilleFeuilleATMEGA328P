#include "Arduino.h"
#include "IRSEND.h"

IRSEND::IRSEND(uint8_t ledPin) {
  _ledPin = 1 << ledPin;
   
  pinMode(ledPin, OUTPUT);  // set the ledPin as an OUTPUT
}
 
void IRSEND::sendNECCommand(uint8_t data, uint8_t custom0, uint8_t custom1){
  
  _custom0 = custom0;
  _custom1 = custom1;
  on(346);                  // leader code(ON) 346x26usec = 8996usec about 8992usec
  delayMicroseconds(4500);  // leader code(OFF) 4.5msec 
   
  sendData(_custom0);       // custom code
  sendData(_custom1);       // custom code
   
  sendData(data);           // data
  sendData(~data);          // ~data
   
  on(22);                   // stop bit
}
 
void IRSEND::sendData(uint8_t data) {
  for(int i = 0; i < 8; i++) {
    on(22);
    switch(data & 1) {
    case 0:
      delayMicroseconds(565);
      break;
    case 1:
      delayMicroseconds(1690);
      break;
    }
    data = data >> 1;
  }
}
 
void IRSEND::on(int num) {
  for(int i = 0; i < num; i++) {
    PORTD |= _ledPin;
    delayMicroseconds(9);
    PORTD &= ~_ledPin;
    delayMicroseconds(17);
  }
}
