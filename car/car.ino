#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>

#define VERY_SHORT_TIME 250
#define SHORT_TIME 500
#define LONG_TIME 800
#define VERY_LONG_TIME 1200
#define LEFT_FORWARD 4   //  white wire
#define LEFT_BACKWARD 11  // blue wire
#define RIGHT_FORWARD 13  // yellow wire
#define RIGHT_BACKWARD 12 // green wire
#define TRIG 3            // orange wire
#define ECHO 2            // green wire
#define EN_RIGHT 6
#define EN_LEFT 5
#define SERVO 10
#define LOOK_FORWARD 105
#define LOOK_RIGHT 30
#define LOOK_LEFT 180
#define MAX_SPEED 255

enum Turn {
  LEFT, RIGHT
};

int THRESHOLD = 20;
int distance = 1000;
int rightMotorSpeed = 255;
int leftMotorSpeed = 255;
int watch = LOOK_FORWARD;
Turn lastTurn = LEFT;
float angle = 0, targetAngle, gyroZ = 0;
Servo servo;
MPU6050 mpu6050(Wire);

/**
  IMPORTANT: 
    Left motor is linked at the bottom ("supply side")
    Right motor is linked on top ("non supply side")
    Both motors are linked with pins poiting outside

    The gyroscope MPU6050 must be mounted with pins oriented forward
    Wiring: SDA A4, SCL A5
**/

void setup() {
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(EN_RIGHT, OUTPUT);
  pinMode(EN_LEFT, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  servo.attach(SERVO);

  // Waiting the gyroscope setup
  // Wire.begin();
  // mpu6050.begin();
  // mpu6050.calcGyroOffsets(true);
  servo.write(watch);
  // targetAngle = measureAngle();
  // Serial.begin(9600);
}

void loop() {
  distance = measureDistance();
  // angle = measureAngle();
  // analogWrite(EN_RIGHT, rightMotorSpeed);
  // analogWrite(EN_LEFT, leftMotorSpeed);

  // Serial.print("Distance:");Serial.println(distance);
  // Serial.print("Angle:");Serial.println(angle);

  if(distance > THRESHOLD) {
    forward();
  } else {
    stop(SHORT_TIME);
    rotateTillNoObstacle();
  }
}

void rotateTillNoObstacle() {
  smoothlyLookLeft();
  int distanceLeft = measureDistance();
  smoothlyLookRight();
  int distanceRight = measureDistance();
  smoothlyLookForward();

  if(distanceLeft > distanceRight) {
    left();
  } else {
    right();
  }
  // targetAngle = measureAngle();
}

bool obstacleTooClose() {
  distance = measureDistance();
  return distance < THRESHOLD;
}

void chooseRandomlyWhereToGo() {
  random(0,2) == 0 ? left(SHORT_TIME) : right(SHORT_TIME);
}

int measureDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  int duration = pulseIn(ECHO, HIGH);
  return duration * 0.034 / 2;
}

// float measureAngularSpeed() {
//   float angSpeed = mpu6050.getGyroZ();

//   return angSpeed;
// }

float measureAngle() {
  mpu6050.update();
  return mpu6050.getAngleZ();
}

void forward() {
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
  // if(angle < targetAngle - 5) {
  //   // it's turning RIGHT
  //   rightMotorSpeed++;
  //   leftMotorSpeed--;
  // } else if(angle > targetAngle + 5) {
  //   //it's turning LEFT
  //   rightMotorSpeed--;
  //   leftMotorSpeed++;
  // }
  // rightMotorSpeed = constrain(rightMotorSpeed, 0, MAX_SPEED);
  // leftMotorSpeed = constrain(leftMotorSpeed, 0, MAX_SPEED);
}

void backward(int time) {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH);
  delay(time);
}

void left(int time) {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
  lastTurn = LEFT;
  delay(time);
}

void left90Degrees() {
  float actualAngle = measureAngle();
  while(abs(angle - actualAngle) < 90) {
    digitalWrite(LEFT_FORWARD, LOW);
    digitalWrite(LEFT_BACKWARD, LOW);
    digitalWrite(RIGHT_FORWARD, HIGH);
    digitalWrite(RIGHT_BACKWARD, LOW);
    actualAngle = measureAngle();
    delay(10);
  }
  lastTurn = LEFT;
}

void right(int time) {
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  lastTurn = RIGHT;
  delay(time);
}

void right90Degrees() {
  float actualAngle = measureAngle();
  while(abs(angle - actualAngle) < 90) {
    digitalWrite(LEFT_FORWARD, HIGH);
    digitalWrite(LEFT_BACKWARD, LOW);
    digitalWrite(RIGHT_FORWARD, LOW);
    digitalWrite(RIGHT_BACKWARD, LOW);
    actualAngle = measureAngle();
    delay(10);
  }
  lastTurn = RIGHT;
}

void stop(int time) {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  rightMotorSpeed = 0;
  leftMotorSpeed = 0;
}

void smoothlyLookRight() {
  for(; watch>=LOOK_RIGHT; watch--) {
    servo.write(watch);
    delay(10);
  }
}

void smoothlyLookLeft() {
  for(; watch<LOOK_LEFT; watch++) {
    servo.write(watch);
    delay(10);
  }
}

void smoothlyLookForward() {
  if(watch < LOOK_FORWARD) {
    for(; watch<LOOK_FORWARD; watch++) {
      servo.write(watch);
      delay(10);
    }
  } else {
    for(; watch>=LOOK_FORWARD; watch--) {
      servo.write(watch);
      delay(10);
    }
  }
}

// void testMovement() {
//   delay(5000);
//   forward();
//   delay(1000);
//   stop();
//   delay(1000);
//   backward();
//   delay(1000);
//   stop();
//   delay(1000);
//   left(50);
//   delay(1000);
//   stop();
//   delay(1000);
//   right(50);
//   delay(1000);
//   stop();
//   delay(100000);
// }