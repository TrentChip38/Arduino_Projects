int buttons[6];

//notes Custom, D, E and F
int notes[] = {480, 294, 330, 349};

void setup() {
  Serial.begin(9600);//initialize serial
buttons[0] = 2;//No idea why it said to put this part...
}

void loop () {
  int keyVal = analogRead(A0);//continuously read A0
  Serial.println(keyVal);
  
  if (keyVal == 1023){//check 4 ranges for voltage to know what button
    tone(8, notes[0]);//play that positions note in the array
  }
  else if (keyVal >= 990 && keyVal <= 1010) {
    tone(8, notes[1]);
  }
  else if(keyVal >= 505 && keyVal <= 515) {
    tone(8, notes[2]);
  }
  else if(keyVal >= 5 && keyVal <= 10) {
    tone(8, notes[3]);
  }
  else{
    noTone(8);//turn off
  }
}