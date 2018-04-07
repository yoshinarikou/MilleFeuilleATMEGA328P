#ifndef ___MILLE_FEUILLE_H___
#define ___MILLE_FEUILLE_H___
 
#include "MILLE.h"

//////////////
//IO setting//
//////////////
#define ARDUNOUNO
//#define ESP32

#define NUM_OUTPUT 6
#define NUM_INPUT 5

#ifdef ARDUNOUNO
#define mySoftTX 3
#define mySoftRX 2
#define myMOSI 11
#define myMISO 12
#define mySCK 13
#define myNCS 10
#define mySDA 18
#define mySCL 19
#define myNC 0
#endif

#ifdef ESP32
uint8_t myOutPin[NUM_OUTPUT] = {16,15,13,14,12,27,2,34};
uint8_t myInPin[NUM_INPUT] = {17,4,0,35};
uint8_t myMOSI = 23;
uint8_t myMISO = 19;
uint8_t mySCK = 18;
uint8_t myNCS= 5;
#endif


void getWireSetting(uint8_t myPin[4],sDevInfo *DeviceInfomation);
void getWire(uint64_t myAddress, uint8_t *wire, uint8_t connectorNo);
#endif
