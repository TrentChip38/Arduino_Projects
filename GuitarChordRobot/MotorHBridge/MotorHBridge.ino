//Trent Chipman 1/27/25

/************************************/
//These can be changed
//milliseconds 5000 = 5 seconds
//Don't set any of these to 0
const unsigned int out_time = 50;
const unsigned int in_time = 100;
const unsigned int Aout_time = 100;
const unsigned int Ain_time = 120;
const unsigned int Bout_time = 300;
const unsigned int Bin_time = 300;
const unsigned int Cout_time = 50;
const unsigned int Cin_time = 70;
const int set_cycle_amount = 1000;
/************************************/

int mode = 1;
unsigned long seconds;
int cycle_amount = 0;
float minutes;

// constants Used here to set pin numbers
const int MotorAPos =  8;
const int MotorANeg =  7;
const int MotorBPos =  6;
const int MotorBNeg =  5;
const int MotorCPos =  4;
const int MotorCNeg =  3;

// Variables will change:
//int upState = LOW; //Up/Down state
//int downState = LOW;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis  = 0;
unsigned long previousStrokeMillis = 0;
// constants won't change:
const long interval = 1000;


void setup() {
  //initialize outputs and start LOW
  pinMode(MotorAPos, OUTPUT);
  pinMode(MotorANeg, OUTPUT);
  pinMode(MotorBPos, OUTPUT);
  pinMode(MotorBNeg, OUTPUT);
  pinMode(MotorCPos, OUTPUT);
  pinMode(MotorCNeg, OUTPUT);
  digitalWrite(MotorAPos, LOW);
  digitalWrite(MotorANeg, LOW);
  digitalWrite(MotorBPos, LOW);
  digitalWrite(MotorBNeg, LOW);
  digitalWrite(MotorCPos, LOW);
  digitalWrite(MotorCNeg, LOW);
  delay(200);
  
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);
  // make the pushbutton's pin an input:
  //pinMode(decoder, INPUT);
  previousMillis = millis();
  previousStrokeMillis = previousMillis;

  //Calibaration testing
  delay(4000);
  //Motor A go in
  digitalWrite(MotorANeg, HIGH);
  digitalWrite(MotorAPos, LOW);
  delay(in_time);
  digitalWrite(MotorAPos, LOW);
  digitalWrite(MotorANeg, LOW);
  delay(2000);
  //Motor B go in
  digitalWrite(MotorBNeg, LOW);
  digitalWrite(MotorBPos, HIGH);
  delay(in_time);
  digitalWrite(MotorBPos, LOW);
  digitalWrite(MotorBNeg, LOW);
  delay(2000);
  //Motor C go in
  digitalWrite(MotorCNeg, LOW);
  digitalWrite(MotorCPos, HIGH);
  delay(in_time);
  digitalWrite(MotorCPos, LOW);
  digitalWrite(MotorCNeg, LOW);
  delay(4000);
}

void loop() {
  if(cycle_amount >= set_cycle_amount){
    //total cycles reached
    //turn off
    digitalWrite(MotorAPos, LOW);
    digitalWrite(MotorANeg, LOW);
    //If you want logic for it to wait and then keep going after it cooled
    //cycle_amount = 0; //also get rid of return
    //currentMillis = millis();
    //if((currentMillis - previousStrokeMillis) >= cool_time)
  }else{
  //Motor A go out
  digitalWrite(MotorAPos, HIGH);
  digitalWrite(MotorANeg, LOW);
  delay(Aout_time);
  digitalWrite(MotorANeg, LOW);
  digitalWrite(MotorAPos, LOW);
  delay(500);
  //Motor B go out
  digitalWrite(MotorBNeg, HIGH);
  digitalWrite(MotorBPos, LOW);
  delay(Bout_time);
  digitalWrite(MotorBPos, LOW);
  digitalWrite(MotorBNeg, LOW);
  //delay(500);
  //Motor C go out
  digitalWrite(MotorCNeg, HIGH);
  digitalWrite(MotorCPos, LOW);
  delay(Bout_time);
  digitalWrite(MotorCPos, LOW);
  digitalWrite(MotorCNeg, LOW);
  
  delay(2000);

  //Motor A go in
  digitalWrite(MotorANeg, HIGH);
  digitalWrite(MotorAPos, LOW);
  delay(Ain_time);
  digitalWrite(MotorAPos, LOW);
  digitalWrite(MotorANeg, LOW);
  delay(500);
  //Motor B go in
  digitalWrite(MotorBPos, HIGH);
  digitalWrite(MotorBNeg, LOW);
  delay(Bin_time);
  digitalWrite(MotorBNeg, LOW);
  digitalWrite(MotorBPos, LOW);
  //delay(500);
  //Motor C go in
  digitalWrite(MotorCNeg, LOW);
  digitalWrite(MotorCPos, HIGH);
  delay(Bin_time);
  digitalWrite(MotorCPos, LOW);
  digitalWrite(MotorCNeg, LOW);
  cycle_amount +=1;

  delay(2000);
  }
}
