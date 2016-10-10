/*
   Input source changer for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#ifndef InputSource_h
#define InputSource_h

#include "Arduino.h"
#include "Logging.h"

class InputSource
{

  public:
    InputSource(int*, unsigned int*, unsigned int);
    void change();
    void set();
  private:
    Logging mBus;
    int* _srcChange;
    unsigned int _maxSrc;
    unsigned int* _source;

};
#endif
