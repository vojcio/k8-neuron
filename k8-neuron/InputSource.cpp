/*
   Input source changer for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/


#include "Arduino.h"
#include "InputSource.h"
#include "Log.h"
#include "Eprom.h"                                                        // Library to controll Eeprom

InputSource::InputSource(int* srcChange, unsigned int maxSrc) : eprom(), mBus() {
  _srcChange = srcChange;
  _source = 1;
  _maxSrc = maxSrc;
}

void InputSource::change() {
  
  _source += *_srcChange;
  
  if(_source <= 0) {
    _source = _maxSrc;
  }  else if(_source > _maxSrc) {
    _source = 1;
  }
  set();
        //eprom.save(2, newSource);                                                        // save to eeprom
}

void InputSource::set() {
    // TODO: mcp
}

