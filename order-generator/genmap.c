// Map generator for thermal printer

// Copyright (C) 2017 Embecosm Limited <www.embecosm.com>

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


// Build this program on your host machine, to create the declaration for an
// image map of a black circle within a square.

// These have to be constant static declarations, so they end up in Flash, not
// RAM in the Arduino.

// Usage

//   genmap <varname> <square-size> <hole-diam> [ <fill-ratio> ]

// varname

//   name of the map (C variable name)

// square-size

//   size of the square (pixels)

// hole-diam

//   diameter of the hole.

// fill-ratio

//   gray ratio, 1 in <fill-ratio> black pixels will be white. An omitted
//   value, or value less than 1  means no black pixels are white.  Note that
//   a value of 1 will mean no pixels are printed at all!

// Error checking is minimal.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
main (int   argc,
      char *argv[])
{
  char *varname;
  int  width;
  int  diam;
  int  fill_ratio = 0;
  int  r;
  int  r_sq;

  int  i, x, y;

  uint8_t *pixmap;
  int map_bytes = (width * width + 7) / 8;

  // Get arguments

  if ((argc < 4) || (argc > 5))
    {
      printf ("Usage: genmap <varname> <square-size> <hole-diam> [ <fill-ratio> ]\n");
      exit (EXIT_FAILURE);
    }

  varname = argv[1];
  width = atoi (argv[2]);
  diam = atoi (argv[3]);

  if (5 == argc)
    fill_ratio = atoi (argv[4]);

  if ((4 == argc) || (fill_ratio < 1))
    fill_ratio = width * width;

  // Compute derived values

  r = diam / 2;
  r_sq = r * r;
  map_bytes = (width * width + 7) / 8;

  // Set up and clear the pixmap

  pixmap = malloc (width * width * sizeof (*pixmap));
  memset (pixmap, 0, map_bytes);

  for (x = 0; x < width; x++)
    {
      int  x_off    = x - width / 2;
      int  x_off_sq = x_off * x_off;

      for (y = 0; y < width; y++)
	{
	  int  y_off = y - width / 2;
	  int  y_off_sq = y_off * y_off;

	  int rowbit  = y * width + x;
	  int rowbyte = rowbit / 8;
	  int bit     = 7 - rowbit % 8;

	  if (((x_off_sq + y_off_sq) < r_sq)
	      && (0 != ((x + y) % fill_ratio)))
	    {
	      // In circle and filled - bit is black.

	      pixmap[rowbyte] |= 1 << bit;
	    }
	  else
	    {
	      // Not in circle or not filled - bit is white

	      pixmap[rowbyte] &= ~(1 << bit);
	    }
	}
    }

  printf ("static const uint8_t  IMAGE_BYTES = %d;\n\n", map_bytes);
  printf ("static const uint8_t  %s[IMAGE_BYTES] = {", varname);

  for (i = 0; i < map_bytes; i++)
    {
      if (0 == i % 8)
	printf ("\n  ");
      else
	printf (" ");

      printf ("0x%02x", pixmap[i]);

      if (i < (map_bytes - 1))
	printf (",");
    }

  printf ("\n};\n");
  free (pixmap);
}
