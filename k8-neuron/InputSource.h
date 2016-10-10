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
    InputSource(int*, unsigned int);
    void change();
  private:
    Log mBus;
    Eprom eprom;
    int* _srcChange;
    unsigned int _maxSrc;
    unsigned int _source;
    void set();

};
#endif
