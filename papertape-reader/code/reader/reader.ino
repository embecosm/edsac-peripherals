/* The code to work the EDSAC simulating tape reader

   Copyright (C) 2017  Embecosm Ltd
   Contributor: Peter Bennett <peter.bennett@embecosm.com>

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation, either version 3 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <math.h>

// Number of sensors

static const int NUM_BITS = 5;

// How many value to aggregate

static const int NUM_VALS = 10;

// All the LED sensors

static const int sensorPin[NUM_BITS] = {
  A5, A4, A2, A1, A0 };
static const int sprocketPin = A3;

// All 6 reader LEDs are driven off the same pin.

static const int readerLedPin = 13;      // select the pin for the LED

// Add a LED to tell us we are alive!

static const int statusLedPin = 12;

// Record of the last 20 sensor and sprocket values

int sensorValue[NUM_VALS][NUM_BITS];
int sprocketValue[NUM_VALS];

// Which is the next set of data to be collected (range 0 to NUM_VALS - 1)

int nextData;

// State of pins

uint8_t sensorState[NUM_BITS];
uint8_t sprocketState;

// Threshold for slope

static const int THRESHOLD = 20;

// Debug counter

static const int DBG_CNT = 250;

struct
{
  int  current;
  int  oldest;
  int  gradient;
} debugData[DBG_CNT];

int debugCount;

//! Standard setup

//! @note Don't go for GNU style declaration here - it breaks Arduino

void setup()
{
  // declare the various LED pins as outputs:

  pinMode(readerLedPin, OUTPUT);
  pinMode(statusLedPin, OUTPUT);

  // Make sure we can talk to the serial monitor

  Serial.begin(9600);

  // Populate our initial data

  nextData = 0;

  do
    {
      sprocketValue[nextData] = analogRead (sprocketPin);

      for (int i = 0; i < NUM_BITS; i++)
        sensorValue[nextData][i] = analogRead (sensorPin[i]);

      nextData = (nextData == (NUM_VALS - 1)) ? 0 : nextData + 1;
    }
  while (nextData != 0);

  // Set up state. Assume all LOW (FALSE) to start with.

  sprocketState = 0;

  for (int i = 0; i < NUM_BITS; i++)
    sensorState[i] = 0;

  // Turn on the LEDs

  digitalWrite (readerLedPin, HIGH);
  digitalWrite (statusLedPin, LOW);

  debugCount = 0;
  Serial.println ("Get ready");
  delay (2000);
  Serial.println ("Go");
  delay (500);

}       // setup ()


//! Main loop

//! @note Don't go for GNU style declaration here - it breaks Arduino

void loop()
{
  delay (5);

  // Capture gradients

  int dataGradient[NUM_BITS];
  int sprocketGradient;

  int oldestData = (nextData + 1) % NUM_VALS;

  // Get the sprocket and sensor values and calculate gradients

  sprocketValue[nextData] = analogRead (sprocketPin);
  sprocketGradient = sprocketValue[nextData] - sprocketValue[oldestData];

  if (debugCount < DBG_CNT)
    {
      debugData[debugCount].current = sprocketValue[nextData];
      debugData[debugCount].oldest = sprocketValue[oldestData];
      debugData[debugCount].gradient = sprocketGradient;
      debugCount++;
    }
  else if (debugCount == DBG_CNT)
    {
      Serial.println ("\"Current\",\"Oldest\",\"Gradient\"");

      for (int i = 0; i < DBG_CNT; i++)
        {
          Serial.print ("\"");
          Serial.print (debugData[i].current);
          Serial.print ("\",\"");
          Serial.print (debugData[i].oldest);
          Serial.print ("\",\"");
          Serial.print (debugData[i].gradient);
          Serial.println ("\"");
        }

      debugCount++;
    }

  for (int i = 0; i < NUM_BITS; i++)
    {
      sensorValue[nextData][i] = analogRead (sensorPin[i]);
      dataGradient[i] = sensorValue[nextData][i] - sensorValue[oldestData][i];

      if (dataGradient[i] > THRESHOLD)
        sensorState[i] = 1;

      if (dataGradient[i] < -THRESHOLD)
        sensorState[i] = 0;
    }

  // For sprocket we need to capture the point of change.

  if ((1 == sprocketState) && (sprocketGradient > THRESHOLD))
    {
      uint8_t dataVal = 0;

      digitalWrite (statusLedPin, HIGH);

      for (int i = 0; i < NUM_BITS; i++)
        dataVal = dataVal << 1 | sensorState[i];

      Serial.println (dataVal, HEX);
    }

  // Update sprocketGradient info

  if (sprocketGradient > THRESHOLD)
    sprocketGradient = 1;

  if (sprocketGradient < - THRESHOLD)
    {
      sprocketGradient = 0;
      digitalWrite (statusLedPin, LOW);
    }

  // And ready for the next data

  nextData = (nextData == (NUM_VALS - 1)) ? 0 : nextData + 1;
}


// Local Variables:
// mode: C++
// c-file-style: "gnu"
// indent-tabs-mode: nil
// End:
