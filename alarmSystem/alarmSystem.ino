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
**/
#include <Keypad.h>

#define RELE 1
#define ALARM_SENSOR 2
#define ALARM 13
#define ALARM_DURATION 1000
#define KEY_DURATION 200
#define PASSWORD "1234"
#define GREEN_LIGHT 3
#define RED_LIGHT 4

uint8_t personDetected;
bool active = false;
bool alarm = false;
long timestamp, lastAlarm;
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
char key;
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

void setup() {
  pinMode(ALARM_SENSOR, INPUT);
  pinMode(ALARM, OUTPUT);
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
  key = kpd.getKey();

  if(key) {
    pin = pin + key;
    tone(ALARM, 440, KEY_DURATION);
    delay(200);
  }

  if(pin.equals(PASSWORD)) {
    active = !active;
    pin = "";
    setLedLight();
    if(alarm) {
      //reset the status
      noTone(ALARM);
      digitalWrite(RELE, LOW);
      alarm = !alarm;
    }
  } else {
      if(pin.length() == 4) {
        pin = "";
        tone(ALARM, 440, KEY_DURATION);
        delay(200);
        tone(ALARM, 440, KEY_DURATION);
        delay(200);
    }
  }

  if(alarm) {
    digitalWrite(RELE, HIGH);
    tone(ALARM, 440, ALARM_DURATION);
  }

  if(active && personDetected == HIGH) {
    alarm = true;
  }
}


/**
EXAMPLE SKETCH FOR TESTING
#define ALARM_SENSOR 2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ALARM_SENSOR, INPUT);
}
uint8_t alarm;

void loop() {
  // put your main code here, to run repeatedly:
  alarm = digitalRead(ALARM_SENSOR);
  Serial.print("Alarm status:");
  Serial.println(alarm);
  delay(1000);
}
**/