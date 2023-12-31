/**
  HUM SENSOR
    S to to pin 7
    middle pin to Vcc
    right pin to ground
  LCD
    Vss not connected (don't know exactly why)
    Vdd to Vcc
    V0 to ground with 2KH resistor
    Rs to pin 8
    Rw to ground
    E to pin 9
    d4 d5 d6 d7 to 10 11 12 13
    A to pin 6
    K to ground
  REAL TIME CLOCK
    SDA and SCL to SDA and SCL respectively
    Vcc to Vcc
    GND to ground
    Other pins are useless
  BUTTON
    S to pin 2
    GND to ground
    Vcc to Vcc
**/
#include <LiquidCrystal.h>
#include <SimpleDHT.h>
#include <Wire.h>
#include <RTClib.h>

#define DHTPIN 7
#define LIGHT 6
#define BUTTON 2
#define INPUT_THRESHOLD 250
#define MAX_LIGHT_ON 5000
#define MEASURE_TIME 1000

SimpleDHT11 dht11;
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long lastMeasureTime = 0, timestamp, lastChange;
byte temp, umid;
RTC_DS1307 rtc;
uint8_t light = LOW;
uint8_t button = HIGH;

void printOnLCD(int, int);
void changeLight();

void setup() {
  lcd.begin(16, 2);
  if(!rtc.begin()) {
    return;
  }

  if(!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  pinMode(LIGHT, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  timestamp = millis();

  if(light == HIGH && (timestamp - lastChange > MAX_LIGHT_ON)) {
    changeLight();
  }

  //Update LCD
  if(timestamp - lastMeasureTime > MEASURE_TIME) {
    dht11.read(DHTPIN, &temp, &umid, NULL);
    DateTime now = rtc.now();
    printOnLCD((int) temp, (int)umid, now);
    lastMeasureTime = timestamp;
  }

  // light up the screen on button pressed
  if(timestamp - lastChange >= INPUT_THRESHOLD) {
    button = digitalRead(BUTTON);
    if(button == LOW) {
      changeLight();
      lastChange = timestamp;
    }
  }
}

void printOnLCD(int t, int h, DateTime now) {
  lcd.setCursor(0,0);
  lcd.print("T=");
  lcd.setCursor(2,0);
  lcd.print(t);
  lcd.setCursor(4,0);
  lcd.print("*C");
  lcd.setCursor(0,1);
  lcd.print("H=");
  lcd.setCursor(2,1);
  lcd.print(h);
  lcd.setCursor(4,1);
  lcd.print("%");

  int hour = now.twelveHour();
  int minute = now.minute();
  int cursor = 7;

  lcd.setCursor(cursor, 0);
  if(hour < 10) {
    lcd.print(hour);
    cursor++;
  } else {
    lcd.print(hour);
    cursor+=2;
  }
  lcd.setCursor(cursor, 0);
  lcd.print(":");
  cursor++;
  lcd.setCursor(cursor, 0);
  if(minute < 10) {
    lcd.print("0");
    cursor++;
    lcd.print(minute);
    cursor++;
  } else {
    lcd.print(minute);
    cursor+=2;
  }
  lcd.setCursor(cursor, 0);
  if(now.isPM()) {
    lcd.print("PM");
  } else {
    lcd.print("AM");
  }
}

void changeLight() {
  if(light == LOW) {
    light = HIGH;
  } else {
    light = LOW;
  }
  digitalWrite(LIGHT, light);
}