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
    Inputs(float*, int*, float*, int, int, int, int, int);
    void initMuteButton();
    bool getVolChange();
    bool getSrcChange();
    bool getMuteChange();
  private:
    RotaryEncoder VolEncoder;
    RotaryEncoder SrcEncoder;
    Logging mBus;
    int readRotEncVol();
    int readRotEncSrc();
    int readMuteButton();
    float* _volChange;
    int* _srcChange;
    float _volBeforeMute;
    float* _currentVolume;
    int _mutePin;

};
#endif
