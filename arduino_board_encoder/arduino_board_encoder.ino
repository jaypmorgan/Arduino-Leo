#include <Bounce.h>

const int buttonRight = 9;       // Push Switch Left
const int buttonLeft = 12;        // Push Switch right
const int buttonUp = 13;         // Push Switch Up
const int buttonDown = 11;       // Push Switch Down
const int EncoderPinA = 3;       // knob turn left
const int EncoderPinB = 2;       // knob turn right
const int EncoderInterrupt = 0;  // interrupt feature, might replace with polling tech
const int SW = 5;               // push down feature on the rotary encoder
//const int redLED = 7; 
//const int greLED = 8; 
//const int bluLED = 9;

Bounce bouncerPinA = Bounce(20, EncoderPinA);
Bounce bouncerPinB = Bounce(20, EncoderPinB);

void setup() { 
    Serial.begin(9600);
    
    pinMode(EncoderPinA, INPUT); //set pin A and pin B as inputs
    pinMode(EncoderPinB, INPUT);
    pinMode(SW, INPUT);
    digitalWrite(EncoderPinA, HIGH); // software pull up
    digitalWrite(EncoderPinB, HIGH);
    
    // Push Buttons 
    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);
    pinMode(buttonLeft, INPUT);
    pinMode(buttonRight, INPUT);
    
    digitalWrite(buttonUp, HIGH);
    digitalWrite(buttonDown, HIGH);
    digitalWrite(buttonLeft, HIGH);
    digitalWrite(buttonRight, HIGH);
   
    attachInterrupt(0, HandleEncoderInterrupt, CHANGE); //add interrupt for any change in pins
    //attachInterrupt(1, SwitchInterrupt, LOW);
}                                                                                                   

void loop() {
  
  if (digitalRead(buttonLeft) == LOW) { 
      //output
      Keyboard.begin();
      Keyboard.press(216); // left arrow
      Keyboard.releaseAll();
  } 
  
  if (digitalRead(buttonRight) == LOW) { 
    //output  
    Keyboard.begin();
    Keyboard.press(215); // right arrow
    Keyboard.releaseAll();
  }
  
  if (digitalRead(buttonUp) == LOW) { 
      //output
      Keyboard.begin();
      Keyboard.press(218); // up arrow
      Keyboard.releaseAll(); 
  } 
  
  if(digitalRead(buttonDown) == LOW) { 
    //output  
    Keyboard.begin();
    Keyboard.press(217); // down arrow
    Keyboard.releaseAll();
  }
  
  if (digitalRead(SW) == HIGH) {
    Keyboard.begin();
    Keyboard.press('f'); // down arrow
    Keyboard.releaseAll();
    
  } 

  Serial.println(digitalRead(SW));  
  delay(10);
}
    
    
void HandleEncoderInterrupt() { 
  bouncerPinA.update();
  bouncerPinB.update();
  
  Serial.println(digitalRead(EncoderPinA));
  Serial.println(digitalRead(EncoderPinB));
  
  
  if (digitalRead(EncoderPinA) == digitalRead(EncoderPinB)) {
    Mouse.move(-10,0,0);
  } else  {
    Mouse.move(10,0,0);
  }
}
