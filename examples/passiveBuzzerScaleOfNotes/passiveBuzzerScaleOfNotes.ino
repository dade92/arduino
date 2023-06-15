#include "notes.h"

#define BUZZER_PIN 2 //Pin generico
 
//Note melodia:
unsigned int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
  
unsigned int duration = 500;  //Durata nota in millisecondi
 
void setup() {
  pinMode(BUZZER_PIN, OUTPUT); //Impostiamo il pin come uscita 
}
 
void loop() {  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    tone(BUZZER_PIN, melody[thisNote], duration);

     //Dopo un secondo cambiamo nota
    delay(1000);
  }
   
  //Dopo due secondi dalla fine, ricominciamo la melodia
  delay(2000);
}