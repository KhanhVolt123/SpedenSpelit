#ifndef BUTTONS_H
#define BUTTONS_H

#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const byte firstPin = 2; // First PinChangeInterrupt on D-bus
const byte secondPin =  3; // Last PinChangeInterrupt on D-bus
const byte fourthPin = 4; // First PinChangeInterrupt on D-bus
const byte lastPin =  5; // First PinChangeInterrupt on D-bus
int buttonState[4]={HIGH,HIGH,HIGH,HIGH};
/* 
  initButtonsAndButtonInterrupts subroutine is called from Setup() function
  during the initialization of Speden Spelit. This function does the following:
  1) Initializes 4 button pins for the game = Arduino pins 2,3,4,5
  2) Initializes 1 button pin for starting the game = Aruino pin 6
  3) Enables PinChangeInterrupt on D-bus in a way that interrupt
     is generated whenever some of pins 2,3,4,5,6 is connected to LOW state

*/
void initButtonsAndButtonInterrupts(void);

/*
  Debounce is called in loop() function during the initialization of Speden Spelit. This function does the following:
  Debounce prevents the button from imputting many times from one button click. This function checks the button press
  in short period of time to make sure the push button is definitely pressed.
*/
void debounce(void);
/*
  Gives buttonsate 
*/
int getButtonState(int buttonIndex);

// Intoduce PCINT2_vect Interrupt SeRvice (ISR) function for Pin Change Interrupt.
ISR(PCINT2_vect); 
#endif;