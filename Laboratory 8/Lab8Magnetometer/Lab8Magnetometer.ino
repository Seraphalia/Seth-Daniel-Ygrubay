#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// --- Motor Driver Pins (DRV8833) ---
const int MOTOR_A_IN1 = 10;
const int MOTOR_A_IN2 = 3;
const int MOTOR_B_IN1 = 5;
const int MOTOR_B_IN2 = 6;

// --- Constants ---
const int FORWARD_SPEED = 200;
const int TURN_SPEED = 150;

// =================================================================
// <<< CALIBRATION OFFSETS - REPLACE THESE VALUES WITH YOURS! >>>
const float X_OFFSET = 0.0; // Example: (x_max + x_min) / 2
const float Y_OFFSET = 0.0; // Example: (y_max + y_min) / 2
// =================================================================


// --- HMC5883L Sensor ---
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// (The rest of your setup() and loop() functions are the same)
// ...

void setup() {
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);
  Serial.begin(9600);
  if(!mag.begin()) {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
}

// ... loop(), moveForward(), turnRight(), turnLeft(), stopMotors() ...
// (These functions remain unchanged from the previous version)

void loop() {
  Serial.println("Moving Forward");
  moveForward();
  delay(1500);
  stopMotors();
  Serial.println("Stopping");
  delay(1000);
  Serial.println("Turning 90 Degrees Right");
  turnDegrees(90);
  stopMotors();
  Serial.println("Stopping");
  delay(1000);
  Serial.println("Moving Forward");
  moveForward();
  delay(1500);
  stopMotors();
  Serial.println("Stopping");
  delay(1000);
  Serial.println("Turning 90 Degrees Left");
  turnDegrees(-90);
  stopMotors();
  Serial.println("Stopping");
  delay(1000);
}

void moveForward() {
  analogWrite(MOTOR_A_IN1, FORWARD_SPEED);
  analogWrite(MOTOR_A_IN2, 0);
  analogWrite(MOTOR_B_IN1, FORWARD_SPEED);
  analogWrite(MOTOR_B_IN2, 0);
}

void turnRight() {
  analogWrite(MOTOR_A_IN1, TURN_SPEED);
  analogWrite(MOTOR_A_IN2, 0);
  analogWrite(MOTOR_B_IN1, 0);
  analogWrite(MOTOR_B_IN2, TURN_SPEED);
}

void turnLeft() {
  analogWrite(MOTOR_A_IN1, 0);
  analogWrite(MOTOR_A_IN2, TURN_SPEED);
  analogWrite(MOTOR_B_IN1, TURN_SPEED);
  analogWrite(MOTOR_B_IN2, 0);
}

void stopMotors() {
  analogWrite(MOTOR_A_IN1, 0);
  analogWrite(MOTOR_A_IN2, 0);
  analogWrite(MOTOR_B_IN1, 0);
  analogWrite(MOTOR_B_IN2, 0);
}


// --- UPDATED getHeading() FUNCTION ---
float getHeading() {
  sensors_event_t event;
  mag.getEvent(&event);

  // Apply the calibration offsets
  float x = event.magnetic.x - X_OFFSET;
  float y = event.magnetic.y - Y_OFFSET;
  
  // Calculate the heading in degrees
  float heading = atan2(y, x);

  // Magnetic Declination for Catbalogan City, Philippines is approx -0.73 degrees
  float declinationAngle = -0.73;
  heading += declinationAngle * M_PI / 180;
  
  // Convert from radians to degrees
  heading = heading * 180 / M_PI;

  // Normalize to 0-360
  if(heading < 0) {
    heading += 360;
  }
  return heading;
}

// --- UPDATED turnDegrees() FUNCTION ---
void turnDegrees(int degrees) {
  float currentHeading = getHeading();
  float targetHeading = currentHeading + degrees;

  // Normalize target heading to be within 0-360
  targetHeading = fmod(targetHeading + 360, 360);

  Serial.print("Current Heading: "); Serial.print(currentHeading);
  Serial.print(" | Target Heading: "); Serial.println(targetHeading);

  int tolerance = 5; // Degrees of tolerance

  if (degrees > 0) { // Turn right
    turnRight();
  } else { // Turn left
    turnLeft();
  }

  while (true) {
    currentHeading = getHeading();
    float delta = targetHeading - currentHeading;

    // Handle the 0/360 "wraparound"
    if (delta > 180) delta -= 360;
    if (delta < -180) delta += 360;

    if (abs(delta) <= tolerance) {
      break; // We've reached the target
    }
  }
  
  stopMotors();
  Serial.println("Turn complete.");
}