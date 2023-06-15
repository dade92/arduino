int TILT_BALL = 2;
int alarmOutput = 5;
int tilt = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  // put your setup code here, to run once:
  pinMode(TILT_BALL, INPUT);
  pinMode(alarmOutput, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  tilt = digitalRead(TILT_BALL);
  // put your main code here, to run repeatedly:
  if(millis() - lastDebounceTime > debounceDelay) {
    if(tilt) {
      digitalWrite(alarmOutput, HIGH);
    } else {
      digitalWrite(alarmOutput, LOW);
    }
    lastDebounceTime = millis();
  }
}
