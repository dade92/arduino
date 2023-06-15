// Definizione tastiera
#include <Keypad.h>

int potentiometer = A0;
const byte ROWS = 4; // Quattro righe
const byte COLS = 4; // Quattro colonne
// Definizione mappa della tastiera
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = { 12, 11, 10, 9 }; // Riga0,1,2,3.
byte colPins[COLS] = { 8, 7, 6, 5 }; // Colonna0,1,2,3
// Creazione della tastiera
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  pinMode(potentiometer, INPUT);
  Serial.begin(9600);
}

void loop() {
  float value = analogRead(potentiometer);
  Serial.println(value);

  char key = kpd.getKey();
  if (key) {
    Serial.println(key);
  }
  delay(1000);
}