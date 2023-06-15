#define TRIG 7
#define ECHO 6
#define ALARM 8

long THRESHOLD = 50; //in cm

int distance = 0;
unsigned long lastMeasure = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ALARM, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;

  if(distance < THRESHOLD) {
    digitalWrite(ALARM, HIGH);
    lastMeasure = millis();
  } else if (distance > THRESHOLD && millis() - lastMeasure > 1000){
    digitalWrite(ALARM, LOW);
  }
  Serial.print("Distance: ");
  Serial.println(distance);
}
