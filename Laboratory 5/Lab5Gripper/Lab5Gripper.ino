/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo; 


int pos = 90; 

void setup() {
  myservo.attach(11);
}

void loop() {
  for (pos = 90; pos <= 180; pos += 1) { 
    // in steps of 1 degree
    myservo.write(pos);              
    delay(1000);                     
  }
  delay(150);
  for (pos = 180; pos >= 90; pos -= 1) { 
    myservo.write(pos);             
    delay(1000);                      
  }
}