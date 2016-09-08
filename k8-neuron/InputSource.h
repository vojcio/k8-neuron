/*
   Input source changer for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#ifndef InputSource_h
#define InputSource_h

#include "Arduino.h"
#include "Log.h"

class InputSource 
{

  public:
    InputSource(const int logLevel, const boolean serialLog);
    void change(int newPos);
  private:
    Log mBus;

};
#endif
