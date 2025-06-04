#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../include/common.h"

// Movement structure for tracking car movements
struct Movement {
    int inputValue;
    unsigned long startTime;
    unsigned long duration;
};

// Global movement history
extern std::vector<Movement> movements;

// Function declarations
void traceBackMovements();

#endif // MOVEMENT_H 