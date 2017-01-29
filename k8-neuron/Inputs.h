
/*******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

project by vojcio: https://github.com/vojcio/k8-neuron

Inputs controll for k8-neuron

*******************************************************************************************************************/


#ifndef Inputs_h
#define Inputs_h

#include "Arduino.h"
#include "Logging.h"
#include "libraries/RotaryEncoder.h"

class Inputs
{

  public:
    Inputs(float*, int*, float*);
    void initMuteButton(const int);
    void initRotEncVol(int, int);
    void initRotEncSrc(int, int);
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
    int _volUpPin;
    int _volDownPin;
    int _srcUpPin;
    int _srcDownPin;

};
#endif
