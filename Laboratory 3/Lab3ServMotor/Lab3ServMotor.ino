#include <Servo.h>

Servo myServo;
int angle = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
  Serial.println("Timestamp(ms),Angle,Speed");
}

void loop() {
  // Fast sweep (delay 200ms)
  for (angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);
    Serial.print(millis());
    Serial.print(",");
    Serial.print(angle);
    Serial.println(",Fast");
    delay(200);
  }
  for (angle = 180; angle >= 0; angle -= 10) {
    myServo.write(angle);
    Serial.print(millis());
    Serial.print(",");
    Serial.print(angle);
    Serial.println(",Fast");
    delay(200);
  }

  // Medium sweep (delay 500ms)
  for (angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);
    Serial.print(millis());
    Serial.print(",");
    Serial.print(angle);
    Serial.println(",Medium");
    delay(500);
  }
  for (angle = 180; angle >= 0; angle -= 10) {
    myServo.write(angle);
    Serial.print(millis());
    Serial.print(",");
    Serial.print(angle);
    Serial.println(",Medium");
    delay(500);
  }

  // Slow sweep (delay 800ms)
  for (angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);
    Serial.print(millis());
    Serial.print(",");
    Serial.print(angle);
    Serial.println(",Slow");
    delay(800);
  }
  for (angle = 180; angle >= 0; angle -= 10) {
    myServo.write(angle);
    Serial.print(millis());
    Serial.print(",");
    Serial.print(angle);
    Serial.println(",Slow");
    delay(800);
  }

  // Stop execution
  while (true);
}
