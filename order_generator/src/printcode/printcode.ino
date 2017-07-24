// Thermal binary printer

// Copyright (C) 2017 Embecosm Limited <www.embecosm.com>

// Contributor: Peter Bennett <peter.bennett@embecosm.com>
// Contributor: Dan Gorringe <dan.gorringe@embecosm.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "Adafruit_Thermal.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"

// Printer connection buttons

#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

int led = 13;

  // How many bit rows to print

  static const int MAX_ROWS = 1400;

// How many orders to print

static const int MAX_ORDERS = 14;

// Which row are we one

int  rowNum = 0;

//width of bitmap

static const int PIXEL_WIDTH = 384;

// Constants for holes

static const int HOLE_START  = 74;                      // Center of first hole
static const int HOLE_OFF    = 61;                      // Offset to next hole
static const int HOLE_WIDTH  = 50;

// For recieving over serial


int incomingByte;
int integerValue;

void setup() {

   Serial.begin(9600);

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(19200);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer.begin();        // Init printer (same regardless of serial type)

  rowNum = 0;           // Next row to print
  incomingByte = 0;
  integerValue = 0;
}


// Print a 5 hole row

// Holes go at 49-99 and then 61 bits on from the centre at 74.

static void
print5Holes (uint8_t bits)
{
  bool data[5];                                 // Easier to have a vector

  for (int i = 0; i < 5; i++)
    data[i] = (bits >> i & 1) == 1;


  uint8_t row[PIXEL_WIDTH/8];           // Single pixel line

  memset (row, 0, PIXEL_WIDTH / 8);     // Clear all the bits

  // Print 5 holes

  for(int i = 0; i < 5; i++)
    {
      // Set all the pixels of this hole if enabled, just a thin line
      // otherwise.

      int w = data[i] ? HOLE_WIDTH : 2;               // If data[i] is true w = HOLE_WIDTH else w = 2
      int pixel = HOLE_START - w / 2 + i * HOLE_OFF;

      for (int j = pixel; j < pixel + w; j++)
        {
          int ibyte = j / 8;            // Which byte to modify
          int ibit  = j % 8;            // Which bit within the byte
          uint8_t x = 0x80 >> ibit;     // The modified byte

          row[ibyte] |= x;              // OR the byte into the row
        }
    }

  // Print the completed line. FALSE says data mem, not code mem
  // Print HOLE_WIDTH rows

  for (int h = 0; h < HOLE_WIDTH; h++)
    {
      rowNum++;
      printer.printBitmap(PIXEL_WIDTH, 1, row, false);
    }
}       // print5Holes ();

// Recieve data over serial and print if you do not recieve another number

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // Print back for debugging
    Serial.print("IncomingByte is: ");
    Serial.println((incomingByte), DEC);
    // If an ascii number increment the integer value
    if (incomingByte > 47){
      Serial.print("Incrementing integer Value");
      integerValue = (integerValue * 10) + (incomingByte - 48);
      Serial.print("integer is now:");
      Serial.println((integerValue), DEC);
    }
    // If not a number inputted then print out the order
    else{
    Serial.print("Printing:");
    Serial.println((integerValue), DEC);
    print5Holes(integerValue);
    print5Holes(0);
    integerValue = 0;
    }
  }
}
