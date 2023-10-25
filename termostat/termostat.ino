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
    A to Vcc    (these last two are for retro light)
    K to ground
**/
#include <LiquidCrystal.h>
#include <SimpleDHT.h>

#define DHTPIN 7

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SimpleDHT11 dht11;

void printOnLCD(int, int);
long lastMeasureTime = 0, timestamp;
byte temp, umid;

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  timestamp = millis();

  if(timestamp - lastMeasureTime > 1000) {
    dht11.read(DHTPIN, &temp, &umid, NULL);
    printOnLCD((int) temp, (int)umid);
    lastMeasureTime = timestamp;
  }
}

void printOnLCD(int t, int h) {
  lcd.setCursor(0,0);
  lcd.print("T=");
  lcd.setCursor(2,0);
  lcd.print((int)t);
  lcd.setCursor(4,0);
  lcd.print("*C");
  lcd.setCursor(0,1);
  lcd.print("H=");
  lcd.setCursor(2,1);
  lcd.print((int)h);
  lcd.setCursor(4,1);
  lcd.print("%");
}