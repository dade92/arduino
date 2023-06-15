#define ALARM 13
#define SHOCK 2

void setup() {
  // put your setup code here, to run once:
  pinMode(ALARM, OUTPUT);
  pinMode(SHOCK, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(SHOCK);
  if(value == LOW) {
    digitalWrite(ALARM, HIGH);
    delay(1000);
  } else {
    digitalWrite(ALARM, LOW);
  }

}
