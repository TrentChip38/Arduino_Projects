const int chPins[2] = {26, 27}; // CH5 and CH6 pins
unsigned long chValues[2] = {0, 0};
int currentChannel = 0; // 0 for CH5, 1 for CH6

void setup() {
  Serial.begin(9600);
  pinMode(chPins[0], INPUT);
  pinMode(chPins[1], INPUT);
}

void loop() {
  // Alternate reading CH5 and CH6
  chValues[currentChannel] = pulseIn(chPins[currentChannel], HIGH, 25000);

  // Print both channel values every cycle
  Serial.print("CH5: ");
  Serial.print(chValues[0]);
  Serial.print("  CH6: ");
  Serial.println(chValues[1]);

  // Switch to the other channel for next loop
  currentChannel = 1 - currentChannel;

  delay(10); // Small delay for stability
}