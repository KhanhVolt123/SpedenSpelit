#include "display.h"

// The values of the variables below tell us the number of the Arduino digital pin in which the referenced shift register pin is connected to.
uint8_t dataPin = 8; // A variable for the Serial Data Input pin (SER). The next bit value to be written to the shift register is 0 (LOW) or 1 (HIGH).
uint8_t oePin = 9; // A variable for the Output Enable pin (QA-QH). LOW = QA-QH outputs are used, HIGH = QA-QH outputs are not used.
uint8_t latchPin = 10; // A variable for the Register Clock pin (RCLK). LOW -> HIGH = Copy everything inside the shift register to the QA-QH outputs.
uint8_t clockPin = 11; // A variable for the Shift Register Clock pin (SRCLK). LOW -> HIGH = The value determined by the SER pin is moved to the shift register.
uint8_t resetPin = 12; // A variable for the Shift Register Clear pin (SRCLR). LOW = All bits are reset, HIGH = Normal bit activity.

byte displayNumbers[10] = { // A byte type array. Every binary number in it lights up a specific number (0-9) in the segment display.
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111 // 9
};

void initializeDisplay(void) 
{
  for (int i = 8; i < 13; i++) // When the function is called using a for loop we'll set the states of Arduino digital pins 8-12 to output.
  { 
    pinMode(i, OUTPUT);
  }
}

void writeByte(uint8_t bits,bool last) {
  if (bits > 9) return;

  digitalWrite(oePin, LOW); // Enable the output pins that are connected to the display segments.
  digitalWrite(resetPin, HIGH); // Set the SRCLR pin state to high so that the bits work correctly.
  digitalWrite(latchPin, LOW); // Set the RCLK pin state to low so data can be collected to the register.

  byte value = displayNumbers[bits]; // A byte type variable to store a specific displayNumbers array element.

  // Send the bits of the byte in the MSB order (bits 7...0).
  for (int i = 7; i >= 0; i--) {
    digitalWrite(clockPin, LOW); // Set the SRCLK pin state to low to wait for the clock pulse.
    // In the row below value is a binary number, >> tells us the direction
    // where the bits of it are moved to and i tells how many times the bits are moved by one bit. 
    // & operator compares (value >> i) to 1. This way we ensure that the state is same as the bit.
    // Set the SER pin state either to low or high. LOW if (value >> i) is 0 and HIGH if (value >> i) is 1.
    digitalWrite(dataPin, (value >> i) & 1);

    // Set the SRCLK pin state to high: the clock pulse happens and the data determined by
    // the dataPin moves into the shift register on the edge of the clock.
    digitalWrite(clockPin, HIGH);
  }

  // If the last parameter is true, we set the RCLK pin state to high to update the QA-QH outputs at the same time.
  if(last) {
    digitalWrite(latchPin, HIGH);
  }
}

void writeHighAndLowNumber(uint8_t tens, uint8_t ones) {
  writeByte(tens, false);
  writeByte(ones, true);
}

void showResult(byte number) // This subroutine is called in the void loop();
{
  uint8_t tens = 0; // A variable to store the left number.
  uint8_t ones = 0; // A variable to store the right number.
  ones = number % 10; // Take the remainder from the given number when divided by ten and store it to ones. For example if the number is 17, the remainder will be 7.
  tens = number / 10; // The number is then divided by ten to get the tens. For example if the number is 65, you'll get 6 because decimal numbers like 6.5 are rounded down in C.
  Serial.print(tens); // A debug print.
  Serial.println(ones); // A debug print.
  writeHighAndLowNumber(tens, ones); // Call the writeHighAndLowNumber subroutine with both numbers given as parameters.
}