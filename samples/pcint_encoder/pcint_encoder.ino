/*
 * pcint_encoder
 * (c) john@slowlybendingelectrons.com
 *     October 2013
 *
 * Demonstrating how to use PCINT on Leonardo to read two simple rotary encoders, by direct access to registers.
 *
 * Encoder handling technique based on code by Oleg at: http://www.circuitsathome.com/mcu/programming/reading-rotary-encoder-on-arduino
 * Thank you johngineer for this handy reference: http://www.flickr.com/photos/johngineer/7329403498/in/photostream
 *
 * Code references two encoders, one Left on PORTB pins 7 and 6, and one Right on pins 5 and 4. (Arduino pins: 11, 10, 9 and 8)
 * Encoder pins are debouced with a simple low pass RC filter and use an external pull up.
 * This is not very portable code and will not work on other Arduino variants.
 */

// Name some LED outputs, all on PWM pins.
#define    RedLeft 13
#define  GreenLeft  6
#define   RedRight  5
#define GreenRight  3

// Switches used on external interrupts.
#define  SwitchLeft 4 // Arduino pin 7
#define SwitchRight 1 // Arduino pin 2

// Remember past encoder state.
volatile byte  _storeLeft = 0;
volatile byte _storeRight = 0;

// Store for counting encoder ticks up and down.
volatile byte  _ticksLeft = 0;
volatile byte _ticksRight = 0;

// Given past and current encoder state, we can lookup whether that makes a tick up or a tick down. See PCINT0 ISR for context.
const int lookup[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };

// States to be flipped by switches.
volatile boolean  _stateLeft = false;
volatile boolean _stateRight = false;

void setup() {
  // encoder pin change interrupt setup on PORTB pins 7-4, ( Arduino pins 11-8 ). 
  DDRB  |= B11110000; // set bits 7-4 input, bits 3-0 untouched.
  PCMSK0 = B11110000; // enable PCINT on bits 7-4 only.
  PCICR  = B00000001; // enable PCINT0.
  
  // LEDs connected to the remaing available PWM outputs.
  pinMode(    RedLeft, OUTPUT);
  pinMode(  GreenLeft, OUTPUT);
  pinMode(   RedRight, OUTPUT);
  pinMode( GreenRight, OUTPUT);
  
  // use the switches as interrupts
  attachInterrupt(  SwitchLeft,  ISRLeft, FALLING);
  attachInterrupt( SwitchRight, ISRRight, FALLING);
}

void loop() {
  // Encoder rotation will set brightness on the Red LEDs.
  analogWrite(  RedLeft,  _ticksLeft );
  analogWrite( RedRight, _ticksRight );
  
  // Encoder switches will toggle Green LEDs.
  digitalWrite(  GreenLeft,  _stateLeft );
  digitalWrite( GreenRight, _stateRight );
}

/*
 * This Interrupt Service Routine uses a combination of past and current state of the encoder output to index a lookup table.
 * The return from the lookup is used to increment or decrement the related tick.
 */
ISR(PCINT0_vect){
  int temp = ( PINB >> 2 );              // read PORTB and line up the bits in a temporary variable ready for inclusion in the first state lookup reference.
  _storeRight |= ( temp & B00001100 );   // mask two bits and include in the lookup reference.
  _ticksRight += lookup[ _storeRight ];  // lookup increment or decrement adding directly to tick counter.
  _storeRight >>= 2;                     // make current state -> old state, discarding previous old state.
  temp >>= 2;                            // make next two bits available repeating lookup procedure for second encoder.
  _storeLeft |= ( temp & B00001100 );
  _ticksLeft += lookup[ _storeLeft ];
  _storeLeft >>= 2;
}

// Just flip a state when either switch is pressed.
void ISRLeft() {
 _stateLeft != _stateLeft; 
}

void ISRRight() {
 _stateRight != _stateRight; 
}
