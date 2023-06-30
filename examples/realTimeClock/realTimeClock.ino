#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);

  if(!rtc.begin()) {
    Serial.println("Error!");
    return;
  }
  
  if(!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

String days[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

void loop() {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(days[now.dayOfTheWeek()-1]);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);

  Serial.println();

  delay(10000);
}