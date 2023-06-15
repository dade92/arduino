int led = 9;
int tap = 4;
int button = 2;
unsigned long lastTime = 0;
unsigned long lastTap = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(tap, INPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = digitalRead(tap);
  int buttonValue = digitalRead(button);

  if(!buttonValue && millis() - lastTime > 200) {
    Serial.println("Button pressed");
    lastTime = millis();
  }

  if(!value && millis() - lastTap > 200) {
    Serial.println("I've been tapped");
    lastTap = millis();
  }
}
