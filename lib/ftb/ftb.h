#pragma once
#include <Wire.h>
#define PCA9685_ADDR 0x40

void initPCA9685();
void setPWM(uint8_t channel, uint16_t on, uint16_t off);