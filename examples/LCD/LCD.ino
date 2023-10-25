// Use 2Kh resistor to see something good on the screen!

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

int c = 0;

void loop() {
  lcd.setCursor(0, 1);  
  lcd.print(c);
  delay(1000);
  c++;
}