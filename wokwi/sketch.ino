#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ================================
// OLED SETTINGS
// ================================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

// ================================
// DS18B20 TEMPERATURE SENSOR
// ================================
#define ONE_WIRE_BUS 4

// Create OLED object
Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// Create temperature sensor objects
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temperatureSensor(&oneWire);

// ================================
// SETUP
// ================================
void setup() {
  Serial.begin(115200);

  // Initialize I2C for OLED
  Wire.begin(21, 22);

  // Initialize OLED
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
      )) {

    Serial.println("OLED initialization failed!");

    while (true) {
      delay(100);
    }
  }

  // Initialize DS18B20
  temperatureSensor.begin();

  Serial.println("OLED initialized successfully!");
  Serial.println("DS18B20 initialized.");
  Serial.println("IoT Stress Monitor Started!");

  // Show startup screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);

  display.println("IoT Stress Monitor");
  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

  display.setCursor(0, 25);
  display.println("Initializing...");
  display.println("Please wait");

  display.display();

  delay(1500);
}

// ================================
// MAIN LOOP
// ================================
void loop() {

  // Read temperature
  temperatureSensor.requestTemperatures();

  float temperatureC =
    temperatureSensor.getTempCByIndex(0);

  // Print reading to Serial Monitor
  Serial.print("Temperature: ");

  if (temperatureC == DEVICE_DISCONNECTED_C) {
    Serial.println("Sensor not detected!");
  } else {
    Serial.print(temperatureC, 1);
    Serial.println(" C");
  }

  // ================================
  // UPDATE OLED DISPLAY
  // ================================
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Project title
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("IoT Stress Monitor");

  // Horizontal separator
  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

  // Temperature label
  display.setTextSize(1);
  display.setCursor(0, 22);
  display.println("Temperature");

  // Temperature value
  display.setTextSize(2);
  display.setCursor(0, 38);

  if (temperatureC == DEVICE_DISCONNECTED_C) {
    display.setTextSize(1);
    display.println("Sensor Error");
  } else {
    display.print(temperatureC, 1);
    display.println(" C");
  }

  // Refresh display
  display.display();

  // Wait 2 seconds before next reading
  delay(2000);
}