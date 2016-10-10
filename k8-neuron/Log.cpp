/*
   Logging module for arduino projects by vojcio.
   Originally created for pre-amplifier software, but written as a general use logging module, very lightweight.
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#include "Log.h"
#include "Arduino.h"

Log::Log() {}

/// Logging bus

void Log::prepare(String message, String variable, int mLevel) {
  String logType = "";
  if (mLevel <= _logLevel) {                                      // check if message should be logged
    switch (mLevel) {
      case 1:
        logType = "Error: ";
        break;
      case 2:
        logType = "Notice: ";
        break;
      default:
        logType = "Debug: ";
        break;
    }

    String messageOut = logType + message + variable;
    if (_serialLog == 1 )  serial(messageOut);      // check if logger type enabled and push message
    // Add new logers here
  }
}

// Logging serial
void Log::configure(int logLevel, boolean serialLog, int _baudRate) {
  _logLevel = logLevel;
  _serialLog = serialLog;
  Serial.begin(_baudRate);
  while (Serial.available() < 0) {
    Serial.println("waiting for serial");
  }
  Serial.println("Initialized Serial output, starting log module...");
}

/// Logging levels

void Log::debug(String message, String variable) {
  prepare(message, variable, 3);
}

void Log::info(String message, String variable) {
  prepare(message, variable, 2);
}

void Log::error(String message, String variable) {
  prepare(message, variable, 1);
}

//// Logging outputs
void Log::serial(String message) {
  Serial.println(message);
}
