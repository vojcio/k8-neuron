/*
   Inputs controll for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#ifndef Inputs_h
#define Inputs_h

#include "Arduino.h"
#include "Logging.h"
#include <RotaryEncoder.h>                                                // Library for the encoder.

class Inputs
{

  public:
    Inputs(float*, int*, int, int, int, int);
    bool getVolChange();
    bool getSrcChange();
  private:
    RotaryEncoder VolEncoder;
    RotaryEncoder SrcEncoder;
    Logging mBus;
    int readRotEncVol();
    int readRotEncSrc();
    float* _volChange;
    int* _srcChange;

};
#endif
