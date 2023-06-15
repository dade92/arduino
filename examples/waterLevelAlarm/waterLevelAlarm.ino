// Sensor pins
#define SENSOR_POWER 7
#define SENSOR_PIN A0
#define ALARM 3

int THRESHOLD = 300;

// Value for storing water level
int val = 0;

void setup() {
	// Set D7 as an OUTPUT
	pinMode(SENSOR_POWER, OUTPUT);
  pinMode(ALARM, OUTPUT);
	digitalWrite(SENSOR_POWER, LOW);
	
	Serial.begin(9600);
}

void loop() {
	//get the reading from the function below and print it
	int level = readSensor();
	
	Serial.print("Water level: ");
	Serial.println(level);

  if(level < THRESHOLD) {
    digitalWrite(ALARM, HIGH);
  } else {
    digitalWrite(ALARM, LOW);
  }
	
	delay(1000);
}

//This is a function used to get the reading
int readSensor() {
	digitalWrite(SENSOR_POWER, HIGH);	// Turn the sensor ON
	delay(10);							// wait 10 milliseconds
	val = analogRead(SENSOR_PIN);		// Read the analog value form sensor
	digitalWrite(SENSOR_POWER, LOW);		// Turn the sensor OFF
	return val;							// send current reading
}