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
