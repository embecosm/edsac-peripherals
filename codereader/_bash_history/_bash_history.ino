/*
The code to work the EDSAC simulating tape reader stop waiting for me dan
 */

int sensorPin1  = A4;    // select the input pin for the potentiometer
int sensorPin2  = A3;    // select the input pin for the potentiometer
int sensorPin4  = A2;    // select the input pin for the potentiometer
int sensorPin8  = A1;    // select the input pin for the potentiometer
int sensorPin16 = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue1  = 0;  // variable to store the Value coming from the sensor
int sensorValue2  = 0;  // variable to store the Value coming from the sensor
int sensorValue4  = 0;  // variable to store the Value coming from the sensor
int sensorValue8  = 0;  // variable to store the Value coming from the sensor
int sensorValue16 = 0;  // variable to store the Value coming from the sensor
int olderValue1  = 0;  // variable to store the Value coming from the sensor
int olderValue2  = 0;  // variable to store the Value coming from the sensor
int olderValue4  = 0;  // variable to store the Value coming from the sensor
int olderValue8  = 0;  // variable to store the Value coming from the sensor
int olderValue16 = 0;  // variable to store the Value coming from the sensor
int oldestValue1  = 0;  // variable to store the Value coming from the sensor
int oldestValue2  = 0;  // variable to store the Value coming from the sensor
int oldestValue4  = 0;  // variable to store the Value coming from the sensor
int oldestValue8  = 0;  // variable to store the Value coming from the sensor
int oldestValue16 = 0;  // variable to store the Value coming from the sensor
int bit1  = 0;
int bit2  = 0;
int bit4  = 0;
int bit8  = 0;
int bit16 = 0;
int bitVal1  = 0;
int bitVal2  = 0;
int bitVal4  = 0;
int bitVal8  = 0;
int bitVal16 = 0;
int olderResponse = 0;
int oldestResponse = 0;
int currentResponse = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  // shift everything about:
  oldestResponse = olderResponse;
  olderResponse = currentResponse;
  oldestValue1  = olderValue1;
  oldestValue2  = olderValue2;
  oldestValue4  = olderValue4;
  oldestValue8  = olderValue8;
  oldestValue16 = olderValue16;
  olderValue1  = sensorValue1;
  olderValue2  = sensorValue2;
  olderValue4  = sensorValue4;
  olderValue8  = sensorValue8;
  olderValue16 = sensorValue16;
  sensorValue1  = analogRead(sensorPin1);
  sensorValue2  = analogRead(sensorPin2);
  sensorValue4  = analogRead(sensorPin4);
  sensorValue8  = analogRead(sensorPin8);
  sensorValue16 = analogRead(sensorPin16); 
  //make any changes to the bits
  if(sensorValue1 < oldestValue1 - 20){
    bit1 = 1;
    bitVal1 = 1;
  }
  else if (sensorValue1 > oldestValue1 + 20){
    bit1 = 0;
    bitVal1 = 0;
  };
  if(sensorValue2 < oldestValue2 - 20){
    bit2 = 1;
    bitVal2 = 2;
  }
  else if (sensorValue2 > oldestValue2 + 20){
    bit2 = 0;
    bitVal2 = 0;
  };
  if(sensorValue4 < oldestValue4 - 20){
    bit4 = 1;
    bitVal4 = 4;
  }
  else if (sensorValue4 > oldestValue4 + 20){
    bit4 = 0;
    bitVal4 = 0;
  };
  if(sensorValue8 < oldestValue8 - 20){
    bit8 = 1;
    bitVal8 = 8;
  }
  else if (sensorValue8 > oldestValue8 + 20){
    bit8 = 0;
    bitVal8 = 0;
  };
  if(sensorValue16 < oldestValue16 - 20){
    bit16 = 1;
    bitVal16 = 16;
  }
  else if (sensorValue16 > oldestValue16 + 20){
    bit16 = 0;
    bitVal16 = 0;
  };
  currentResponse = bitVal1 + bitVal2 + bitVal4 + bitVal8 + bitVal16;
  if(currentResponse == olderResponse){
  }
  else{
    Serial.print("Binary: ");
    Serial.print(bit16);
    Serial.print(bit8);
    Serial.print(bit4);
    Serial.print(bit2);
    Serial.print(bit1);
    Serial.print("    Actual value: ");
    if(bitVal16 + bitVal8 + bitVal4 + bitVal2 + bitVal1 < 10){
      Serial.print(" ");
    };
    Serial.print(bitVal16 + bitVal8 + bitVal4 + bitVal2 + bitVal1);
    Serial.print("    Differences: ");
    if (sensorValue16 - oldestValue16 < -100){
      Serial.print(" ");
    }
    else if (sensorValue16 - oldestValue16 < -10){
      Serial.print("  ");
    }
    else if (sensorValue16 - oldestValue16 < 0){
      Serial.print("   ");
    }
    else if (sensorValue16 - oldestValue16 < 10){
      Serial.print("    ");
    }
    else if (sensorValue16 - oldestValue16 < 100){
      Serial.print("   ");
    }
    else{
      Serial.print("  ");
    };
    Serial.print(sensorValue16 - oldestValue16);
    Serial.print(" ");  
    if (sensorValue8 - oldestValue8 < -100){
      Serial.print(" ");
    }
    else if (sensorValue8 - oldestValue8 < -10){
      Serial.print("  ");
    }
    else if (sensorValue8 - oldestValue8 < 0){
      Serial.print("   ");
    }
    else if (sensorValue8 - oldestValue8 < 10){
      Serial.print("    ");
    }
    else if (sensorValue8 - oldestValue8 < 100){
      Serial.print("   ");
    }
    else{
      Serial.print("  ");
    };
    Serial.print(sensorValue8 - oldestValue8);
    Serial.print(" ");  
    if (sensorValue4 - oldestValue4 < -100){
      Serial.print(" ");
    }
    else if (sensorValue4 - oldestValue4 < -10){
      Serial.print("  ");
    }
    else if (sensorValue4 - oldestValue4 < 0){
      Serial.print("   ");
    }
    else if (sensorValue4 - oldestValue4 < 10){
      Serial.print("    ");
    }
    else if (sensorValue4 - oldestValue4 < 100){
      Serial.print("   ");
    }
    else{
      Serial.print("  ");
    };
    Serial.print(sensorValue4 - oldestValue4);
    Serial.print(" ");
    if (sensorValue2 - oldestValue2 < -100){
      Serial.print(" ");
    }
    else if (sensorValue2 - oldestValue2 < -10){
      Serial.print("  ");
    }
    else if (sensorValue2 - oldestValue2 < 0){
      Serial.print("   ");
    }
    else if (sensorValue2 - oldestValue2 < 10){
      Serial.print("    ");
    }
    else if (sensorValue2 - oldestValue2 < 100){
      Serial.print("   ");
    }
    else{
      Serial.print("  ");
    };
    Serial.print(sensorValue2 - oldestValue2);
    Serial.print(" ");  
    if (sensorValue1 - oldestValue1 < -100){
      Serial.print(" ");
    }
    else if (sensorValue1 - oldestValue1 < -10){
      Serial.print("  ");
    }
    else if (sensorValue1 - oldestValue1 < 0){
      Serial.print("   ");
    }
    else if (sensorValue1 - oldestValue1 < 10){
      Serial.print("    ");
    }
    else if (sensorValue1 - oldestValue1 < 100){
      Serial.print("   ");
    }
    else{
      Serial.print("  ");
    };
    Serial.print(sensorValue1 - oldestValue1);
    Serial.println();
  };
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);  
  delay(20);                  
}
