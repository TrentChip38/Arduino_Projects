int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

void setup() {
  while (millis() > 5000) {
    sensorValue = analogRead(A0);
  }
} 

  

void loop() {
  sensorValue = analogRead(A0);
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 1000);
  tone(8, pitch, 20);
  delay (10);
}