// Map generator for thermal printer

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

// Build this program on your host machine, to create the declaration for an
// image map of a black circle within a square.

// These have to be constant static declarations, so they end up in Flash, not
// RAM in the Arduino.

// Takes three arguments in position order

// - name of the map (C variable name)
// - size of the square (pixels)
// - diameter of the hole.

// Error checking is minimal.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
main (int   argc,
      char *argv[])
{
  char *varname = argv[1];
  int  width = atoi (argv[2]);
  int  diam = atoi (argv[3]);
  int  r = diam / 2;
  int  r_sq = r * r;

  int  i, x, y;
  uint8_t pixmap[50000];		// Just loads
  int map_bytes = (width * width + 7) / 8;

  memset (pixmap, 0, map_bytes);     // Clear all the bits

  for (x = 0; x < width; x++)
    {
      int  x_off    = x - width / 2;
      int  x_off_sq = x_off * x_off;

      for (int y = 0; y < width; y++)
	{
	  int  y_off = y - width / 2;
	  int  y_off_sq = y_off * y_off;

	  int rowbit  = y * width + x;
	  int rowbyte = rowbit / 8;
	  int bit     = 7 - rowbit % 8;

	  if (((x_off_sq + y_off_sq) < r_sq)
	      && (0 == ((x_off ^ y_off) % 2)))
	    {
	      // In circle and alternate - bit is black.
	      pixmap[rowbyte] |= 1 << bit;
	    }
	  else
	    {
	      // Not in circle - bit is white
	      pixmap[rowbyte] &= ~(1 << bit);
	    }
	}
    }

  printf ("static const uint8_t  %s[%d] = {", varname, map_bytes);

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

}
