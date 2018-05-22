// The speaker will only play a sound when there is a change in pd 

//const boolean START[10] = {1,1,1,1,1,1,1,1,1,1};
//const boolean START[10] = {0,0,0,0,0,0,0,0,0,0};
const boolean START[10] = {1,0,0,1,0,1,0,0,0,0};

boolean value[10] = {1,1,1,1,1,1,1,1,1,1};

// speaker pin: PD4
const unsigned int SPEAKER_PIN = 4;

// microphone pin: PD3
const unsigned int MIC_PIN = 3;

const unsigned int LED = 2;
const unsigned int THRESHOLD = 345; //340 definately works

// Clock: 3.432kHz
const unsigned int SOUND = 343;
const unsigned int CLK = 3430;
const unsigned int DELAY_CLK = 1000000 / CLK; //~291us
const unsigned int DELAY_CLK_4 = DELAY_CLK / 4;
const unsigned int DELAY_CLK_2 = DELAY_CLK / 2;

const unsigned int READ_TIME = 4;  //1us -> 4us
const unsigned int WRITE_TIME = 2; //2us
const unsigned int SERIAL_TIME = 104;  //10s/9600 = 104us

int i, reset;
const unsigned int RESET_AMOUNT = 10;  // amount of seconds

//for when value[i] = 1
//up, wait 1/4, read, wait 1/4, low, wait 1/2

void start() {
  int j;
  // need to have bits in tube before reading

    for (j = 0; j < 10; j++)
    {
      value[j] = START[j];
      if (value[j] == 1)
      {
        tone(SPEAKER_PIN, CLK);
        delay(50);
        delay(50);
        
      }
      else if (value[j] == 0)
      {   
        noTone(SPEAKER_PIN);
        delay(50);
        delay(50);
      }
    }  
}

void setup() {
  
  // initialize pins
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(MIC_PIN, INPUT);
  pinMode(LED, OUTPUT);

  //reset
  reset = 0;
  i = 0;
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("ON");
  delay(1000);

  start();
}

void loop() {

  // define the current and next bit from value
  unsigned int thisBit = value[i];
  unsigned int store;
  
  if (thisBit == 1)
  {
    tone(SPEAKER_PIN, CLK);
    delay(42);
    value[i] = digitalRead(MIC_PIN);
    delay(58 - 1);
  }
  else if (thisBit == 0)
  {    
    noTone(SPEAKER_PIN);
    delay(42);
    store = analogRead(MIC_PIN);
    if (store > THRESHOLD) value[i] = 1;
    else value[i] = 0;
    //value[i] = digitalRead(MIC_PIN);
    delay(58 - 1);
  }

  if (value[i] == 1) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);

  // Increase i
  if (i == 9) //repeat
  {
    i = 0;
    reset++;
    Serial.println(value[9]);
  }
  else 
  {
    i++;
    Serial.print(value[i-1]);
  }
  //Reset
  if (reset == RESET_AMOUNT)
  {
    noTone(SPEAKER_PIN);
    reset = 0;
    delay (1000);
    Serial.println("Reset!");
    start();
  }
}
