/*
  Trent Chipman TESY 3300
  Blink two LEDs while button not pressed, 
  then stop and turn on other LED when pressed.
*/
const int LED1 = 3;
const int LED2 = 4;
const int LED3 = 5;
const int btn = 2;
int btnstate = 0;
// the setup function runs once
void setup() {
  // initialize digital pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(btn, INPUT);
}

// the loop function runs forever
void loop() {
  btnstate = digitalRead(btn); // read button
  if(btnstate == 0){
    digitalWrite(LED3, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, HIGH);  // turn one LED on
    delay(200);                // wait for a bit
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);  // turn the other LED on
    delay(200);  
  }else{
    digitalWrite(LED1, LOW);   // turn these off, and the 3rd on
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
  }
}
