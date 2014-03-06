#include <Bounce.h>

const int buttonRight = 10;       // Push Switch Left
const int buttonLeft = 11;        // Push Switch right
const int buttonUp = 12;         // Push Switch Up
const int buttonDown = 9;       // Push Switch Down
const int EncoderPinA = 2;       // knob turn left
const int EncoderPinB = 3;       // knob turn right
const int EncoderInterrupt = 0;  // interrupt feature, might replace with polling tech
//const int redLED = 7; 
//const int greLED = 8; 
//const int bluLED = 9;
//const int SW = 10;               // push down feature on the rotary encoder
const int LED = 13;              // standard LED pin
volatile int buttonState = 0;    // state of button
volatile int _encoderTicks = 0;

//Software Debouncers
//Bounce debounceBLeft = Bounce(buttonLeft, 1);   // 1 milliseconds delay, good switches
//Bounce debounceBRight = Bounce(buttonRight, 1);
//Bounce debounceBUp = Bounce(buttonUp, 1);   // 1 milliseconds delay, good switches
//Bounce debounceBDown = Bounce(buttonDown, 1);
//Bounce pushSwitch = Bounce(SW, 5);

void setup() { 
  Serial.begin(9600);
    pinMode(EncoderPinA, INPUT); //set pin A and pin B as inputs
    pinMode(EncoderPinB, INPUT);
    pinMode(buttonLeft, INPUT);
    pinMode(buttonRight, INPUT);
   // pinMode(SW, INPUT);
   
    //attachInterrupt(EncoderInterrupt, HandleEncoderInterrupt, CHANGE); //add interrupt for any change in pins
}

void loop() {
  //debounceBLeft.update();  //update debouncers
  //debounceBRight.update();
  //pushSwitch.update(); 
  
  if (digitalRead(buttonLeft) == HIGH) { 
      //output
      Keyboard.begin();
      Keyboard.press(216); // left arrow
      Keyboard.releaseAll();
  } 
  
  if (digitalRead(buttonRight) == HIGH) { 
    //output  
    Keyboard.begin();
    Keyboard.press(215); // right arrow
    Keyboard.releaseAll();
  }
  
  if (digitalRead(buttonUp) == HIGH) { 
      //output
      Keyboard.begin();
      Keyboard.press(218); // up arrow
      Keyboard.releaseAll();
  } 
  
  if (digitalRead(buttonDown) == HIGH) { 
    //output  
    Keyboard.begin();
    Keyboard.press(217); // down arrow
    Keyboard.releaseAll();
  }
  
  /*if (pushSwitch.read() == HIGH) {
    Keyboard.begin();
    Keyboard.press(32); // page up
    Keyboard.releaseAll();
    analogWrite(greLED, HIGH); 
  }*/
  
  
  
  /*if (digitalRead(EncoderPinA) == LOW) { 
     turnRight(); 
  } 
  
  if (digitalRead(EncoderPinB) == LOW) { 
     turnLeft(); 
  }*/
         
  delay(10);
}
    
    
void HandleEncoderInterrupt() { 
  //_encoderTicks = ((PIND >> 1) & 0x1) ? 1 : 2 ;
  
  //_encoderTicks = 0;
}

void turnLeft() { 
      Keyboard.begin();
      Keyboard.press(216);
      Keyboard.releaseAll();
      //analogWrite(redLED, 1); 
}

void turnRight() { 
   Keyboard.begin();
      Keyboard.press(215);
      Keyboard.releaseAll(); 
      //analogWrite(bluLED, 1);
}
