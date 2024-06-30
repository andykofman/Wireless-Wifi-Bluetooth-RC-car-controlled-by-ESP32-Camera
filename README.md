

# Project: Arduino-based Car Control System (Wifi + Bluetooth) with ESP32 - Camera

## Overview
This project involves an Arduino-based car control system that allows for remote control of the car using a web interface. The system also includes a camera for visual feedback, and it uses WebSocket communication for real-time control and image transmission.

## Objective
The primary objective of this project is to develop a WiFi-enabled car that can be controlled over the internet, offering real-time video streaming capabilities. The car should be capable of moving in multiple directions and capturing live video feeds from its surroundings. Moreover, if the WiFi is disconnected, it returns back as a safety measure.

## Components
- **ESP32 Camera Module**: Captures images and streams them to the web interface.
- **Motors**: Controlled via H-bridge motor drivers for movement in multiple directions.
- **WiFi Module**: Connects to a network to allow remote control via a web interface.
- **Web Interface**: Provides controls for car movement and speed, as well as a live camera feed.

## Libraries Used
- `esp_camera.h`: For camera operations.
- `Arduino.h`: Core Arduino library.
- `WiFi.h`: For WiFi connectivity.
- `AsyncTCP.h`: Asynchronous TCP library.
- `ESPAsyncWebServer.h`: Asynchronous web server library.

## Pin Configuration
### Camera Pins:
- `PWDN_GPIO_NUM`: 32
- `XCLK_GPIO_NUM`: 0
- `SIOD_GPIO_NUM`: 26
- `SIOC_GPIO_NUM`: 27
- `Y9_GPIO_NUM`: 35
- `Y8_GPIO_NUM`: 34
- `Y7_GPIO_NUM`: 39
- `Y6_GPIO_NUM`: 36
- `Y5_GPIO_NUM`: 21
- `Y4_GPIO_NUM`: 19
- `Y3_GPIO_NUM`: 18
- `Y2_GPIO_NUM`: 5
- `VSYNC_GPIO_NUM`: 25
- `HREF_GPIO_NUM`: 23
- `PCLK_GPIO_NUM`: 22

### Motor Control Pins:
- `RIGHT_MOTOR`: 12, 13, 15
- `LEFT_MOTOR`: 12, 14, 2

## Constants
### Motor Directions:
- `UP`: 1
- `DOWN`: 2
- `LEFT`: 3
- `RIGHT`: 4
- `STOP`: 0

### PWM Configuration:
- `PWMFreq`: 1000 Hz
- `PWMResolution`: 8 bits
- `PWMSpeedChannel`: 2
- `PWMLightChannel`: 3

## Code Structure
### Setup:
- Initialize motor pin modes.
- Configure and start the camera.
- Set up the WiFi access point.
- Configure and start the web server.

### Loop:
- Clean up WebSocket clients.
- Send camera pictures periodically.
- Check WiFi connections and trace back movements if necessary.

## Functions
- `rotateMotor(int motorNumber, int motorDirection)`: Controls the rotation direction of a specified motor.
- `moveCar(int inputValue)`: Moves the car based on the input command.
- `traceBackMovements()`: Reverses the car's movements.
- `handleRoot(AsyncWebServerRequest *request)`: Handles the root web page request.
- `handleNotFound(AsyncWebServerRequest *request)`: Handles 404 errors.
- `onCarInputWebSocketEvent(...)`: Handles WebSocket events for car control.
- `onCameraWebSocketEvent(...)`: Handles WebSocket events for the camera.
- `setupCamera()`: Initializes the camera.
- `sendCameraPicture()`: Captures and sends a picture from the camera.
- `setUpPinModes()`: Configures the pin modes for motor control and PWM.
- `checkWifiConnections()`: Checks for WiFi connections and triggers movement trace back if necessary.

## Web Interface
The web interface includes buttons for car movement, sliders for speed and light control, and a live feed from the camera.

## How to Use
1. Upload the code to your ESP32 board.
2. Connect to the WiFi access point named "Ferionki" with the password "omar1234".
3. Open a web browser and navigate to the IP address displayed in the serial monitor.
4. Use the web interface to control the car and view the camera feed.
