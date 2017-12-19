/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int analogValue = 0;        // value read from the pot
int analogValueInv = 0; 
float analogVolts = 0;
int chartValue = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  analogValue = analogRead(A0); // read the analog signal
  analogVolts = (analogValue * 3.08) / 1024;
  analogValueInv = 1024-analogValue;
  chartValue = map(analogValueInv,0,750,0,100);
  
  // print the results to the serial monitor:
  Serial.print("  V = ");
  Serial.print(analogVolts);
  Serial.print("  AV = ");
  Serial.print(analogValue);
  Serial.print("  chart = ");
  Serial.print(chartValue);
  Serial.println("\n");

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(200);
}
