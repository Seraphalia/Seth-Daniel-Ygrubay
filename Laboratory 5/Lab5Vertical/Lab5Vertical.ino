/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

int pos = 90;    // variable to store the servo position

void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the Servo object
}

void loop() {
  for (pos = 10; pos <= 115; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15 ms for the servo to reach the position
  }
  delay(150);
  for (pos = 115; pos >= 10; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15 ms for the servo to reach the position
  }
}