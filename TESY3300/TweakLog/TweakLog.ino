void setup() {
  // Init serial
  Serial.begin(9600);
}

void loop() {
  //read A0, map to 0-255, and print to serial
  //Serial.print(analogRead(A0)/7);
  Serial.write(analogRead(A0)/3);
  delay(100);
}
/*
import processing.serial.*;
Serial myPort;
PImage logo;
int bgcolor = 0;
void setup(){
  colorMode(HSB, 255);
  logo = loadImage("https://arduino.cc/logo.png");  //en/pub/skins/arduinoWide/img/logo.png");
  size(logo.width, logo.height);
  println("Avaliable serial ports:");
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
}
void draw(){
  if (myPort.available() > 0) {
    bgcolor = myPort.read();
    println(bgcolor);
  }
  background(bgcolor, bgcolor, 255);
  image(logo, 0, 0);
}

import processing.serial.*;
Serial myPort;
PImage logo;
int bgcolor = 0;
int read = 0;
void setup(){
  colorMode(HSB, 255);//99
  logo = loadImage("https://upload.wikimedia.org/wikipedia/commons/thumb/8/87/Arduino_Logo.svg/720px-Arduino_Logo.svg.png?20200922062315");  //https://arduino.cc/logo.png
  //size(logo.width, logo.height);
  size(720, 520);
  println("Avaliable serial ports:");
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
}
void draw(){
  if (myPort.available() > 0) {
    bgcolor = myPort.read();
    /*read = (myPort.read() - 48)*10;
    read = read + (myPort.read() - 48);
    if (read > 0){
      if ((bgcolor - read) < 14)
        bgcolor = read;
    }
    println(bgcolor);
  }
  background(bgcolor, bgcolor, 255);
  image(logo, 0, 0);
}*/