/*******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

project by vojcio: https://github.com/vojcio/k8-neuron

Credits:
La Skala Attenuator: A ladder-type volume attenuator with Arduino control.
Heavily rewritten version of original project by dimdim.gr:
Original Project Page: http://www.dimdim.gr/diyaudio/la-skala-attenuator/
*******************************************************************************************************************/

#ifndef Volume_h
#define Volume_h

#include "Arduino.h"
#include "Logging.h"							                                            // Logging message bus
//#include "libraries/Adafruit_MCP23008.h"                                            // Library for the I/O expander.

class Volume
{
  public:
    Volume(float resVals[], float*, float*);
    void set();
    void change();
    void initMcp();
  private:
    Logging mBus;
//    Adafruit_MCP23008 mcp;
    void increase();
    void decrease();
    float _resVals[];
    int _changeRelaysCurrent;
    int _changeRelaysPrev;
    int _relDelay;
    int relDelay();
    boolean _relay[];
    float* _volume;
    float* _volChange;
};

#endif
