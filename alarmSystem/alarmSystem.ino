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

#define ALARM_SENSOR 2
#define ALARM 13
#define ALARM_DURATION 1000
#define KEY_DURATION 300
#define PASSWORD "1234"

uint8_t alarm;
bool active = false;
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

void setup() {
  pinMode(ALARM_SENSOR, INPUT);
  pinMode(ALARM, OUTPUT);
  delay(3000);  //For PIR sensor to set up
  Serial.begin(9600);
}

void loop() {
  timestamp = millis();
  alarm = digitalRead(ALARM_SENSOR);
  key = kpd.getKey();

  if(key) {
    Serial.println(key);
    pin = pin + key;
    tone(ALARM, 440, KEY_DURATION);
    delay(200);
  }

  if(pin.equals(PASSWORD)) {
    active = !active;
    Serial.println("Password OK");
    pin = "";
  } else {
      if(pin.length() == 4) {
        pin = "";
        tone(ALARM, 440, KEY_DURATION);
        delay(200);
        tone(ALARM, 440, KEY_DURATION);
        delay(200);
    }
  }

  if(active && alarm == HIGH) {
    lastAlarm = timestamp;
    tone(ALARM, 440, ALARM_DURATION);
  } else {
    noTone(ALARM);
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