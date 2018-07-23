#include <BnrOneA.h>
#include <EEPROM.h>
#include <SPI.h>
BnrOneA one;

int lVal = 0;
int rVal = 0;
bool leftRight = false;

#define SSPIN 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  one.spiConnect(SSPIN);
  one.stop();
  one.obstacleEmitters(true);
}

void loop() {
  switch(one.readButton()) {
    case 0:
       break; 
    case 1:
       if(leftRight) {
         rVal++; 
       } else {
         lVal++; 
       }
       break; 
    case 2:
       if(leftRight) {
         rVal--; 
       } else {
         lVal--; 
       }
       break;
    case 3:
       leftRight = !leftRight;
       break; 
  }
  
  if(leftRight) {
    one.lcd2("Right"); 
  } else {
    one.lcd2("Left"); 
  }
  
  one.lcd1(lVal, rVal); 
  
  // put your main code here, to run repeatedly:
  int sensor = one.obstacleSensors();
  if(sensor == 0){
    one.move(lVal,rVal);
    //Serial.print("No objects detected");
    //one.lcd1("No objects detected");
  }
  else {
    one.move(0,0);
    one.brake(100,100);
    //Serial.print("Object detected");
    //one.lcd1("Object detected");
  }
}
