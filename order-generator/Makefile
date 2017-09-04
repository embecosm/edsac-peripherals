# Make file for map generator for thermal printer

# Copyright (C) 2017 Embecosm Limited <www.embecosm.com>

# Contributor: Peter Bennett <peter.bennett@embecosm.com>
# Contributor: Dan Gorringe <dan.gorringe@embecosm.com>
# Contributor: Jeremy Bennett <jeremy.bennett@embecosm.com>

# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.

# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http:#www.gnu.org/licenses/>.


CC = gcc
CPPFLAGS =
CFLAGS = -ggdb3 -O2
LD = gcc
LDFLAGS =

EXE = genmap
OBJS = genmap.o

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(EXE) $(OBJS)
