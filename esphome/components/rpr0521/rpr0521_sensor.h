#pragma once

#include <list>

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace rpr0521 {

class RPR0521Sensor : public PollingComponent, public i2c::I2CDevice {
 public:
  sensor::Sensor *proximity_sensor = new sensor::Sensor();
  sensor::Sensor *ambient_light_sensor = new sensor::Sensor();
  RPR0521Sensor();

  void setup() override;

  float get_setup_priority() const override { return setup_priority::DATA; }
  void update() override;

  void loop() override;

  void set_interrupt_pin(GPIOPin *interrupt) { this->interrupt_pin_ = interrupt; }

 protected:
  uint8_t read_id_();
  void wait_until_found_();

  void soft_reset_();
  void clear_interrupt_();

  void initial_setup_();

  bool read_data_(uint16_t *proximity, uint16_t *ambient);

  float prox_(uint16_t *proximity);
  float lux_(uint16_t *ambient);

  void read_and_publish_();

  GPIOPin *interrupt_pin_{nullptr};

  uint16_t timeout_start_us_;
  uint16_t timeout_us_{};

  static std::list<RPR0521Sensor *> rpr0521_sensors;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
  static bool interrupt_pin_setup_complete;           // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

}  // namespace rpr0521
}  // namespace esphome
