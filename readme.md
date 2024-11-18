
# README for Fire and Gas Detection System

## Overview

This project implements a fire and gas detection system using the ESP8266 microcontroller. It monitors for fire and gas presence and sends alerts via WhatsApp using the CallMeBot API. The system activates a buzzer when a danger is detected.

## Features

-   **WiFi Connectivity**: Connects to a specified WiFi network.
-   **Fire and Gas Detection**: Monitors specific GPIO pins for fire and gas detection.
-   **WhatsApp Notifications**: Sends alerts through WhatsApp when danger is detected.
-   **Buzzer Activation**: Activates a buzzer for audible alerts.

## Components Required

-   ESP8266 NodeMCU
-   Buzzer
-   Fire sensor (compatible with GPIO)
-   Gas sensor (compatible with GPIO)
-   Jumper wires
-   Power supply

## Pin Configuration

Pin Name

GPIO Number

Function

BUZ_PIN

D6 (GPIO12)

Buzzer Output

FIRE_PIN

D7 (GPIO13)

Fire Sensor Input

GAS_PIN

D5 (GPIO14)

Gas Sensor Input

## Setup Instructions

1.  **Install Libraries**:
    
    -   Ensure you have the  `ESP8266WiFi`  and  `ESP8266HTTPClient`  libraries installed in your Arduino IDE.
2.  **Connect Hardware**:
    
    -   Connect the buzzer, fire sensor, and gas sensor to the appropriate GPIO pins on the NodeMCU.
3.  **Configure WiFi**:
    
    -   Update the  `ssid`  and  `password`  variables in the code with your WiFi credentials.
4.  **Configure CallMeBot**:
    
    -   Update the  `phoneNumber`  and  `apiKey`  variables in the code with your WhatsApp number and CallMeBot API key.
5.  **Upload the Code**:
    
    -   Upload the code to the ESP8266 using the Arduino IDE.

## Code Explanation

### Setup Function

-   Initializes serial communication.
-   Configures GPIO pins.
-   Connects to the WiFi network.
-   Sends an initial WhatsApp message indicating that the system has started.

### sendWhatsAppMessage Function

-   Sends a message to the specified WhatsApp number using the CallMeBot API.
-   Handles HTTP requests and responses.

### Loop Function

-   Continuously checks for fire and gas detection every 500 ms.
-   Activates the buzzer and sends a WhatsApp alert if fire or gas is detected.
-   Deactivates the buzzer if no danger is detected.

## Usage

-   Once the system is powered on, it will connect to the WiFi and begin monitoring for fire and gas.
-   The buzzer will sound, and a WhatsApp message will be sent if either condition is detected.

## Troubleshooting

-   **WiFi Connection Issues**: Ensure the SSID and password are correct.
-   **WhatsApp Notification Issues**: Verify the phone number format and API key.
-   **Buzzer Not Activating**: Check the connections and ensure the buzzer is functional.

## License

This project is open-source and available for modification and distribution under the MIT License.

## Contact

For questions or support, please contact [Your Name] at [Your Email].
