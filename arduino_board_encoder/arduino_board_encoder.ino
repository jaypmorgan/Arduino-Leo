#include <Bounce.h>

const int buttonLeft = 4;       // Switch Left
const int buttonRight = 5;      // Switch right
const int EncoderPinA = 2;      // knob turn left
const int EncoderPinB = 3;      // knob turn right
const int EncoderInterrupt = 0; // interrupt feature, might replace with polling tech
const int LED = 13;             // standard LED pin
volatile int buttonState = 0;   //state of button
volatile int _encoderTicks = 0;

//Software Debouncers
Bounce debounceBLeft = Bounce(buttonLeft, 5);   // 5 milliseconds delay
Bounce debounceBRight = Bounce(buttonRight, 5);
Bounce debounceEPinA = Bounce(EncoderPinA, 5);
Bounce debounceEPinB = Bounce(EncoderPinB, 5);

void setup() { 
  Serial.begin(9600);
    pinMode(EncoderPinA, INPUT); //set pin A and pin B as inputs
    pinMode(EncoderPinB, INPUT);
    pinMode(buttonLeft, INPUT);
    pinMode(buttonRight, INPUT);
    
    attachInterrupt(EncoderInterrupt, HandleEncoderInterrupt, CHANGE); //add interrupt for any change in pins
}

void loop() { 
  debounceBLeft.update();  //update debouncers
  debounceBRight.update();
  debounceEPinA.update();
  debounceEPinB.update();
    
  if (debounceBLeft.read() == HIGH) { 
      //output
      Keyboard.begin();
      Keyboard.press(KEY_PAGE_UP);
      Keyboard.releaseAll();
  } 
  
  if (debounceBRight.read() == HIGH) { 
    //output  
    Keyboard.begin();
    Keyboard.press(KEY_PAGE_DOWN);
    Keyboard.releaseAll();
  }
  
  analogWrite(LED, _encoderTicks);
  Serial.write(_encoderTicks);
  delay(10);
}
    
    
void HandleEncoderInterrupt() { 
  //if pin is 2 then state left if pin is more than 2 (3) then state is right
  _encoderTicks += ((PIND >> 1) & 0x1) ? -1 : +1;
  if(_encoderTicks < 0 ) _encoderTicks = 255;
  if(_encoderTicks > 255 ) _encoderTicks = 0;
 
}
