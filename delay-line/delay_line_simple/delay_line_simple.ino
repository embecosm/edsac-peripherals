/* The simple program that uss a 4kHz signal from the active buzzer
 * where; 0 = no signal, 1 = signal for 1 second
 * The first value recieved by the microphone is always 1.
 * ***********************************************************
 * First edit: 2017 August 31st, by maryEmbecosm
 *   Added serial ports for testing
 *   Decreased CLK for testing
 * *********************************************************** */

// speaker pin: PD4

const int SPEAKER_PIN = 4;

// microphone pin: PD8

const int MICROPHONE_PIN = 8;

// length of a clk pulse in ms

const int CLK = 1000;

// amount of bits being sent through the tube

const int LENGTH = 36;

// array of information being sent through the tube

int buzz [LENGTH] = {0, 1, 0, 1, 0, 0,
                     1, 1, 0, 1, 0, 1,
                     1, 1, 0, 1, 0, 0,
                     1, 1, 0, 0, 0, 1,
                     0, 0, 1, 0, 1, 0,
                     0, 1, 1, 0, 1, 0};

// First word sent
const int WRITE [LENGTH] = {0, 1, 0, 1, 0, 0,
                            1, 1, 0, 1, 0, 1,
                            1, 1, 0, 1, 0, 0,
                            1, 1, 0, 0, 0, 1,
                            0, 0, 1, 0, 1, 0,
                            0, 1, 1, 0, 1, 0};

// which value in buzz gets sent

int increment;

// store samples used to calculate what the singal is

int reading;

// stores the information recieved from the buzzer

int mic_reading [LENGTH];

/*************************************************************/

// converts 0s and 1s to respective pulse required by buzzer
// buzzer is on when LOW
// int value is the bit being sent
void sendVal(int value) {
  if (value == 1) digitalWrite(SPEAKER_PIN, LOW);
  else if (value == 0) digitalWrite(SPEAKER_PIN, HIGH);
  delay(CLK);
}

// initialise pins, serial ports and variables
void setup() {
  // initialise pins
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(MICROPHONE_PIN, INPUT);

  // initialise serial port
  Serial.begin(9600);
  Serial.println("Start:");

  // initialise variables
  increment = 0;

  //initialise buzz
  for (int i = 0; i < LENGTH; i++)
    buzz[i] = WRITE[i];

  // wait half a second so that any remaining pulses/ reflections are gone
  delay(500);
}

void loop() {
  int reading_total = 0;
  
  // output to buzzer
  sendVal(buzz[increment]);
  
  // input: test for a 4kHz signal using 3 samples
  reading = digitalRead(MICROPHONE_PIN);
  
  if (reading_total == 1) mic_reading[increment] = 1;  // higher than threshold
  else mic_reading[increment] = 0;                            // lower

  buzz[increment] = mic_reading[increment];
  
  increment++;

  // print to screen after each word is sent
  if (increment == LENGTH) {
    for(int i = 0; i < LENGTH; i++) {
      Serial.print(mic_reading[i]);
    }
    Serial.println();
    digitalWrite(SPEAKER_PIN, HIGH);
    increment = 0;
    delay(CLK);
  }
}
