#include "movement.h"
#include "../motor/motor.h"

void traceBackMovements() {
    // Reverse through the movement history
    for (auto it = movements.rbegin(); it != movements.rend(); ++it) {
        // Calculate the reverse movement
        int reverseInput;
        switch (it->inputValue) {
            case UP:
                reverseInput = DOWN;
                break;
            case DOWN:
                reverseInput = UP;
                break;
            case LEFT:
                reverseInput = RIGHT;
                break;
            case RIGHT:
                reverseInput = LEFT;
                break;
            default:
                continue;
        }
        
        // Execute the reverse movement for the same duration
        moveCar(reverseInput);
        delay(it->duration);
        moveCar(STOP);
        delay(500); // Small pause between movements
    }
    
    // Clear the movement history after tracing back
    movements.clear();
} 