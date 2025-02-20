//Trent Chipman 2/17/25

//Define all notes and chords
/************************************/
struct Note{
  //Name is string #(left to right) and fret #(top to bottom)
  int name;
  //Pins for motor
  int pin1;
  int pin2;
  //State 1 = on/down, 0 = off/up
  int on;
  //Time to run, Default value 120?
  int motorTimeOut;
  int motorTimeIn;
};
//Structs for every note (every motor spot)
int numNotes = 6;//9
int defaultTimeOut = 40;//50;
int defaultTimeIn = 100;
int TimeIn = 120;
int calibrationTimeIn = 80;
Note Notes[] ={
  //{11, 1, 2, 0, defaultTimeOut, defaultTimeIn},
  //{12, 3, 4, 0, defaultTimeOut, defaultTimeIn},
  //{13, 5, 6, 0, defaultTimeOut, defaultTimeIn},
  {22, 3, 2, 0, defaultTimeOut, defaultTimeIn},
  {23, 8, 9, 0, defaultTimeOut, defaultTimeIn},
  {32, 1, 0, 0, defaultTimeOut, defaultTimeIn},
  {42, 4, 5, 0, defaultTimeOut, defaultTimeIn},
  //{52, 13, 14, 0, defaultTimeOut, defaultTimeIn},
  {51, 6, 7, 0, defaultTimeOut, defaultTimeIn},
  {53, 10, 11, 0, defaultTimeOut, defaultTimeIn}
};
//All Chords made of a list of notes
int Open[] = {0};
int G[] = {13,22,63};
int C[] = {23,32,51};
int Cmaj7[] = {23,32};
int Cadd9[] = {23,32,53};
int A[] = {32,42,52};
int Am[] = {32,42,51};
int Amsus2[] = {32,42};
int Amsus4[] = {32,42,53};
int E[] = {22,32,41};
int Em[] = {22,32};
int D[] = {42,53,62};
int D7[] = {42,51,62};
int Chord[9];
/************************************/

/*
struct LEDConfig {
  int pin;
  int blinkDelay;
};

LEDConfig leds[] = {
  {2, 500},
  {3, 1000},
  {4, 250}
};

const int numLeds = sizeof(leds) / sizeof(leds[0]);

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i].pin, OUTPUT);
  }
}


//int mode = 1;
//unsigned long seconds;
//int cycle_amount = 0;
//float minutes;
// Variables will change:
//int upState = LOW; //Up/Down state
//int downState = LOW;
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
//unsigned long previousMillis = 0;        // will store last time LED was updated
//unsigned long currentMillis  = 0;
//unsigned long previousStrokeMillis = 0;
// constants won't change:
//const long interval = 1000;
*/

//Functions for running any motor to play a note
void NoteOn(Note &note){
  //If note already on, don't run
  if (note.on == 1){
    return;
  }
  else{
    //Run motor for time
    digitalWrite(note.pin1, HIGH);
    digitalWrite(note.pin2, LOW);
    delay(note.motorTimeOut);
    digitalWrite(note.pin1, LOW);
    digitalWrite(note.pin2, LOW);
    note.on = 1;
  }
}
void NoteOff(Note &note){
  //If note on, pull off
  if (note.on == 1){
    //Run motor for time
    digitalWrite(note.pin1, LOW);
    digitalWrite(note.pin2, HIGH);
    delay(note.motorTimeIn);
    digitalWrite(note.pin1, LOW);
    digitalWrite(note.pin2, LOW);
    note.on = 0;
  }
}

void PlayChord(int chord[], int sizeChord){
  int inChord = 0;
  //Go through every note
  for (int i = 0; i < numNotes; i++) {
    //Turn off all except those in this chord
    inChord = 0;
    //Check if note in this chord
    for (int n = 0; n < sizeChord; n++){
      if(Notes[i].name == chord[n]){
        inChord = 1;
      }
    }
    if(inChord){
      //Turn on that motor
      NoteOn(Notes[i]);
    }else{
      //Turn off motor not in chord
      NoteOff(Notes[i]);
    }
  }
}

void setup() {
  //Initialize outputs and start LOW
  //For each motor spot
  for (int i = 0; i < numNotes; i++) {
    //Initialize both pins as output
    pinMode(Notes[i].pin1, OUTPUT);
    pinMode(Notes[i].pin2, OUTPUT);
    //Start both as low
    digitalWrite(Notes[i].pin1, LOW);
    digitalWrite(Notes[i].pin2, LOW);
  }
  delay(200);
  
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);
  // make the pushbutton's pin an input:
  //pinMode(decoder, INPUT);
  //previousMillis = millis();
  //previousStrokeMillis = previousMillis;

  //Calibaration
  for (int i = 0; i < numNotes; i++) {
    //Run motor in for time
    digitalWrite(Notes[i].pin1, LOW);
    digitalWrite(Notes[i].pin2, HIGH);
    delay(calibrationTimeIn);
    digitalWrite(Notes[i].pin1, LOW);
    digitalWrite(Notes[i].pin2, LOW);
  }
  delay(200);
}

void loop() {
  //Play chord on and off
  //PlayChord(G);
  //delay(5000);
  int timeDelay = 3000;
  PlayChord(C, (sizeof(C) / sizeof(C[0])));
  delay(timeDelay);
  PlayChord(Cmaj7, (sizeof(Cmaj7) / sizeof(Cmaj7[0])));
  delay(timeDelay);
  PlayChord(Cadd9, (sizeof(Cadd9) / sizeof(Cadd9[0])));
  delay(timeDelay);
  PlayChord(Am, (sizeof(Am) / sizeof(Am[0])));
  delay(timeDelay);
  PlayChord(Amsus2, (sizeof(Amsus2) / sizeof(Amsus2[0])));
  delay(timeDelay);
  PlayChord(Amsus4, (sizeof(Amsus4) / sizeof(Amsus4[0])));
  delay(timeDelay);
}
