int latchPin = 5;      // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 6;      // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 4;       // Data pin of 74HC595 is connected to Digital pin 4

byte leds = 0;         // Variable to hold the pattern of which LEDs are currently turned on or off

void setup() {
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

/*
 * loop() - this function runs over and over again
 */
void loop() {
  //EXAMPLE 1
  // leds = 0;        // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  // updateShiftRegister();
  // delay(500);
  // for (int i = 0; i < 8; i++)        // Turn all the LEDs ON one by one.
  // {
  //   bitSet(leds, i);                // Set the bit that controls that LED in the variable 'leds'
  //   updateShiftRegister();
  //   delay(500);
  // }

  // byte n = 0x01;

  // for(int i = 0;i<8;i++) {
  //   digitalWrite(latchPin, LOW);
  //   shiftOut(dataPin, clockPin, LSBFIRST, n);
  //   digitalWrite(latchPin, HIGH); 
  //   n = n << 1;
  //   delay(1000);
  // }

  // EXAMPLE 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
  digitalWrite(latchPin, HIGH); 
  delay(1000);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0x01);
  digitalWrite(latchPin, HIGH); 
  delay(1000);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0x02);
  digitalWrite(latchPin, HIGH); 
  delay(1000);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0x04);
  digitalWrite(latchPin, HIGH); 
  delay(1000);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0x08);
  digitalWrite(latchPin, HIGH); 
  delay(1000);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0x0F);
  digitalWrite(latchPin, HIGH); 
  delay(1000);

  //EXAMPLE 3
  // digitalWrite(latchPin, LOW);
  // shiftOut(dataPin, clockPin, MSBFIRST, 0x03);
  // digitalWrite(latchPin, HIGH); 
  // delay(1000);
  // digitalWrite(clockPin, HIGH);
  // digitalWrite(clockPin, LOW);
  // digitalWrite(latchPin, LOW);
  // digitalWrite(latchPin, HIGH);
  // delay(2000);
}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}