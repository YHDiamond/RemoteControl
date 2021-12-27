#include <ESP32Servo.h>

#define servoPin 33
Servo servo;
int pos = 0;

void setup() {
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    servo.setPeriodHertz(50);
    servo.attach(servoPin, 500, 2400);
}

void loop() {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo.write(pos);    // tell servo to go to position in variable 'pos'
      delay(15);             // waits 15ms for the servo to reach the position
    }
}
