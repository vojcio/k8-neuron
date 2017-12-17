/*******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

project by vojcio: https://github.com/vojcio/k8-neuron

Input source changer for k8-neuron

*******************************************************************************************************************/

#ifndef InputSource_h
#define InputSource_h

#include "Arduino.h"
#include "Logging.h"
#include "pcf8574.h"

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
