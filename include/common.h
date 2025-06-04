#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <esp_camera.h>
#include <vector>
#include <string>

// Movement direction constants
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

// Motor indices
#define RIGHT_MOTOR 0
#define LEFT_MOTOR 1

// Motor direction
#define FORWARD 1
#define BACKWARD -1

// PWM settings
const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int PWMSpeedChannel = 2;
const int PWMLightChannel = 3;

// Timing constants
const unsigned long interval = 120000; // 2 minutes in milliseconds

// Global variables
extern int connect;
extern int users;
extern unsigned long lastChecktime;

#endif // COMMON_H 