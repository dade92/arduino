#define BUTTON 6

int lastValue = LOW;
unsigned long lastEvent = 0;
bool switchButton = false; 

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(BUTTON);

  if(value == HIGH && millis() - lastEvent > 300) {
    Serial.println("Button is being pressed");
    switchButton = !switchButton;
    lastEvent = millis();
    if(switchButton) {
      Serial.println("Feature ON");
    } else {
      Serial.println("Feature OFF");
    }
  }

  lastValue = value;
}
