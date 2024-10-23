//Pin constants and switchstate
const int switchPin = 2;
const int motorPin = 9;
const int LEDPin = 13;
int switchState = 0;
void setup()
{
  pinMode(switchPin, INPUT);//setup in/out pins
  pinMode(motorPin, OUTPUT);
  pinMode(LEDPin , OUTPUT);
}

void loop()
{
  switchState = digitalRead(switchPin);//Read switch
  if (switchState == HIGH)
  {
    digitalWrite(motorPin, HIGH);//If pushed spin motor
    digitalWrite(LEDPin, HIGH);//And turn on LED
  }
  else
  {
    digitalWrite(motorPin, LOW);//Not pushed, turn off
    digitalWrite(LEDPin, LOW);//And turn off LED
  }
}