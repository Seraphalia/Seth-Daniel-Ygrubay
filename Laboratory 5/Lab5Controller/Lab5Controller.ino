#include <Servo.h>

// Servo index definitions
enum { BASE, SHOULDER, GRIPPER, N_SV };

// Pin assignments for each servo
const uint8_t PIN[N_SV] = {11, 10, 9};
const uint32_t BAUD = 115200;

Servo sv[N_SV];     // Servo objects
String line;        // Serial input buffer

// Clamp value between 0 and 180
inline uint8_t clamp180(int v) { return constrain(v, 0, 180); }

// Move all three servos to specified angles
void moveArm(uint8_t b, uint8_t s, uint8_t g) {
  const uint8_t tgt[N_SV] = {b, s, g};
  for (uint8_t i = 0; i < N_SV; ++i) sv[i].write(tgt[i]);

  // Echo back confirmation message
  Serial.print(F("ACK "));
  Serial.print(b); Serial.print(',');
  Serial.print(s); Serial.print(',');
  Serial.println(g);
}

// Demo routine: sweeps through full operational range
void demo() {
  for (uint8_t i = 0; i <= 9; ++i) {
    moveArm(90 + i * 10,     // BASE (forward-backward): 90–180
            i * 20,          // SHOULDER (up-down): 0–180
            90 + i * 10);    // GRIPPER: 90–180
    delay(1000);
  }
  for (int8_t i = 8; i >= 0; --i) {
    moveArm(90 + i * 10,
            i * 20,
            90 + i * 10);
    delay(1000);
  }
}

// Arduino setup: attach servos and wait for commands
void setup() {
  Serial.begin(BAUD);
  for (uint8_t i = 0; i < N_SV; ++i) {
    sv[i].attach(PIN[i]);
    sv[i].write(90);   // Initialize all servos to neutral position
  }
  Serial.println(F("UNO_ARM_READY   send  b,s,g  or  demo"));
}

// Main loop: parse serial input and execute commands
void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    
    // When end of line is received
    if (c == '\n' || c == '\r') {
      if (line.length()) {
        if (line == "demo") {
          demo();  // Run demo routine
        } else {
          // Parse b,s,g format
          int k1 = line.indexOf(',');
          int k2 = line.indexOf(',', k1 + 1);
          if (k1 > 0 && k2 > k1) {
            uint8_t b = clamp180(line.substring(0, k1).toInt());
            uint8_t s = clamp180(line.substring(k1 + 1, k2).toInt());
            uint8_t g = clamp180(line.substring(k2 + 1).toInt());
            moveArm(b, s, g);  // Move servos to specified angles
          } else {
            Serial.println(F("ERR bad format"));  // Invalid command
          }
        }
        line = "";  // Clear input buffer
      }
    } else {
      line += c;  // Accumulate input characters
    }
  }
}
