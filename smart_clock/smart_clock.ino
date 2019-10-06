#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Declaring all the output pins
const int soundPin         = D0;
const int displayVccPin    = D2;
const int displayGroundPin = D1;
const int displaySDA       = D4;
const int displaySLC       = D3;

//Declaring all the input pins
const int upButton     = D5;
const int downButton   = D6;
const int okButton     = D7;
const int optionButton = D8;

//mode constants
const int TOTAL_NUM_OF_MODES = 4;
const int VIEW_TIME  = 0;
const int EDIT_TIME  = 1;
const int VIEW_ALARM = 2;
const int EDIT_ALARM = 3;

int upBtnCurState  = 0;
int upBtnPrevState = 0;

int downBtnCurState  = 0;
int downBtnPrevState = 0;

int optionBtnCurState  = 0;
int optionBtnPrevState = 0;

int okBtnCurState  = 0;
int okBtnPrevState = 0;

int currentMode = VIEW_TIME;

int generalCounter = 0;

//How frequently to blink the characters being edited
const int BLINK_DELAY_MAX = 50;
bool toBlink = false;
int blinkDelay = 0;

//setup all the input and output modes
void setupPinModes(){
  
  pinMode(soundPin, OUTPUT);
  pinMode(displayGroundPin, OUTPUT);
  pinMode(displayVccPin, OUTPUT);
  
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(okButton, INPUT);
  pinMode(optionButton, INPUT);
}

void setupDisplayConfig(){
  digitalWrite (displayGroundPin, LOW);
  digitalWrite (displayVccPin, HIGH);

  Wire.begin(displaySDA,displaySLC);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void setup() {
  Serial.begin(115200);

  setupPinModes();
  setupDisplayConfig();
  
  delay(2000);
}

void loop() {
/*------------------------------ <handle button inputs> ----------------------------------------*/

/*------------------------------- <VIEW_TIME mode> --------------------------*/
if(currentMode == VIEW_TIME){
  toBlink = false;
    /*------------------------------ <option button> ----------------------------------------*/
  //if option is pressed while in edit mode, switch the blink between minutes, hours, etc
// read the pushbutton input pin:
  optionBtnCurState = digitalRead(optionButton);

  // compare the buttonState to its previous state
  if (optionBtnCurState != optionBtnPrevState) {
    // if the state has changed, increment the counter
    if (optionBtnCurState == LOW){
      // if the current state is LOW then the button went from on to off:
      currentMode = (currentMode+1)%TOTAL_NUM_OF_MODES;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  optionBtnPrevState = optionBtnCurState;
/*------------------------------ </option button> ----------------------------------------*/
}
/*------------------------------- </VIEW_TIME mode> --------------------------*/
/*------------------------------- <EDIT_TIME mode> --------------------------*/
if(currentMode == EDIT_TIME){
  toBlink = true;
  /*------------------------------ <option button> ----------------------------------------*/
  //if option is pressed while in edit mode, switch the blink between minutes, hours, etc
// read the pushbutton input pin:
  optionBtnCurState = digitalRead(optionButton);

  // compare the buttonState to its previous state
  if (optionBtnCurState != optionBtnPrevState) {
    // if the state has changed, increment the counter
    if (optionBtnCurState == LOW){
      // if the current state is LOW then the button went from on to off:
      //currentMode = (currentMode+1)%TOTAL_NUM_OF_MODES;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  optionBtnPrevState = optionBtnCurState;
/*------------------------------ </option button> ----------------------------------------*/
  /*------------------------------ <ok button> ----------------------------------------*/
  //if ok is pressed while in edit mode, switch to the view mode
// read the pushbutton input pin:
  okBtnCurState = digitalRead(okButton);

  // compare the buttonState to its previous state
  if (okBtnCurState != okBtnPrevState) {
    // if the state has changed, increment the counter
    if (okBtnCurState == LOW){
      // if the current state is LOW then the button went from on to off:
      currentMode = VIEW_TIME;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  okBtnPrevState = okBtnCurState;
/*------------------------------ </ok button> ----------------------------------------*/
/*------------------------------ <up button> ----------------------------------------*/
// read the pushbutton input pin:
  upBtnCurState = digitalRead(upButton);

  // compare the buttonState to its previous state
  if (upBtnCurState != upBtnPrevState) {
    // if the state has changed, increment the counter
    if (upBtnCurState == LOW){
      // if the current state is LOW then the button went from on to off:
      generalCounter++;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  upBtnPrevState = upBtnCurState;
/*------------------------------ </up button> ----------------------------------------*/
/*------------------------------ <down button> ----------------------------------------*/
// read the pushbutton input pin:
  downBtnCurState = digitalRead(downButton);

  // compare the buttonState to its previous state
  if (downBtnCurState != downBtnPrevState) {
    // if the state has changed, increment the counter
    if (downBtnCurState == LOW){
      // if the current state is LOW then the button went from on to off:
      generalCounter--;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  downBtnPrevState = downBtnCurState;
/*------------------------------ </down button> ----------------------------------------*/
}
/*------------------------------- </EDIT_TIME mode> --------------------------*/
/*------------------------------- <VIEW_ALARM mode> --------------------------*/
if(currentMode == VIEW_ALARM){
  toBlink = false;
    /*------------------------------ <option button> ----------------------------------------*/
  //if option is pressed while in edit mode, switch the blink between minutes, hours, etc
// read the pushbutton input pin:
  optionBtnCurState = digitalRead(optionButton);

  // compare the buttonState to its previous state
  if (optionBtnCurState != optionBtnPrevState) {
    // if the state has changed, increment the counter
    if (optionBtnCurState == LOW){
      // if the current state is LOW then the button went from on to off:
      currentMode = (currentMode+1)%TOTAL_NUM_OF_MODES;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  optionBtnPrevState = optionBtnCurState;
/*------------------------------ </option button> ----------------------------------------*/
}
/*------------------------------- </VIEW_ALARM mode> --------------------------*/
/*------------------------------- <EDIT_ALARM mode> --------------------------*/
if(currentMode == EDIT_ALARM){
  toBlink = false;
    /*------------------------------ <option button> ----------------------------------------*/
  //if option is pressed while in edit mode, switch the blink between minutes, hours, etc
// read the pushbutton input pin:
  optionBtnCurState = digitalRead(optionButton);

  // compare the buttonState to its previous state
  if (optionBtnCurState != optionBtnPrevState) {
    // if the state has changed, increment the counter
    if (optionBtnCurState == LOW){
      // if the current state is LOW then the button went from on to off:
      currentMode = (currentMode+1)%TOTAL_NUM_OF_MODES;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  optionBtnPrevState = optionBtnCurState;
/*------------------------------ </option button> ----------------------------------------*/
}
/*------------------------------- </EDIT_ALARM mode> --------------------------*/
/*------------------------------ </handle button inputs> ----------------------------------------*/

  display.clearDisplay();
  
  display.setCursor(0, 0);
  //display.print(currentMode == EDIT_TIME ? "EDIT" : "VIEW");
  display.print("MODE : ");
  display.print(currentMode);
  display.print("\n");
  
  display.setCursor(0, 20);
//  if(toBlink == true && blinkDelay % 100 == 0){
//    
//    toBlink = !toBlink;
//  }


  if(toBlink == false){
    display.print(generalCounter);
  }else{
    if(blinkDelay % 10 == 0){
      display.print(generalCounter);
    }
  }

  blinkDelay = (blinkDelay+1)%BLINK_DELAY_MAX;
  display.display();
}
