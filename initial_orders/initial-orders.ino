
#include <Wire.h>
#include "Adafruit_MCP23017.h"

// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)
// Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)

// Input #0 is on pin 21 so connect a button or switch from there to ground

Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp1;
  
void setup() {  
  mcp1.begin(1);      // use default address 0
  mcp2.begin(0);      // use default address 0
  mcp1.pinMode( 0, INPUT);
  mcp1.pinMode( 1, INPUT);
  mcp1.pinMode( 2, INPUT);
  mcp1.pinMode( 3, INPUT);
  mcp1.pinMode( 4, INPUT);
  mcp1.pinMode( 5, INPUT);
  mcp1.pinMode( 6, INPUT);
  mcp1.pinMode( 7, INPUT);
  mcp1.pinMode( 8, INPUT);
  mcp1.pinMode( 9, INPUT);
  mcp1.pinMode(10, INPUT);
  mcp1.pinMode(11, INPUT);
  mcp1.pinMode(12, INPUT);
  mcp1.pinMode(13, INPUT);
  mcp1.pinMode(14, INPUT);
  mcp1.pinMode(15, INPUT);
  mcp2.pinMode( 2, INPUT);
  pinMode(13, OUTPUT);  // use the p13 LED as debugging
  Serial.begin(9600);
}



void loop() {
  // The LED will 'echo' the button
  digitalWrite(13, mcp2.digitalRead(2));
  Serial.print(mcp1.digitalRead(8));
  Serial.print(mcp1.digitalRead(9));
  Serial.print(mcp1.digitalRead(10));
  Serial.print(mcp1.digitalRead(11));
  Serial.print(mcp1.digitalRead(12));
  Serial.print(mcp1.digitalRead(13));
  Serial.print(mcp1.digitalRead(14));
  Serial.print(mcp1.digitalRead(15));
  Serial.print(mcp1.digitalRead(0));
  Serial.print(mcp1.digitalRead(1));
  Serial.print(mcp1.digitalRead(2));
  Serial.print(mcp1.digitalRead(3));
  Serial.print(mcp1.digitalRead(4));
  Serial.print(mcp1.digitalRead(5));
  Serial.print(mcp1.digitalRead(6));
  Serial.print(mcp1.digitalRead(7));
  Serial.print(mcp2.digitalRead(2));
  Serial.println();
  delay(100);
}
