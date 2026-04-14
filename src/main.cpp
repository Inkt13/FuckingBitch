#include <Arduino.h>
#include <ftb.h>
#include <Motor.h>
#include <SerialDecoder.h>
#include <ESP32Servo.h>

void setup() {
    initPCA9685();
    Serial.begin(115200);
    robotMovement.motorsInit();
    robotMovement.servoInit();
}

byte serialData = 0;

void loop() {
    if (Serial.available() > 0) {
    serialData = Serial.read();
    SerialDecoder::handleSerialData(serialData);
  }
}