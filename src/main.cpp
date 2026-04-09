#include <Arduino.h>
#include <ftb.h>

void setup() {
    initPCA9685();
}

void loop() {
    motorForward(50);  // 50% speed
    delay(2000);

    motorBackward(50);
    delay(2000);

    motorStop();
    delay(2000);
}