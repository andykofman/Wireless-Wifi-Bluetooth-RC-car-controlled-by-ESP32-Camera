#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include "../include/common.h"

// WiFi credentials
extern const char* ssid;
extern const char* password;

// WebSocket endpoints
extern AsyncWebSocket wsCamera;
extern AsyncWebSocket wsCarInput;
extern uint32_t cameraClientId;

// Function declarations
void checkWifiConnections();

#endif // WIFI_CONFIG_H 