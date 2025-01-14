#include <LedControl.h>

//Define The Snake as a Struct
typedef struct Snake Snake;
struct Snake{
  int head[2];     // the (row, column) of the snake head
  int body[40][2]; //An array that contains the (row, column) coordinates
  int len;         //The length of the snake 
  int dir[4];      //A direction to move the snake along
};

//Define The Apple as a Struct
typedef struct Apple Apple;
struct Apple{
  int rPos; //The row index of the apple
  int cPos; //The column index of the apple
};

//MAX72XX led Matrix
const int DIN =12;
const int CS =11;
const int CLK = 10;
const int piezo = 5;
LedControl lc = LedControl(DIN, CLK, CS,1);

//Variables for buttons and direction changing
const int RightB = 8;//right button
const int LeftB = 9;//left button
int TurnR = 0;//Variable to read Right button
int TurnL = 0;//Variable to read Left button
int RightC = 0;//Right button count
int LeftC = 0;//Left button count
int hold; //Variable to hold a value for re-assignment

byte pic[8] = {0,0,0,0,0,0,0,0};//The 8 rows of the LED Matrix

Snake snake = {{1,5},{{0,5}, {1,5}}, 2, {0, 1, 0, -1}};//Initialize a snake object
Apple apple = {(int)random(0,8),(int)random(0,8)};//Initialize an apple object

//Variables To Handle The Game Time
float oldTime = 0;
float timer = 0;
float updateRate = 3;

int i,j;//Counters
void setup() {
  // put your setup code here, to run once:
    /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin(9600);
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  //Set Joystick Pins as INPUTs
  //pinMode(varXPin, INPUT);
  //pinMode(varYPin, INPUT);
  pinMode(RightB, INPUT);
  pinMode(LeftB, INPUT);
  //Start tone
  tone(piezo, 420, 800);
  delay(400);
  tone(piezo, 630, 600);
  delay(300);
  noTone(piezo);
}

void loop() {
  // put your main code here, to run repeatedly:
  float deltaTime = calculateDeltaTime();
  timer += deltaTime;

  //Read buttons
  TurnR = digitalRead(RightB);
  TurnL = digitalRead(LeftB);
  //Count how many times they were read as high
  if(TurnR)
    RightC ++;
  if(TurnL)
    LeftC ++;
  //Update
  if(timer > 1000/updateRate){
    //if button pressed for certain amount
    int CheckCount = 1000/updateRate/10;
    if(RightC > CheckCount){//rotate all values to the right
    //Serial.println("Right");
      hold = snake.dir[0];
      for(i = 0; i < 3; i++){
        snake.dir[i] = snake.dir[i+1];
      }
      snake.dir[3] = hold;
      //Serial.println("Direction:");
    }else if(LeftC > CheckCount){//rotate all values to the left
    //Serial.println("Left");
      hold = snake.dir[3];
      for(i = 3; i > 0; i--){
        snake.dir[i] = snake.dir[i-1];
      }
      snake.dir[0] = hold;
      //Serial.println(snake.dir[0]);
    }
    //reset timer and button press counts
    timer = 0;
    RightC = 0;
    LeftC = 0;
    //Then update to next dot
    Update();
  }
  
  //Render Everytime
  Render();
  
}

float calculateDeltaTime(){
  float currentTime = millis();
  float dt = currentTime - oldTime;
  oldTime = currentTime;
  return dt;
}

void reset(){
  for(int j=0;j<8;j++){
    pic[j] = 0;
  }
}
void Update(){
  reset();//Reset (Clear) the 8x8 LED matrix
  
  int newHead[2] = {snake.head[0]+snake.dir[0], snake.head[1]+snake.dir[1]};

  //Handle Borders
  if(newHead[0]==8){
    newHead[0]=0;
  }else if(newHead[0]==-1){
    newHead[0] = 7;
  }else if(newHead[1]==8){
    newHead[1]=0;
  }else if(newHead[1]==-1){
    newHead[1]=7;
  }
  
  //Check If The Snake hits itself
   for(j=0;j<snake.len;j++){
    //If hit, then restart
    if(snake.body[j][0] == newHead[0] && snake.body[j][1] == newHead[1]){
      //Play death tone then reset
      tone(piezo, 210, 800);
      delay(400);
      noTone(piezo);
      delay(3000);
      noTone(piezo);
      snake = {{1,5},{{0,5}, {1,5}}, 2, {0,1,0,-1}};//Reinitialize the snake object
      apple = {(int)random(0,8),(int)random(0,8)};//Reinitialize an apple object
      //Start tone
      tone(piezo, 420, 800);
      delay(400);
      tone(piezo, 630, 600);
      delay(300);
      noTone(piezo);
      return;
    }
  }

  //Check if The snake ate the apple
  if(newHead[0] == apple.rPos && newHead[1] ==apple.cPos){
    snake.len = snake.len+1;
    apple.rPos = (int)random(0,8);
    apple.cPos = (int)random(0,8);
  }else{
    removeFirst();//Shifting the array to the left
  }
  
  snake.body[snake.len-1][0]= newHead[0];
  snake.body[snake.len-1][1]= newHead[1];
  
  snake.head[0] = newHead[0];
  snake.head[1] = newHead[1];
  
  //Update the pic Array to Display(snake and apple)
  for(j=0;j<snake.len;j++){
    pic[snake.body[j][0]] |= 128 >> snake.body[j][1];
  }
  pic[apple.rPos] |= 128 >> apple.cPos;
  
}

void Render(){
  
   for(i=0;i<8;i++){
    lc.setRow(0,i,pic[i]);
   }
}

void removeFirst(){
  for(j=1;j<snake.len;j++){
    snake.body[j-1][0] = snake.body[j][0];
    snake.body[j-1][1] = snake.body[j][1];
  }
}