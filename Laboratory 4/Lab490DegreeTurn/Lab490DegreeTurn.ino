// Motor control pins
#define IN1 6   // Motor 1 forward pin
#define IN2 9   // Motor 1 backward pin
#define IN3 5   // Motor 2 forward pin
#define IN4 3   // Motor 2 backward pin

// Wheel parameters
const float averageSpeed = 0.46;  // m/s (average speed)
const float wheelbase = 0.2;      // meters (distance between wheels)
const float turnRadius = 0.1;     // meters (turning radius for 90-degree turn)

// Function to calculate time to turn 90 degrees
unsigned long calculateTurnTime(float angleDegrees);

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Turn left by 90 degrees
  turnLeft90();
}

void loop() {
  // No need to do anything in loop
}

// Function to calculate time to turn 90 degrees
unsigned long calculateTurnTime(float angleDegrees) {
  // Convert angle to radians
  float angleRadians = radians(angleDegrees);

  // Time to turn (based on turning radius and speed)
  unsigned long turnDuration = (angleRadians * turnRadius) / averageSpeed * 1000; // Time in milliseconds
  return turnDuration;
}

// Function to turn the robot left by 90 degrees
void turnLeft90() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(650);

  unsigned long turnTime = calculateTurnTime(90); // 90-degree turn

  Serial.print("Turning left for ");
  Serial.print(turnTime);
  Serial.println(" ms");

  // Wait for the turn to complete
  delay(turnTime);

  // Stop both motors after turning
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Turn completed.");
}
