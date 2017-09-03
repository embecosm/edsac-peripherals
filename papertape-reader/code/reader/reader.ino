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

// All the LED sensors

static const int sensorPin[NUM_BITS] = {
  A5, A4, A3, A1, A0 };
static const int sprocketPin = A2;

// All 6 reader LEDs are driven off the same pin.

static const int readerLedPin = 13;      // select the pin for the LED

// Add a LED to tell us we are alive!

static const int statusLedPin = 12;

// Number of values to average forwards and backwards.

static const int NUM_VALS = 5;

// Number of samples to aggregate to be able to compute a central second
// derivative. We smooth NUM_VALS each side of the raw data to get the
// derivative. No further smoothing after that.

static const int NUM_SAMPLES = NUM_VALS * 2 + 1;

// Structure of a sensor value

struct sensorData
{
  int vals[NUM_SAMPLES];
  int gradients[NUM_SAMPLES];
  int gradient2;
  int gradient2prev;
};

// Record of sensor and sprocket values

struct sensorData  dataInfo[NUM_BITS];
struct sensorData  sprocketInfo;

// Which is the next set of data to be collected (range 0 to NUM_SAMPLES - 1)

static int nextData;

// True if we are in a sprocket hole

static bool sprocketState;

// Threshold for sprocket state change. First derivative must be more than
// this.

static const int SPROCKET_THRESHOLD = 20;

// State of pins. True if we are in a hole

static bool sensorState[NUM_BITS];

// Threshold for sensor state change. First derivative must be more than
// this.

static const int SENSOR_THRESHOLD = 20;

// The data we read;

static uint8_t data;

// Maximum abount of debug

static const int DBG_MAX = 1500;

// Debug counter

int dbgCnt;

//! Standard setup

//! @note Don't go for GNU style declaration here - it breaks Arduino

void setup()
{
  // declare the various LED pins as outputs:

  pinMode(readerLedPin, OUTPUT);
  pinMode(statusLedPin, OUTPUT);

  // Make sure we can talk to the serial monitor

  Serial.begin(115200);

  // Debug setup

  dbgCnt = 0;
  Serial.println ("Get ready");
  delay (2000);

  // Turn on the LEDs and allow resistors to respond.

  digitalWrite (readerLedPin, HIGH);
  digitalWrite (statusLedPin, LOW);
  delay (500);

  // Populate our initial data.  Need to do this twice to ensure the first
  // derivative values are meaningful.

  nextData = 0;

  do
    {
      sprocketInfo.vals[nextData] = analogRead (sprocketPin);

      for (int i = 0; i < NUM_BITS; i++)
        dataInfo[i].vals[nextData] = analogRead (sensorPin[i]);

      nextData = (nextData + 1) % NUM_SAMPLES;
    }
  while (nextData != 0);

  // Second time round, populate the gradients

  do
    {
      int tot = 0;
      int nextGrad = (nextData - NUM_VALS + 1 + NUM_SAMPLES) % NUM_SAMPLES;

      sprocketInfo.vals[nextData] = analogRead (sprocketPin);

      for (int j = nextGrad - NUM_VALS; j < nextGrad; j++)
        {
          int prev = (j + NUM_SAMPLES) % NUM_SAMPLES;
          int curr = (j + NUM_VALS) % NUM_SAMPLES;
          tot += sprocketInfo.vals[curr] - sprocketInfo.vals[prev];
        }

      sprocketInfo.gradients[nextGrad] = tot;

      for (int i = 0; i < NUM_BITS; i++)
        {
          tot = 0;
          dataInfo[i].vals[nextData] = analogRead (sensorPin[i]);

          for (int j = nextGrad - NUM_VALS; j < nextGrad; j++)
            {
              int prev = (j + NUM_SAMPLES) % NUM_SAMPLES;
              int curr = (j + NUM_VALS) % NUM_SAMPLES;
              tot += dataInfo[i].vals[curr] - dataInfo[i].vals[prev];
            }

          dataInfo[i].gradients[nextGrad] = tot;
        }

      nextData = (nextData + 1) % NUM_VALS;
    }
  while (nextData != 0);

  // Assume not in sprocket hole or data hole

  sprocketState = false;

  for (int i = 0; i < NUM_BITS; i++)
    sensorState[i] = false;

  // No data read yet

  data = 0;

  Serial.println ("Go");
  delay (500);

}       // setup ()


//! Main loop

