/*******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

project by vojcio: https://github.com/vojcio/k8-neuron

Input source changer for k8-neuron

*******************************************************************************************************************/

#include "Arduino.h"
#include "InputSource.h"
#include "Logging.h"
// Library to controll Eeprom

InputSource::InputSource(int* srcChange, unsigned int* currentSource, unsigned int maxSrc) : mBus() {
  _srcChange = srcChange;
  _source = currentSource;
  _maxSrc = maxSrc;
}

void InputSource::change() {

  *_source += *_srcChange;
  set();
  *_srcChange = 0;
}

void InputSource::set() {

  if (*_source <= 0) {
    *_source = _maxSrc;
  }  else if (*_source > _maxSrc) {
    *_source = 1;
  }
  // TODO: mcp set *_source
}
