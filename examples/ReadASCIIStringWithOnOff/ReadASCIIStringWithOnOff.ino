// pins for the LEDs:
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

const int button = 2;
int status = LOW;
bool circuitOn = false;
int red, green, blue;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  int currentStatus = digitalRead(button);
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if(currentStatus != status && currentStatus == HIGH) {
      lastDebounceTime = millis();
      circuitOn = !circuitOn;
      if(!circuitOn) {
        reset();
      } else {
        lightOn(red, green, blue);
      }
    }
  }
  
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    readSerial();
    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);

      // fade the red, green, and blue legs of the LED:
      if(circuitOn) {
        lightOn(red, green, blue);
      }
      // print the three numbers in one string as hexadecimal:
      Serial.print(red, HEX);
      Serial.print(green, HEX);
      Serial.println(blue, HEX);
    }
  }
  status = currentStatus;
}

void lightOn(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void reset() {
  lightOn(0,0,0);
}

void readSerial() {
  red = Serial.parseInt();
  green = Serial.parseInt();
  blue = Serial.parseInt();
}
