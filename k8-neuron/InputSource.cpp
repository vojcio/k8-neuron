/*
   Input source changer for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/


#include "Arduino.h"
#include "InputSource.h"
#include "Log.h"
#include "Eprom.h"                                                        // Library to controll Eeprom

InputSource::InputSource(const int logLevel, const boolean serialLog) : eprom(logLevel, serialLog), mBus(logLevel, serialLog) {

}

void InputSource::set(int newSource) {                                         // Calculating the change based on reading from different inputs
  mBus.info("Setting source to: ", String(newSource));
  int oldPos = eprom.get(2);
    if (newSource != oldPos)

    eprom.save(2, newSource);                                                        // save to eeprom
    //TODO: mcp...

}

