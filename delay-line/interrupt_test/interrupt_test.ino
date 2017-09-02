/* Using the sensor kit stuff and the timer1.h file 
 * Bits are written to the speaker
 * Bits are red from the mic
 * Using passive buzzer and big sound microphone
 * Design did not work
 * First draft 2017 August 31st
 ***************************************************/ 

#include <TimerOne.h>

// Number of bits

const int NUM_TX_BITS = 36;
const int NUM_RX_BITS = NUM_TX_BITS * 2;

// Work out number of usecs per bit, on the basis that the speed of sound
// is 343 m/s and the tube is 1 m long
// For 36bits: 80.98477, wait a second then send the other half

const long int TIMING = 1000000L / 343 / NUM_RX_BITS /2;

// Arrays for output and input words

bool tx_bits[NUM_TX_BITS];		// Output
bool rx_bits[NUM_RX_BITS];		// Input

// Microphone is set to digital pin 5

const uint8_t MICROPHONE_PIN = 5;

// Speaker is on digital pin 6

const uint8_t SPEAKER_PIN = 6;

// The next bits to process

int nextRxBit;
int nextTxBit;

/***************************************************/ 

// converts 0 and 1 to pulses
void sendVal (int value) {
  if (value == 1) {
    digitalWrite(SPEAKER_PIN, LOW);
  }
  else if (value == 0) {
    digitalWrite(SPEAKER_PIN, HIGH);
  }
}

// ISW wakes up at 12kHz. Get everything done in 80us!
// Send next pulse
// Read the microphone
// Store in array
// Repeats
void isr () {
  
  // Output to buzzer
  sendVal(tx_bits[nextTxBit]);

  // increment next bit
  if (nextTxBit == (NUM_TX_BITS - 1))
  {
    nextTxBit = 0;
  }
  else nextTxBit++;

  // Read from microphone
  rx_bits[nextRxBit] = (HIGH == digitalRead (MICROPHONE_PIN)) ? false : true;

  // Increment next bit, stopping if we have read all of them

  if (nextRxBit == (NUM_RX_BITS - 1))
  {
      Timer1.stop ();

      for (int i = 0; i < NUM_RX_BITS; i++)
    	{
	      Serial.print (rx_bits[i] ? '1' : '0');
    	}
      
      // All done - loop forever

      while (1)
	    ;
  }
  else
  {
      nextRxBit++;
  }
}

// initialises the pins, interrupt, and FPGA array
void setup() {

  // Use serial port for output
  Serial.begin (9600);
  Serial.println ("Away we go...");

  // initialise tx_bits, in final will be from FPGA
  static int initialise[NUM_TX_BITS] =
    { 0, 1, 0, 0, 1, 1,
      0, 0, 0, 1, 1, 1,
      0, 0, 0, 0, 1, 1,
      1, 1, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 1,
      0, 0, 0, 1, 1, 1 };

  for(int i = 0; i < NUM_TX_BITS; i++) {
    tx_bits[i] = initialise[i];
  }

  // initialise pins  
  pinMode(MICROPHONE_PIN, INPUT); // microphone
  pinMode(SPEAKER_PIN, OUTPUT);  // speaker

  // Initialize the counters

  nextTxBit = 0;
  nextRxBit = 0;

  // initialise timer
  Timer1.initialize(TIMING);
  
  // set counter to 12kHz 
  Timer1.attachInterrupt (isr, TIMING);  // wakes the arduino up every timing, uses interrupts
}


// dont need
void loop() {}
