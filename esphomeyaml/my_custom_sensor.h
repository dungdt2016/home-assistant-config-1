#include "esphomelib.h"
#include "Adafruit_BMP085.h"

using namespace esphomelib;

class MyCustomSensor : public PollingComponent {
 public:
  Adafruit_BMP085 bmp;
  sensor::Sensor *temperature_sensor = new sensor::Sensor();
  sensor::Sensor *pressure_sensor = new sensor::Sensor();

  MyCustomSensor() : PollingComponent(15000) { }

  void setup() override {
    bmp.begin();
  }

  void update() override {
    // This is the actual sensor reading logic.
    float temperature = bmp.readTemperature();
    temperature_sensor->publish_state(temperature);

    int pressure = bmp.readPressure();
    pressure_sensor->publish_state(pressure / 100.0);
  }
};