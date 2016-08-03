/*******************************************************************************************************************
   La Skala Attenuator: A ladder-type volume attenuator with Arduino control.

   Rewriten version of original project by dimdim.gr:
   Original Project Page: http://www.dimdim.gr/diyaudio/la-skala-attenuator/

   Fork mainentained by vojcio   : https://github.com/vojcio/laskala

   v1.00    01/08/2016 : - forked by vojcio, revision controll moved to GitHub

   v0.52    30/05/2016 : - Bug fixes. Everything seems to be working OK.
                         - First public release.
                         - Commented out TFT code to make code fit in an UNO.
 *******************************************************************************************************************/

#include <Wire.h>                                                         // Library for the I2C communication.
#include "Adafruit_MCP23008.h"                                            // Library for the I/O expander.
#include "Arduino.h"                                                      // Basic Arduino library 
#include "Volume.h"                                                       // Volume attenuator library
#include "Log.h"



// config
const int volUpPin = 'A3';                                                 // RotEnc A terminal for right rotary encoder.
const int volDownPin = 'A2';                                               // RotEnc B terminal for right rotary encoder.
float volume = 10;                                                         // Default attenuation.
const boolean serialLog = 1;                                               // Enables or disables logging to serial output
const int logLevel = 1;                                                    // Possible log levels: 1 - Info, 2 - Error, 3 - disable logging                                     
// config end

float volume_old = 1000;                                                  // Store old volume.
int energ_relays;                                                         // Store the number of energized relays.
int energ_relays_old;                                                     // Store the number of previously energized relays.
int relay_delay;

Adafruit_MCP23008 mcp;
Volume vol(volDownPin, volUpPin, logLevel, serialLog);                                           // Construct volume attenuation class
Log mBus(logLevel, serialLog);

 
float mcpRef[8] = {64, 32, 16, 8, 4, 2, 1, 0.5};                          // First relay will attenuate by 64db, Eighth relay will attenuate by 0.5db.
boolean relay[8] = {0, 0, 0, 0, 0, 0, 0, 0};

float vol_temp_2;


void setup() {

mcp.begin();                                                              // use default address 0

for(int i = 0; i<8; i++) {                                                // Set all pin's to OUTPUT mode
    mcp.pinMode(i, OUTPUT);
}

//setVol(volume);                                                         // Set the attenuation at its default value.   TODO: check if this will work
                                                                          // Must be as close to the beginning of the code as possible to avoid audio spikes at start-up.

  Serial.begin(115200);
}

void loop() {                                                             // MAIN LOOP

  vol.calc(volume);
  
//  vol.prep
//  vol.change
  
//  float newVol = calcChange();                                            // Calculate a volume change
//  if (newVol != volume_old) {                                             // if volume has changed proceed, else finish main loop TODO: why do we need so many global variables, need cleanup
//    setVol(newVol);                                                       // calculate change in volume and finish loop, or:
//    energRel();                                                           // count the delay
//    if (vol_temp_2 > volume_old) decVol();                                // decrease
//    if (vol_temp_2 < volume_old) incVol();                                // or increase volume
//      else mBus.info("Volume setting wrong!: ", String(vol_temp_2));          // or handle error TODO: set volume to some default to avoid deadend...
//    }
}


int energRel() {
    int diff = energ_relays_old - energ_relays;                           // count how many relays will be switched TODO: maybe it is possible to count the "1s" in array? and avoid this complicated function

    mBus.info("Difference in switched relays: ", String(diff));        // Determine how many relays will be switching states.
                                                                          // Useful to predict the current load imposed on the power supply.

    if (diff <= 3) { relay_delay = 0; }                                   // When a large number of relays is expected to switch states,
    if (diff == 4) { relay_delay = 5; }                                   // introduce a delay between activations to ease the burden
    if (diff == 5) { relay_delay = 10;}                                   // of the power supply (and decrease switching noise).
    if (diff == 6) { relay_delay = 20;}
    if (diff >= 7) { relay_delay = 50;}

    energ_relays_old = energ_relays;
}
