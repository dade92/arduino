#include<Servo.h>

#define SERVO 9

Servo myservo; 

int pos = 0;    // variable to store the servo position
int current = 105;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(SERVO);
  myservo.write(current);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(5);                       // waits 15ms for the servo to reach the position
  // }
  // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }

  

  // myservo.write(105);
  // smoothlyLookLeft(105);
  // smoothlyLookRight(160);

  // delay(2000);
  // myservo.write(160);
  // delay(2000);
  smoothlyLookRight();
  delay(2000);
  smoothlyLookLeft();
  delay(2000);
  smoothlyLookForward();
  delay(5000);

}

void smoothlyLookRight() {
  for(; current>=35; current--) {
    myservo.write(current);
    delay(10);
  }
}

void smoothlyLookLeft() {
  for(; current<170; current++) {
    myservo.write(current);
    delay(10);
  }
}

void smoothlyLookForward() {
  if(current < 105) {
    for(; current<105; current++) {
      myservo.write(current);
      delay(10);
    }
  } else {
    for(; current>=105; current--) {
      myservo.write(current);
      delay(10);
    }
  }
}


