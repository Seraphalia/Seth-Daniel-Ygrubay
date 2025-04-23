#include <Stepper.h>

const int stepsPerRevolution = 2048; // 28BYJ-48 in half-step mode
unsigned long currentMillis;

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); // 1,3,2,4 order

void setup() {
  Serial.begin(9600);
  delay(2000); // Give serial monitor time to connect
  Serial.println("Timestamp (ms)\tTimestamp (s)\tDirection\tSpeed (RPM)");
}

void loop() {
  // Clockwise - 10 RPM
  myStepper.setSpeed(10);
  currentMillis = millis();
  Serial.print(currentMillis); Serial.print("\t");
  Serial.print(currentMillis / 1000.0, 3); Serial.print("\t");
  Serial.println("Clockwise\t10");
  myStepper.step(stepsPerRevolution);
  delay(2000);

  // Clockwise - 5 RPM
  myStepper.setSpeed(5);
  currentMillis = millis();
  Serial.print(currentMillis); Serial.print("\t");
  Serial.print(currentMillis / 1000.0, 3); Serial.print("\t");
  Serial.println("Clockwise\t5");
  myStepper.step(stepsPerRevolution);
  delay(2000);

  // Counter-Clockwise - 10 RPM
  myStepper.setSpeed(10);
  currentMillis = millis();
  Serial.print(currentMillis); Serial.print("\t");
  Serial.print(currentMillis / 1000.0, 3); Serial.print("\t");
  Serial.println("Counter-Clockwise\t10");
  myStepper.step(-stepsPerRevolution);
  delay(2000);

  // Counter-Clockwise - 5 RPM
  myStepper.setSpeed(5);
  currentMillis = millis();
  Serial.print(currentMillis); Serial.print("\t");
  Serial.print(currentMillis / 1000.0, 3); Serial.print("\t");
  Serial.println("Counter-Clockwise\t5");
  myStepper.step(-stepsPerRevolution);
  delay(2000);

  // Stop after one loop
  while (true);
}
