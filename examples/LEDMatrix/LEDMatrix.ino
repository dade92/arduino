#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const uint32_t littleHeart[] = {
    0x1B,
    0x2481100,
    0xA0040000
};

const uint32_t bigHeart[] = {
    0x3B86A,
    0xC64C3181,
    0xB0040000
};

void setup() {
  Serial.begin(115200);
  matrix.begin();
}
  
void loop() {
  matrix.loadFrame(littleHeart);
  delay(500);

  matrix.loadFrame(bigHeart);
  delay(500);
}