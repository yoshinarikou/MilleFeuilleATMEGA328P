#include <inttypes.h>
#include "MILLEIO.h"
#include "MILLE.h"
#include <Stepper.h>

#define UNISTEP_ADDRESS 0x8000001D

mille myMille;//mille-feuille contorol instance.
sDevInfo infoUNISTEP;  //define structure for device information.

const float turnSteps = 360;
float Steps = 360; 
float rpm = 5;

uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数 
MILLEIO myUNISTEP(UNISTEP_ADDRESS, myWire,&infoUNISTEP,0);//Class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します
Stepper myStepper0(turnSteps, myWire[0],myWire[1],myWire[2],myWire[3]);

void setup() {
  // put your setup code here, to run once:
  if(myMille.detectModule(&infoUNISTEP)){  //Find the device
    exit(0);    //device conection error
  }
  myStepper0.setSpeed(10); //1rpm
}

void loop() {
  myMille.connect(&infoUNISTEP);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  
  myStepper0.step(Steps);
  
  myMille.disconnect(&infoUNISTEP);//別のデバイスに接続する前に接続断をします。
  delay(1000);    
}
