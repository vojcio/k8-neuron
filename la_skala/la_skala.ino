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
#include "Arduino.h"                                                      // Basic Arduino library 
#include "Volume.h"                                                       // Volume attenuator library
#include "Log.h"

// config
const int volUpPin = 'A3';                                                 // RotEnc A terminal for right rotary encoder.
const int volDownPin = 'A2';                                               // RotEnc B terminal for right rotary encoder.
float initialVolume = 10;                                                         // Default attenuation.
const boolean serialLog = 1;                                               // Enables or disables logging to serial output
const int logLevel = 1;                                                    // Possible log levels: 1 - Info, 2 - Error, 3 - disable logging 
float resVals[8] = {64, 32, 16, 8, 4, 2, 1, 0.5};                          // First relay will attenuate by 64db, Eighth relay will attenuate by 0.5db.                                    
// config end

Volume vol(volDownPin, volUpPin, resVals, logLevel, serialLog, initialVolume);                                           // Construct volume attenuation class
Log mBus(logLevel, serialLog); 


void setup() {
   Serial.begin(115200);                                                     // TODO: move this to Log class?????
}

void loop() {                                                             // MAIN LOOP

  int newVol = vol.readRotEnc();
  vol.change(newVol);                         // volChange can get value for which volume schould be changed
 
//float newVol = vol.calc(volume);
//if (newVol != volume) {
//  vol.set(newVol);
}
  
//  float newVol = calcChange();                                            // Calculate a volume change
//  if (newVol != volume_old) {                                             // if volume has changed proceed, else finish main loop TODO: why do we need so many global variables, need cleanup
//    setVol(newVol);                                                       // calculate change in volume and finish loop, or:
//    energRel();                                                           // count the delay
//    if (vol_temp_2 > volume_old) decVol();                                // decrease
//    if (vol_temp_2 < volume_old) incVol();                                // or increase volume
//      else mBus.info("Volume setting wrong!: ", String(vol_temp_2));          // or handle error TODO: set volume to some default to avoid deadend...
//    }
//}
