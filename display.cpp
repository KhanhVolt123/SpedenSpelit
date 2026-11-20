#include "display.h"

// Alla olevien muuttujien arvot kertoo minkä numeroiseen Arduinon digitaaliseen pinniin SN74HC595N:n pinnit on kytketty.
uint8_t dataPin = 8; // Muuttuja Serial Data Input -pinnille (SER). Seuraavaksi siirtorekisteriin kirjoitettavan bitin arvo on 0 (LOW) tai 1 (HIGH).
uint8_t oePin = 9; // Muuttuja Output Enable -pinnille. LOW = lähdöt QA-QH ovat käytössä, HIGH = lähdöt QA-QH eivät ole käytössä.
uint8_t latchPin = 10; // Muuttuja Register Clock -pinnille. LOW -> HIGH = kopioidaan siirtorekisterin sisältö lähtöihin QA-QH.
uint8_t clockPin = 11; // Muuttuja Shift Register Clock -pinnille. LOW -> HIGH = SER-pinnin päättämä arvo siirretään siirtorekisteriin.
uint8_t resetPin = 12; // Muuttuja Shift Register Clear -pinnille. LOW = Kaikki bitit nollataan, HIGH = Normaali toiminta.

byte numbers[10] = { // Tavutyyppinen taulukko, minkä jokainen binääriluku sytyttää tietyn luvun (0-9) tarvitsemat segmentit näytöllä.
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
    for (int i = 8; i < 13; i++) // Kutsuttaessa funktiota määritetään Arduinon digitaaliset pinnit 8-12 lähtöpinneiksi (OUTPUT-modeen) for-loopilla.
    { 
        pinMode(i, OUTPUT);
    }
}

void writeByte(uint8_t bits,bool last) // Tätä kutsutaan void loop()-funktion sisällä. bits on luku 0-9
{
    if (bits > 9) // Jos annettava kokonaisluku on suurempi kuin 9, poistutaan funktiosta.
    {
        return;
    }
    digitalWrite(oePin, LOW); // Kutsuttaessa funktiota otetaan näytön segmentteihin yhdistetyt lähtöpinnit käyttöön.
    digitalWrite(resetPin, HIGH); // Asetetaan SRCLR-pinni korkeaan tilaan, jotta bitit toimii normaalisti.

    if (last == true) // Jos halutaan tulostaa luku, niin last on true.
    {
        digitalWrite(latchPin, LOW); // Asetetaan RCLK-pinni matalaan tilaan, jotta dataa voidaan kerätä rekisteriin.

        byte value = numbers[bits]; // Tavutyyppinen muuttuja varastoimaan tiettyä numbers-taulukon alkiota.

        for (int i = 7; i >= 0; i--) // Lähetetään tavun bitit MSB-järjestyksessä (bitit 7...0).
        {
            digitalWrite(clockPin, LOW); // Asetetaan SRCLK-pinni matalaan tilaan odottamaan kellopulssia.
            // Alla olevassa rivissä value on binääriluku, >> kertoo, että bitit siirretään oikealle ja i kertoo montako bittiä siirrytään oikealle. 
            // &-operaattori vertaa (value >> i) -arvoa ykköseen. Näin tila on varmasti bitin mukainen.
            digitalWrite(dataPin, (value >> i) & 1); // Asetetaan SER-pinni joko matalaan tai korkeaan tilaan. LOW, jos (value >> i) on 0 ja HIGH, jos (value >> i) on 1.

            digitalWrite(clockPin, HIGH); // Asetetaan SRCLK-pinni korkeaan tilaan: kellopulssi tapahtuu ja kellonreunalla dataPin-pinnin määräämä data siirtyy siirtorekisteriin.
        }

        digitalWrite(latchPin, HIGH); // Asetetaan RCLK-pinni korkeaan tilaan, jotta kellonreunalla lähdöt QA-QH päivittyvät yhtäaikaa.
    }
}

void writeHighAndLowNumber(uint8_t tens,uint8_t ones) 
{
    // See requirements for this function from display.h
}

void showResult(byte number) 
{
    // See requirements for this function from display.h
}