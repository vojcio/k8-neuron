/*
   Inputs controll for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/
#include "Arduino.h"
#include "Inputs.h"
#include "Log.h"
#include "Eprom.h"
#include <RotaryEncoder.h>

Inputs::Inputs(int VOLDOWNPIN, int VOLUPPIN, int SRCDOWNPIN, int SRCUPPIN, const int logLevel, const boolean serialLog) : VolEncoder(VOLDOWNPIN, VOLUPPIN), SrcEncoder(SRCDOWNPIN, SRCUPPIN), mBus(logLevel, serialLog), eprom(logLevel, serialLog) {

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
  int srcActual = eprom.get(2);                                         // get source
  int srcChange = SrcEncoder.getPosition();
  if (srcChange != 0) {
    if (srcChange > 0) {
      srcActual++;
    } else {
      srcActual--;
    }
    return srcActual;
  }
}

int Inputs::readSerial() {
  if (Serial.available() > 0) {
    return Serial.read();
  }
}

int Inputs::getVolChange() {
      mBus.info("reading if volume should be changed...", "");
      
      int _change = readRotEncVol();                           // sum all inputs
      // we will return 1 or -1
      if (_change =! 0) {
        if (_change > 0) {
          _change = 1;
        }
        else if (_change < 0) {
          _change = -1;
        }
      }
    return _change;
}

int Inputs::getNewSource() {
            mBus.info("reading if source should be changed...", "");
           

     return readRotEncSrc();
}


