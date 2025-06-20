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

  Serial.println("Starting full circular path (r ≈ 30cm)...");
  followCircularPath(3925);  // Full 360° circle
  stopMotors();
  Serial.println("Circular path complete.");
}

void loop() {
  // No loop behavior required
}

void followCircularPath(int durationMs) {
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