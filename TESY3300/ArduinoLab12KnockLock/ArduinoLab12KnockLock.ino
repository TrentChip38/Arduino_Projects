#include <Servo.h>
Servo myServo;
//set all pins
const int piezo = A0;
const int switchPin = 2;
const int yellowLED = 3;
const int greenLED = 4;
const int redLED = 5;
//vallues
int knockVal;
int switchVal;
//tolerance
const int quietKnock = 10;
const int loudKnock = 100;

boolean locked = false;
int numberOfKnocks = 0;

void setup() {
  myServo.attach(9);//servo object
  pinMode(yellowLED, OUTPUT);//set up LEDs
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);//start serial
  digitalWrite(greenLED, HIGH);
  myServo.write(0);//start state
  Serial.println("The box is unlocked!");
}

void loop() {
  if(locked == false){
    //check for button push
    switchVal = digitalRead(switchPin);
    if(switchVal == HIGH){
      locked = true;
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
      myServo.write(90);
      Serial.println("The box is locked!");
      delay(1000);
    }
  }

  if(locked == true){
    //check for vibration through piezo
    knockVal = analogRead(piezo);
    if(numberOfKnocks < 3 && knockVal > 0){
      if(checkForKnock(knockVal) == true){
        numberOfKnocks++;
      }
      //Serial.print(3-numberOfKnocks);
      //Serial.println(" more knocks to go");
    }

    if(numberOfKnocks >= 3){
      locked = false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      Serial.println("The box is unlocked!");
    }
  }
}
//Check for knock
boolean checkForKnock(int value){
  if(value > quietKnock && value < loudKnock){
    digitalWrite(yellowLED, HIGH);
    delay(50);
    digitalWrite(yellowLED, LOW);
    Serial.print("Valid knock of value ");
    Serial.println(value);
    return true;
  }
  else{
    //Serial.print("Bad knock value ");
    Serial.println(value);
    return false;
  }
}