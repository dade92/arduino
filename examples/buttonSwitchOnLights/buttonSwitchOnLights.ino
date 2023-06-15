int button = 4;
int led = 2;
int buttonStatus = LOW;
bool ledOn = false;
unsigned long lastReadTime = 0;
int THRESHOLD = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int currentStatus = digitalRead(button);

  if(currentStatus != buttonStatus && millis() - lastReadTime > THRESHOLD) {
    if(buttonStatus == HIGH) {
      ledOn = !ledOn;
      if(ledOn) {
        digitalWrite(led, HIGH);
      } else {
        digitalWrite(led, LOW);
      }
    }

    buttonStatus = currentStatus;
    lastReadTime = millis();
  }

}
