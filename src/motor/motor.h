#ifndef MOTOR_H
#define MOTOR_H

#include "../include/common.h"
#include "../config/pins.h"

// Function declarations
void setUpPinModes();
void moveCar(int inputValue);
void setMotorSpeed(int motorIndex, int speed, int direction);

#endif // MOTOR_H 