#include "motor.h"
#include "../movement/movement.h"

void setUpPinModes() {
    // Configure PWM for motor speed control
    ledcSetup(PWMSpeedChannel, PWMFreq, PWMResolution);
    ledcSetup(PWMLightChannel, PWMFreq, PWMResolution);
    
    // Configure motor pins
    for (const auto& motor : motorPins) {
        pinMode(motor.pinEn, OUTPUT);
        pinMode(motor.pinIN1, OUTPUT);
        pinMode(motor.pinIN2, OUTPUT);
    }
    
    // Configure light pin
    pinMode(LIGHT_PIN, OUTPUT);
    ledcAttachPin(LIGHT_PIN, PWMLightChannel);
}

void setMotorSpeed(int motorIndex, int speed, int direction) {
    if (motorIndex < 0 || motorIndex >= motorPins.size()) return;
    
    const auto& motor = motorPins[motorIndex];
    
    // Set direction
    if (direction == FORWARD) {
        digitalWrite(motor.pinIN1, HIGH);
        digitalWrite(motor.pinIN2, LOW);
    } else if (direction == BACKWARD) {
        digitalWrite(motor.pinIN1, LOW);
        digitalWrite(motor.pinIN2, HIGH);
    } else {
        digitalWrite(motor.pinIN1, LOW);
        digitalWrite(motor.pinIN2, LOW);
    }
    
    // Set speed
    ledcWrite(PWMSpeedChannel, speed);
}

void moveCar(int inputValue) {
    static unsigned long lastMoveTime = 0;
    static int lastInputValue = 0;
    
    // Record movement if it's different from last movement
    if (inputValue != lastInputValue) {
        if (lastInputValue != 0) {
            // Record the duration of the last movement
            Movement lastMove = {
                lastInputValue,
                lastMoveTime,
                millis() - lastMoveTime
            };
            movements.push_back(lastMove);
        }
        
        if (inputValue != 0) {
            lastMoveTime = millis();
        }
        
        lastInputValue = inputValue;
    }
    
    // Control motors based on input
    switch (inputValue) {
        case UP: // Forward
            setMotorSpeed(RIGHT_MOTOR, 255, FORWARD);
            setMotorSpeed(LEFT_MOTOR, 255, FORWARD);
            break;
            
        case DOWN: // Backward
            setMotorSpeed(RIGHT_MOTOR, 255, BACKWARD);
            setMotorSpeed(LEFT_MOTOR, 255, BACKWARD);
            break;
            
        case LEFT: // Turn left
            setMotorSpeed(RIGHT_MOTOR, 255, FORWARD);
            setMotorSpeed(LEFT_MOTOR, 255, BACKWARD);
            break;
            
        case RIGHT: // Turn right
            setMotorSpeed(RIGHT_MOTOR, 255, BACKWARD);
            setMotorSpeed(LEFT_MOTOR, 255, FORWARD);
            break;
            
        case STOP: // Stop
            setMotorSpeed(RIGHT_MOTOR, 0, 0);
            setMotorSpeed(LEFT_MOTOR, 0, 0);
            break;
    }
} 