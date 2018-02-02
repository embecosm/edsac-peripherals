// Thermal binary printer

// Copyright (C) 2017-18 Embecosm Limited <www.embecosm.com>

// Contributor: Peter Bennett <peter.bennett@embecosm.com>
// Contributor: Dan Gorringe <dan.gorringe@embecosm.com>
// Contributor: Jeremy Bennett <jeremy.bennett@embecosm.com>

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

SoftwareSerial mySerial (RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

// Constants for holes

static const int HOLE_START    = 44;	// Center of first hole
static const int HOLE_OFF      = 61;	// Offset to next hole
static const int HOLE_DIAM     = 50;
static const int SPROCKET_DIAM = 35;

// Which is the sprocket hole

static const int SPROCKET_HOLE = 3;

//! How much leader space

//static const int BLANK_LINES = 24;
static const int BLANK_LINES = 6;

// Size of bitmap

static const int PIXEL_WIDTH  = 384;
static const int ROW_DEPTH    = HOLE_DIAM;
//static const int SPACER_DEPTH = ROW_DEPTH / 2;
static const int SPACER_DEPTH = ROW_DEPTH;
static const int BITMAP_BYTES = (PIXEL_WIDTH + 7) / 8;

// Size of hole images

static const int IMAGE_BYTES = (ROW_DEPTH * ROW_DEPTH + 7) / 8;

// Image maps for holes and sprocket holes. These are generated on the host
// computer, using the genmap.c program

static const uint8_t hole_map[IMAGE_BYTES] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0xb6, 0xc0, 0x00, 0x00, 0x00, 0x06, 0xdb,
  0x6c, 0x00, 0x00, 0x00, 0x0b, 0x6d, 0xb6, 0xc0,
  0x00, 0x00, 0x0d, 0xb6, 0xdb, 0x6c, 0x00, 0x00,
  0x06, 0xdb, 0x6d, 0xb6, 0xc0, 0x00, 0x03, 0x6d,
  0xb6, 0xdb, 0x6c, 0x00, 0x01, 0xb6, 0xdb, 0x6d,
  0xb6, 0x80, 0x00, 0xdb, 0x6d, 0xb6, 0xdb, 0x60,
  0x00, 0x6d, 0xb6, 0xdb, 0x6d, 0xb6, 0x00, 0x36,
  0xdb, 0x6d, 0xb6, 0xdb, 0x00, 0x1b, 0x6d, 0xb6,
  0xdb, 0x6d, 0xb0, 0x0d, 0xb6, 0xdb, 0x6d, 0xb6,
  0xda, 0x02, 0xdb, 0x6d, 0xb6, 0xdb, 0x6d, 0x81,
  0x6d, 0xb6, 0xdb, 0x6d, 0xb6, 0xd0, 0x36, 0xdb,
  0x6d, 0xb6, 0xdb, 0x6c, 0x1b, 0x6d, 0xb6, 0xdb,
  0x6d, 0xb6, 0x8d, 0xb6, 0xdb, 0x6d, 0xb6, 0xdb,
  0x62, 0xdb, 0x6d, 0xb6, 0xdb, 0x6d, 0xb1, 0x6d,
  0xb6, 0xdb, 0x6d, 0xb6, 0xdb, 0x36, 0xdb, 0x6d,
  0xb6, 0xdb, 0x6d, 0x9b, 0x6d, 0xb6, 0xdb, 0x6d,
  0xb6, 0xd5, 0xb6, 0xdb, 0x6d, 0xb6, 0xdb, 0x6c,
  0xdb, 0x6d, 0xb6, 0xdb, 0x6d, 0xb6, 0x6d, 0xb6,
  0xdb, 0x6d, 0xb6, 0xdb, 0x56, 0xdb, 0x6d, 0xb6,
  0xdb, 0x6d, 0xb3, 0x6d, 0xb6, 0xdb, 0x6d, 0xb6,
  0xd9, 0xb6, 0xdb, 0x6d, 0xb6, 0xdb, 0x6d, 0x5b,
  0x6d, 0xb6, 0xdb, 0x6d, 0xb6, 0xcd, 0xb6, 0xdb,
  0x6d, 0xb6, 0xdb, 0x66, 0xdb, 0x6d, 0xb6, 0xdb,
  0x6d, 0xb5, 0x6d, 0xb6, 0xdb, 0x6d, 0xb6, 0xdb,
  0x36, 0xdb, 0x6d, 0xb6, 0xdb, 0x6d, 0x8b, 0x6d,
  0xb6, 0xdb, 0x6d, 0xb6, 0xc1, 0xb6, 0xdb, 0x6d,
  0xb6, 0xdb, 0x68, 0x5b, 0x6d, 0xb6, 0xdb, 0x6d,
  0xb4, 0x0d, 0xb6, 0xdb, 0x6d, 0xb6, 0xdb, 0x02,
  0xdb, 0x6d, 0xb6, 0xdb, 0x6d, 0x80, 0x6d, 0xb6,
  0xdb, 0x6d, 0xb6, 0xc0, 0x16, 0xdb, 0x6d, 0xb6,
  0xdb, 0x60, 0x03, 0x6d, 0xb6, 0xdb, 0x6d, 0xb0,
  0x00, 0xb6, 0xdb, 0x6d, 0xb6, 0xda, 0x00, 0x1b,
  0x6d, 0xb6, 0xdb, 0x6d, 0x00, 0x01, 0xb6, 0xdb,
  0x6d, 0xb6, 0x80, 0x00, 0x5b, 0x6d, 0xb6, 0xdb,
  0x40, 0x00, 0x05, 0xb6, 0xdb, 0x6d, 0x80, 0x00,
  0x00, 0xdb, 0x6d, 0xb6, 0xc0, 0x00, 0x00, 0x0d,
  0xb6, 0xdb, 0x60, 0x00, 0x00, 0x00, 0xdb, 0x6d,
  0xa0, 0x00, 0x00, 0x00, 0x05, 0xb6, 0xc0, 0x00,
  0x00
};

