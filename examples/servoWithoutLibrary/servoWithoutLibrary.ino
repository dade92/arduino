#define SERVO 3

int posizione;
int direzione;
int step_motore_indietro = 5;
int step_motore_avanti = 5;

void setup() {
  Serial.begin(9600);
  pinMode(SERVO, OUTPUT);
  posizione = 100;
  direzione = 1;
}

void loop() {
  // turnServo();

  // Set a specific posiiton:
  setPrecisePosition();
}

void turnServo() {
  analogWrite(SERVO, posizione);
  Serial.println(posizione);

  delay(50);

  if(direzione == 1) {
    posizione += step_motore_avanti;
    if(posizione > 245) {
      direzione = 0;
    }
  } else {
    posizione -= step_motore_indietro;
    if(posizione < 10) {
      direzione = 1;
    }
  }
}

void setPrecisePosition() {
  String setPos = Serial.readString();

  if(setPos.toInt() != 0) {
    Serial.println(setPos);
    analogWrite(SERVO, setPos.toInt());
  }
}
