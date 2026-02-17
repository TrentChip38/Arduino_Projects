// Motor pins (2–9)
const int LEFT_FWD = 3;
const int LEFT_BWD = 2;
const int RIGHT_FWD = 5;
const int RIGHT_BWD = 4;
const int A_FWD = 9;
const int A_BWD = 8;
const int B_BWD = 7;
const int B_FWD = 6;

// Function prototypes
void LeftMotor(int direction, int time_ms);
void RightMotor(int direction, int time_ms);
void AMotor(int direction, int time_ms);
void BMotor(int direction, int time_ms);
//Press functions prototypes
void LeftPress();
void RightPress();
void APress();
void BPress();
//Hold on/off functions
const int on = 1;
const int off = 0;
void LeftHOld(int direction);
void RightHold(int direction);
void BHold(int direction);
//Game sequences, movements, tasks
void FightBasic();
void FindEnemy();
void CaveToRestore();
void RestoreToCave();

void setup() {
  // Set all motor pins as outputs
  for (int pin = 2; pin <= 9; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  // Run each motor forward then backward
  APress();
  BPress();
  RightPress();
  LeftPress();
  //delay(4000);
}
//Global time vars. Funcs normally use t and tBack
  int tBack = 200;
  int t = 400; // 1/4 second in milliseconds
  int t1 = 10;
  int t2 = 1000;

void loop() {
  //Fight untill PP runs out
  for (int i = 0; i < 34; i++){
    //35 times for Aron with Metal Slash
    FindEnemy();
    FightBasic();
  }
  //Go to restoration center from cave and back
  CaveToRestore();
  RestoreToCave();
}

//Tasks
void FightBasic(){
  //Start fighting, and wait these amounts to press buttons to advance
  //Uses first move
  int delays[9] = {3000, 0, 6000, 3000, 2000, 2000, 1000, 1000, 0};
  delay(4000);
  //Loop through pressing A 9 times (only need 6/7) with delays inbetween
  for(int i = 0; i < 9; i++){
    APress();
    delay(delays[i]);
  }
}
void FindEnemy(){
  //Go back on forth 4 times
  BHold(on);
  //Run right
  RightHold(on);
  delay(2000); 
  RightHold(off);
  //Run left
  LeftHold(on);
  delay(2000); 
  LeftHold(off);
  //Run right
  RightHold(on);
  delay(2000); 
  RightHold(off);
  //Run left
  LeftHold(on);
  delay(2000); 
  LeftHold(off);
  BHold(off);
}
void CaveToRestore(){
  //A sequence of specific moves 
  //that will get you out of the cave 
  //no matter where you are in the first section
  delay(100);
  //A sequence of moves that will get you to the restoration center

  //Go in and restore your pokemon

  //Leave the restoration center
}
void RestoreToCave(){
  //Moves that get you from restoration center to the cave
  delay(100);
  //Try to get a little further into the cave, might get stopped.

}

//  ------ Pressing Functions
//Press functions prototypes
void LeftPress(){
  LeftMotor(1, t);
  LeftMotor(0, tBack);
  delay(100);
}
void RightPress(){
  RightMotor(1, t);
  RightMotor(0, tBack);
  delay(100);
}
void APress(){
  AMotor(1, t2);
  AMotor(0, tBack);
  delay(100);
}
void BPress(){
  BMotor(1, t);
  BMotor(0, tBack);
  delay(100);
}
//Hold on/off functions
void LeftHold(int direction){
  if (direction == 1){
    LeftMotor(1, t);
    delay(100);
  }else if (direction == 0){
    LeftMotor(0, tBack);
    delay(100);
  }
}
void RightHold(int direction){
    if (direction == 1){
        RightMotor(1, t);
        delay(100);
    }else if (direction == 0){
        RightMotor(0, tBack);
        delay(100);
    }
}
void BHold(int direction){
    if (direction == 1){
        BMotor(1, t);
        delay(100);
    }else if (direction == 0){
        BMotor(0, tBack);
        delay(100);
    }
}

// ==================== MOTOR FUNCTIONS ====================

void LeftMotor(int direction, int time_ms) {
  digitalWrite(LEFT_FWD, direction ? HIGH : LOW);
  digitalWrite(LEFT_BWD, direction ? LOW : HIGH);
  delay(time_ms);
  // Stop motor
  digitalWrite(LEFT_FWD, LOW);
  digitalWrite(LEFT_BWD, LOW);
}

void RightMotor(int direction, int time_ms) {
  digitalWrite(RIGHT_FWD, direction ? HIGH : LOW);
  digitalWrite(RIGHT_BWD, direction ? LOW : HIGH);
  delay(time_ms);
  digitalWrite(RIGHT_FWD, LOW);
  digitalWrite(RIGHT_BWD, LOW);
}

void AMotor(int direction, int time_ms) {
  digitalWrite(A_FWD, direction ? HIGH : LOW);
  digitalWrite(A_BWD, direction ? LOW : HIGH);
  delay(time_ms);
  digitalWrite(A_FWD, LOW);
  digitalWrite(A_BWD, LOW);
}

void BMotor(int direction, int time_ms) {
  digitalWrite(B_FWD, direction ? HIGH : LOW);
  digitalWrite(B_BWD, direction ? LOW : HIGH);
  delay(time_ms);
  digitalWrite(B_FWD, LOW);
  digitalWrite(B_BWD, LOW);
}
