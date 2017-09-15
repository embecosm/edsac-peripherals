Welcome to the level shifter folder.
---

One the small breadboards there are two circuits. Both circuits are powered with 5V throough the red wire and GND to the black wire.
Circuit schematic 2 uses the pink wires; 3.3v to 5v. Connect the myStorm output to the arduino input using this circuit.
The other wires are circuit schematic 1; 5v to 3.3v. This is the myStorm input to the arduino output circuit.

They use the BJT common emitter circuits to amplify the input signal to the appropriate level chossen by the resistor ratios.

Please ask if you need another breadboard to seperate the circuits to make them easier to use.

Bill of materials
---

Circuit 1 uses:
 * 2 npn BJTs
 * 3 1k ohm resistos
 * 1 470 ohm resistor
 * 22 ohm, 330 ohm, 150 ohm resistors (to convert 5v power to 3.3v using a potential divider)
 
 Circuit 2 uses:
 * 2 npn BJTs
 * 3 4k ohm resistors
 * 1 470 ohm resistor
