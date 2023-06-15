// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4

#define LED 5

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;
const int fadeAmount = 10;

void setup() {
        
	// Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
  pinMode(LED, OUTPUT);
  pinMode(SW, INPUT_PULLUP);

	// Setup Serial Monitor
	Serial.begin(9600);

	// Read the initial state of CLK
	lastStateCLK = digitalRead(CLK);
	
	// Call updateEncoder() when any high/low changed seen
	// on interrupt 0 (pin 2), or interrupt 1 (pin 3)
	attachInterrupt(digitalPinToInterrupt(CLK), updateEncoder, CHANGE);
	attachInterrupt(digitalPinToInterrupt(DT), updateEncoder, CHANGE);
}

void loop() {
	// Read the button state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			Serial.println("Button pressed!");
		}

		// Remember last button press event
		lastButtonPress = millis();
	}

  analogWrite(LED, counter);
	// Put in a slight delay to help debounce the reading
	delay(1);
}

void updateEncoder() {
	// Read the current state of CLK
	currentStateCLK = digitalRead(CLK);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
			counter -= fadeAmount;
			currentDir ="CCW";
		} else {
			// Encoder is rotating CW so increment
			counter += fadeAmount;
			currentDir ="CW";
		}

    counter = constrain(counter, 0, 255);

		Serial.print("Direction: ");
		Serial.print(currentDir);
		Serial.print(" | Counter: ");
		Serial.println(counter);
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;
}