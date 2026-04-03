#include <SoftwareSerial.h>
// Define pins for serial communication
const int rxPin = 19; // Connect to MP3 Trigger TX
const int txPin = 18; // Connect to MP3 Trigger RX
SoftwareSerial mp3Trigger(rxPin, txPin);

const int chPins[2] = {26, 27}; // CH5 and CH6 pins
unsigned long chValues[2] = {0, 0};
int currentChannel = 0; // 0 for CH5, 1 for CH6

// For edge detection on CH6 (3-position switch)
int lastCh6Pos = 1; // 0=down, 1=middle, 2=up

void setup() {
  Serial.begin(9600);      // For debugging
  // Start communication with MP3 Trigger at its default baud rate
  mp3Trigger.begin(38400); 
  pinMode(chPins[0], INPUT);
  pinMode(chPins[1], INPUT);
  // Wait for the MP3 Trigger to boot and mount the SD card
  delay(2000); 
  Serial.println("MP3 Trigger Ready.");
  playTrack(4);
  delay(4000);
}
int ch6Pos;
int ch5Pos;
void loop() {
  // Alternate reading CH5 and CH6
  chValues[currentChannel] = pulseIn(chPins[currentChannel], HIGH, 25000);

  // Map CH5 (2-pos) and CH6 (3-pos) to logical positions
  ch5Pos = (chValues[0] > 1500) ? 1 : 0; // 0=down, 1=up
  if (chValues[1] < 800) ch6Pos = ch6Pos;    //Stay the same when not reading correctly
  else if (chValues[1] < 1250) ch6Pos = 0;   // down
  else if (chValues[1] > 1750) ch6Pos = 2;   // up
  else ch6Pos = 1;                           // middle

  // Edge detection: only trigger when CH6 moves away from middle
  if (ch6Pos != 1 && lastCh6Pos == 1) {
    // Encode sound: 0=down+down, 1=down+up, 2=up+down, 3=up+up
    //int soundIndex = (ch6Pos == 2 ? 2 : 0) + ch5Pos;
    if (ch6Pos == 0 && ch5Pos == 0){
      playSound(17);//Try 17, 42/43, 57, 59, 87, 89, 90 are long screams
    }else if(ch6Pos == 0 && ch5Pos == 1){
      playSound(42);
    }else if(ch6Pos == 2 && ch5Pos == 0){
      playSound(60);
    }else if(ch6Pos == 2 && ch5Pos == 1){
      playSound(89);
    }
    delay(2000);
  }
  lastCh6Pos = ch6Pos;

  // Print both channel values for debugging
  Serial.print("CH5: ");
  Serial.print(chValues[0]);
  Serial.print("  CH6: ");
  Serial.println(chValues[1]);

  // Switch to the other channel for next loop
  currentChannel = 1 - currentChannel;

  delay(10); // Small delay for stability
}

void playSound(int soundIndex) {
  // MP3 Trigger tracks: 001.mp3, 002.mp3, 003.mp3, 004.mp3
  int trackNum = soundIndex + 1; // 1-based for MP3 Trigger
  //char cmd[6];
  // snprintf(cmd, sizeof(cmd), "t%03d\r", trackNum);
  // Serial1.print(cmd);
  playTrack(soundIndex);
  Serial.println("Playing track...");

  // For debugging
  Serial.print("Play sound: ");
  Serial.println(trackNum);
}

// Function to send the 't' (trigger) command followed by the track number
void playTrack(int trackNumber) {
  // The 't' command followed by a byte (1-255) triggers tracks by filename prefix
  mp3Trigger.print('t');
  mp3Trigger.write(trackNumber);
}