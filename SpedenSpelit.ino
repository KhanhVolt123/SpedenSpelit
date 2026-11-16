#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// meininki

volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile int isrCallIndex = 0;            // this index is raised every time the isr is called.

int numbers[100];                         // array for the numbers that are generated
int score = 0;

bool gameStarted = false;

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(0));              // Random seed from analog pin 0s noise.

  initializeLeds();

  // Timer setup
  noInterrupts();
  initializeTimer();

  interrupts();
}

void loop() {
  if(!gameStarted) idle();

  gameInput();

  if(buttonNumber >= 0 && buttonNumber < 4) checkGame(buttonNumber);
  else if(buttonNumber == 4) startTheGame();

  if(newTimerInterrupt == true) {
    // new random number must be generated
    // and corresponding let must be activated
    
    //Serial.println("Beep...Boop...Making a new number...");

    clearAllLeds();
    setLed(numbers[isrCallIndex]);

    newTimerInterrupt = false;
  }
}

void initializeTimer(void) {
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
}

ISR(TIMER1_COMPA_vect) {
  if(gameStarted) {
    isrCallIndex++;

    newTimerInterrupt = true;
    
    if(isrCallIndex % 10 == 0) {
      // Increase speed

      OCR1A -= 1000;
    }
  }
}

void gameInput() {
  // Taking input through the serial monitor for testing
  if(Serial.available() > 0) {
    int input = Serial.parseInt();

    if(input <= 4 && input >= 0) {
      buttonNumber = input;

      Serial.print("Pressed: ");
      Serial.println(input);
    }
  }

  // TODO: get real input from buttons
}

void checkGame(byte lastButtonPress) {
  if(!gameStarted) return;

  if(numbers[score] != lastButtonPress) {
    Serial.println("Game over");
    score = 0;

    showResult(score);

    // reset shit
    gameStarted = false;
    OCR1A = 15624;

  } else {
    score++;

    writeHighAndLowNumber(score / 10, score % 10);

    Serial.print("Score: ");
    Serial.println(score);
  }
}

void initializeGame() {
  clearAllLeds();

  for(int i = 0; i < 200; i++) {
    numbers[i] = random(0, 4);
  }

  Serial.println("Game initialized");
}

void startTheGame() {
  initializeGame();

  gameStarted = true;
}

void idle() {
  for(int i = 0; i < 10; i++) {
    clearAllLeds();

    switch(i) {
      case 0: setLed(1); setLed(3); break;
      case 1: setLed(0); setLed(2); break;
      case 2: setLed(1); setLed(3); break;
      case 3: setLed(0); setLed(2); break;
      case 4: setLed(0); break;
      case 5: setLed(1); break;
      case 6: setLed(2); break;
      case 7: setLed(3); break;
      case 8: clearAllLeds(); break;
      case 9: setAllLeds(); break;
    }

    delay(500);
  }
}