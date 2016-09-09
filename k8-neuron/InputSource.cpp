/*
   Input source changer for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/


#include "Arduino.h"
#include "InputSource.h"
#include "Log.h"
#include "Eprom.h"                                                        // Library to controll Eeprom

InputSource::InputSource(const int source, const int logLevel, const boolean serialLog) : eprom(logLevel, serialLog), mBus(logLevel, serialLog) {
    _source = source;
}

void InputSource::set(int newPos) {                                         // Calculating the change based on reading from different inputs
  mBus.info("Setting source to: ", String(newPos));
  int oldPos = get();
    if (newPos != oldPos)

    eprom.save(_source, newPos);                                                        // save to eeprom

}

int InputSource::get() {
  
  return eprom.get(_source);; 
}

