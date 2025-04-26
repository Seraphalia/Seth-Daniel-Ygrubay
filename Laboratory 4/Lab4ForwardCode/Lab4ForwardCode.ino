// Motor control pins
#define IN1 6   // Motor 1 forward pin
#define IN2 9   // Motor 1 backward pin
#define IN3 5   // Motor 2 forward pin
#define IN4 3   // Motor 2 backward pin

// Wheel parameters
const float averageSpeed = 0.46;  // m/s (average speed)

// Time to move 1 meter (calculated from average speed)
const float distanceToMove = 1.0; // meters
unsigned long moveTime = (distanceToMove / averageSpeed) * 1000; // Time in milliseconds

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Start the motors to move forward 1 meter
  moveForward(1.0); // Move forward by 1 meter
}

void loop() {
  // No need to do anything in loop
}

// Function to move both motors forward by a given distance (in meters)
void moveForward(float distance) {
  // Time to move (based on average speed)
  unsigned long moveDuration = (distance / averageSpeed) * 1000; // Time in milliseconds

  // Activate both motors to move forward
  digitalWrite(IN1, HIGH);  // Motor 1 forward
  digitalWrite(IN2, LOW);   // Motor 1 backward
  digitalWrite(IN3, HIGH);  // Motor 2 forward
  digitalWrite(IN4, LOW);   // Motor 2 backward

  Serial.print("Moving forward for ");
  Serial.print(moveDuration);
  Serial.println(" ms");

  // Wait for the motor to run the required time
  delay(moveDuration);

  // Stop both motors after moving
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Movement completed.");
}
