#pragma once
#include <Wire.h>
#define PCA9685_ADDR 0x40

void initPCA9685();
void setPWM();
void motorForward();