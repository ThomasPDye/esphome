#pragma once

#include <list>

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace rpr0521 {

class RPR0521Sensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  RPR0521Sensor();

  void setup() override;

  float get_setup_priority() const override { return setup_priority::DATA; }
  void update() override;

  void loop() override;

  void set_timeout_us(uint32_t timeout_us) { this->timeout_us_ = timeout_us; }
  void set_interrupt_pin(GPIOPin *interrupt) { this->interrupt_pin_ = interrupt; }

 protected:
  GPIOPin *interrupt_pin_{nullptr};

  uint16_t timeout_start_us_;
  uint16_t timeout_us_{};

  uint8_t readId();
  void wait_until_found();

  void soft_reset();
  void clear_interrupt();

  void initial_setup();

  bool read_data(uint16_t *data16);

  static std::list<RPR0521Sensor *> rpr0521_sensors;
  static bool interrupt_pin_setup_complete;
};

}  // namespace rpr0521
}  // namespace esphome
