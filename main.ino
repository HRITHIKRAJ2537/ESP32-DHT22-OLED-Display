#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DHT22_PIN 32 // The ESP32 pin GPIO2 connected to DHT22 sensor

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // create SSD1306 display object connected to I2C
DHT dht22(DHT22_PIN, DHT22);

String temperature;
String humidity;

void setup() {
  Serial.begin(115200);

  // Initialize I2C with custom pins
  Wire.begin(15, 16);

  // Initialize the OLED display with address 0x3C for 128x64
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  delay(2000);         // wait for initializing
  display.clearDisplay(); // clear display

  display.setTextSize(3);      // text size
  display.setTextColor(SSD1306_WHITE); // text color
  display.setCursor(0, 10);    // position to display

  dht22.begin();              // initialize DHT22 the temperature and humidity sensor

  temperature.reserve(10); // to avoid fragmenting memory when using String
  humidity.reserve(10); // to avoid fragmenting memory when using String
}

void loop() {
  float humi  = dht22.readHumidity();    // read humidity
  float tempC = dht22.readTemperature(); // read temperature

  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    temperature = "Failed";
    humidity = "Failed";
  } else {
    temperature  = String(tempC, 1); // one decimal places
    temperature += char (247); // degree character
    temperature += "C";
    humidity = String(humi, 1); // one decimal places
    humidity += "%";

    Serial.print(tempC);  // print to Serial Monitor
    Serial.print("°C | " );  // print to Serial Monitor
    Serial.print(humi);  // print to Serial Monitor
    Serial.println("%");  // print to Serial Monitor
  }

  oledDisplayCenter(temperature, humidity); // display temperature and humidity on OLED
}

void oledDisplayCenter(String temperature, String humidity) {
  int16_t x1;
  int16_t y1;
  uint16_t width_T;
  uint16_t height_T;
  uint16_t width_H;
  uint16_t height_H;

  display.getTextBounds(temperature, 0, 0, &x1, &y1, &width_T, &height_T);
  display.getTextBounds(temperature, 0, 0, &x1, &y1, &width_H, &height_H);

  // display on horizontal and vertical center
  display.clearDisplay(); // clear display
  display.setCursor((SCREEN_WIDTH - width_T) / 2, SCREEN_HEIGHT/2 - height_T - 5);
  display.println(temperature); // text to display
  display.setCursor((SCREEN_WIDTH - width_H) / 2, SCREEN_HEIGHT/2 + 5);
  display.println(humidity); // text to display
  display.display();
}
