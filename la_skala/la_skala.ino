/*******************************************************************************************************************
   La Skala Attenuator: A ladder-type volume attenuator with Arduino control.

   Rewriten version of original project by dimdim.gr:
   Original Project Page: http://www.dimdim.gr/diyaudio/la-skala-attenuator/

   Fork mainentained by vojcio   : https://github.com/vojcio/laskala

   v1.00    01/08/2016 : - fork by vojcio, revision controll moved to GitHub

   v0.52    30/05/2016 : - Bug fixes. Everything seems to be working OK.
                         - First public release.
                         - Commented out TFT code to make code fit in an UNO.

   v0.44    11/05/2016 : - Added code to take into account the number of relays that switch states, so as to
                           reduce power supply loading due to many relays activating at the same time.
                         - Attempt to eliminate small glitches occuring at certain steps by implementing different
                           function for increasing & decreasing attenuation.

   v0.30    15/02/2016 : - First attempt at coding an appropriate algorithm. It works!
                         - Outputs status info to serial port and TFT (ILI9341 with SPI).
 *******************************************************************************************************************/

#include <Wire.h>                                     // Library for the I2C communication.
#include "Adafruit_MCP23008.h"                        // Library for the I/O expander.
#include <RotaryEncoder.h>                            // Library for the encoder.

float volume = 10;                                    // Default attenuation.
float volume_old = 1000;                              // Store old volume.
int energ_relays;                                     // Store the number of energized relays.
int energ_relays_old;                                 // Store the number of previously energized relays.
int relay_delay;

Adafruit_MCP23008 mcp;

float mcpRef[8] = {64, 32, 16, 8, 4, 2, 1, 0.5}; // First relay will attenuate by 64db, Eighth relay will attenuate by 0.5db.
boolean relay[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int VOLUPPIN = 'A3';              // RotEnc A terminal for right rotary encoder.
int VOLDOWNPIN = 'A2';            // RotEnc B terminal for right rotary encoder.

RotaryEncoder encoder(VOLDOWNPIN, VOLUPPIN);       // Setup the first Rotary Encoder

float vol_temp_2;
void setup() {

mcp.begin();                      // use default address 0

for(int i = 0; i<8; i++) {        // Set all pin's to OUTPUT mode
    mcp.pinMode(i, OUTPUT);
}

  setVol(volume);                 // Set the attenuation at its default value. Must be as close to the beginning of the code as possible to avoid audio spikes at start-up.

  pinMode(VOLUPPIN, INPUT);       // Button switch or Encoder pin for volume up
  digitalWrite(VOLUPPIN, HIGH);   // If H/W debouncing is implemented, set to LOW
  pinMode(VOLDOWNPIN, INPUT);     // Button switch or Encoder pin for volume down
  digitalWrite(VOLDOWNPIN, HIGH); // If H/W debouncing is implemented, set to LOW

  Serial.begin(115200);
}

// main loop
void loop() {
    setVol(calcChange());
}


int calcChange() {
  static int pos = 0;                        // Read the rotary encoder and increase or decrease attenuation.
  encoder.tick();
  int newPos = encoder.getPosition();
  if (pos != newPos)
  {
    if (pos < newPos)
    {
      if (volume > 0)
      {
        volume = volume - 0.5;
      }
      pos = newPos;
    }
    else if (pos > newPos)
    {
      if (volume < 127)
      {
        volume = volume + 0.5;
      }
      pos = newPos;
    }
  }
}

void setVol(float volume_received)              // Set the volume by controlling the 8 relays.
{
  if (volume_received != volume_old) {
    Serial.print("Setting volume to: ");
    Serial.println(volume_received);
    energ_relays = 0;
    vol_temp_2 = volume_received;

    for (int i = 0 ; i < 8 ; i++)
    {
      if (volume_received >= mcpRef[i])
      {
        relay[i] = 1;
        energ_relays++;
        volume_received = volume_received - mcpRef[i];
        Serial.println(volume_received);
      } else {
        relay[i] = 0;
      }
    }

    Serial.print("Difference in switched relays: ");                  // Determine how many relays will be switching states. Useful to predict the current load imposed on the power supply.
    Serial.println(abs(energ_relays_old - energ_relays));

    if (abs(energ_relays_old - energ_relays) <= 3)
    {
      relay_delay = 0;
    }
    if (abs(energ_relays_old - energ_relays) == 4)                  // When a large number of relays is expected to switch states, introduce a delay between activations to ease the burden of the power supply (and decrease switching noise).
    {
      relay_delay = 5;
    }
    if (abs(energ_relays_old - energ_relays) == 5)
    {
      relay_delay = 10;
    }
    if (abs(energ_relays_old - energ_relays) == 6)
    {
      relay_delay = 20;
    }
    if (abs(energ_relays_old - energ_relays) >= 7)
    {
      relay_delay = 50;
    }

    energ_relays_old = energ_relays;

    if (vol_temp_2 > volume_old)
      decVol();
    if (vol_temp_2 < volume_old)
      incVol();     
    else 
    Serial.println("Error! Unexpected behaviour");
  }
}
  void incVol() {
    for (int i ; i < 8 ; i++) {
      Serial.println("Increasing the attenuation");
      if (relay[i] == 0)
        {
          mcp.digitalWrite(i, LOW);
        }
        else mcp.digitalWrite(i, HIGH);
      }
      volume_old = vol_temp_2;
  }

  void decVol() {
    for (int i ; i > 8 ; i--) {
      Serial.println("Decreasing the attenuation");
      if (relay[i] == 0) {
        mcp.digitalWrite(i, LOW);
      }
      else mcp.digitalWrite(i, HIGH);
      delay(relay_delay);
    }
      volume_old = vol_temp_2;
  }