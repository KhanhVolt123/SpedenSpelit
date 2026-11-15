#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// meininki

volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile int isrCallIndex = 0;            // this index is raised every time the isr is called. When it reaches ten, the speed increases.

// Overly commented setup because I hardly understand this shi myself
void setup() {
  Serial.begin(9600);

  // Timer setup
  noInterrupts();
  TCCR1A = 0;     // Clear these so there are no surprises ;)
  TCCR1B = 0;
  TCNT1 = 0;      // Counter starts from zero. Using CTC mode does this already but there could be some garbage left over.

  /*
    With this formula a timer for a desired frequency can be made easily :P

    OCR = CPU / (PRESCALER * FREQ) - 1 = OUTPUT.

    Since the ATMegaWhatevr in the arduino is 16 Mhz, if that 
    is divided by the prescaler value times 1 (hz) - 1 (because counting starts at zero so at count 15624 there has been 15625 counts...) we get 1 hz.

    So...

    OCR = 16000000 / (1024 * 1) - 1 = 15624.

    If the prescaler value is too small the output can be too large
    to fit into a 16 bit unsigned integer (65500 or somethng) so by using a bigger prescaler that doesn't happen.
    It does affect the resolution of the timer but this game is so slow it doesn't matter... Probably 乁( ˙ ω˙乁).
  */
  OCR1A = 15624;

  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode (count up to OCR1A and then reset to 0), prescaler 1024 (CS12 and CS10 set).
  TIMSK1 |= (1 << OCIE1A);                            // no OCIE1A, no isr :P when counter reaches OCR1A the isr func is run.

  interrupts();
}

void loop() {

  gameInput();

  if(buttonNumber >= 0) {
     // start the game if buttonNumber == 4
     // check the game if 0<=buttonNumber<4
  }

  if(newTimerInterrupt == true) {
    // new random number must be generated
    // and corresponding let must be activated
    
    Serial.println("Beep...Boop...Making a new number...");

    newTimerInterrupt = false;
  }
}

void initializeTimer(void) {
	// see requirements for the function from SpedenSpelit.h
}

ISR(TIMER1_COMPA_vect) {
  isrCallIndex++;

  // Generate number
  newTimerInterrupt = true;
  
  if(isrCallIndex == 10) {
    // Increase speed

    isrCallIndex = 0;
  }
}

// Taking input through the serial monitor for testing
void gameInput() {
  if(Serial.available() > 0) {
    int input = Serial.parseInt();

    if(input <= 4 && input >= 0) {
      buttonNumber = input;

      Serial.print("Pressed: ");
      Serial.println(input);
    }
  }
}

void checkGame(byte nbrOfButtonPush) {
	// see requirements for the function from SpedenSpelit.h
}

void initializeGame() {
	// see requirements for the function from SpedenSpelit.h
}

void startTheGame() {
   // see requirements for the function from SpedenSpelit.h
}