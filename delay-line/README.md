Welcome to the delay line prototype folder.

simple_code.ino is the code for a simple design. It sends a 36bit word through the tube where a logic 1 is a one second long 4kHz sine wave with a large amplitute and a logic 0 is silence for one second. 

The 4kHz signal can be recieved by the microphone (if the sensitivity is correct) and then it is smoothed using a capacitor and diode. The minimum delay depends on the rise/ fall time of this circuit.

To interface to the FPGA two pins on the arduino should be used as TX and RX. When the FPGA asks for the word, the arduino should wait for the first bit of the word before sending anything.

If you are struggleing to set the microphone sensitivity, connect a wire between two pins on the arduino and send the 36bit word bettween the pins.
