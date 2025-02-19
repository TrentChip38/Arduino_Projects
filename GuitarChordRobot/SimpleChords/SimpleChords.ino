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
int numNotes = 9;
Note Notes[] ={
  {11, 1, 2, 120, 120},
  {12, 3, 4},
  {13, 5, 6},
  {23, 7, 8},
  {32, 9, 10},
  {42, 11, 12},
  {52, 13, 14},
  {51, 15, 16},
  {53, 17, 18}
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
void NoteOn(Note note){
  //If note already on, don't run
  if (note.on){}
  else{
    //Run motor for time
    digitalWrite(note.pin1, HIGH);
    digitalWrite(note.pin2, LOW);
    delay(note.motorTimeOut);
    digitalWrite(note.pin1, LOW);
    digitalWrite(note.pin2, LOW);
  }
}
void NoteOff(Note note){
  //If note on
  if (note.on){
    //Run motor for time
    digitalWrite(note.pin1, LOW);
    digitalWrite(note.pin2, HIGH);
    delay(note.motorTimeIn);
    digitalWrite(note.pin1, LOW);
    digitalWrite(note.pin2, LOW);
  }
}

void PlayChord(int chord[]){
  int inChord = 0;
  int num = sizeof(chord);
  //Go through every note
  for (int i = 0; i < numNotes; i++) {
    //Turn off all except those in this chord
    inChord = 0;
    //Check if note in this chord
    for (int n = num; n < numNotes; n++){
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
}

void loop() {
  //Play chord on and off
  PlayChord(G);
  delay(5000);
  PlayChord(C);
  delay(4000);
}
