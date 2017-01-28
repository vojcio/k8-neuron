
/*******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

project by vojcio: https://github.com/vojcio/k8-neuron

Library to controll persistant values for k8-neuron
*******************************************************************************************************************/

#include "Arduino.h"
#include "Eprom.h"
#include "Logging.h"
#include <EEPROM.h>

Eprom::Eprom(const int epromVolume, const int epromSource, unsigned int* currentSource, float* currentVolume) : mBus() {

  int tmp;
  EEPROM.get(0, tmp);
  if (tmp != 123) // our initial value for reference
  {
    EEPROM.write(0, 123);       // write our reference value
    EEPROM.write(1, 10);        // set initial volume to 10
    EEPROM.write(2, 1);         // set initialSrc to 1
  }

  _notified = false;
  _currentMillis = millis();
  _previousMillis = 0;
  _epromVolume = epromVolume;
  _epromSource = epromSource;
  _currentSource = currentSource;
  _currentVolume = currentVolume;
}

void Eprom::periodicInterval(unsigned int intervalSec) {
  _interval = intervalSec * 1000;
}

void Eprom::overrideCurrentVolume() {
  *_currentVolume = Eprom::get(_epromVolume);
}
void Eprom::overrideCurrentSource() {
  *_currentSource = Eprom::get(_epromSource);
}

void Eprom::save(int what, int val) {      //TODO: validate it better...
  if (val < 255) {
    if (val > 0) {
      int val2;
      EEPROM.get(what, val2);
      if (val2 != val) {
        EEPROM.write(what, val);         // TODO: do not use write!!! why update does not work???
      }
    }
  }
}

int Eprom::get(int what) {
  mBus.Info("getting value from eeprom");

  int val;
  EEPROM.get(what, val);

  //  mBus.info("value is: ", String (val));
  return val;
}

void Eprom::notify() {
  _notified = true;
}

void Eprom::periodic() {
  if (_notified = true) {
    _currentMillis = millis();
    if (_currentMillis - _previousMillis >= _interval) {
      _previousMillis = _currentMillis;
      _notified = false;

      save(_epromSource, *_currentSource);
      save(_epromVolume, *_currentVolume); //TODO: do not save volume as float..
    }
  }
}
