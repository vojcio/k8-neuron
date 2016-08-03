/*
   La Skala Attenuator: A ladder-type volume attenuator with Arduino control.
   Rewriten version of original project by dimdim.gr:
   Original Project Page: http://www.dimdim.gr/diyaudio/la-skala-attenuator/
   Fork mainentained by vojcio: https://github.com/vojcio/laskala
*/
#include "Arduino.h"
#include "Volume.h"
#include <RotaryEncoder.h>
#include "Log.h"

Volume::Volume(int VOLDOWNPIN, int VOLUPPIN, int logLevel, boolean serialLog) : encoder(VOLDOWNPIN, VOLUPPIN), mBus(logLevel, serialLog) {

	pinMode(VOLUPPIN, INPUT);                                               // Button switch or Encoder pin for volume up
  	digitalWrite(VOLUPPIN, HIGH);                                           // If H/W debouncing is implemented, set to LOW
  	pinMode(VOLDOWNPIN, INPUT);                                             // Button switch or Encoder pin for volume down
  	digitalWrite(VOLDOWNPIN, HIGH);                                         // If H/W debouncing is implemented, set to LOW

}

int Volume::calc(float volume) {
  static int pos = 0;                                                     // Read the rotary encoder and increase or decrease attenuation.
  encoder.tick();
  int newPos = encoder.getPosition();
  if (pos != newPos) {
    if (pos < newPos) {
      if (volume > 0) {
        volume = volume - 0.5;
      }
    }
    else if (pos > newPos) {
      if (volume < 127) {
        volume = volume + 0.5;
      } 
    }
    pos = newPos;
  }
}

void Volume::set() {
    mBus.info("Setting volume to: ", String(volume_received));
    energ_relays = 0;
    vol_temp_2 = volume_received;

    for (int i = 0 ; i < 8 ; i++)
    {
      if (volume_received >= mcpRef[i])
      {
        relay[i] = 1;
        energ_relays++;
        volume_received = volume_received - mcpRef[i];
        mBus.info("Volume will be set to: ", String(volume_received));
      } else {
        relay[i] = 0;
      }
    }
}

void Volume::increase() {
  for (int i ; i < 8 ; i++) {
    if (relay[i] == 0)
      {
        mcp.digitalWrite(i, LOW);
        mBus.info("(increasingVol ; Scheduling relay to disable: ", String(relay[i]));
      }
      else mcp.digitalWrite(i, HIGH);
      mBus.info("(increasingVol ; Scheduling relay to enable: ", String(relay[i]));
   }
   volume_old = vol_temp_2;
}

void Volume::decrease() {
  for (int i ; i > 8 ; i--) {
    if (relay[i] == 0) {
      mcp.digitalWrite(i, LOW);
      mBus.info("(decreaseingVol ; Scheduling relay to disable: ", String(relay[i]));
    }
    else mcp.digitalWrite(i, HIGH);
    mBus.info("(decreaseingVol ; Scheduling relay to enable: ", String(relay[i]));
    delay(relay_delay);
  }
  volume_old = vol_temp_2;
}
