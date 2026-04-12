#include <ftb.h>

void setPWM(uint8_t channel, uint16_t on, uint16_t off) {
    if (channel > 15) return;

    uint8_t reg = 6 + 4 * channel;

    Wire.beginTransmission(PCA9685_ADDR);
    Wire.write(reg);
    Wire.write(on & 0xFF);
    Wire.write((on >> 8) & 0xFF);
    Wire.write(off & 0xFF);
    Wire.write((off >> 8) & 0xFF);
    Wire.endTransmission();
}

void initPCA9685() {
    Wire.begin();

    // Reset MODE1
    Wire.beginTransmission(PCA9685_ADDR);
    Wire.write(0x00);
    Wire.write(0x10); // sleep
    Wire.endTransmission();

    // Set frequency to ~50Hz (good for motors/servos)
    Wire.beginTransmission(PCA9685_ADDR);
    Wire.write(0xFE);
    Wire.write(121);  // prescaler for ~50Hz
    Wire.endTransmission();

    // Wake up
    Wire.beginTransmission(PCA9685_ADDR);
    Wire.write(0x00);
    Wire.write(0x20);
    Wire.endTransmission();
}