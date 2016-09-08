/*
   Inputs controll for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/
#include "Arduino.h"
#include "Inputs.h"
#include "Log.h"
#include <RotaryEncoder.h>

Inputs::Inputs(int VOLDOWNPIN, int VOLUPPIN, int SRCDOWNPIN, int SRCUPPIN, const int logLevel, const boolean serialLog) : VolEncoder(VOLDOWNPIN, VOLUPPIN), SrcEncoder(SRCDOWNPIN, SRCUPPIN), mBus(logLevel, serialLog) {

  pinMode(VOLUPPIN, INPUT);                                               // Button switch or Encoder pin for volume up
  digitalWrite(VOLUPPIN, HIGH);                                           // If H/W debouncing is implemented, set to LOW
  pinMode(VOLDOWNPIN, INPUT);                                             // Button switch or Encoder pin for volume down
  digitalWrite(VOLDOWNPIN, HIGH);                                         // If H/W debouncing is implemented, set to LOW

  pinMode(SRCUPPIN, INPUT);                                               // Button switch or Encoder pin for src up
  digitalWrite(SRCUPPIN, HIGH);                                           // If H/W debouncing is implemented, set to LOW
  pinMode(SRCDOWNPIN, INPUT);                                             // Button switch or Encoder pin for src down
  digitalWrite(SRCDOWNPIN, HIGH);                                         // If H/W debouncing is implemented, set to LOW
  
}
int Inputs::readRotEncVol() {
  VolEncoder.tick();
  mBus.info("reading volume rotary encoder", "");
  return VolEncoder.getPosition();
}

int Inputs::readRotEncSrc() {
  SrcEncoder.tick();
  mBus.info("reading src rotary encoder", "");
  return SrcEncoder.getPosition();
}

int Inputs::getChange(int ofWhat) {

      int change = 0;
      switch (ofWhat) {
        case 1:
          mBus.info("reading if volume should be changed...", "");
          change = readRotEncVol();                           // sum all inputs
        break;
        case 2:
          mBus.info("reading if source should be changed...", "");
          change = readRotEncSrc();                           // sum all inputs
        break;
        default:
          mBus.error("Didn't recognized what input should be changed.", "");
        break;
      }
      // we will return 1 or -1
      if (change =! 0) {
        if (change > 0) {
          change = 1;
        }
        else if (change < 0) {
          change = -1;
        }
      }
      return change;
}




