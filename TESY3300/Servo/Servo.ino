#include <Servo.h>  //Servo library
Servo myServo;  //Servo object

int const potPin = A0; // analog pin for potentiometer
int potVal;  // variable for pot pin
int angle;   // servo motor angle

void setup() {
  myServo.attach(9); // attaches pin 9 to servo object
  Serial.begin(9600); // open serial
}

void loop() {
  potVal = analogRead(potPin); // read the pot value
  Serial.print("potVal: ");// print out to Serial
  Serial.print(potVal);
  angle = map(potVal, 0, 1023, 0, 179);//scale
  Serial.print(", angle: ");// print angle
  Serial.println(angle);
  myServo.write(angle);//set servo position
  delay(15);//wait
}