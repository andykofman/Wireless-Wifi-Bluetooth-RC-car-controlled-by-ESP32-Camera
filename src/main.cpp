#include "include/common.h"
#include "config/pins.h"
#include "config/wifi_config.h"
#include "motor/motor.h"
#include "camera/camera.h"
#include "webserver/webserver.h"
#include "webserver/webpage.h"
#include "movement/movement.h"

// Global variables
int connect = 0;
int users = 0;
unsigned long lastChecktime = 0;

// Motor pin configurations
std::vector<MOTOR_PINS> motorPins = {
    {12, 13, 15},  // RIGHT_MOTOR Pins (EnA, IN1, IN2)
    {12, 14, 2},   // LEFT_MOTOR  Pins (EnB, IN3, IN4)
};

// WiFi credentials
const char* ssid = "Ferionki";
const char* password = "omar1234";

// Web server and WebSocket instances
AsyncWebServer server(80);
AsyncWebSocket wsCamera("/Camera");
AsyncWebSocket wsCarInput("/CarInput");
uint32_t cameraClientId = 0;

// Movement history
std::vector<Movement> movements;

void setup() {
    Serial.begin(115200);
    
    // Initialize pins
    setUpPinModes();
    
    // Setup camera
    setupCamera();
    
    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    
    // Setup web server routes
    server.on("/", HTTP_GET, handleRoot);
    server.onNotFound(handleNotFound);
    
    // Setup WebSocket handlers
    wsCamera.onEvent(onCameraWebSocketEvent);
    wsCarInput.onEvent(onCarInputWebSocketEvent);
    
    // Add WebSocket to server
    server.addHandler(&wsCamera);
    server.addHandler(&wsCarInput);
    
    // Start server
    server.begin();
}

void loop() {
    // Check WiFi connections periodically
    if (millis() - lastChecktime > interval) {
        checkWifiConnections();
        lastChecktime = millis();
    }
    
    // Send camera picture if client is connected
    if (cameraClientId != 0) {
        sendCameraPicture();
    }
    
    // Handle WebSocket cleanup
    wsCamera.cleanupClients();
    wsCarInput.cleanupClients();
    
    // Small delay to prevent overwhelming the system
    delay(10);
} 