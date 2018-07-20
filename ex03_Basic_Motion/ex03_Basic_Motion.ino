#include <BnrOneA.h>
#include <EEPROM.h>
#include <SPI.h>
BnrOneA one;

#define SSPIN 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  one.spiConnect(SSPIN);
  one.stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor = one.obstacleSensors();
  if(sensor == 0){
    one.move(50,50);
    Serial.print("No objects detected");
    one.lcd1("No objects detected");
  }
  else {
    one.brake(50,50);
    Serial.print("Object detected");
    one.lcd1("Object detected");
  }
}
