/*******************************************************************************************************************
K8 Neutron is intended to be a fully featured, open source and open hardware pre-amplifier

project by vojcio: https://github.com/vojcio/k8-neuron

Library to controll LCD in k8-neuron

Credits:
https://github.com/seanauff/BigNumbers/blob/master/BigNumbers.cpp
and
https://github.com/dblachut/LCD-font-generator
*******************************************************************************************************************/
#ifndef Lcd_h
#define Lcd_h

#include "Arduino.h"
#include <LiquidCrystal.h>

class Lcd
{
  public:
    Lcd(LiquidCrystal*);
    void DefineLargeChar();
    void printOneNumber(uint8_t);
    void printTwoNumber(uint8_t);
    void test();
  private:
    LiquidCrystal* _lcd;

};

#endif