static const uint8_t sprocket_map[IMAGE_BYTES] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x02, 0xdb, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x6d, 0xb0, 0x00, 0x00, 0x00, 0x01, 0xb6,
  0xdb, 0x00, 0x00, 0x00, 0x00, 0xdb, 0x6d, 0xb0,
  0x00, 0x00, 0x01, 0x6d, 0xb6, 0xdb, 0x00, 0x00,
  0x00, 0x36, 0xdb, 0x6d, 0x80, 0x00, 0x00, 0x1b,
  0x6d, 0xb6, 0xd8, 0x00, 0x00, 0x0d, 0xb6, 0xdb,
  0x6d, 0x00, 0x00, 0x06, 0xdb, 0x6d, 0xb6, 0xc0,
  0x00, 0x03, 0x6d, 0xb6, 0xdb, 0x68, 0x00, 0x00,
  0xb6, 0xdb, 0x6d, 0xb6, 0x00, 0x00, 0x5b, 0x6d,
  0xb6, 0xdb, 0x40, 0x00, 0x0d, 0xb6, 0xdb, 0x6d,
  0xb0, 0x00, 0x06, 0xdb, 0x6d, 0xb6, 0xd8, 0x00,
  0x01, 0x6d, 0xb6, 0xdb, 0x6d, 0x00, 0x00, 0x36,
  0xdb, 0x6d, 0xb6, 0xc0, 0x00, 0x1b, 0x6d, 0xb6,
  0xdb, 0x60, 0x00, 0x05, 0xb6, 0xdb, 0x6d, 0xb4,
  0x00, 0x00, 0xdb, 0x6d, 0xb6, 0xdb, 0x00, 0x00,
  0x6d, 0xb6, 0xdb, 0x6d, 0x80, 0x00, 0x16, 0xdb,
  0x6d, 0xb6, 0xd0, 0x00, 0x03, 0x6d, 0xb6, 0xdb,
  0x6c, 0x00, 0x00, 0xb6, 0xdb, 0x6d, 0xb6, 0x00,
  0x00, 0x1b, 0x6d, 0xb6, 0xdb, 0x00, 0x00, 0x05,
  0xb6, 0xdb, 0x6d, 0x80, 0x00, 0x00, 0xdb, 0x6d,
  0xb6, 0xd0, 0x00, 0x00, 0x2d, 0xb6, 0xdb, 0x68,
  0x00, 0x00, 0x06, 0xdb, 0x6d, 0xb4, 0x00, 0x00,
  0x01, 0x6d, 0xb6, 0xdb, 0x00, 0x00, 0x00, 0x16,
  0xdb, 0x6d, 0x00, 0x00, 0x00, 0x03, 0x6d, 0xb6,
  0x80, 0x00, 0x00, 0x00, 0x36, 0xdb, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x6d, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00
};


