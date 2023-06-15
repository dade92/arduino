// IMPORTANT: does not work don't know why probably sensor needs better calibration

int ledPin = 3;      // LED pin on arduino
int detectorPin = 5;  // obstacle avoidance sensor interface
int val;              // variable to store result
int enablePin = 4;  // sensor enable interface (EN)
void setup()
{
  pinMode(ledPin, OUTPUT);  // Define LED as output interface
  pinMode(detectorPin, INPUT);  // Define obstacle avoidance sensor as input interface
  
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);  // Enable sensor

  Serial.begin(9600);
}
void loop()
{
  val = digitalRead(detectorPin); // Read value from sensor
  Serial.println(val);
  if(val == LOW) // When the sensor detects an obstacle, the LED on the Arduino lights up
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }

}