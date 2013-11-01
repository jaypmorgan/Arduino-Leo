/*Arduino Parrallax Effect Board*/
#define EncoderPinA 2
#define EncoderPinB 3
#define EncoderInterrupt 0

#define LED 13

volatile int _encoderTicks = 0;

void setup() { 
  Serial.begin(9600);
    pinMode(EncoderPinA, INPUT); //set pin A and pin B as inputs
    pinMode(EncoderPinB, INPUT);
    
    attachInterrupt(EncoderInterrupt, HandleEncoderInterrupt, CHANGE); //add interrupt for any change in pins
}

void loop() { 
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
