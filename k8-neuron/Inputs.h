/*
   Inputs controll for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#ifndef Inputs_h
#define Inputs_h

#include "Arduino.h"
#include "Log.h"
#include <RotaryEncoder.h>                                                // Library for the encoder.

class Inputs
{

  public:
    Inputs(int VOLDOWNPIN, int VOLUPPIN, int SRCDOWNPIN, int SRCUPPIN, const int logLevel, const boolean serialLog);
    int getVolChange();
    int getSrcChange();
  private:
    RotaryEncoder VolEncoder;
    RotaryEncoder SrcEncoder;
    Log mBus;
    int readRotEncVol();
    int readRotEncSrc();
    void volChange();

};
#endif
