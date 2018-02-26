#include <inttypes.h>
#include "ADC121S021.h"
#include "MILLE.h"
#include "MILLEIO.h"

#define MOISTURE_ADDRESS 0x80000031

uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数
sDevInfo infoADC12_0;  //define structure for device information. デバイスの情報を格納する構造体

mille myMille;//mille-feuille contorol instance. ミルフィーユのコントローラー
MILLEIO myADC121S021IO(MOISTURE_ADDRESS,myWire,&infoADC12_0,0); //get device IO information MILLEIO, connector number on baseboard is zero.ベースボードのコネクタ番号0につながっているデバイスの配線情報を呼び出します。

ADC121S021 myADC12_0(myWire[0],myWire[1],myWire[2],myWire[3]);//ADC121S021 sensor Libraly.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myADC12_0.setup();
  if(myMille.detectModule(&infoADC12_0)){  //Find the device
    exit(0);    //device conection error
  }
}

void loop() {
  myMille.connect(&infoADC12_0);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
  
  int data = myADC12_0.read();  //fsample = 200Kps maximum.
  
  Serial.write("data = ");
  Serial.print(data);
  Serial.write("\r\n");
  
  myMille.disconnect(&infoADC12_0);//別のデバイスに接続する前に接続断をします。
  delay(1000);

    
}
