/*
   Logging module for arduino projects by vojcio.
   Originally created for pre-amplifier software, but written as a general use logging module, very lightweight.
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/
 
#ifndef Log_h
#define Log_h

#include "Arduino.h"

class Log
{
  public:
    Log(int logLevel, boolean serialLog) ;
    void info(String message, String variable);
    void error(String message, String variable);
  private:
    void serial(String message);
    void prepare(String message, String variable, int logLevel);
    int _logLevel;
    boolean _serialLog;
};

#endif
