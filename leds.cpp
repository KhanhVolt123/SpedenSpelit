#include "leds.h"


void initializeLeds() {         //Sets the pins A2-A5 to output
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);

}

void setLed(byte ledNumber) {       //Turns on the designated led
    switch(ledNumber) {
        case 0:
            digitalWrite(A2, HIGH);
            break;
        case 1:
            digitalWrite(A3, HIGH);
            break;
        case 2:
            digitalWrite(A4, HIGH);
            break;
        case 3:
            digitalWrite(A5, HIGH);
            break;
    }

}


void clearAllLeds() {       //Turns off all the leds
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
 
}

void setAllLeds() {         //Turns on all the leds
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
    digitalWrite(A5, HIGH);
}

void show2(int a){                  //Turns on the leds in order for a set amount of loops with the speed increasing at the end of each loop
    for(int i = 0; i > a; i++){
        for(int j = 4; j > 0; j--){
            clearAllLeds();
            switch(j) {
                case 0: digitalWrite(A2, HIGH); break;
                case 1: digitalWrite(A3, HIGH); break;
                case 2: digitalWrite(A4, HIGH); break;
                case 3: digitalWrite(A5, HIGH); break;
            }
            delay(j * 100);
        }
    }
}
