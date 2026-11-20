#include "buttons.h"
volatile byte first_buttonpressed = 0;
volatile byte second_buttonpressed = 0;
volatile byte third_buttonpressed = 0;
volatile byte fourth_buttonpressed  = 0;
volatile byte buttonstatus = 0; 

byte buttonpin[]={2,3,4,5};
int buttonState[4]={HIGH,HIGH,HIGH,HIGH};             
int lastButtonState[4] = {HIGH,HIGH,HIGH,HIGH};     
unsigned long lastDebounceTime[4] = {0,0,0,0};  
unsigned long debounceDelay = 50; 
void initButtonsAndButtonInterrupts(void)
{
  // See requirements for this function from buttons.h
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);

PCICR |= (1 << PCIE2);

PCMSK2 |= (1 << PCINT18);
PCMSK2 |= (1 << PCINT19);
PCMSK2 |= (1 << PCINT20);
PCMSK2 |= (1 << PCINT21);
}


ISR(PCINT2_vect) {
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
buttonstatus = PIND;
first_buttonpressed  = (buttonstatus & (1 << PD2)) == 0; //Tarkistaa, että onko D2 painettu
second_buttonpressed   = (buttonstatus & (1 << PD3)) == 0;
third_buttonpressed = (buttonstatus & (1 << PD4)) == 0;
fourth_buttonpressed = (buttonstatus & (1 << PD5)) == 0;
}
void debounce(void){
for(int i = 0;i < 4;i++){
int reading = digitalRead(buttonpin[i]);

if(reading != lastButtonState[i]){
  lastDebounceTime[i] = millis();
}
if((millis() - lastDebounceTime[i]) > debounceDelay){
  if(reading != buttonState[i]){
    buttonState[i] = reading;
     if (buttonState[i] == LOW) {
   Serial.println(buttonpin[i]);
  }
  }
}
 lastButtonState[i] = reading;//tallentaa painikkeen nyky lukeman seuraavalle kierrokselle
}
}
