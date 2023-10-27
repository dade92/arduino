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

#define ALARM_SENSOR 2
#define ALARM 13
#define ALARM_DURATION 1000

uint8_t alarm;
bool active = true;
long timestamp, lastAlarm;


void setup() {
  pinMode(ALARM_SENSOR, INPUT);
  pinMode(ALARM, OUTPUT);
  delay(3000);  //For PIR sensor to set up
}

void loop() {
  timestamp = millis();
  alarm = digitalRead(ALARM_SENSOR);

  if(active && alarm == HIGH) {
    lastAlarm = timestamp;
    tone(ALARM, 440 ,ALARM_DURATION);
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