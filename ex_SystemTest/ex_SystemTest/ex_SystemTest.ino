#include <BnrOneA.h>
#include <EEPROM.h>
#include <SPI.h>
BnrOneA one;

#define SSPIN 2

int curTest = 1;
boolean testEmitters = false;
boolean testSerial = false;

void testOne() {
  one.lcd1("PRESS PB1");
  one.lcd2("If this looks okay");
}

void testTwo() {
  one.lcd1("PRESS PB2");
  one.lcd2("");
}

void testThree() {
  one.lcd1("PRESS PB3");
  one.lcd2("");
}

void testFour() {
  one.lcd1("PB1 to OK each test");
  one.lcd2("");
}

void testFive() {
  one.obstacleEmitters(true);
  testEmitters = true;
  one.lcd1("Emitters ON");
  one.lcd2("True = Wheels Spin");
}

void testSix() {
  one.obstacleEmitters(false);
  testEmitters = true;
  one.lcd1("Emitters OFF");
  one.lcd2("True = NOTHING");
}

void testSeven() {
  testEmitters = false;
  one.lcd1("L Forward");
  one.lcd2("=-)");
  one.move(100, 0);
}

void testEight() {
  one.lcd1("L Backward");
  one.lcd2("XD");
  one.move(-100, 0);
}

void testNine() {
  one.lcd1("R Forward");
  one.lcd2("LOL");
  one.move(0, 100);
}

void testTen() {
  one.lcd1("R Backward");
  one.lcd2(";-)");
  one.move(0, -100);
}

void testEleven() {
  one.lcd1("Serial IO");
  one.lcd2("HELLO WORLD");
  one.move(0, 0);
  testSerial = true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  one.spiConnect(SSPIN);
  one.stop();
}

void loop() {
  switch(curTest) {
    case 1:
      testOne();
      break;
    case 2:
      testTwo();
      break;
    case 3:
      testThree();
      break;
    case 4:
      testFour();
      break;
    case 5:
      testFive();
      break;
    case 6:
      testSix();
      break;
    case 7:
      testSeven();
      break;
    case 8:
      testEight();
      break;
    case 9:
      testNine();
      break;
    case 10:
      testTen();
      break;
    case 11:
      testEleven();
      break;
  }
  
  byte button = one.readButton();
  switch(curTest) {
    case 1:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
      if(button == 1) curTest++;
      break;
    case 2:
      if(button == 2) curTest++;
      break;
    case 3:
      if(button == 3) curTest++;
      break;
  }
  
  if(testEmitters) {
    switch(one.obstacleSensors()) {
       case 0:
           one.move(0, 0);
           break;
       case 1:
           one.move(100, 0);
           break;
       case 2:
           one.move(0, 100);
           break;
       case 3:
           one.move(100, 100);
           break;
    }
  }
  
  if(testSerial)  Serial.print("Hello World!\n");
  delay(50);
}