//! The sensor is a light dependent resistor (LDR). The LDR resistance varies
//! from 10s of kOhm in full light to 20MOhm in the dark.  The LDR is
//! connected to the 5V rail and then via a 22kOhm resistor to ground, with
//! the value read at the connection between the LDR and resistor.

//! So the more light the LDR receives, the higher the read value.  Since
//! holes in the paper tape are represented as dark spots, this means minima
//! correspond to holes.

//! We calculate mid-point central first and second derivatives for the current
//! reading of the sprocket hole. When the second deriviative is zero, we
//! treat this as the edge of a sprocket hole. If the first derivative is
//! positive we are approaching a minimum (i.e. entering the sprocket hole)
//! and if it is negative we are approaching a maximum (i.e. leaving the
//! sprocket hole).

//! During the

//! @note Don't go for GNU style declaration here - it breaks Arduino

void loop()
{
  delay (5);

  // Capture data and compute second derivatives

  int nextGrad = (nextData - NUM_VALS + 1 + NUM_SAMPLES) % NUM_SAMPLES;
  int prevGrad = (nextGrad - 1 + NUM_SAMPLES) % NUM_SAMPLES;
  int tot = 0;

  sprocketInfo.vals[nextData] = analogRead (sprocketPin);

  for (int j = nextGrad - NUM_VALS; j < nextGrad; j++)
    {
      int prev = (j + NUM_SAMPLES) % NUM_SAMPLES;
      int curr = (j + NUM_VALS) % NUM_SAMPLES;
      tot += sprocketInfo.vals[curr] - sprocketInfo.vals[prev];
    }

  sprocketInfo.gradients[nextGrad] = tot;
  sprocketInfo.gradient2prev = sprocketInfo.gradient2;
  sprocketInfo.gradient2     = tot - sprocketInfo.gradients[prevGrad];

  // Second derivative tells us when we crossed a sprocket edge. Because we
  // may not get lucky with hitting zero, we look to see if we have changed
  // sign.

  // We look that we have a large enough first derivative to be sure this is a
  // serious crossing, rather than just noise when there is no signal.

  // We also can only enter if we are not already in and vice versa!

  if ((sprocketInfo.gradient2 * sprocketInfo.gradient2prev) <= 0)
    {
      if (!sprocketState
          && (sprocketInfo.gradients[nextGrad] < -SPROCKET_THRESHOLD))
        {
          // Entering a sprocket

          sprocketState = true;
          //Serial.println ("In");

          // If we have any data pin driving, accept it.

          for (int i = 0; i < NUM_BITS; i++)
            if (sensorState[i])
              data |= 1 << i;
        }
      else if (sprocketState
               && (sprocketInfo.gradients[nextGrad] > SPROCKET_THRESHOLD))
        {
          // Leaving a sprocket

          sprocketState = false;
          //Serial.println ("Out");

          // Record the data

          Serial.println (data, HEX);
          data = 0;
        }
    }

  for (int i = 0; i < NUM_BITS; i++)
    {
      tot = 0;
      dataInfo[i].vals[nextData] = analogRead (sensorPin[i]);

      for (int j = nextGrad - NUM_VALS; j < nextGrad; j++)
        {
          int prev = (j + NUM_SAMPLES) % NUM_SAMPLES;
          int curr = (j + NUM_VALS) % NUM_SAMPLES;
          tot += dataInfo[i].vals[curr] - dataInfo[i].vals[prev];
        }

      dataInfo[i].gradients[nextGrad] = tot;
      dataInfo[i].gradient2prev = dataInfo[i].gradient2;
      dataInfo[i].gradient2     = tot - dataInfo[i].gradients[prevGrad];

      // Recognize edges using second derivatives again.

      if ((dataInfo[i].gradient2 * dataInfo[i].gradient2prev) <= 0)
        {
          if (!sensorState[i]
              && (dataInfo[i].gradients[nextGrad] < -SPROCKET_THRESHOLD))
            {
              // Entering a hole

              sensorState[i] = true;
              //Serial.print ("In ");
              //Serial.println (i);

              // If we are in a sprocket hole, mark this as data.

              if (sprocketState)
                data |= 1 << i;

            }
          else if (sensorState[i]
                   && (dataInfo[i].gradients[nextGrad] > SPROCKET_THRESHOLD))
            {
              // Leaving a hole

              sensorState[i] = false;
              //Serial.print ("Out ");
              //Serial.println (i);
            }
        }
    }

  // And ready for the next data

  nextData = (nextData + 1) % NUM_SAMPLES;
}


// Local Variables:
// mode: C++
// c-file-style: "gnu"
// indent-tabs-mode: nil
// End:
