/**
  ABOUT PIR SENSOR
    Position is: knobs up (all'insu) and yellow selector on the left
    selector in single selector mode, remains high only for the time of the delay, low for 3 seconds, then repeat
    selector in repetable trigger, remains high as long as it detects movement and the delay is restarted every new detection
    left knob is range adjustment: clockwise turn, increase range/sensibility
    right knob is the time delay adjustment: clockwise turn, increase timing

    Wiring:
    middle pin is signal (to pin 2)
    left pin ground
    right pin Vcc

    USAGE MODE: repetable mode with low delay. With this settings, delay is around 9s

  PASSIVE BUZZER
    right pin is signal
    middle pin Vcc
    left pin ground

  RELAY
    right pin ground
    middle pin Vcc
    left pin signal
    IMPORTANT: for this project I used the analog A5 pin as digital pin
  
  LED
    right pin ground
    R pin is green (WRONG PIN ON THE CHIP)
    G pin is red (WRONG PIN ON THE CHIP)

  KEYPAD
    from left to right, pins from 5 to 12
**/
#include <Keypad.h>

#define RELE A5
#define ALARM_SENSOR 2
#define ALARM_SOUND A0
#define ALARM_DURATION 1000
#define KEY_DURATION 200
#define KEY_STORED_TIME 5000
#define PASSWORD "1234"
#define GREEN_LIGHT 3
#define RED_LIGHT 4

uint8_t personDetected;
bool active = false;
bool alarm = false;
long timestamp, lastAlarm, lastKeyPressed;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = { 5, 6, 7, 8 };
byte colPins[COLS] = { 9, 10, 11, 12 };
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char keyPressed;
String pin = "";

void waitForSensorCalibration() {
  delay(3000);
}

void setLedLight() {
  if(active) {
    digitalWrite(RED_LIGHT, HIGH);
    digitalWrite(GREEN_LIGHT, LOW);
  } else {
    digitalWrite(RED_LIGHT, LOW);
    digitalWrite(GREEN_LIGHT, HIGH);
  }
}

void resetPin() {
  pin = "";
}

void sound() {
  tone(ALARM_SOUND, 440, KEY_DURATION);
  delay(200);
}

bool personIsDetected() {
  return active && !alarm && personDetected == HIGH;
}

void handleAlarm() {
  if(personIsDetected()) {
    alarm = true;
  }
  if(alarm) {
    digitalWrite(RELE, HIGH);
    tone(ALARM_SOUND, 440, ALARM_DURATION); //This is used as alarm but in the future relay will be enough
  }
}

void handleUserInput() {
  if(keyPressed) {
    pin = pin + keyPressed;
    sound();
    lastKeyPressed = timestamp;
  }

  if(pin.equals(PASSWORD)) {
    active = !active;
    resetPin();
    setLedLight();
    if(alarm) {
      noTone(ALARM_SOUND);
      digitalWrite(RELE, LOW);
      alarm = !alarm;
    }
  } else {
      if(pin.length() == 4) {
        resetPin();
        sound();
        sound();
    }
  }
}

void setup() {
  pinMode(ALARM_SENSOR, INPUT);
  pinMode(ALARM_SOUND, OUTPUT);
  pinMode(GREEN_LIGHT, OUTPUT);
  pinMode(RED_LIGHT, OUTPUT);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, LOW);
  waitForSensorCalibration();
  setLedLight();
}

void loop() {
  timestamp = millis();

  personDetected = digitalRead(ALARM_SENSOR);
  keyPressed = kpd.getKey();

  handleAlarm();
  handleUserInput();

  if(pin.length() > 0 && (timestamp - lastKeyPressed > KEY_STORED_TIME)) {
    resetPin();
    sound();
    sound();
  }
}