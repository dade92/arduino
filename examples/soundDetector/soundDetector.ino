#define SOUND_DIGITAL 2
#define LED 3
#define SOUND_ANALOG A0

bool switchOn = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(SOUND_DIGITAL, INPUT);
  pinMode(SOUND_ANALOG, INPUT);

  attachInterrupt(digitalPinToInterrupt(SOUND_DIGITAL), lightOn, RISING);
}

void lightOn() {
  switchOn = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(switchOn) {
    digitalWrite(LED, HIGH);
    delay(1000);
    switchOn = false;
  } else {
    digitalWrite(LED, LOW);
  }

  delay(50);
}
