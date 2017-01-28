/*******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

project by vojcio: https://github.com/vojcio/k8-neuron

Library to controll LCD in k8-neuron

Credits:
https://github.com/seanauff/BigNumbers/blob/master/BigNumbers.cpp
and
https://github.com/dblachut/LCD-font-generator
*******************************************************************************************************************/
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "lcd.h"


Lcd::Lcd(LiquidCrystal* lcd) {

  _lcd = lcd;
  _lcd->begin(20, 4);
  _lcd->setCursor(0, 0);
}

void Lcd::test() {
  _lcd->print("bla bla bla blaaaa");
  _lcd->setCursor(0, 1);
  _lcd->print("dupa");
  _lcd->setCursor(0, 2);
  _lcd->print("dupa2");
  _lcd->setCursor(0, 3);
  _lcd->print("dupa3");
}

void Lcd::DefineLargeChar()
{

  // A 1 in the binary representation of the character means it is filled in
  // characters are 5 pixels wide by 8 pixels tall

  // We need 7 custom characters for the OPUS DAC display.
  // (Custom character 0 doesn't work in the Web4Robot LCD)

  // Define Custom Characters

  uint8_t cc1[8] = {     // Custom Character 1
    B00111,
    B01111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  uint8_t cc2[8] = {    // Custom Character 2
    B11100,
    B11110,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  uint8_t cc3[8] = {    // Custom Character 3
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  uint8_t cc4[8] = {   // Custom Character 4
    B11111,
    B11111,
    B11110,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  uint8_t cc5[8] = {    // Custom Character 5
    B11111,
    B11111,
    B01111,
    B00111,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  uint8_t cc6[8] = {    // Custom Character 6
    B00111,
    B01111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
  };

  uint8_t cc7[8] = {     // Custom Character 7
    B11100,
    B11110,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
  };
  uint8_t cc8[8] = {     // Custom Character 7
    B00011,
    B00111,
    B01111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  // send custom characters to the display
  _lcd->createChar(1, cc1);
  _lcd->createChar(2, cc2);
  _lcd->createChar(3, cc3);
  _lcd->createChar(4, cc4);
  _lcd->createChar(5, cc5);
  _lcd->createChar(6, cc6);
  _lcd->createChar(7, cc7);
  _lcd->createChar(8, cc8);
}

// Array index into parts of big numbers. Numbers consist of 9 custom characters in 3 lines
//          0                 1                2           3            4               5         6           7           8           9
char bn1[] = {6, 3, 7,        1, 255, 254,    1, 3, 7,    1, 3, 7,      255,254,255,    255,3,4,  6, 3, 2,    5, 3,255,   6,3,7,      6, 3, 7};
char bn2[] = {255, 254,255,   254, 255, 254,  6, 3, 4,    254, 3, 255,  5, 3, 255,      3, 3, 7,  255,3,7,    254,6,4,    255,3,255,  5, 3, 255};
char bn3[] = {5, 3, 4,        3, 3, 3,        3, 3, 3,    5, 3, 4,      254, 254, 3,    5, 3, 4,  5, 3, 4,    254,3,254,  5, 3, 4,    5, 3, 4};

// 1 - pelne - 255
// 4 - puste - 254
void Lcd::printOneNumber(uint8_t digit)
{
  // Print position is hardcoded


  // Line 1 of the one digit number
  _lcd->setCursor(0, 1);
  _lcd->write(bn1[digit * 3]);
  _lcd->write(bn1[digit * 3 + 1]);
  _lcd->write(bn1[digit * 3 + 2]);

  // Line 2 of the one-digit number
  _lcd->setCursor(0, 2);
  _lcd->write(bn2[digit * 3]);
  _lcd->write(bn2[digit * 3 + 1]);
  _lcd->write(bn2[digit * 3 + 2]);

  // Line 3 of the one-digit number
  _lcd->setCursor(0, 3);
  _lcd->write(bn3[digit * 3]);
  _lcd->write(bn3[digit * 3 + 1]);
  _lcd->write(bn3[digit * 3 + 2]);
}

void Lcd::printTwoNumber(uint8_t number)
{
  // Print position is hardcoded
  int digit0;  // To represent the ones
  int digit1;  // To represent the tens
  digit0 = number % 10;
  digit1 = number / 10;

  // Line 1 of the two-digit number
  _lcd->setCursor(13, 1);
  _lcd->write(bn1[digit1 * 3]);
  _lcd->write(bn1[digit1 * 3 + 1]);
  _lcd->write(bn1[digit1 * 3 + 2]);
  _lcd->write(254); // Blank
  _lcd->write(bn1[digit0 * 3]);
  _lcd->write(bn1[digit0 * 3 + 1]);
  _lcd->write(bn1[digit0 * 3 + 2]);

  // Line 2 of the two-digit number
  _lcd->setCursor(13, 2);
  _lcd->write(bn2[digit1 * 3]);
  _lcd->write(bn2[digit1 * 3 + 1]);
  _lcd->write(bn2[digit1 * 3 + 2]);
  _lcd->write(254); // Blank
  _lcd->write(bn2[digit0 * 3]);
  _lcd->write(bn2[digit0 * 3 + 1]);
  _lcd->write(bn2[digit0 * 3 + 2]);

  // Line 3 of the two-digit number
  _lcd->setCursor(13, 3);
  _lcd->write(bn3[digit1 * 3]);
  _lcd->write(bn3[digit1 * 3 + 1]);
  _lcd->write(bn3[digit1 * 3 + 2]);
  _lcd->write(254); // Blank
  _lcd->write(bn3[digit0 * 3]);
  _lcd->write(bn3[digit0 * 3 + 1]);
  _lcd->write(bn3[digit0 * 3 + 2]);
}
