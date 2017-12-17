/******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier
project by vojcio: https://github.com/vojcio/k8-neuron
Inputs controll for k8-neuron
*******************************************************************************************************************/

#include "Arduino.h"
#include "Inputs.h"
#include "Logging.h"
#include "RotaryEncoder.h"
#include "pcf8574.h"

Inputs::Inputs(float* volChange, int* srcChange, float* currentVolume) : VolEncoder(_volDownPin, _volUpPin), SrcEncoder(_srcDownPin, _srcUpPin), mBus() {

  _volChange = volChange;
  _srcChange = srcChange;
  _currentVolume = currentVolume;
  _volBeforeMute = 0;

}

void Inputs::initRotEncVol(int volUpPin, int volDownPin) {
  _volUpPin = volUpPin;
  _volDownPin = volDownPin;
  pinMode(volUpPin, INPUT);                                               // Button switch or Encoder pin for volume up
  digitalWrite(volUpPin, HIGH);                                           // If H/W debouncing is implemented, set to LOW
  pinMode(volDownPin, INPUT);                                             // Button switch or Encoder pin for volume down
  digitalWrite(volDownPin, HIGH);                                         // If H/W debouncing is implemented, set to LOW
}

void Inputs::initRotEncSrc(int srcUpPin, int srcDownPin) {
  _srcUpPin = srcUpPin;
  _srcDownPin = srcDownPin;
  pinMode(srcUpPin, INPUT);                                               // Button switch or Encoder pin for src up
  digitalWrite(srcUpPin, HIGH);                                           // If H/W debouncing is implemented, set to LOW
  pinMode(srcDownPin, INPUT);                                             // Button switch or Encoder pin for src down
  digitalWrite(srcDownPin, HIGH);                                         // If H/W debouncing is implemented, set to LOW
}

void Inputs::initMuteButton(const int mutePin) { //TODO: pass pins here
  _mutePin = mutePin;
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
