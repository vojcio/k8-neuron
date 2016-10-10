/*
   Inputs controll for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/
#include "Arduino.h"
#include "Inputs.h"
#include "Log.h"
#include "Eprom.h"
#include <RotaryEncoder.h>

Inputs::Inputs(float* volChange, int* srcChange, int VOLDOWNPIN, int VOLUPPIN, int SRCDOWNPIN, int SRCUPPIN) : VolEncoder(VOLDOWNPIN, VOLUPPIN), SrcEncoder(SRCDOWNPIN, SRCUPPIN), mBus(), eprom() {

  _volChange = volChange;
  _srcChange = srcChange;
  
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
  return SrcEncoder.getPosition();
}

/*int Inputs::readSerialVol() {
  if (Serial.available() > 0) {
    return Serial.read();
  }
}
*/
bool Inputs::getVolChange() {
      
      int _change = readRotEncVol();                           // sum all inputs here
      
      *_volChange = 0;                                        // reset variable
      
      if (_change != 0) {
        if (_change > 0) {
          *_volChange = 0.5;
        }
        else if (_change < 0) {
          *_volChange = -0.5;
        }
        return true;
      } else { return false; }
}

bool Inputs::getSrcChange() {      

  int _change = readRotEncSrc();                            // sum all inputs here

  *_srcChange = 0;
  
  if (_change != 0) {
    if (_change > 0) {
      *_srcChange = 1;
     } else {
      *_srcChange = -1;
    }
    return true;
  } else { return false; }
}  

