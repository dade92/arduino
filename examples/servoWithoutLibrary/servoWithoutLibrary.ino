#define SERVO 3

int posizione;
int direzione;
int step_motore_indietro = 1;
int step_motore_avanti = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(SERVO, OUTPUT);
  posizione = 100;
  direzione = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  // analogWrite(SERVO, posizione);

  // delay(10);

  // if(direzione == 1) {
  //   posizione += step_motore_avanti;
  //   if(posizione > 255) {
  //     direzione = 0;
  //   }
  // } else {
  //   posizione -= step_motore_indietro;
  //   if(posizione < 10) {
  //     direzione = 1;
  //   }
  // }

  // delay
  analogWrite(SERVO, 70);

  delay(1000);

  analogWrite(SERVO, 200);

  delay(1000);

  analogWrite(SERVO, 250);

  delay(1000);
}
