#include <inttypes.h>
#include "MILLE.h"
#include "MILLEIO.h"

#define DEVICE_ADDRESS 0x80000000

uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数
sDevInfo infoDevice;  //define structure for device information.

mille myMille;//mille-feuille contorol instance.
MILLEIO myDevice(DEVICE_ADDRESS,myWire,&infoDevice,0);//AD2CH class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("---Copy following text to your .txt file---");
}

void loop() {
  unsigned int myAddr;
  unsigned int data;
  uint8_t connector;
  for(myAddr=1;myAddr<=500;++myAddr){
    infoDevice.address = infoDevice.address + 1;
    if(!myMille.detectModule(&infoDevice)){  //Find the device
      
//      Serial.write("infoDevice.address = ");
      data = infoDevice.address;
//      Serial.print(data,HEX);
//      Serial.write(" : myAddr = ");
      Serial.print(myAddr);
//      Serial.write(" I find!!\r\n");
      connector = myAddr%4-1;
      Serial.write("[");
      myDevice.getMyWire(data,myWire,connector);
      Serial.print(myWire[0]);
      Serial.write(", ");
      Serial.print(myWire[1]);
      Serial.write(", ");
      Serial.print(myWire[2]);
      Serial.write(", ");
      Serial.print(myWire[3]);
      Serial.write("]");
      Serial.write("\r\n");
    }
  }
  exit(0);
}
