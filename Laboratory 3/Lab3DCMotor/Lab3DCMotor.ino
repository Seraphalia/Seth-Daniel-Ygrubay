const int ENA = 10;     // PWM pin for speed control
const int IN1 = 8;      // Direction pin
const int IN2 = 9;      // Direction pin

unsigned long t;

void setup() {

  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

}

void logData(String direction, int speed) {

  t = millis();
  Serial.print(t);
  Serial.print(",");  
  Serial.print(direction);
  Serial.print(",");
  Serial.println(speed);
}


void loop() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 128);
  logData("Forward", 50);
  delay(2000);

  analogWrite(ENA, 192);
  logData("Forward", 75);
  delay(2000);

  analogWrite(ENA, 255);
  logData("Forward", 100);
  delay(2000);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 192);
  logData("Reverse", 75);
  delay(2000);



}









