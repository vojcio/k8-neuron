/*
   Input source changer for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#ifndef InputSource_h
#define InputSource_h

#include "Arduino.h"
#include "Log.h"
#include "Eprom.h"                                                        // Library to controll Eeprom

class InputSource 
{

  public:
    InputSource();
    void set(const int source);
  private:
    Log mBus;
    Eprom eprom;
    int _source;

};
#endif
