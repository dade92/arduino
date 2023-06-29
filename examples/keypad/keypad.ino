#include <Keypad.h>
#define LED_ERROR 4
#define LED_SUCCESS 3
#define SOUND 13

const String VERY_STRONG_PIN = "666D";

const byte ROWS = 4; // Quattro righe
const byte COLS = 4; // Quattro colonne
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = { 12, 11, 10, 9 }; // Riga0,1,2,3.
byte colPins[COLS] = { 8, 7, 6, 5 }; // Colonna0,1,2,3
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int RESET_TIME = 5000;
unsigned long lastDigitTime = 0;
const String pin = "";

void setup() {
  Serial.begin(9600);
  pinMode(LED_ERROR, OUTPUT);
  pinMode(LED_SUCCESS, OUTPUT);
  pinMode(SOUND, OUTPUT);
}

void loop() {
  char key = kpd.getKey();
  digitalWrite(SOUND, LOW);
  
  if(millis() - lastDigitTime > RESET_TIME) {
    Serial.println("resetting pin");
    pin = "";
    digitalWrite(LED_ERROR, LOW);
    digitalWrite(LED_SUCCESS, LOW);
    lastDigitTime = millis();
  }
  if (key && millis() - lastDigitTime < RESET_TIME) {
    pin = pin + key;
    Serial.print("Pin so far: ");Serial.println(pin);
    digitalWrite(SOUND, HIGH);
    if(pin.equals(VERY_STRONG_PIN)) {
      Serial.println("Pin correct");
      digitalWrite(LED_SUCCESS, HIGH);
      pin = "";
      delay(100);
      digitalWrite(SOUND, LOW);
      delay(100);
      digitalWrite(SOUND, HIGH);
    }
    if(pin.length() == VERY_STRONG_PIN.length()) {
      Serial.println("Wrong pin, reset");
      digitalWrite(LED_ERROR, HIGH);
      pin = "";
    }
    lastDigitTime = millis();
  }
  delay(100);
}