/*
  Trent Chipman TESY 3300
  Test temperature, and light up LEDs accordingly
*/
const int LED1 = 2; // names for all the pins used
const int LED2 = 3;
const int LED3 = 4;
const int sensorPin = A0;
const float baselineTemp = 21.2;
void setup() {
    // initialize digital pin modes for LEDs and sensor input and serial monitor
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}


void loop() {
  int sensorVal = analogRead(sensorPin);  //Read sensor
  Serial.print("Sensor Value: ");         //Print value
  Serial.print(sensorVal);
  float voltage = (sensorVal/1024.0) * 5.0;
  Serial.print(", Volts: ");//convert to volts and print
  Serial.print(voltage);
  Serial.print(", degrees C: "); 
  // convert the voltage to temperature in degrees
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);//convert to C and print


  if(temperature < baselineTemp){//turn on amount of LEDs for temperature
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }else if(temperature >= baselineTemp+2 &&                               
    temperature < baselineTemp+4){
   digitalWrite(LED1, HIGH);
   digitalWrite(LED2, LOW);
   digitalWrite(LED3, LOW);
  }else if(temperature >= baselineTemp+4 &&   
    temperature < baselineTemp+6){
   digitalWrite(LED1, HIGH);
   digitalWrite(LED2, HIGH);
   digitalWrite(LED3, LOW);
  }else if(temperature >= baselineTemp+6){
   digitalWrite(LED1, HIGH);
   digitalWrite(LED2, HIGH);
   digitalWrite(LED3, HIGH);
  }
 delay(1);
}
