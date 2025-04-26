// Pin connected to Hall effect sensor output
const int hallPin = 2; // Must be an interrupt-capable pin!

// Variables to track time
volatile unsigned long lastPulseTime = 0;
volatile unsigned long pulseInterval = 0;

// Wheel parameters
const float wheelDiameter = 0.04; // meters
const float pi = 3.14159265;

// For calculating speed
float speed = 0.0; // meters per second

// Sampling control
int sampleCount = 0;
const int maxSamples = 50;

void setup() {
  Serial.begin(9600);
  pinMode(hallPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallPin), onPulse, FALLING);

  Serial.println("Timestamp (ms), Speed (m/s)");
}

void loop() {
  if (sampleCount >= maxSamples) {
    // Stop collecting after 50 samples
    detachInterrupt(digitalPinToInterrupt(hallPin));
    Serial.println("Finished collecting 50 samples.");
    while (true); // Stop the program
  }

  noInterrupts();
  unsigned long interval = pulseInterval;
  interrupts();

  if (interval > 0) {
    // Calculate wheel circumference
    float wheelCircumference = pi * wheelDiameter;
    
    // Speed = distance/time (interval is in microseconds)
    speed = wheelCircumference / (interval / 1e6);
    
    // Print timestamp and speed
    Serial.print(millis());
    Serial.print(", ");
    Serial.println(speed);

    pulseInterval = 0; // Reset to wait for next valid pulse
    sampleCount++;
  }

  // No need to delay heavily; just a light delay
  delay(10);
}

void onPulse() {
  unsigned long currentTime = micros();
  pulseInterval = currentTime - lastPulseTime;
  lastPulseTime = currentTime;
}
