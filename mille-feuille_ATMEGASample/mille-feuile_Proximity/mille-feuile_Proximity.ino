#include <inttypes.h>
#include "MILLE.h"
#include "MILLEIO.h"

#define PROXIMITY_ADDRESS 0x80000029

sDevInfo infoPROXIMITY;  //define structure for device information.
uint8_t myWire[4];  //The wire for device.配線の情報を格納する変数

mille myMille;//mille-feuille contorol instance.
MILLEIO myPROXIMITY(PROXIMITY_ADDRESS, myWire, &infoPROXIMITY, 0);//AD2CH class instance.ベースボードのコネクタ番号0につながっているデバイスのインスタンスを生成します

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(myMille.detectModule(&infoPROXIMITY)){  //Find the device
    exit(0);    //device conection error
  }
  pinMode(myWire[0],OUTPUT);
  pinMode(myWire[1],INPUT);
}

void loop() {
    myMille.connect(&infoPROXIMITY);//wire from MCU to device. デバイスと配線を接続、この後は普通にArduinoのコードで走ります。
    
    digitalWrite(myWire[0],HIGH);//LED ON
    //delay(1);
    int data = digitalRead(myWire[1]);
    Serial.write("data = ");
    Serial.print(data);
    Serial.write("\r\n");
    
    myMille.disconnect(&infoPROXIMITY);//別のデバイスに接続する前に接続断をします。
    delay(1000);
}
