/*
some initial comment nosense
 */

int sensorPin1  = A4;    // select the input pin for the potentiometer
int sensorPin2  = A3;    // select the input pin for the potentiometer
int sensorPin4  = A2;    // select the input pin for the potentiometer
int sensorPin8  = A1;    // select the input pin for the potentiometer
int sensorPin16 = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue1  = 0;  // variable to store the value coming from the sensor
int sensorValue2  = 0;  // variable to store the value coming from the sensor
int sensorValue4  = 0;  // variable to store the value coming from the sensor
int sensorValue8  = 0;  // variable to store the value coming from the sensor
int sensorValue16 = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  // read the value from the sensor:
  sensorValue1  = analogRead(sensorPin1);
  sensorValue2  = analogRead(sensorPin2);
  sensorValue4  = analogRead(sensorPin4);
  sensorValue8  = analogRead(sensorPin8);
  sensorValue16 = analogRead(sensorPin16); 
  if(sensorValue16 < 250){
    Serial.print("1");
  }
  else{
    Serial.print("0");
  }
  if(sensorValue8 < 240){
    Serial.print("1");
  }
  else{
    Serial.print("0");
  }  
  if(sensorValue4 < 350){
    Serial.print("1");
  }
  else{
    Serial.print("0");
  }
  if(sensorValue2 < 373){
    Serial.print("1");
  }
  else{
    Serial.print("0");
  }
  if(sensorValue1 < 490){
    Serial.print("1");
  }
  else{
    Serial.print("0");
  }
  Serial.print(" ");
  Serial.print(sensorValue16);
  Serial.print(" ");
  Serial.print(sensorValue8);
  Serial.print(" ");
  Serial.print(sensorValue4);
  Serial.print(" ");
  Serial.print(sensorValue2);
  Serial.print(" ");
  Serial.print(sensorValue1);
  Serial.println();
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);  
  delay(6000);                  
}
