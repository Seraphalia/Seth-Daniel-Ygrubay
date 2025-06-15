/*
  Arduino Nano Line Avoidance Sketch Using DRV8833 Motor Driver
  
  Setup:
    - Left Motor is controlled via MOTOR_A (pins 10 and 3).
    - Right Motor is controlled via MOTOR_B (pins 5 and 6).
    - Left IR sensor is connected to A0 and Right IR sensor to A1.
  
  Sensor calibration:
    - White surface: readings around 20 or lower.
    - Black line: readings around 600 or higher.
  
  Behavior:
    - Both sensors safely read white (≤20): Move forward at full speed.
    - Left sensor reads black (≥600) while right sensor reads white (≤20): Pivot right.
    - Right sensor reads black (≥600) while left sensor reads white (≤20): Pivot left.
    - Both sensors detect black (≥600): Stop.
  
  Note: For sensor readings between these ranges, the sketch defaults to forward motion.
*/

//
// --- Motor Driver Pins (DRV8833) ---
const int MOTOR_A_IN1 = 10; // Left Motor forward
const int MOTOR_A_IN2 = 3;  // Left Motor backward (unused in this sketch)
const int MOTOR_B_IN1 = 5;  // Right Motor forward
const int MOTOR_B_IN2 = 6;  // Right Motor backward (unused)

// --- Constants ---
const int FORWARD_SPEED_LEFT  = 255;  // Full speed for left motor
const int FORWARD_SPEED_RIGHT = 255;  // Full speed for right motor

// Sensor thresholds based on your calibration:
const int whiteThreshold = 20;   // Readings ≤20 indicate white (safe).
const int blackThreshold = 600;  // Readings ≥600 indicate black (line).

//
// --- Setup Function ---
void setup() {
  // Set motor driver pins as outputs.
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);

  // Initialize serial communication for debugging.
  Serial.begin(9600);
}

//
// --- Main Loop ---
void loop() {
  // Read the IR sensor values.
  int leftSensor  = analogRead(A0);
  int rightSensor = analogRead(A1);

  // Debug output to monitor sensor values.
  Serial.print("Left Sensor: ");
  Serial.print(leftSensor);
  Serial.print(" | Right Sensor: ");
  Serial.println(rightSensor);

  // Decision logic based on calibrated sensor values:
  if (leftSensor <= whiteThreshold && rightSensor <= whiteThreshold) {
    // Both sensors are clearly on white: move forward.
    moveForward();
    Serial.println("Action: Moving Forward");
  }
  else if (leftSensor >= blackThreshold && rightSensor <= whiteThreshold) {
    // Left sensor detects black, right sensor is safe: pivot right.
    pivotRight();
    Serial.println("Action: Pivoting Right (avoiding left black line)");
  }
  else if (rightSensor >= blackThreshold && leftSensor <= whiteThreshold) {
    // Right sensor detects black, left sensor is safe: pivot left.
    pivotLeft();
    Serial.println("Action: Pivoting Left (avoiding right black line)");
  }
  else if (leftSensor >= blackThreshold && rightSensor >= blackThreshold) {
    // Both sensors detect black: stop.
    stopMotors();
    Serial.println("Action: Stopping (both sensors detect black)");
  }
  else {
    // If readings are ambiguous (between white and black thresholds), default to forward.
    moveForward();
    Serial.println("Action: Ambiguous reading, moving forward");
  }

  delay(50);  // Brief delay for sensor stabilization.
}

//
// --- Helper Functions ---
void moveForward() {
  // Drive both motors forward at full speed.
  analogWrite(MOTOR_A_IN1, FORWARD_SPEED_LEFT);
  analogWrite(MOTOR_A_IN2, 0);
  analogWrite(MOTOR_B_IN1, FORWARD_SPEED_RIGHT);
  analogWrite(MOTOR_B_IN2, 0);
}

void pivotLeft() {
  // To pivot left: run left motor forward while stopping right motor.
  analogWrite(MOTOR_A_IN1, FORWARD_SPEED_LEFT);
  analogWrite(MOTOR_A_IN2, 0);
  analogWrite(MOTOR_B_IN1, 0);
  analogWrite(MOTOR_B_IN2, 0);
}

void pivotRight() {
  // To pivot right: run right motor forward while stopping left motor.
  analogWrite(MOTOR_A_IN1, 0);
  analogWrite(MOTOR_A_IN2, 0);
  analogWrite(MOTOR_B_IN1, FORWARD_SPEED_RIGHT);
  analogWrite(MOTOR_B_IN2, 0);
}

void stopMotors() {
  // Stop both motors.
  analogWrite(MOTOR_A_IN1, 0);
  analogWrite(MOTOR_A_IN2, 0);
  analogWrite(MOTOR_B_IN1, 0);
  analogWrite(MOTOR_B_IN2, 0);
}