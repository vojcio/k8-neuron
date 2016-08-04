/*
   Logging module for arduino projects by vojcio.
   Originally created for pre-amplifier software, but written as a general use logging module, very lightweight.
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/

#include "Log.h"
#include "Arduino.h"

Log::Log(int logLevel, boolean serialLog) {

  _serialLog = serialLog;
  _logLevel = logLevel;
  if (_serialLog == 1) {
    Serial.begin(115200);                                                     // TODO: move this to Log class?????
  }

}

/// Logging bus

void Log::prepare(String message, String variable, int mLevel) {
  String logType = "";
  if (_logLevel < 3) {                                              // check if message have one of the supported logLevels
    if (mLevel <= _logLevel) {                                      // check if message should be logged
      switch (mLevel) {
        case 2:
          logType = "Error: ";
        break;
        default:
          logType = "Notice: ";
        break;
      }

	String messageOut = logType + message + variable;

      if (_serialLog == 1 )  serial(messageOut);      // check if logger type enabled and push message
        // Add new logers here
    }
  }
}

/// Logging levels

void Log::info(String message, String variable) {
        prepare(message, variable, 1);
}

void Log::error(String message, String variable) {
        prepare(message, variable, 2);
}

//// Logging outputs
void Log::serial(String message) {
	Serial.println(message);
}
