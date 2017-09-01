/* 4kHz pulse idea with interupt 
 * First edit: 2017 August 31st
 *****************************************************
 * 2017 September 1st
 * Completed interupt handler routine using withInterupt
 * Added Serial port testing
 * Compiles: 9:40
 *****************************************************/

#include <TimerOne.h>


// Number of bits to buzzer

const int NUM_TX_BITS = 36;

// Number of bits for the speaker

const int NUM_RX_BITS = NUM_TX_BITS + 10;

// The time to wake up for, us

const long int TIMING = 50000;//1000000L / 343 / NUM_TX_BITS /2;

// Speaker pin: PD6

const uint8_t SPEAKER_PIN = 6;

// Microphone pin: PD5

const uint8_t MICROPHONE_PIN = 5;

// Arrays for information

/* For testing the speaker, ignore the first bit */
bool WRITE [NUM_TX_BITS + 1] = { 1, 0, 1, 0, 0, 1,
                 	   		       	 1, 0, 0, 0, 1, 0,
                        				 0, 1, 0, 1, 0, 0,
                        				 1, 1, 0, 1, 0, 1,
                        				 1, 1, 0, 1, 0, 0,
                        				 1, 1, 0, 0, 0, 1, 0};
/* For testing the microphone, shall be printed output to serial */
bool rx_bits [NUM_RX_BITS];

// The next bits to process

int nextRxBit;
int nextTxBit;

/*******************************************************/

// Converts 0s and 1s to repective pulse
void sendVal(int value) {
  if (value == 1) digitalWrite(SPEAKER_PIN, LOW);
  else if (value == 0) digitalWrite(SPEAKER_PIN, HIGH);
}

// ISW wakes up at a variable time
// Send the pulse
// Read the microphone
// Store in array
void isr () {
  // Buzzer output
  sendVal(WRITE[nextTxBit]);

  // Increment to next Tx bit
  if (nextTxBit == NUM_TX_BITS)
  {
    nextTxBit = 0;
  }
  else nextTxBit++;

  // Microphone input to replace the value sent to the buzzer & invert
  if(nextRxBit != 0) rx_bits[nextRxBit - 1] = ((digitalRead(MICROPHONE_PIN) == LOW) ? HIGH : LOW);
  
  // Increment next Rx bit or print data
  if (nextRxBit == (NUM_RX_BITS - 1))
  {
    nextRxBit = 0;
    sendVal(0);
    Timer1.stop ();
  }
  else nextRxBit++;
}

// initialises variables and calls the interrupt, isr
void setup() {
  // initialise pins
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(MICROPHONE_PIN, INPUT);

  // Initialise Serial port
  Serial.begin(9600);
  Serial.println("Start Serial port");

  // initialise bit counters
  nextTxBit = 0;
  nextRxBit = 0;

  // initialise timer
  Timer1.initialize(TIMING);
  Timer1.attachInterrupt(isr, TIMING);
}

// not needed
void loop() {
  sendVal(0);
  
  for (int i = 0; i < NUM_RX_BITS; i++)
  {
    Serial.print (rx_bits[i] ? '1' : '0');
  }
  Serial.println();

  delay(1000);
}
