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
  
  vol.set(initialVolume);                                                             //setup starting volume, as fast at it can, to avoid noises

}

void loop() {                                                               // MAIN LOOP
  
  int newVol = vol.readRotEnc();                                            // Read the Rotary Encoder change
  vol.change(newVol);                                                       // volChange can get value for which volume schould be changed
  
}
