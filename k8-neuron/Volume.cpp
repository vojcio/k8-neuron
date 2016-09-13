/*
   La Skala Attenuator: A ladder-type volume attenuator with Arduino control.
   Heavily rewritten version of original project by dimdim.gr:
   Original Project Page: http://www.dimdim.gr/diyaudio/la-skala-attenuator/
   Mainentained by vojcio: https://github.com/vojcio/k8-neuron
*/

#include "Arduino.h"
#include "Volume.h"
#include "Log.h"
#include "Adafruit_MCP23008.h"                                            // Library for the I/O expander.

Volume::Volume(float resVals[], const int logLevel, const boolean serialLog) : mBus(logLevel, serialLog), mcp() {

	memcpy( _resVals, resVals, 8 );
	int _changeRelaysCurrent = 0;						                                // number of relays to be changed
	int _changeRelaysPrev = 0;
	boolean _relay[8] = {0, 0, 0, 0, 0, 0, 0, 0};				                    // relays status
	mcp.begin();                                                            // use default address 0
	for(int i = 0; i<8; i++) { mcp.pinMode(i, OUTPUT); }                    // Set all pin's to OUTPUT mode
	float _volume = 0;
}

void Volume::change(int newPos) { 						                            // Calculating the change based on reading from different inputs
  static int pos = 0;                                                     // Read the rotary encoder and increase or decrease attenuation.
  if (pos != newPos) {
    if (pos < newPos) {
      if (_volume > 0) {
        _volume = _volume - 0.5;
      }
    }
    else if (pos > newPos) {
      if (_volume < 127) {
        _volume = _volume + 0.5;
      } 
    }
  }
  else {
    mBus.error("Rotary encoder unknown change: ", String(newPos));  
  }
  set(_volume);
}

void Volume::set(float volume) {					// setting the volume to fixed value, between 0 and 127
    mBus.info("Setting volume to: ", String(volume));
    float volTemp = volume;

    for (int i = 0 ; i < 8 ; i++)
    {
      if (volTemp >= _resVals[i])
      {
        _relay[i] = 1;
        _changeRelaysCurrent++;
        volTemp = volTemp - _resVals[i];
        mBus.info("Volume will be set to: ", String(volume));
      } else {
        _relay[i] = 0;
      }
    }

  if (volTemp > volume) { increase(); }
  else if (volTemp < volume) { decrease(); }
}

void Volume::increase() {
  for (int i = 0; i < 8 ; i++) {
    if (_relay[i] == 0)
      {
        mcp.digitalWrite(i, LOW);
        mBus.info("(increasingVol ; Scheduling relay to disable: ", String(_relay[i]));
      }
      else mcp.digitalWrite(i, HIGH);
      mBus.info("(increasingVol ; Scheduling relay to enable: ", String(_relay[i]));
   }
}

void Volume::decrease() {
  for (int i = 8; i > 0 ; i--) {
    if (_relay[i] == 0) {
      mcp.digitalWrite(i, LOW);
      mBus.info("(decreaseingVol ; Scheduling relay to disable: ", String(_relay[i]));
    }
    else mcp.digitalWrite(i, HIGH);
    mBus.info("(decreaseingVol ; Scheduling relay to enable: ", String(_relay[i]));
    delay(relDelay());
  }
}

int Volume::relDelay() {
    int diff = _changeRelaysCurrent - _changeRelaysPrev;                // count how many relays will be switched TODO: maybe it is possible to count the "1s" in array? and avoid this complicated function
  int _relDelay = 0;

    mBus.info("Difference in switched relays: ", String(diff));        // Determine how many relays will be switching states.

    if (diff <= 3) { _relDelay = 0; }                                   // When a large number of relays is expected to switch states,
    if (diff == 4) { _relDelay = 5; }                                   // introduce a delay between activations to ease the burden
    if (diff == 5) { _relDelay = 10;}                                   // of the power supply (and decrease switching noise).
    if (diff == 6) { _relDelay = 20;}
    if (diff >= 7) { _relDelay = 50;}

    mBus.info("Inrtoducing delay of: ", String(_relDelay));

    _changeRelaysPrev = _changeRelaysCurrent;
    return _relDelay;
}
