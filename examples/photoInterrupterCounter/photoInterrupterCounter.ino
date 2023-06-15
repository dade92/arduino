int PHOTO = 2;
int ALARM = 5;
int tilt = 0;
int counter = 0;
bool lightOn = false;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  // put your setup code here, to run once:
  pinMode(PHOTO, INPUT);
  pinMode(ALARM, OUTPUT);
}

void loop() {

  if(millis() - lastDebounceTime > debounceDelay) {
    int value = digitalRead(PHOTO);

    digitalWrite(ALARM, value);

    lastDebounceTime = millis();
  }
}