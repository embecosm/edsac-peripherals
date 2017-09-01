# Order Generator

An Arduino program to generate 5-hole paper tape using an Adafruit thermal
printer.

## Prequisites

This uses the
[Adafruit Thermal Printer library](https://github.com/adafruit/Adafruit-Thermal-Printer-Library). Clone
this into your Arduino library directory:
- On Linux: (home directory)/sketchbook/libraries
- On Mac:: In (home directory)/Documents/Arduino/libraries
- On Windows:: My Documents\Arduino\libraries

For example on Linux
```
cd ~/sketchbook/libraries
git clone https://github.com/adafruit/Adafruit-Thermal-Printer-Library.git Adafruit_Thermal
```
You will need to restart the Arduino IDE after setting this up.

## The program

Load `printcode.ino` into the Arduino IDE and upload to the printer.

Open a serial monitor and enter numbers (in decimal) to be uploaded, with each
number followed by a comma.

The numbers will be printed in 5-hole format. Note that only the bottom 5 bits
of numbers larger than 31 will be printed.


## The generator program

The images for the data and sprocket holes are held as constant bitmaps in
`printcode.ino`. The declarations and initialization of these can be generated
on your host computer using the `gencode.c` program.  For example on Linux.
```
gcc -o genmap genmap.c
./genmap holeMap 50 50
./genmap holeMap 50 35
```
