#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H

#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "utils.h"

/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
*/
void initializeTimer(void);

// Intoduce TIMER1_COMPA_vect Interrupt Service (ISR) function for timer.
ISR(TIMER1_COMPA_vect);

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
*/
void initializeGame(void);

/*
  Gets button input from the player.
*/
void gameInput(void);

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
*/
void checkGame(byte);

/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame(void);

/*
  endTheGame() is used to stop the game and reset
  all variables to their initial state.
  
  Params:
    int scoreReached = the score reached by the player before the game ended.
*/
void endTheGame(int scoreReached);


bool wait(unsigned long ms, unsigned long &last);

/*
  This idle() function is called from loop() and makes the leds "dance" 
  while waiting for the user to start the game.
*/
void idle(void);

#endif