int photoResistor = A0;
int led = 2;
int THRESHOLD = 900;
int ledStatus = LOW;
unsigned long lastChange = 0;
int min = 1023;
int max = 0;

void setup() {
  pinMode(photoResistor, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  digitalWrite(led, LOW);
}

void loop() {
  long light = analogRead(photoResistor);

  if(light > THRESHOLD && ledStatus == LOW && (millis() - lastChange > 200)) {
    ledStatus = HIGH;
    digitalWrite(led, ledStatus);
    lastChange = millis();
  } else if (light <= THRESHOLD && ledStatus == HIGH && (millis() - lastChange > 200)) {
    ledStatus = LOW;
    digitalWrite(led, ledStatus);
    lastChange = millis();
  }

  Serial.println(light);
  delay(500);
}
