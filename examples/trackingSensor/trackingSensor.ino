#define SENSOR 5
#define LED 3

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(SENSOR);

  if(value == HIGH) {
    digitalWrite(LED, LOW);
    Serial.println("I'm on black space");
  } else {
    Serial.println("I'm on white space");
    digitalWrite(LED, HIGH);
  }
  delay(500);
}
