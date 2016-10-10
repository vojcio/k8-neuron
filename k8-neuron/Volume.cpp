/*
   La Skala Attenuator: A ladder-type volume attenuator with Arduino control.
   Heavily rewritten version of original project by dimdim.gr:
   Original Project Page: http://www.dimdim.gr/diyaudio/la-skala-attenuator/
   Mainentained by vojcio: https://github.com/vojcio/k8-neuron
*/

#include "Arduino.h"
#include "Volume.h"
#include "Logging.h"
#include "Adafruit_MCP23008.h"                                            // Library for the I/O expander.

Volume::Volume(float resVals[], float* volChange, float* currentVolume) : mBus(), mcp() {

  _volChange = volChange;
  _volume = currentVolume;
  memcpy(_resVals, resVals, 8);
  int _changeRelaysCurrent = 0;						                                // number of relays to be changed
  int _changeRelaysPrev = 0;
  boolean _relay[8] = {0, 0, 0, 0, 0, 0, 0, 0};				                    // relays status
}

void Volume::initMcp() {
  mcp.begin();                                                            // use default address 0
  for (int i = 0; i < 8; i++) {
    mcp.pinMode(i, OUTPUT);  // Set all pin's to OUTPUT mode
  }
}

void Volume::change() { 						                            // Calculating the change based on reading from different inputs

  *_volume += *_volChange;
  set();
}

void Volume::set() {					// setting the volume to fixed value, between 0 and 127

  if (*_volume < 0) {
    *_volume = 0;
  }
  if (*_volume > 127) {
    *_volume = 127;
  }
  if (*_volume > 0 and * _volume < 127) {

    mBus.Info("Setting volume to: %d", *_volume);
    float volTemp = *_volume;

    for (int i = 0 ; i < 8 ; i++)
    {
      if (volTemp >= _resVals[i])
      {
        _relay[i] = 1;
        _changeRelaysCurrent++;
        volTemp = volTemp - _resVals[i];
        mBus.Info("Volume will be set to: %d", *_volume);
      } else {
        _relay[i] = 0;
      }
    }

    if (volTemp > *_volume) {
      increase();
    }
    else if (volTemp < *_volume) {
      decrease();
    }
  }
}

void Volume::increase() {
  for (int i = 0; i < 8 ; i++) {
    if (_relay[i] == 0)
    {
      mcp.digitalWrite(i, LOW);
      mBus.Info("(increasingVol ; Scheduling relay to disable: %d", _relay[i]);
    }
    else mcp.digitalWrite(i, HIGH);
    mBus.Info("(increasingVol ; Scheduling relay to enable: %d", _relay[i]);
  }
}

void Volume::decrease() {
  for (int i = 8; i > 0 ; i--) {
    if (_relay[i] == 0) {
      mcp.digitalWrite(i, LOW);
      mBus.Info("(decreaseingVol ; Scheduling relay to disable: %d", _relay[i]);
    }
    else mcp.digitalWrite(i, HIGH);
    mBus.Info("(decreaseingVol ; Scheduling relay to enable: %d", _relay[i]);
    delay(relDelay());
  }
}

int Volume::relDelay() {
  int diff = _changeRelaysCurrent - _changeRelaysPrev;                // count how many relays will be switched TODO: maybe it is possible to count the "1s" in array? and avoid this complicated function
  int _relDelay = 0;

  mBus.Info("Difference in switched relays: %d", diff);        // Determine how many relays will be switching states.

  if (diff <= 3) {
    _relDelay = 0;  // When a large number of relays is expected to switch states,
  }
  if (diff == 4) {
    _relDelay = 5;  // introduce a delay between activations to ease the burden
  }
  if (diff == 5) {
    _relDelay = 10; // of the power supply (and decrease switching noise).
  }
  if (diff == 6) {
    _relDelay = 20;
  }
  if (diff >= 7) {
    _relDelay = 50;
  }

  mBus.Info("Inrtoducing delay of: %d ", _relDelay);

  _changeRelaysPrev = _changeRelaysCurrent;
  return _relDelay;
}
