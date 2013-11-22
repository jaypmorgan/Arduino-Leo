#include <Bounce.h>

const int buttonLeft = 4;       // Switch Left
const int buttonRight = 5;      // Switch right
const int EncoderPinA = 2;      // knob turn left
const int EncoderPinB = 3;      // knob turn right
const int EncoderInterrupt = 0; // interrupt feature, might replace with polling tech
const int redLED = 7; 
const int greLED = 8; 
const int bluLED = 9;
const int SW = 10; 
const int LED = 13;             // standard LED pin
volatile int buttonState = 0;   //state of button
volatile int _encoderTicks = 0;

//Software Debouncers
Bounce debounceBLeft = Bounce(buttonLeft, 1);   // 1 milliseconds delay, good switches
Bounce debounceBRight = Bounce(buttonRight, 1);
Bounce pushSwitch = Bounce(SW, 5);

void setup() { 
  Serial.begin(9600);
    pinMode(EncoderPinA, INPUT); //set pin A and pin B as inputs
    pinMode(EncoderPinB, INPUT);
    pinMode(buttonLeft, INPUT);
    pinMode(buttonRight, INPUT);
    pinMode(SW, INPUT);
   
    attachInterrupt(EncoderInterrupt, HandleEncoderInterrupt, CHANGE); //add interrupt for any change in pins
}

void loop() {
  debounceBLeft.update();  //update debouncers
  debounceBRight.update();
  pushSwitch.update(); 
  
  if (debounceBLeft.read() == LOW) { 
      //output
      Keyboard.begin();
      Keyboard.press(218); // up arrow
      Keyboard.releaseAll();
  } 
  
  if (debounceBRight.read() == LOW) { 
    //output  
    Keyboard.begin();
    Keyboard.press(217); // down arrow
    Keyboard.releaseAll();
  }
  
  if (pushSwitch.read() == HIGH) {
    Keyboard.begin();
    Keyboard.press(211); // page up
    Keyboard.releaseAll();
    analogWrite(greLED, HIGH); 
  }
  
  delay(10);
}
    
    
void HandleEncoderInterrupt() { 
  _encoderTicks = ((PIND >> 1) & 0x1) ? 1 : 2 ;
  
  if (_encoderTicks != 2) { 
     turnLeft(); 
  } else if (_encoderTicks != 1) { 
     turnRight(); 
  }
  
  _encoderTicks = 0;
}

void turnLeft() { 
      Keyboard.begin();
      Keyboard.press(216);
      Keyboard.releaseAll();
      analogWrite(redLED, 1); 
}

void turnRight() { 
   Keyboard.begin();
      Keyboard.press(215);
      Keyboard.releaseAll(); 
      analogWrite(bluLED, 1);
}
