#include "display.h"

uint8_t rows[10][7] = { // Kokonaislukumatriisi, minkä jokainen taulukko vastaa yhden luvun (0-9 väliltä) vaatimia pinnien tiloja.
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1} // 9
};

void initializeDisplay(void) 
{
    // See requirements for this function from display.h
    for (int i = 2; i < 9; i++) { // Enabloidaan for-loopilla tässä kohtaa tarvittavat Arduinon digitaaliset pinnit.
        pinMode(i, OUTPUT);
    }
}

void writeByte(uint8_t bits,bool last) 
{
    if (last == true) // Jos halutaan tulostaa luku, niin last on true.
    {
        for (int i = 0; i < 9; i++)
        {   
            digitalWrite(i + 2, rows[bits][i]); // Käydään for-loopilla läpi kaikki tarvittavat Arduinon pinnit, ja 0 (LOW), sekä 1 (HIGH) määräävät segmenttien syttymisestä.
        }
    }
}

void writeHighAndLowNumber(uint8_t tens,uint8_t ones) {
    // See requirements for this function from display.h
}

void showResult(byte number) {
    // See requirements for this function from display.h
}