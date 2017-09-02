/* The simple program that uss a 4kHz signal from the active buzzer
 * where; 0 = no signal, 1 = signal for 1 second
 * The first value recieved by the microphone is always 1.
 * ***********************************************************
 * First edit: 2017 August 31st, by maryEmbecosm
 *   Added serial ports for testing
 *   Decreased CLK for testing
 * *********************************************************** */

// speaker pin: PD6

const int SPEAKER_PIN = 6;

// microphone pin: PD5

const int MICROPHONE_PIN = 5;

// length of a clk pulse in ms

const int CLK = 50;
const int CLK_TWO = CLK/2;

// threshold for average calculation

const int THRESHOLD = 1;

// amount of bits being sent through the tube

const int LENGTH = 50;    //add 1, the first bit is always 1

// array of information being sent through the tube, first bit sent == 1 when recieved

const int WRITE [LENGTH] = {0, 1, 0, 1, 0, 0,
                            1, 1, 0, 1, 0, 1,
                            1, 1, 0, 1, 0, 0,
                            1, 1, 0, 0, 0, 1,
                            0, 0, 1, 0, 1, 0,
                            0, 1, 1, 0, 1, 0,
                            1, 1 ,1 ,0 ,1 ,0,
                            0, 1, 1, 0, 0, 0,
                            1, 0};

// which value in WRITE gets sent

int increment;

// store samples used to calculate what the singal is

int reading [3];

// stores the information recieved from the buzzer

int mic_reading [LENGTH];

/*************************************************************/

// converts 0s and 1s to respective pulse required by buzzer
// buzzer is on when LOW
// int value is the bit being sent
void sendVal(int value) {
  if (value == 1) digitalWrite(SPEAKER_PIN, LOW);
  else if (value == 0) digitalWrite(SPEAKER_PIN, HIGH);
  delay(CLK_TWO);
}

// initialise pins, serial ports and variables
void setup() {
  // initialise pins
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(MICROPHONE_PIN, INPUT);

  // initialise serial port
  Serial.begin(9600);
  Serial.println("Start");

  // initialise variables
  increment = 0;

  // wait half a second so that any remaining pulses/ reflections are gone
  delay(500);
}

// 
void loop() {
  int reading_total = 0;
  
  // output to buzzer
  sendVal(WRITE[increment]);
  
  // input: test for a 4kHz signal using 3 samples
  for (int i = 0; i < 3; i++) {
    reading[i] = digitalRead(MICROPHONE_PIN);
  }
  reading_total = reading[0] + reading[1] + reading[2];
  if (reading_total > THRESHOLD) mic_reading[increment] = 0;  // higher than threshold
  else mic_reading[increment] = 1;                            // lower

  // so that the readings are in the middle of the pulse
  delay(CLK_TWO);
  
  increment++;

  // print to screen after each word is sent
  if (increment == LENGTH) {
    for(int i = 0; i < LENGTH; i++) {
      if (i != 0) Serial.print(mic_reading[i]);
    }
    Serial.println();
    digitalWrite(SPEAKER_PIN, HIGH);
    delay(CLK);
  }
}
