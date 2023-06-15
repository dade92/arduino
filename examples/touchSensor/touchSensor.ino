#define SENSOR 8 
#define ALARM 9

int touch = LOW;
unsigned long lastMeasure = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR, INPUT);
  pinMode(ALARM, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  touch = digitalRead(SENSOR);

  if(touch == HIGH) {
    digitalWrite(ALARM, HIGH);
    lastMeasure = millis();
  } else if(touch == LOW && millis() - lastMeasure > 1000) {
    digitalWrite(ALARM, LOW);
  }
}
