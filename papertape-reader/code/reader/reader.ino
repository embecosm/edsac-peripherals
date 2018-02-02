/* The code to work the EDSAC simulating tape reader

   Copyright (C) 2017-2018  Embecosm Limited

   Contributor: Jeremy Bennett <jeremy.bennett@embecosm.com>
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

//! Inverse exponential smoothing factor.  Using the inverse allows us to keep
//! arithmetic integer.

static const int INV_SMOOTH = 5;

//! Number of data sensors

static const int NUM_SENSORS = 6;

//! All the data sensors

static const int SENSOR_PIN[NUM_SENSORS] = {
  A5, A4, A3, A2, A1, A0 };

//! The sprocket sensor (A3)

static const int SPROCKET_PIN = 2;

//! All 6 reader LEDs are driven off the same pin.

static const int READER_LED_PIN = 13;      // select the pin for the LED

//! A LED to tell us we are alive!

static const int STATUS_LED_PIN = 12;

//! A heuristic to determine if we have a strong enough signal for the
//! sprocket.  We only recognize a minimum if the slope has got below this
//! value before crossing zero.

static const int DXDT_HEUR_SPROCKET = -30;

//! A heuristic to determine if we have a strong enough signal for the
//! data.  We only recognize a minimum if the slope has got below this
//! value before crossing zero.

static const int DXDT_HEUR_DATA = -50;

//! Type for data. Signed, because when used for derivatives these may be
//! negative.

struct PtData
{
  int val[NUM_SENSORS];           // Data values
};

//! We use backward differences, so need 2 data points for dx/dt and
//! d2x/dt2. 2 element circular buffers with a pointer are appropriate

//! Raw data is in the range 0 - 1023.  We multiply by 10 to give more bits
//! for the exponential smoothing, while remaining an integer < 32768.

struct {
  struct PtData x[2];
  struct PtData dxdt[2];
  struct PtData minDxdt;
  unsigned int curr;
} data;

//! Debug counter

int dbgCnt;

//! Debug max

static const int DBG_MAX = 0;


//! Get first set of data

//! Smoothing is best if the first data point is just read.

static void
initData ()
{
  int prev = data.curr;
  int curr = 1 - prev;

  // Get initial sensor value

  for (size_t i = 0; i < NUM_SENSORS; i++)
    data.x[curr].val[i] = analogRead (SENSOR_PIN[i]) * 10;

  // Rotate the circular buffer

  data.curr = curr;

}       // initData ()


//! Get another set of data

//! We compute the derivatve and the minimum derivative values.

static void
updateData ()
{
  int prev = data.curr;
  int curr = 1 - prev;

  // Process each sensor in turn

  for (size_t i = 0; i < NUM_SENSORS; i++)
    {
      // Read and smooth the data

      int  newVal = analogRead (SENSOR_PIN[i]);
      int  oldVal = data.x[prev].val[i];

      data.x[curr].val[i] =
        (oldVal * (INV_SMOOTH - 1) + newVal * 10) / INV_SMOOTH;

      // dx/dt and its minimum recorded value

      data.dxdt[curr].val[i] = data.x[curr].val[i] - data.x[prev].val[i];
      data.minDxdt.val[i] = min (data.minDxdt.val[i], data.dxdt[curr].val[i]);

      if ((dbgCnt < DBG_MAX))
        {
          Serial.print (newVal, DEC);
          Serial.print (",");
          Serial.print (data.x[curr].val[i], DEC);
          Serial.print (",");
          Serial.print (data.dxdt[curr].val[i], DEC);
          Serial.print (",");
          Serial.print (data.minDxdt.val[i], DEC);

          if (i < (NUM_SENSORS - 1))
            Serial.print (",");
        }
    }

  if (dbgCnt < DBG_MAX)
    {
      Serial.println ("");
      dbgCnt++;
    }

  // Rotate the circular buffer

  data.curr = curr;

}       // updateData ()


//! Standard setup

//! @note Don't go for GNU style declaration here - it breaks Arduino

void setup()
{
  // declare the various LED pins as outputs:

  pinMode(READER_LED_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);

  // Make sure we can talk to the serial monitor

  Serial.begin(115200);

  // Debug setup

  dbgCnt = 0;

  Serial.println ("Get ready");
  delay (2000);

  // Turn on the LEDs and allow resistors to respond.

  digitalWrite (READER_LED_PIN, HIGH);
  digitalWrite (STATUS_LED_PIN, LOW);
  delay (500);

  // Populate our initial data.  A second set of data is needed to ensure the
  // first derivative values are meaningful, but this will be at the start of
  // the main loop.

  data.curr = 0;
  initData ();

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

//! We find the center point of the sprocket hole when the following is true.
//! 1. the first derivative of the sprocket hole has crossed zero from
//!    negative to non-negative (including zero).  This means it is a minimum,
//!    not a maximum.
//! 2. the first derivative of the sprocket hole has gone below
//!    DXDT_HEUR_SPROCKET since last being positive.  This allows us to ignore
//!    noise before the tape starts.

//! Once we have the center of the sprocket hole, we look at all the data
//! holes. We have a data hole if the first derivative of the data hole has
//! gone below DXDT_HEUR_DATA since last being positive.

//! @note Don't go for GNU style declaration here - it breaks Arduino

void loop()
{
  // Wait, so we don't go too fast and then turn off the status light (in case
  // it was on) and update the data.

  delay (5);
  digitalWrite (STATUS_LED_PIN, LOW);
  updateData ();

  // Have we found the center of a sprocket hole? If so reset minDxdt value
  // and capture the data value.

  int  curr = data.curr;
  int  prev = 1 - data.curr;

  if ((data.dxdt[prev].val[SPROCKET_PIN] < 0)
      && (data.dxdt[curr].val[SPROCKET_PIN] >= 0))
    {
      // A real sprocket hole if we had had enough slope

      if (data.minDxdt.val[SPROCKET_PIN] < DXDT_HEUR_SPROCKET)
        {
          // Holes are LSB to MSB.  Build up value. Don't use an unsigned
          // index for counting backwards (always >= 0).

          unsigned char  res = 0;

          for (int i = (NUM_SENSORS - 1); i >= 0; i--)
            if (SPROCKET_PIN != i)
              {
                res = res << 1;
                res |= (data.minDxdt.val[i] < DXDT_HEUR_DATA) ? 1 : 0;
              }

          // Log the output and flash the light

          Serial.print ("Hex: ");
          Serial.println (res, HEX);
          digitalWrite (STATUS_LED_PIN, HIGH);
        }

      // Always reset all minima at a crossing (do this after the test above
      // of course)

      for (int i = (NUM_SENSORS - 1); i >= 0; i--)
        data.minDxdt.val[i] = 0;            // Reset
    }
}       // loop ()


// Local Variables:
// mode: C++
// c-file-style: "gnu"
// indent-tabs-mode: nil
// End:
