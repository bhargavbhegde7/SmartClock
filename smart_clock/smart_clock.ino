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
const int VIEW_TIME  = 1;
const int EDIT_TIME  = 2;
const int VIEW_ALARM = 3;
const int EDIT_ALARM = 4;

int upBtnCurState  = 0;
int upBtnPrevState = 0;

int downBtnCurState  = 0;
int downBtnPrevState = 0;

int optionBtnCurState  = 0;
int optionBtnPrevState = 0;

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

/*------------------------------ <option button> ----------------------------------------*/
//no matter what the current mode is, always change mode when the option is pressed.
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

/*------------------------------- <VIEW_TIME mode> --------------------------*/
if(currentMode == VIEW_TIME){
  toBlink = false;
}
/*------------------------------- </VIEW_TIME mode> --------------------------*/
/*------------------------------- <EDIT_TIME mode> --------------------------*/
if(currentMode == EDIT_TIME){
  toBlink = true;
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
/*------------------------------ </handle button inputs> ----------------------------------------*/

  display.clearDisplay();
  
  display.setCursor(0, 0);
  display.print(currentMode == EDIT_TIME ? "EDIT" : "VIEW");
  
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
















