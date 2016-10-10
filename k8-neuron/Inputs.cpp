/*
   Inputs controll for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/
#include "Arduino.h"
#include "Inputs.h"
#include "Logging.h"
#include <RotaryEncoder.h>

Inputs::Inputs(float* volChange, int* srcChange, float* currentVolume, int VOLDOWNPIN, int VOLUPPIN, int SRCDOWNPIN, int SRCUPPIN, int mutePin) : VolEncoder(VOLDOWNPIN, VOLUPPIN), SrcEncoder(SRCDOWNPIN, SRCUPPIN), mBus() {

  _volChange = volChange;
  _srcChange = srcChange;
  _currentVolume = currentVolume;
  _volBeforeMute = 0;
  _mutePin = mutePin;
  pinMode(VOLUPPIN, INPUT);                                               // Button switch or Encoder pin for volume up
  digitalWrite(VOLUPPIN, HIGH);                                           // If H/W debouncing is implemented, set to LOW
  pinMode(VOLDOWNPIN, INPUT);                                             // Button switch or Encoder pin for volume down
  digitalWrite(VOLDOWNPIN, HIGH);                                         // If H/W debouncing is implemented, set to LOW

  pinMode(SRCUPPIN, INPUT);                                               // Button switch or Encoder pin for src up
  digitalWrite(SRCUPPIN, HIGH);                                           // If H/W debouncing is implemented, set to LOW
  pinMode(SRCDOWNPIN, INPUT);                                             // Button switch or Encoder pin for src down
  digitalWrite(SRCDOWNPIN, HIGH);                                         // If H/W debouncing is implemented, set to LOW

}

void Inputs::initMuteButton() { //TODO: pass pins here

  pinMode(_mutePin, INPUT);
}

int Inputs::readRotEncVol() {
  VolEncoder.tick();
  return VolEncoder.getPosition();
}

int Inputs::readRotEncSrc() {
  SrcEncoder.tick();
  return SrcEncoder.getPosition();
}

int Inputs::readMuteButton() {
  int  muteButtonState = digitalRead(_mutePin);
  if (muteButtonState == HIGH) {
    return 1;
  }
}
/*int Inputs::readSerialVol() {
  if (Serial.available() > 0) {
    return Serial.read();
  }
  }
*/

bool Inputs::getMuteChange() {

  int _change = readMuteButton();                         //sum all inputs here

  if (_change > 0) {
    if (_volBeforeMute = 0) {
      _volBeforeMute = *_currentVolume;
      *_currentVolume = 128;
    } else {
      *_currentVolume = _volBeforeMute;
      _volBeforeMute = 0;
    }
    return true;
  } else {
    return false;
  }
}
bool Inputs::getVolChange() {

  int _change = readRotEncVol();                           // sum all inputs here

  if (_change != 0) {
    if (_change > 0) {
      *_volChange = 0.5;
    }
    else if (_change < 0) {
      *_volChange = -0.5;
    }
    return true;
  } else {
    return false;
  }
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
  } else {
    return false;
  }
}

