/*
   Library to controll persistant values for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#include "Arduino.h"
#include "Eprom.h"
#include "Log.h"
#include <EEPROM.h>

Eprom::Eprom() : mBus() {

  int tmp;
  EEPROM.get(0, tmp);
  if (tmp != 123) // our initial value for reference
  {
    EEPROM.write(0, 123);       // write our reference value
    EEPROM.write(1, 10);        // set initial volume to 10
    EEPROM.write(2, 1);         // set initialSrc to 1
  }
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
  mBus.info("getting value from eeprom: ", String(what));

  int val;
  EEPROM.get(what, val);

  mBus.info("value is: ", String (val));
  return val;
}

