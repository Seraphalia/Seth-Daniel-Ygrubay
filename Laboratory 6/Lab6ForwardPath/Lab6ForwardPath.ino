#include <Servo.h>

// Motor Pins
#define IN1 6
#define IN2 9
#define IN3 5
#define IN4 3

// Ultrasonic Pins
#define TRIG A4
#define ECHO A5

// Servo Pin
#define SERVO_PIN 10
Servo scanServo;

bool pathCompleted = false;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(90); // Forward

  Serial.begin(9600);
  delay(1000);
}

void loop() {
  if (pathCompleted) {
    stopMotors();
    return;
  }

  bool obstacleDetected = isObstacleAhead();

  if (!obstacleDetected) {
    Serial.println("Path clear. Driving forward 1 meter.");
    moveForwardDistance(1.0);
    pathCompleted = true;
  } else {
    Serial.println("Obstacle detected. Planning detour...");
    stopMotors();

    int leftDist = readDistanceAtAngle(150);
    delay(300);
    int rightDist = readDistanceAtAngle(30);
    delay(300);

    Serial.print("Left distance: ");
    Serial.println(leftDist);
    Serial.print("Right distance: ");
    Serial.println(rightDist);

    if (leftDist > rightDist) {
      Serial.println("Turning left to avoid obstacle...");
      turnLeft();
      moveForwardDistance(0.5);
      turnRight();
    } else {
      Serial.println("Turning right to avoid obstacle...");
      turnRight();
      moveForwardDistance(0.5);
      turnLeft();
    }

    Serial.println("Returning to path. Moving final 0.5 meters...");
    moveForwardDistance(0.5);
    pathCompleted = true;
  }
}

// === Utility Functions ===

bool isObstacleAhead() {
  int count = 0;
  for (int i = 0; i < 3; i++) {
    int d = readDistanceAtAngle(90);
    if (d < 35 && d > 0) count++;
    delay(100);
  }
  return (count >= 2);
}

int readDistanceAtAngle(int angle) {
  scanServo.write(angle);
  delay(300);

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return 999;
  int distance = duration * 0.034 / 2;
  return distance;
}

void moveForwardDistance(float distanceMeters) {
  float timeToMove = (distanceMeters / 0.48) * 1000; // ms
  moveForward();
  delay((int)timeToMove);
  stopMotors();
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(650); // 80-degree turn
  stopMotors();
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(730); // 90-degree turn
  stopMotors();
}
