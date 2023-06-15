#define THRESHOLD 22.50
#define SIGNAL 2

#include<OneWire.h>
#include<DallasTemperature.h>

//IMPORTANT: Connect G to ground, R to 5V and Y to signal input

OneWire oneWire(5);
DallasTemperature temp(&oneWire);

float tc,tf;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  temp.begin();
  pinMode(SIGNAL, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp.requestTemperatures();
  tc = temp.getTempCByIndex(0);

  Serial.print("Temperature C: ");
  Serial.println(tc);

  if(tc < THRESHOLD) {
    digitalWrite(SIGNAL, HIGH);
  } else {
    digitalWrite(SIGNAL, LOW);
  }

  delay(1000);
}
