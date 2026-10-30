#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "MAX30105.h"
#include "heartRate.h"

// 1 = Simulation mode
// 0 = Hardware mode
#define SIMULATION_MODE 1

#define I2C_SDA 21
#define I2C_SCL 22
#define DS18B20_PIN 4

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

OneWire oneWire(DS18B20_PIN);
DallasTemperature tempSensor(&oneWire);
MAX30105 particleSensor;

bool oledReady = false;
bool maxReady = false;
bool tempReady = false;

float heartRateBpm = 0.0;
float temperatureC = 0.0;

unsigned long lastUpdate = 0;
unsigned long lastBeat = 0;

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE] = {0};
byte rateSpot = 0;
byte rateCount = 0;

// Educational stress-estimation rule.
// This is not a medically validated algorithm.
String estimateStress(float bpm, float tempC) {
    if (bpm <= 0 || tempC < 25 || tempC > 45) {
        return "NO DATA";
    }

    if (bpm >= 100) {
        return "HIGH";
    }

    if (bpm >= 85) {
        return "MODERATE";
    }

    return "LOW";
}

void showScreen(
    const String &mode,
    float bpm,
    float tempC,
    const String &stress
) {
    if (!oledReady) {
        return;
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);

    display.println("IoT Stress Monitor");
    display.println("-----------------");
    display.println(mode);

    display.print("HR: ");
    display.print(bpm, 1);
    display.println(" BPM");

    display.print("Temp: ");
    display.print(tempC, 2);
    display.println(" C");

    display.print("Level: ");
    display.println(stress);

    display.display();
}

void setup() {
    Serial.begin(115200);
    delay(500);

    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(100000);

    oledReady = display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
    );

    Serial.println();
    Serial.println("IoT-Based Stress Monitoring System");

#if SIMULATION_MODE

    Serial.println(
        "MODE: SIMULATION - values are generated, not measured."
    );

#else

    tempSensor.begin();
    tempReady = tempSensor.getDeviceCount() > 0;

    maxReady = particleSensor.begin(
        Wire,
        I2C_SPEED_STANDARD
    );

    if (maxReady) {
        particleSensor.setup(
            0x1F,
            4,
            2,
            100,
            411,
            16384
        );

        particleSensor.setPulseAmplitudeRed(0x1F);
        particleSensor.setPulseAmplitudeIR(0x1F);
        particleSensor.setPulseAmplitudeGreen(0);
    }

    Serial.printf(
        "OLED: %s | MAX30102: %s | DS18B20: %s\n",
        oledReady ? "OK" : "NOT FOUND",
        maxReady ? "OK" : "NOT FOUND",
        tempReady ? "OK" : "NOT FOUND"
    );

#endif

    Serial.println(
        "elapsed_s,heart_rate_bpm,temperature_c,stress_level,mode"
    );
}

void loop() {
    unsigned long now = millis();

#if SIMULATION_MODE

    if (now - lastUpdate >= 2000) {
        lastUpdate = now;

        static int step = 0;
        step++;

        float bpm =
            74.0 + 14.0 * sinf(step * 0.35);

        float tempC =
            36.5 + 0.15 * sinf(step * 0.2);

        String stress = estimateStress(bpm, tempC);

        Serial.printf(
            "%lu,%.1f,%.2f,%s,SIMULATION\n",
            now / 1000,
            bpm,
            tempC,
            stress.c_str()
        );

        showScreen(
            "SIMULATION MODE",
            bpm,
            tempC,
            stress
        );
    }

#else

    if (maxReady) {
        long ir = particleSensor.getIR();

        if (checkForBeat(ir)) {
            unsigned long delta = now - lastBeat;
            lastBeat = now;

            if (delta > 0) {
                float bpm = 60000.0 / delta;

                if (bpm >= 40 && bpm <= 200) {
                    rates[rateSpot++] = (byte)bpm;
                    rateSpot %= RATE_SIZE;

                    if (rateCount < RATE_SIZE) {
                        rateCount++;
                    }

                    int sum = 0;

                    for (byte i = 0; i < rateCount; i++) {
                        sum += rates[i];
                    }

                    heartRateBpm =
                        (float)sum / rateCount;
                }
            }
        }
    }

    if (tempReady) {
        tempSensor.requestTemperatures();

        float t = tempSensor.getTempCByIndex(0);

        if (t != DEVICE_DISCONNECTED_C &&
            t >= -20 && t <= 80) {
            temperatureC = t;
        }
    }

    if (now - lastUpdate >= 2000) {
        lastUpdate = now;

        String stress =
            estimateStress(heartRateBpm, temperatureC);

        Serial.printf(
            "%lu,%.1f,%.2f,%s,HARDWARE\n",
            now / 1000,
            heartRateBpm,
            temperatureC,
            stress.c_str()
        );

        showScreen(
            maxReady ? "HARDWARE MODE" : "MAX30102 MISSING",
            heartRateBpm,
            temperatureC,
            stress
        );
    }

#endif

    delay(10);
}