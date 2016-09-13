/*
   Library to controll persistant values for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/


#ifndef Eprom_h
#define Eprom_h

#include "Arduino.h"
#include "Log.h"
#include <EEPROM.h>

class Eprom
{

  public:
    Eprom(const int logLevel, const boolean serialLog);
    void save(int what, int val);
    int get(int what);
  private:
    Log mBus;
};
#endif
