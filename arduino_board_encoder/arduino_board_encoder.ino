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
const int LED = 13;

void setup() { 
  Serial.begin(9600);
    pinMode(EncoderPinA, INPUT); //set pin A and pin B as inputs
    digitalWrite(EncoderPinA, HIGH); // software pull up
    pinMode(EncoderPinB, INPUT);
    digitalWrite(EncoderPinB, HIGH);
    pinMode(buttonLeft, INPUT);
    pinMode(buttonRight, INPUT);
   // pinMode(SW, INPUT);
   
    attachInterrupt(0, HandleEncoderInterrupt, CHANGE); //add interrupt for any change in pins
}

void loop() {
  
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
         
  delay(10);
}
    
    
void HandleEncoderInterrupt() { 
  if (digitalRead(EncoderPinA) == digitalRead(EncoderPinB)) {
    Mouse.move(10,0,0);
  } else {
    Mouse.move(-10,0,0);
  }
}
