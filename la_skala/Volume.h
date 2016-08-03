/*
   La Skala Attenuator: A ladder-type volume attenuator with Arduino control.
   Rewriten version of original project by dimdim.gr:
   Original Project Page: http://www.dimdim.gr/diyaudio/la-skala-attenuator/
   Fork mainentained by vojcio: https://github.com/vojcio/laskala
*/

#ifndef Volume_h
#define Volume_h

#include "Arduino.h"
#include <RotaryEncoder.h>                                                // Library for the encoder.
#include "Log.h"

class Volume
{
  public:
    Volume(int VOLDOWNPIN, int VOLUPPIN, float resVals[], const int logLevel, const boolean serialLog);
    int calc(float volume);
    void set(float volume);
    void increase();
    void decrease();
  private:
    RotaryEncoder encoder;
    Log mBus;
//    float volume;
//    int logLevel;
//    boolean serialLog;
    float _resVals[];
};

#endif
