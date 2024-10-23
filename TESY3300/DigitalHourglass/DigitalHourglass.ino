//Set all needed constants and initialize variables
const int switchPin = 8;
unsigned long previousTime=0;
int switchState = 0;
int prevSwitchState = 0;
int led=2;
int endmode = 1;//0 means it will wait
long interval=1000;
 
void setup() {
  Serial.begin(9600);//initialize serial
 for(int x=2;x<8;x++){
  pinMode(x,OUTPUT); //loop through all the LEDs setting as outputs
 }
 pinMode(switchPin,INPUT); //set switch as an input
}

void loop() {
  unsigned long currentTime = millis();//get newest time
  if ((currentTime - previousTime > interval) && endmode) { //check if time elapsed
    previousTime = currentTime;//for next time around
    digitalWrite(led, HIGH);//each time set next LED as high
    Serial.print("Set ON led number ");
    Serial.println(led);
    led++;//go to next LED
    }
    if ((led > 7) && endmode)
      {  //When you have hit the maximum, reset
        Serial.println("Set LEDs to blink"); 
        delay(1000); //stay on a bit
        led = 2;//reset
        endmode = 0;//reached end of count
          for(int x=0;x<5;x++) { //count how many blinks
              for(int x=2;x<8;x++){ digitalWrite(x, LOW); }
              delay(100);//set all low
              Serial.println("blink 1");
              for(int x=2;x<8;x++){ digitalWrite(x, HIGH); }
              delay(100);//set all high to blink
              Serial.println("blink 2"); 
              for(int x=2;x<8;x++){ digitalWrite(x, LOW); }
              Serial.println("blink 3");//set all low again
          }
     }
    switchState = digitalRead(switchPin);//read tilt sensor
    if(switchState != prevSwitchState) {//if switched
        led=2;//reset again
        endmode = 1;//and stop endmode
        previousTime=currentTime;//set time
      prevSwitchState=switchState;//keep track of what tilt sensor direction
    }
}