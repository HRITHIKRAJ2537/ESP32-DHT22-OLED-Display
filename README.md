# ESP32-DHT22-OLED-Display

An ESP32 project that reads temperature and humidity data from a DHT22 sensor and displays it on an OLED screen using the Adafruit SSD1306 library.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/ESP32-DHT22-OLED-Display.git
2.Navigate to the project directory
   cd ESP32-DHT22-OLED-Display

3.Install the necessary libraries:
    Adafruit GFX Library
    Adafruit SSD1306 Library
    DHT sensor library
4.Usage
Connect the DHT22 sensor to GPIO 32 of the ESP32.
Connect the OLED display to the I2C pins (SDA to GPIO 15, SCL to GPIO 16).
