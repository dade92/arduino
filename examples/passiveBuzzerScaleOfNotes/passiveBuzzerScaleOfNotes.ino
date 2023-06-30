#include "notes.h"

#define BUZZER_PIN 3
 
unsigned int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
  
unsigned int duration = 500;
 
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}
 
void loop() {  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    tone(BUZZER_PIN, melody[thisNote], duration);

    delay(1000);
  }

  delay(2000);
}