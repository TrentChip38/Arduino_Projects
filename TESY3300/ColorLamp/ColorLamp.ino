//inputs and outputs
const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;
const int redLEDPin = 11;
const int greenLEDPin = 9;
const int blueLEDPin = 10;

//initialize variables
int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() {
  //start serial
  Serial.begin(9600);

  //set outputs
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  //read photoresistors
  redSensorValue = analogRead(redSensorPin);
  delay(10);
  greenSensorValue = analogRead(greenSensorPin);
  delay(10);
  blueSensorValue = analogRead(blueSensorPin);
  //print out info
  Serial.print("Raw Sensor Values \t Red: ");
  Serial.print(redSensorValue);
  Serial.print("\t Green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);

  //map 0-1023 -> 0-255
  redValue = redSensorValue / 4;
  greenValue = greenSensorValue / 4;
  blueValue = blueSensorValue / 4;
  
  //print out mapped values
  Serial.print("Mapped Sensor Values \t Red: ");
  Serial.print(redValue);
  Serial.print("\t Green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);

  //change RGB LED color
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
}