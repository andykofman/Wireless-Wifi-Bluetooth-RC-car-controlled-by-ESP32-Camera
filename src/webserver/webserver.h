#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "../include/common.h"
#include "../config/wifi_config.h"

// Web server instance
extern AsyncWebServer server;

// Function declarations
void handleRoot(AsyncWebServerRequest *request);
void handleNotFound(AsyncWebServerRequest *request);
void onCarInputWebSocketEvent(AsyncWebSocket *server,
                            AsyncWebSocketClient *client,
                            AwsEventType type,
                            void *arg,
                            uint8_t *data,
                            size_t len);

#endif // WEBSERVER_H 