#include <Servo.h>

// Motor Pins
#define IN1 6
#define IN2 9
#define IN3 5
#define IN4 3

// Ultrasonic Pins
#define TRIG A4
#define ECHO A5

// Servo
#define SERVO_PIN 10
Servo scanServo;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(90); // Face forward

  Serial.begin(9600);
}

void loop() {
  int forwardDist = readDistanceAtAngle(90);
  Serial.print("Forward Distance: ");
  Serial.println(forwardDist);

  if (forwardDist > 25 && forwardDist < 999) { 
    moveForward();
  } else if (forwardDist <= 25 && forwardDist > 0) {
    stopMotors();
    delay(300);

    int leftDist = readDistanceAtAngle(150);
    delay(300);
    int rightDist = readDistanceAtAngle(30);
    delay(300);

    Serial.print("Left Distance: ");
    Serial.println(leftDist);
    Serial.print("Right Distance: ");
    Serial.println(rightDist);


    if (leftDist < rightDist) {
      turnLeft();  // Turn left if there's more space on the left
    } else {
      turnRight(); // Turn right if there's more space on the right
    }

    delay(300);
    forwardDist = readDistanceAtAngle(90); // Recheck after turn
    if (forwardDist > 25 && forwardDist < 999) {
      moveForward();
    }
  } else {
    // If no valid reading, stop to avoid crashing
    stopMotors();
  }

  delay(500);
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
  delay(10);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(1000);
  stopMotors();
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(1000);
  stopMotors();
}