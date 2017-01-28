/*******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

project by vojcio: https://github.com/vojcio/k8-neuron

Library to controll persistant values for k8-neuron
*******************************************************************************************************************/



#ifndef Eprom_h
#define Eprom_h

#include "Arduino.h"
#include "Logging.h"
#include <EEPROM.h>

class Eprom
{

  public:
    Eprom(const int, const int, unsigned int*, float*);
    void periodicInterval(unsigned int);
    void periodic();
    void notify();
    void overrideCurrentVolume();
    void overrideCurrentSource();
  private:
    Logging mBus;
    bool _notified;
    unsigned long _currentMillis;
    unsigned long _previousMillis;
    unsigned int _interval;
    unsigned int* _currentSource;
    float* _currentVolume;
    int _epromVolume;
    int _epromSource;
    int get(int what);
    void save(int what, int val);
};
#endif
