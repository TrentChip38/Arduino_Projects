//constants for output and input pins
const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStateSwitchPin = 5;
const int potPin = A0;

//variables for remembering program state
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

//variables for controlling the DC motor
int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup() {

//Set inputs and outputs for pins
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

//disable motor at start
  digitalWrite(enablePin, LOW);
}

void loop() {
//read sensor information
  onOffSwitchState =
  digitalRead(onOffSwitchStateSwitchPin);
  delay(1);

  directionSwitchState =
  digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4;

//check if on/off sensor has changed
  if(onOffSwitchState != previousOnOffSwitchState){
    if(onOffSwitchState == HIGH){
    motorEnabled = !motorEnabled;
    }
  }  
      
//check to see if direction has changed
  if(directionSwitchState != previousDirectionSwitchState){
      if(directionSwitchState == HIGH){
        motorDirection = !motorDirection;
        }
      }
//change pins to turn motor in the proper direction
  if(motorDirection == 1){
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
    }
  else{
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }
//PWM the motor if it is enabled
  if (motorEnabled == 1){
    analogWrite(enablePin, motorSpeed);
    }
  else{
    analogWrite(enablePin, 0);
    }

//save current state for next loop
  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
}