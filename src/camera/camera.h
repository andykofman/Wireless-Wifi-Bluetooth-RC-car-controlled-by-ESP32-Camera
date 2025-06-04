#ifndef CAMERA_H
#define CAMERA_H

#include "../include/common.h"
#include "../config/pins.h"
#include "../config/wifi_config.h"

// Function declarations
void setupCamera();
void sendCameraPicture();
void onCameraWebSocketEvent(AsyncWebSocket *server,
                          AsyncWebSocketClient *client,
                          AwsEventType type,
                          void *arg,
                          uint8_t *data,
                          size_t len);

#endif // CAMERA_H 