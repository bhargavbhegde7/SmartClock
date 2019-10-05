#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Declaring all the output pins
const int soundPin      = D0;
const int displayVccPin    = D2;
const int displayGroundPin = D1;
const int displaySDA       = D4;
const int displaySLC       = D3;

//Declaring all the input pins
const int upButton     = D5;
const int downButton   = D6;
const int okButton     = D7;
const int optionButton = D8;

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button



void setup() {
  Serial.begin(115200);

  //setup all the input and output modes
  pinMode(soundPin, OUTPUT);
  pinMode(displayGroundPin, OUTPUT);
  pinMode(displayVccPin, OUTPUT);
  
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(okButton, INPUT);
  pinMode(optionButton, INPUT);

  digitalWrite (displayGroundPin, LOW);
  digitalWrite (displayVccPin, HIGH);

  Wire.begin(displaySDA,displaySLC);//sda_pin 4 ,scl_pin 3

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  delay(2000);
   
}

void loop() {
  display.clearDisplay();

  
  display.setCursor(0, 10);

//--------------------------------------------------------------------------------------------
// read the pushbutton input pin:
  buttonState = digitalRead(upButton);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(200);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

  if(buttonPushCounter % 10 == 0){
    digitalWrite (soundPin, HIGH);
  }else{
    digitalWrite (soundPin, LOW);
  }
//--------------------------------------------------------------------------------------------

  display.println(buttonPushCounter);
  display.display();
  
}
