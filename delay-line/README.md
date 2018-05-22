Welcome to the delay line prototype folder.
---

The ouput circuit is connected between pin PD3 and ground. It uses two resistors to impedance match to the arduino.

The input circuit is connected between pin PD3, five volts and ground. The first part of the circuit is impedance matching to the microphone. Second is the basic LM386 circuit. Connecting the two is a trim pot to control the sensitivity of the microphone.

Any ideas for a better design are welcome.

Bill of materials
---

* Microphone (KEEG1538WB-100LB)
* Speaker
* 1k ohm resistor.
* 10k ohm resistor.
* 10k ohm trim potentiometer.
* 0.1uF capacitor.
* 2x 10uF capacitor.
* 100uF capacitor.
* 0.047uF capacitor.
* LM386 audio amplifier.
* 1 meter long plastic pipe.
* Acoustic foam.
* Small screwdriver to change the trim potentiometers sensitivity.

Software
---

To run the basic program, download *delay_line.ino* and upload to arduino. This will store a 10 bit word in the tube.