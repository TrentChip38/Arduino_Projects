#include <CapacitiveSensor.h>
CapacitiveSensor capSensor = CapacitiveSensor(4,2);
//set threshold and pins
int threshold = 700;
const int ledPin = 8;

void setup() {//set up serial and LED
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {//continually check value and sense touches
  long sensorValue = capSensor.capacitiveSensor(30);
  Serial.println(sensorValue);
  //if touched
  if(sensorValue > threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
      digitalWrite(ledPin, LOW);
  }
  delay (10);
}