#include <EEPROM.h>

String pwd = "ciao sono bello";

void setup() {
  Serial.begin(9600);

  // put your setup code here, to run once:
  for(int i = 0; i<pwd.length();i++) {
    Serial.println("Writing char " + pwd[i]);
    EEPROM.write(i, pwd[i]);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
