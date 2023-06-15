#define PIR 7
#define LED 8
#define ON_TIME 5000

unsigned long lastMovement = 0;

void setup() {
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  //This using the PIR sensor in "repeatable" mode
  int movement = digitalRead(PIR);

  if(movement == HIGH) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}