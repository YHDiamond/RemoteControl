#include <ESP32_Servo.h>

#define servoPin 34
Servo servo;

void setup() {
    pinMode(34, OUTPUT);
    servo.attach(servoPin);
}

void loop() {
    servo.write(0);
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(180);
    delay(1000);
    servo.write(90);
    delay(1000);
}
