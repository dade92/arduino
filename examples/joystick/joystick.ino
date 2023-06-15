#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_BUTTON 2
#define LED_GREEN 3
#define LED_BLUE 4
#define LED_RED 6
#define LED_WHITE 5
 
void setup() {
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
  for(int i = 3; i <= 6; i++){
    pinMode(i, OUTPUT);
  }
}
 
void loop() {
  int x = analogRead(JOYSTICK_X);
  int y = analogRead(JOYSTICK_Y);
  int button = !digitalRead(JOYSTICK_BUTTON);
 
  digitalWrite(LED_GREEN, x < 400);
  digitalWrite(LED_WHITE, x > 600);
  digitalWrite(LED_BLUE, y < 400);
  digitalWrite(LED_RED, y > 600);
  if(button) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_WHITE, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, HIGH);
    delay(50);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_WHITE, LOW);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);
  }
 
  delay(100);
}
