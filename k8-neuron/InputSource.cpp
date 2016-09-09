/*
   Input source changer for k8-neuron
   Mainentained by vojcio: https://github.com/vojcio/laskala
*/


#include "Arduino.h"
#include "InputSource.h"
#include "Log.h"

InputSource::InputSource(const int logLevel, const boolean serialLog) : mBus(logLevel, serialLog) {

}


void InputSource::set(int newPos) {                                         // Calculating the change based on reading from different inputs



}


