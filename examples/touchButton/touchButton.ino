#include <CapacitiveSensor.h>

CapacitiveSensor touch = CapacitiveSensor(10, 11);
unsigned long value = 0;
const int THRESHOLD = 500;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = touch.capacitiveSensor(30);
  Serial.println(value);
  if(value > THRESHOLD) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(10);
}
