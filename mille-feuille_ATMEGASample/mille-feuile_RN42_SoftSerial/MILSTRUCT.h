#ifndef ___MILSTRUCT_H___
#define ___MILSTRUCT_H___

#include <inttypes.h>

#define MAX_IONUMBRE 4
#define NORMAL_IONUMBRE 4

//Type of gate
#define mCLOSEGATE 0x01//close gate
#define mOPENALLGATE 0x02//open gate normal IOs
#define mDETECTMODE_ON 0x03//Detect mode ON
#define mDETECTMODE_OFF 0x04//Detect mode OFF
#define mLED_ON 0x05//LED on
#define mLED_OFF 0x06//LED offx06://LED off
#define mSPI1 0x07//SPI gate : MOSI MISO SCK CS
#define mSPI2 0x08//One way SPI gate : MOSI SCK CS EXtra IO
#define mSPI3 0x09//SCK as a clock : SCK Extra IOs
#define mSPI4 0x0A//SPI gate : MISO SCK CS
#define mHOLD_ON 0x0B//hold mode ON
#define mHOLD_OFF 0x0C//hold mode OFF


typedef struct {
    uint64_t address;
    uint8_t location;
    uint8_t typeOfGate;
    uint8_t IOs[MAX_IONUMBRE];
    //uint8_t *IOs;
} sDevInfo;

//struct _DevInfo gpio;

#endif
