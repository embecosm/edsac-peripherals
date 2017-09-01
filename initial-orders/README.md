# Instructions for building
This is the part which allows the initial orders to be manually loaded on to the EDSAC implementation for MyStorm BlackIce
## Bill of materials
_Links provided are from suggested suppliers, other suppliers may exist\._
_Designs for 3D printed parts can be found in this repository\._ 
* 3D printed parts
  * Body
  * Solder board holder
  * Header bar
* [USB to UART adapter \(May require cables and/or headers depending on spec\)](www.amazon.co.uk/UART-CP2102-Module-Serial-Converter/dp/B00AFRXKFU)
* [ATMega 328P-PU \(DIP\)](uk.farnell.com/microchip/atmega328p-pu/mcu-8bit-atmega-20mhz-dip-28/dp/1715487)
* [2x Microchip MCP23017 \(DIP\)](uk.farnell.com/microchip/mcp23017-e-sp/ic-io-expander-16bit-i2c-28dip/dp/1332088)
* [3x 28 pin DIP socket](uk.farnell.com/3m/4828-3004-cp/dip-socket-28pos-2row-2-54mm-th/dp/2672306)
* [16MHz crystal](uk.farnell.com/qantek-technology-corporation/qcl16-0000f18b23b/crystal-16mhz-18pf-hc-49us/dp/2508458)
* [2x 22pF capacitor](uk.farnell.com/multicomp/mcchu5220j5/cap-cer-c0g-np0-22pf-50v-rad/dp/9411674)
* [100nF capacitor](uk.farnell.com/multicomp/mcfyu6104z6/cap-cer-y5v-100nf-50v-rad/dp/9411887)
* [10k resistor](uk.farnell.com/te-connectivity/cfr16j10k/resistor-carbon-10k-0-25w-5/dp/2329474)
* [20x 1M resistor](uk.farnell.com/multicomp/mcre000073/resistor-carbon-film-125mw-1m/dp/1700277)
* [2x 4.7k resistor](uk.farnell.com/multicomp/mcre000045/resistor-carbon-film-4-7k-0-125w/dp/1700245)
* [2x17 pin header](uk.farnell.com/wurth-elektronik/61303421121/header-2-54mm-pin-tht-vert-34way/dp/2356146)
* [25x 6x2 receptacle](uk.farnell.com/amphenol-fci/76342-306lf/socket-2row-6-6way/dp/1098051)
* [12x 5x2 receptacle](uk.farnell.com/harwin/m20-7830546/socket-pcb-0-1-5-5way/dp/7992009)
* [4x2 receptacle](uk.farnell.com/harwin/m20-7830446/socket-pcb-0-1-4-4way/dp/7991991)
* [20x Header jumper](uk.farnell.com/3m/969102-0000-da/shunt-bar-2pos-2-54mm/dp/2579814)
* [Solderable circuit board MC01011](cpc.farnell.com/multicomp/mc01011/circuit-board-152x52-550-ic-board/dp/PC01290)
* [3x 6x7mm two pin tactile switches](uk.farnell.com/multicomp/mc32879/switch-tactile-spst-no-50ma-though/dp/1712994)
* [3x lipped 5mm LED \(color of your choice\)](uk.farnell.com/multicomp/703-0097/led-5mm-green-150mcd-572nm/dp/2112108)
* [2x HDSP-C3x3 7 segment displays \(color of your choice\)](uk.farnell.com/broadcom-limited/hdsp-c3e3/led-display-9-1mm-red-cc/dp/1830006)
* [2x 4511 7 segment decoder](uk.farnell.com/texas-instruments/cd4511be/4000-cmos-4511-dip16-18v/dp/1106122)
* [Solderable circuit board MC01010](cpc.farnell.com/multicomp/mc01010/circuit-board-95x72-780-ic-board/dp/PC01289)
* [2x M3x20 hex head bolt](uk.rs-online.com/web/p/socket-screws/4733530/)
* [4x M3x8 hex head bolt](uk.rs-online.com/web/p/socket-screws/4679789/)
* [6x M3 nut](uk.rs-online.com/web/p/hex-nuts/1224400/)

## Software

### Prequisites

This uses the
[Adafruit Thermal Printer library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library). Clone
this into your Arduino library directory:
- On Linux: (home directory)/sketchbook/libraries
- On Mac:: In (home directory)/Documents/Arduino/libraries
- On Windows:: My Documents\Arduino\libraries

For example on Linux
```
cd ~/sketchbook/libraries
git clone https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library.git Adafruit_Thermal
```
You will need to restart the Arduino IDE after setting this up.

### The program

Load `initial-orders.ino` into the Arduino IDE and upload to the printer.

To load in EDSACs initial orders before sending to the myStorm board.



