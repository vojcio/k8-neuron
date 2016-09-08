/*
   La Skala Attenuator: A ladder-type volume attenuator with Arduino control.
   Heavily rewritten version of original project by dimdim.gr:
   Original Project Page: http://www.dimdim.gr/diyaudio/la-skala-attenuator/
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#ifndef Volume_h
#define Volume_h

#include "Arduino.h"
#include "Log.h"							                                            // Logging message bus
#include "Adafruit_MCP23008.h"                                            // Library for the I/O expander.

class Volume
{
  public:
    Volume(float resVals[], const int logLevel, const boolean serialLog);
    void set(float volume);
    void change(int newPos);
  private:
    Log mBus;
    Adafruit_MCP23008 mcp;
    void increase();
    void decrease();
    float _resVals[];
    int _changeRelaysCurrent;
    int _changeRelaysPrev;
    int _relDelay;
    int relDelay();
    boolean _relay[];
    float _volume;
};

#endif