// The program to print. Just enable one.

#if 1

// Bootloader

char *progText =
  "T0S"
  "H2S"
  "T0S"
  "E6S"
  "P1S"
  "P5S"
  "T0S"
  "I0S"
  "A0S"
  "R16S"
  "T0L"
  "I2S"
  "A2S"
  "S5S"
  "E21S"
  "T3S"
  "V1S"
  "L8S"
  "A2S"
  "T1S"
  "E11S"
  "R4S"
  "A1S"
  "L0L"
  "A0S"
  "T31S"
  "A25S"
  "A4S"
  "U25S"
  "S31S"
  "G6S";
#endif

//! Map from char code to binary representation

struct ChMap
{
  signed char    ch;                    //!< -1 means invalid
  unsigned char  val;                   //!< 32 means invalid
};

static const signed char   INVALID_CH  = -1;
static const unsigned char INVALID_VAL = 32;

//! Size of closed hash table giving char mappings.  We have 32 chars, 10
//! digits, '+' and '-', so 44 entries.  Allow a bit spare to minimize misses,
//! and make it a prime number

static const size_t  HASH_SIZE = 53;

//! THe closed hash table

struct ChMap chMap [HASH_SIZE];


//! Compute the hash function

static size_t
hash (signed char  ch)
{
  return (((size_t) ch) << 2) % HASH_SIZE;

}       // hash ()


//! Function to add a value to the hash table

static void
addHash (signed char    ch,
         unsigned char  val)
{
  size_t  hv = hash (ch);

  while (INVALID_CH != chMap[hv].ch)
    hv = (hv + 1) % HASH_SIZE;

  chMap[hv].ch  = ch;
  chMap[hv].val = val;

}       // addHash ()


//! Look up hash table

//! @para[in] ch  Character to lookup

static unsigned char
lookup (signed char  ch)
{
  size_t  hv = hash (ch);

  while ((ch != chMap[hv].ch) && (INVALID_CH != chMap[hv].ch))
    hv = (hv + 1) % HASH_SIZE;

  return chMap[hv].val;

}       // lookup ()


//! Function to initialize hash table

static void
initHash ()
{
  // Clear the table

  for (size_t i = 0; i < HASH_SIZE; i++)
    {
      chMap[i].ch  = INVALID_CH;
      chMap[i].val = INVALID_VAL;
    }

  // Initialize the lookup.  First the chars - control chars follow the Martin
  // Campbell-Kelly simulator substitution

  addHash ('P', 0x10);
  addHash ('Q', 0x11);
  addHash ('W', 0x12);
  addHash ('E', 0x13);
  addHash ('R', 0x14);
  addHash ('T', 0x15);
  addHash ('Y', 0x16);
  addHash ('U', 0x17);
  addHash ('I', 0x18);
  addHash ('O', 0x19);
  addHash ('J', 0x1a);
  addHash ('#', 0x1b);                   // Pi
  addHash ('S', 0x1c);
  addHash ('Z', 0x1d);
  addHash ('K', 0x1e);
  addHash ('*', 0x1f);                   // Erase
  addHash ('.', 0x00);                   // Blank tape
  addHash ('F', 0x01);
  addHash ('@', 0x02);                   // Phi
  addHash ('D', 0x03);
  addHash ('!', 0x04);                   // Psi
  addHash ('H', 0x05);
  addHash ('N', 0x06);
  addHash ('M', 0x07);
  addHash ('&', 0x08);                   // Delta
  addHash ('L', 0x09);
  addHash ('X', 0x0a);
  addHash ('G', 0x0b);
  addHash ('A', 0x0c);
  addHash ('B', 0x0d);
  addHash ('C', 0x0e);
  addHash ('V', 0x0f);

  // Then digits and signs

  addHash ('0', 0x10);
  addHash ('1', 0x11);
  addHash ('2', 0x12);
  addHash ('3', 0x13);
  addHash ('4', 0x14);
  addHash ('5', 0x15);
  addHash ('6', 0x16);
  addHash ('7', 0x17);
  addHash ('8', 0x18);
  addHash ('9', 0x19);

  addHash ('+', 0x05);
  addHash ('-', 0x06);

}       // initHash ()


//! Print a 5 hole row.

