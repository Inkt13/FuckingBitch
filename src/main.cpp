#include <Arduino.h>
#include <ftb.h>
#include <Motor.h>

void setup() {
    initPCA9685();
    Serial.begin(1152000);
}

void loop() {
    motor.moveY(100);
}