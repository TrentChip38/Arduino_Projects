#include "Keyboard.h"

// Assign pins for each button
const int buttonUp    = 2;
const int buttonEnter = 3;
const int buttonCtrlC = 4;
const int buttonString = 5;
const int buttonOpenTerminal  = 6;

// Store previous states to detect new presses
int prevUpState    = HIGH;
int prevEnterState = HIGH;
int prevCtrlCState = HIGH;
int prevStringState= HIGH;
int prevTermState  = HIGH;

void setup() {
  pinMode(buttonUp,    INPUT_PULLUP);
  pinMode(buttonEnter, INPUT_PULLUP);
  pinMode(buttonCtrlC, INPUT_PULLUP);
  pinMode(buttonString,INPUT_PULLUP);
  pinMode(buttonOpenTerminal,  INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  checkButton(buttonUp,    &prevUpState,    [](){ Keyboard.press(KEY_UP_ARROW); delay(50); Keyboard.release(KEY_UP_ARROW); });
  checkButton(buttonEnter, &prevEnterState, [](){ Keyboard.press(KEY_RETURN); delay(50); Keyboard.release(KEY_RETURN); });
  checkButton(buttonCtrlC, &prevCtrlCState, [](){ Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('c'); delay(50); Keyboard.release('c'); Keyboard.release(KEY_LEFT_CTRL); });
  checkButton(buttonString,&prevStringState,[]{ Keyboard.print("python3 AICAM/picamera2/examples/imx500/phoneAPI_andAI.py\n"); });
  checkButton(buttonOpenTerminal,  &prevTermState,  [](){ Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_ALT); Keyboard.press('t'); delay(50); Keyboard.release('t'); Keyboard.release(KEY_LEFT_ALT); Keyboard.release(KEY_LEFT_CTRL); });
}

void checkButton(int pin, int* prevState, void (*onPress)()) {
  int state = digitalRead(pin);
  if (state == LOW && *prevState == HIGH) {
    onPress();
    delay(200); // Debounce
  }
  *prevState = state;
}