//! Holes are circles centered at x-offset HOLE_START and then every HOLE_OFF
//! bits.

//! Data holes are HOLE_DIAM bits in diameter, sprocket holes are SPROCKET_DIAM
//! bits in diameter. Rows have a blank separation of HOLE_DIAM bits.

//! We have to print one bit row at a time because of the limited memory on
//! the Uno.

//! The encoding of bits within a byte, is that the leftmost bit on the page
//! is the most significant bit in the byte.

//! @param[in] val  Data to print

static void
print6Holes (uint8_t val)
{
  // Break out the data

  bool data[5];

  for (int i = 0; i < 5; i++)
    data[i] = ((val >> i) & 1) == 1;

  // A general vector for a row of bits.

  uint8_t row[BITMAP_BYTES];

  // Print some blank lines before each data row

  memset (row, 0, BITMAP_BYTES);

  for (int i = 0; i < SPACER_DEPTH; i++)
    printer.printBitmap (PIXEL_WIDTH, 1, row, false);

  // Set up the data and print it out.

  for (int y = 0; y < ROW_DEPTH; y++)
    {
      uint8_t row[BITMAP_BYTES];	// Single line
      memset (row, 0, BITMAP_BYTES);    // Clear all the bits

      for(int i = 0; i < 6; i++)
	{
	  // Allow for the sprocket hole in the 2nd position

	  int  data_no = (i > SPROCKET_HOLE) ? i - 1 : i;

	  int x_off = HOLE_START + HOLE_OFF * i - ROW_DEPTH / 2;

	  for (int x = 0; x < ROW_DEPTH; x++)
	    {
	      // Bit position for the complete row

	      int rowbit    = x_off + x;
	      int rowbyte   = rowbit / 8;
	      int rowbitoff = 7- rowbit % 8;

	      // Bit postion for the image map

	      int imgbit    = y * ROW_DEPTH + x;
	      int imgbyte   = imgbit / 8;
	      int imgbitoff = 7 - imgbit % 8;

	      if (SPROCKET_HOLE == i)
		{
		  // Sprocket hole, in line

		  uint8_t imgval = (sprocket_map[imgbyte] >> imgbitoff) & 1;
		  row[rowbyte] |= imgval << rowbitoff;
		}
	      else if (data[data_no])
		{
		  // Mark the hole

		  uint8_t imgval = (hole_map[imgbyte] >> imgbitoff) & 1;
		  row[rowbyte] |= imgval << rowbitoff;
		}
	      else
		{
		  // Don't mark the hole

		  uint8_t imgval = (hole_map[imgbyte] >> imgbitoff) & 1;
		  row[rowbyte] &= ~(imgval << rowbitoff);
		}
	    }
	}

      // Print the data line

      printer.printBitmap (PIXEL_WIDTH, 1, row, false);
    }

}       // print6Holes ();


//! Standard setup code.

//! @Note Due to a bug in Wiring, GNU standard syntax will not work for this
//!       function. The type has to be on the same line as the function name.

void setup ()
{
  // Standard serial port, so we can communicate with a console.

  Serial.begin(9600);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.

  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)

  // Initialize the EDSAC hash table

  initHash ();

  Serial.print("Producing leader");

  // A header to help the user

  printer.justify('C');
  printer.println("start"); // To indicate where the first order is
  printer.justify('L');

  // Blank paper to feed into the reader

  for (int x = 0; x < BLANK_LINES; x++)
    print6Holes (lookup (' '));               // Just sprocket holes

  // Print the tape

  for (int i = 0; progText[i] != 0; i++)
    {
      signed char ch = progText[i];
      unsigned char val = lookup (ch);

      if (INVALID_VAL == val)
        {
          Serial.print("Ignoring char: ");
          Serial.println((char) ch);
        }
      else
        {
          Serial.print("Printing: ");
          Serial.print((char) ch);
          Serial.print(" = 0x");
          Serial.println(val, HEX);

          print6Holes(val);
        }
    }

  Serial.print("Producing trailer");

  // Blank paper tail

  for (int x = 0; x < BLANK_LINES; x++)
    print6Holes (lookup (' '));               // Just sprocket holes

}


//! Receive one 5-bit number over serial and print it.

//! We accept ASCII digits, and print when we receive a non-digit.

void loop() {

}	// loop ()


// Local Variables:
// mode: C++
// c-file-style: "gnu"
// indent-tabs-mode: nil
// End:
