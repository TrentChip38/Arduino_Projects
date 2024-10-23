//Trent Chipman 7/12/24

//This will just go up and down for a specified amount of seconds (set_stroke_time)
//and for a given amount of total cycles (set_cycle_amount)


//Two digital signals propogate through two relays each to switch AC source
//which connects to required pins to make motor go up and down
//The signals are from pins 7 and 8, named signal_up and signal_down
//Which can be set High or Low to turn on and off that relay
//Only one of these should be on at a time

//If anyone edits this you should make sure to use the redundancy safety method
//of turning off the other relay right before you turn on a given relay
//its probably also smart to have a short time when both relays are off
//before switching motor direction. I implemented this: turning off both relays, 
//and waiting 1 second(switch_wait_time), then turning on next relay.

/************************************/
//These can be changed
//milliseconds 5000 = 5 seconds
//Don't set any of these to 0
const unsigned long set_stroke_time = 5000;
const int switch_wait_time = 15000;
const int set_cycle_amount = 1000;
/************************************/

int mode = 1;
unsigned long seconds;
int cycle_amount = 0;
float minutes;

// constants Used here to set pin numbers
const int signal_up =  8;
const int signal_down =  7;

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
  pinMode(signal_up, OUTPUT);
  pinMode(signal_down, OUTPUT);
  digitalWrite(signal_up, LOW);
  digitalWrite(signal_down, LOW);
  delay(200);
  
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);
  // make the pushbutton's pin an input:
  //pinMode(decoder, INPUT);
  previousMillis = millis();
  previousStrokeMillis = previousMillis;
}

void loop() {
  if(cycle_amount >= set_cycle_amount){
    //total cycles reached
    //turn off
    digitalWrite(signal_up, LOW);
    digitalWrite(signal_down, LOW);
    //If you want logic for it to wait and then keep going after it cooled
    //cycle_amount = 0; //also get rid of return
    //currentMillis = millis();
    //if((currentMillis - previousStrokeMillis) >= cool_time)
  }else{
  //go up
  digitalWrite(signal_down, LOW);
  digitalWrite(signal_up, HIGH);
  delay(set_stroke_time);

  //turn off both
  digitalWrite(signal_down, LOW);
  digitalWrite(signal_up, LOW);
  //wait and then turn back on
  delay(switch_wait_time);
  
  //go down
  digitalWrite(signal_up, LOW);
  digitalWrite(signal_down, HIGH);
  delay(set_stroke_time);
  cycle_amount +=1;
  
  //turn off both
  digitalWrite(signal_down, LOW);
  digitalWrite(signal_up, LOW);
  //wait and then turn back on
  delay(switch_wait_time);
  }
}
