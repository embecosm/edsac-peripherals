/*
The code to work the EDSAC simulating tape reader
Copyright (C) 2017  Embecosm Ltd
Contributor: Peter Bennett <peter.bennett@embecosm.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <math.h>

int sensorPin[05] = {A4,A3,A2,A1,A0}; //pins for the analog ins
int ledPin = 13;      // select the pin for the LED
int sensorValue[20][05];
int bits[05];
//length of change measuring period
int readtime = 40;
//difference required over period to be cosidered significant
int threshold = 20;
//x value of old read
int m = 10;
double bitsValue[05];
int response[20];
int difference[05];

void setup() {
  // declare the ledPin for the green leds as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Assign the 0th place to be the most recent, and move everything up one on each new reading
  int i = 0;
  int j = 0;
  int n = 0;
  response[n] = response[n-1];
  for (n = 19; n > 0; n--){
  };
  for (i = 0; i < 5; i++){
    int l = 0;
    for (l = 19; l > -1; l--){
      sensorValue[l][i] = sensorValue[l-1][i];
    };
    // Read the value of the sensor and put in sensorValue[0]
    sensorValue[0][i] = analogRead(sensorPin[i]);
  };
  // Read the difference between the latest reading and the mth value
  int p = 0;
  for (p = 0; p < 5; p++){
    difference[p] = sensorValue[0][p] - sensorValue[m][p];
    //difference is NEGATIVE if you are entering a darker area
  };
  //make any changes to the bits if they have changed by a significant amount recently
  for (j = 0; j < 5; j++){
    if(difference[j] < - threshold){
      //a dark dot signifies a 1
      bits[j] = 1;
      bitsValue[j] = pow(2,j);
    }
    else if(difference[j] > + threshold){
      //If there is no dot, assign the bit to a 0
      bits[j] = 0;
      bitsValue[j] = 0;
    };
  }

  // Create a quasi response, e.g. add up all the values of each reading to create a decimal number
  response[0] = bitsValue[0] + bitsValue[1] + bitsValue[2] + bitsValue[3] + bitsValue[4];

  if(response[0] != response[1]){
    //print the number in binary
    Serial.print("Binary: ");
    int q = 0;
    for (q = 4; q > -1; q--){
      Serial.print (bits[q]);
    };
    Serial.print("    Actual value: ");
    //get the right number of spaces so the next bit lines up
    if(response[0] < 9.5){
      Serial.print(" ");
    };
    //print the decimal value
    Serial.print(response[0]);
    Serial.print("    Differences: ");
    int k = 0;
    for (k=0; k<5; k++){
      //work out the right number of spaces for each difference so they line up and are easy to read
      if (difference[k] < -99.5){
        Serial.print(" ");
      }
      else if (difference[k] < -9.5){
        Serial.print("  ");
      }
      else if (difference[k] < -0.5){
        Serial.print("   ");
      }
      else if (difference[k] < 9.5){
        Serial.print("    ");
      }
      else if (difference[k] < 99.5){
        Serial.print("   ");
      }
      else{
        Serial.print("  ");
      };
      //print those differences
      Serial.print(difference[k]);
    }; // Just printing nicities
    //new line and carriage return
    Serial.println();
  };

  // turn on the leds to reflect off the orders
  digitalWrite(ledPin, HIGH);
  delay(readtime/m);
}
