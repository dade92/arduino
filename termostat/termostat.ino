/**
  HUM SENSOR
    S pin to pin 7
    middle pin to Vcc
    right pin to ground

  LCD
    Vss to ground
    Vdd to Vcc
    V0 to ground with 2KH resistor
    Rs to pin 8
    Rw to ground
    E to pin 9
    d4 d5 d6 d7 to 10 11 12 13
    A to Vcc
    K to ground
**/

#include <LiquidCrystal.h>
#include <SimpleDHT.h>

#define DHTPIN 7

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SimpleDHT11 dht11;

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  byte temp = 0;
  byte umid = 0;
  dht11.read(DHTPIN, &temp, &umid, NULL);
  delay(1000);

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("T=");
  lcd.setCursor(2,0);
  lcd.print((int)temp);
  lcd.setCursor(4,0);
  lcd.print("*C");
  lcd.setCursor(0,1);
  lcd.print("H=");
  lcd.setCursor(2,1);
  lcd.print((int)umid);
  lcd.setCursor(4,1);
  lcd.print("%");
}