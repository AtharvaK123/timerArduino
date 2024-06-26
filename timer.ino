#include "SevSeg.h"
SevSeg sevseg;

#define totalCount 600
int counter = totalCount;

int buzzer = 8;

#define delayTime 1000

void setup()
{
  pinMode(buzzer, OUTPUT);

  byte numDigits = 4;
  
  byte digitPins[] = {50, 51, 52, 53};
  byte segmentPins[] = {42, 43, 44, 45, 46, 47, 48, 49};
  
  bool resistorsOnSegments = false;
  
  byte hardwareConfig = COMMON_CATHODE;
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  
  sevseg.setBrightness(30);
  
  sevseg.blank();
}

void loop() {
  static unsigned long timer = millis();
  static unsigned long buzzerTimer = 0;
  static bool buzzerOn = false;
  static bool countOn = true;

  if (millis() - timer >= delayTime) {
    if(counter % 2 == 0) {
      sevseg.setNumber(counter, 0);
    } else {
      sevseg.setNumber(counter, -1);
    }

    digitalWrite(buzzer, HIGH);
    buzzerTimer = millis();
    buzzerOn = true;

    if(counter > 0) {
      counter--;
    } else {
      countOn = false;
    }

    timer = millis();
  }

  if (buzzerOn && millis() - buzzerTimer >= 800 && countOn == true) {
    digitalWrite(buzzer, LOW);
    buzzerOn = false;
  }

  sevseg.refreshDisplay();
}
