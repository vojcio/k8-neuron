/*******************************************************************************************************************
 K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier 

 project by vojcio: https://github.com/vojcio/k8-neuron

 credits: 
 Volume atenuator algorithm originally from: http://www.dimdim.gr/diyaudio/la-skala-attenuator/
 
 *******************************************************************************************************************/

#include <Wire.h>                                                         // Library for the I2C communication.
#include "Arduino.h"                                                      // Basic Arduino library 
#include "Volume.h"                                                       // Volume attenuator library
#include "Inputs.h"                                                       // Controll the inputs
#include "InputSource.h"                                                  // Input Source selector
#include "Log.h"                                                          // Logging class
#include "Eprom.h"                                                        // Library to controll Eeprom


// config
const int volUpPin = 'A3';                                                 // RotEnc A terminal for right rotary encoder.
const int volDownPin = 'A2';                                               // RotEnc B terminal for right rotary encoder.
const int srcUpPin = 'A5';                                                 // RotEnc A terminal for right rotary encoder.
const int srcDownPin = 'A4';                                               // RotEnc B terminal for right rotary encoder.
const boolean serialLog = 1;                                               // Enables or disables logging to serial output
const int logLevel = 1;                                                    // Possible log levels: 1 - Info, 2 - Error, 3 - disable logging 
float resVals[8] = {64, 32, 16, 8, 4, 2, 1, 0.5};                          // First relay will attenuate by 64db, Eighth relay will attenuate by 0.5db.                                    
// config end

const int volume = 1;                                                       // constants to point classes (inputs class, eeprom class) to valid execution
const int source = 2;

Volume vol(resVals, logLevel, serialLog);                                  // Construct volume attenuation class
InputSource inSrc(logLevel, serialLog);                                    // Construct input source class
Inputs in(volDownPin, volUpPin, srcUpPin, srcDownPin, logLevel, serialLog);                      // Construct inputs 
Log mBus(logLevel, serialLog);                                             // Construct log/message bus class
Eprom eprom(logLevel, serialLog);                                          // Construct class to use eeprom

void setup() {
  Serial.begin(9600);
  Serial.println("Hello world!");
  vol.set(eprom.get(volume));                                              //setup starting volume, as fast as it can be, to avoid noises
  inSrc.set(eprom.get(source));                                            //setup starting input, as fast as it can be, to avoid unexpected behaviour

}

void loop() {                                                               // MAIN LOOP
  Serial.println("test");
  mBus.info("test", "test");
  vol.change(in.getVolChange());                                            // read rotary encoder and set a new volume
  inSrc.set(in.getNewSource());                                             // set a new input source
  
}
