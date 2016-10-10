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
#include "Logging.h"                                                          // Logging class
#include "Eprom.h"                                                        // Library to controll Eeprom

// config
const int volUpPin = '3';                                                 // RotEnc A terminal for right rotary encoder.
const int volDownPin = '2';                                               // RotEnc B terminal for right rotary encoder.
const int srcUpPin = '5';                                                 // RotEnc A terminal for right rotary encoder.
const int srcDownPin = '4';                                               // RotEnc B terminal for right rotary encoder.
const int mutePin = '6';                                                  // mute Button pin
// logging conf
const int logLevel = 3;                                                    // Possible log levels: 1 - Error, 2 - Notice, 3 - Debug - disable logging
const int baudRate = 9600;                                                 // Serial baud rate setting, default = 9600
float resVals[8] = {64, 32, 16, 8, 4, 2, 1, 0.5};                          // First relay will attenuate by 64db, Eighth relay will attenuate by 0.5db.
// config end

const int epromVolume = 1;                                                       // constants to point classes (inputs class, eeprom class) to valid execution
const int epromSource = 2;

float volChange = 0;
int srcChange = 0;
int currentSource = 1;
float currentVolume = 5;
unsigned int maxSrc = 8;
Volume vol(resVals, &volChange, &currentVolume);                                  // Construct volume attenuation class
InputSource inSrc(&srcChange, &currentSource, maxSrc);                                    // Construct input source class
Inputs in(&volChange, &srcChange, &currentVolume, volDownPin, volUpPin, srcUpPin, srcDownPin, mutePin);                      // Construct inputs
Logging mBus;                                             // Construct log/message bus class
Eprom eprom(epromVolume, epromSource, &currentSource, &currentVolume);                                          // Construct class to use eeprom

void setup() {

  //vol.initMcp();

  eprom.overrideCurrentVolume();
  vol.set();                                              // setup starting volume, as fast as it can be, to avoid noises

  eprom.overrideCurrentSource();
  inSrc.set();                                            // setup starting input, as fast as it can be, to avoid unexpected behaviour

  mBus.Init(logLevel, baudRate);
  mBus.Debug("Passed message bus configure with loglevel %d", logLevel);

  mBus.Info("MAIN LOOP BEGINS!!");
  
  eprom.periodicInterval(60); //in seconds
  in.initMuteButton();             //initialize mute pin button
}
void loop() {

  if (in.getVolChange()) {
    Serial.print("volume will be changed to: "); Serial.println(volChange);
    vol.change();
    eprom.notify();
  }
  
  if (in.getMuteChange()) {
    Serial.print("Mute will be enabled");
    vol.set();
  }
  
  if (in.getSrcChange()) {
    Serial.print("Source will be changed to: "); Serial.println(srcChange);
    inSrc.change();
    eprom.notify();
  }

  eprom.periodic();
}
