#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable)
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please

// Encoder
#define EncoderInterrupt 0
#define EncoderPinA 3
#define EncoderPinB 2
// volatile bool _EncoderSet;
volatile long _EncoderTicks = 262;

void setup()
{
  Serial.begin(115200);
 
  // Encoder
  pinMode(EncoderPinA, INPUT);      // sets pin A as input
  digitalWrite(EncoderPinA, HIGH);  // turn on pullup resistors
  pinMode(EncoderPinB, INPUT);      // sets pin B as input
  digitalWrite(EncoderPinB, HIGH);  // turn on pullup resistors
  attachInterrupt(EncoderInterrupt, HandleEncoderInterrupt, RISING);
 
 startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  aSin.setFreq(262); // set the frequency 
} 
 
void updateControl(){
  aSin.setFreq((float)_EncoderTicks);
  Serial.print(_EncoderTicks);
  Serial.print("\n");
}

int updateAudio(){
  return aSin.next(); // return an int signal centred around 0
}

void loop()
{
  audioHook(); // required here
}
 
// Interrupt service routines for the left motor's quadrature encoder
void HandleEncoderInterrupt()
{
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
 // _EncoderSet = ;   // read D2
  _EncoderTicks += ((PIND >> 1) & 0x1) ? -20 : +20;
  if(_EncoderTicks < 65 ) _EncoderTicks = 1047;
  if(_EncoderTicks > 1047 ) _EncoderTicks = 65;
}
 

