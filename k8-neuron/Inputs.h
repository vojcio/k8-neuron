/*
   Inputs controll for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#ifndef Inputs_h
#define Inputs_h

#include "Arduino.h"
#include "Log.h"
#include <RotaryEncoder.h>                                                // Library for the encoder.
#include "Eprom.h"

class Inputs
{

  public:
    Inputs(float*, int*, int, int, int, int);
    bool getVolChange();
    bool getSrcChange();
  private:
    RotaryEncoder VolEncoder;
    RotaryEncoder SrcEncoder;
    Log mBus;
    Eprom eprom;
    int readRotEncVol();
    int readRotEncSrc();
    float* _volChange;
    int* _srcChange;

};
#endif
