#include "camera.h"

void setupCamera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    
    // Initialize with high quality JPEG
    if (psramFound()) {
        config.jpeg_quality = 10;
        config.fb_count = 2;
    } else {
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }
    
    // Camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }
}

void sendCameraPicture() {
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Camera capture failed");
        return;
    }
    
    if (fb->format != PIXFORMAT_JPEG) {
        Serial.println("Camera capture format not JPEG");
        esp_camera_fb_return(fb);
        return;
    }
    
    // Send the picture to the connected client
    if (cameraClientId != 0) {
        wsCamera.binary(cameraClientId, fb->buf, fb->len);
    }
    
    // Return the frame buffer
    esp_camera_fb_return(fb);
}

void onCameraWebSocketEvent(AsyncWebSocket *server,
                          AsyncWebSocketClient *client,
                          AwsEventType type,
                          void *arg,
                          uint8_t *data,
                          size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", 
                         client->id(), client->remoteIP().toString().c_str());
            cameraClientId = client->id();
            break;
            
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            if (cameraClientId == client->id()) {
                cameraClientId = 0;
            }
            break;
            
        case WS_EVT_DATA:
            // Handle any incoming data if needed
            break;
            
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
} 