/*******************************************************************************************************************
  K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

  project by vojcio: https://github.com/vojcio/k8-neuron

 *******************************************************************************************************************/

#include <Wire.h>                                                         // Library for the I2C communication.
#include "Arduino.h"                                                      // Basic Arduino library
#include "Volume.h"                                                       // Volume attenuator library
#include "Inputs.h"                                                       // Controll the inputs
#include "InputSource.h"                                                  // Input Source selector
#include "Logging.h"                                                          // Logging class
#include "Eprom.h"                                                        // Library to controll Eeprom
#include <LiquidCrystal.h>
#include "Lcd.h"
#include "libraries/PCF8574.h"


// PINs config
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
Inputs in(&volChange, &srcChange, &currentVolume);                      // Construct inputs
Logging mBus;                                             // Construct log/message bus class
Eprom eprom(epromVolume, epromSource, &currentSource, &currentVolume);                                          // Construct class to use eeprom
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
Lcd screen(&lcd);

void setup() {

  //vol.initMcp();

  //eprom.overrideCurrentVolume();
  //vol.set();                                              // setup starting volume, as fast as it can be, to avoid noises

  //eprom.overrideCurrentSource();
  //inSrc.set();                                            // setup starting input, as fast as it can be, to avoid unexpected behaviour

  mBus.Init(logLevel, baudRate);
  mBus.Debug("Passed message bus configure with loglevel %d", logLevel);

  eprom.periodicInterval(60); //in seconds

  //in.initMuteButton(mutePin);             //initialize mute pin button
 // in.initRotEncVol(volUpPin, volDownPin);
 // in.initRotEncSrc(srcUpPin, srcDownPin);


screen.DefineLargeChar();

int filter=1;
  int volume=0;

//  screen.printOneNumber(3);

//screen.test();
}
void loop() {
  delay(1000);

  screen.printOneNumber(9);
  screen.printTwoNumber(78);
  delay(10000);


  if (in.getVolChange()) {
    Serial.print("volume will be changed to: "); Serial.println(volChange);
    vol.change();
    eprom.notify();
  }

  if (in.getMuteChange()) {
   // Serial.print("Mute will be enabled");
 //   vol.set();
  }

  if (in.getSrcChange()) {
    Serial.print("Source will be changed to: "); Serial.println(srcChange);
    inSrc.change();
    eprom.notify();
  }

  eprom.periodic();
}
