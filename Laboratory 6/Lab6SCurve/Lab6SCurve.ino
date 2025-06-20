#include <Servo.h>

// Motor Pins
#define IN1 6
#define IN2 9
#define IN3 5
#define IN4 3

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  delay(1000);

  Serial.println("Starting S-curve maneuver (2 sinusoidal arcs)...");

  // First arc: Turn left (left motor slower)
  Serial.println("First arc: turning left...");
  followArcLeft(1960); // half of 3925 ms

  // Second arc: Turn right (right motor slower)
  Serial.println("Second arc: turning right...");
  followArcRight(1960); // half of 3925 ms

  stopMotors();
  Serial.println("S-curve maneuver complete.");
}

void loop() {
  // No loop behavior required
}

void followArcLeft(int durationMs) {
  analogWrite(IN1, 128);  // Left motor at ~50%
  digitalWrite(IN2, LOW);

  analogWrite(IN3, 255);  // Right motor at 100%
  digitalWrite(IN4, LOW);

  delay(durationMs);
}

void followArcRight(int durationMs) {
  analogWrite(IN1, 255);  // Left motor at 100%
  digitalWrite(IN2, LOW);

  analogWrite(IN3, 128);  // Right motor at ~50%
  digitalWrite(IN4, LOW);

  delay(durationMs);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
