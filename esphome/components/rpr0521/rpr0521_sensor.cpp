#include "rpr0521_sensor.h"
#include "esphome/core/log.h"
#include "rpr0521_defs.h"

namespace esphome {
namespace rpr0521 {

static const char *const TAG = "rpr0521";

RPR0521Sensor::RPR0521Sensor() : PollingComponent(100){};

uint8_t RPR0521Sensor::read_id_() {
  uint8_t id;

  if (!read_bytes(RPR0521_MANUFACT, &id, 1)) {
    ESP_LOGD(TAG, "%s", "Manufacturer read failed.\n\r");
    return 255;
  } else {
    uint8_t part_id;

    ESP_LOGD(TAG, "Manufacturer: %u\n\r", id);
    if (!read_bytes(RPR0521_SYSTEM_CONTROL, &part_id, 1)) {
      ESP_LOGD(TAG, "%s", "Part ID read failed.\n\r");
      return 255;
    } else {
      ESP_LOGD(TAG, "Part ID: %u\n\r", (part_id & 0x3f));
      return part_id;
    }
  }
}

void RPR0521Sensor::wait_until_found_() {
  uint8_t id;

  id = read_id_();
  while (id == 255) {
    delayMicroseconds(100);
    id = read_id_();
  }
}

void RPR0521Sensor::soft_reset_() { reg(RPR0521_SYSTEM_CONTROL) = RPR0521_SYSTEM_CONTROL_SW_RESET_START; }

void RPR0521Sensor::clear_interrupt_() { reg(RPR0521_SYSTEM_CONTROL) = RPR0521_SYSTEM_CONTROL_INT_PIN_HI_Z; }

void RPR0521Sensor::initial_setup_() {
  reg(RPR0521_ALS_PS_CONTROL) = (RPR0521_ALS_PS_CONTROL_ALS_DATA0_GAIN_X1 | RPR0521_ALS_PS_CONTROL_ALS_DATA1_GAIN_X1 |
                                 RPR0521_ALS_PS_CONTROL_LED_CURRENT_100MA);
  reg(RPR0521_PS_CONTROL) = (RPR0521_PS_CONTROL_PS_GAIN_X1 | RPR0521_PS_CONTROL_PERSISTENCE_DRDY);
  reg(RPR0521_MODE_CONTROL) =
      (RPR0521_MODE_CONTROL_ALS_EN_TRUE | RPR0521_MODE_CONTROL_PS_EN_TRUE | RPR0521_MODE_CONTROL_PS_PULSE_200US |
       RPR0521_MODE_CONTROL_PS_OPERATING_MODE_NORMAL | RPR0521_MODE_CONTROL_MEASUREMENT_TIME_100MS_100MS);
  reg(RPR0521_INTERRUPT) =
      (RPR0521_INTERRUPT_INT_ASSERT_STABLE | RPR0521_INTERRUPT_INT_LATCH_DISABLED | RPR0521_INTERRUPT_INT_TRIG_BY_BOTH);
}

bool RPR0521Sensor::read_data_(uint16_t *proximity, uint16_t *ambient) {
  static const uint8_t RPR0521_DATA_LEN = 6;
  uint8_t data[RPR0521_DATA_LEN];
  if (read_bytes(RPR0521_PS_DATA_LSBS, data, RPR0521_DATA_LEN)) {
    proximity[0] = (data[0]) | (data[1] << 8);  // ps_data
    ambient[1] = (data[2]) | (data[3] << 8);    // als_data0
    ambient[2] = (data[4]) | (data[5] << 8);    // als_data1
    return true;
  } else {
    ESP_LOGD(TAG, "Read error.\n\r");
    return false;
  }
}

float RPR0521Sensor::lux_(uint16_t *data) {
  float lx;
  const uint16_t als_measure_time = 100, als_data0_gain = 1, als_data1_gain = 1;
  float d0, d1, d1_d0;
  if (als_measure_time == 50) {
    if ((data[0] & 0x8000) == 0x8000) {
      data[0] = 0x7FFF;
    }
    if ((data[1] & 0x8000) == 0x8000) {
      data[1] = 0x7FFF;
    }
  }
  d0 = ((float) data[0]) * (100.0f / als_measure_time) / als_data0_gain;
  d1 = ((float) data[1]) * (100.0f / als_measure_time) / als_data1_gain;

  if (d0 == 0.0) {
    lx = 0.0;
    return lx;
  }

  d1_d0 = d1 / d0;

  if (d1_d0 < 0.595) {
    lx = (1.682 * d0 - 1.877 * d1);
  } else if (d1_d0 < 1.015) {
    lx = (0.644 * d0 - 0.132 * d1);
  } else if (d1_d0 < 1.352) {
    lx = (0.756 * d0 - 0.243 * d1);
  } else if (d1_d0 < 3.053) {
    lx = (0.766 * d0 - 0.25 * d1);
  } else {
    lx = 0.0;
  }

  return lx;
}

float RPR0521Sensor::prox_(uint16_t *data) { return (float) data[0]; }

void RPR0521Sensor::read_and_publish_() {
  uint16_t proximity_data[1], ambient_data[2];
  float proximity, ambient_lux;
  read_data_(proximity_data, ambient_data);
  ESP_LOGD(TAG, "Raw Data: %u, %u, %u", proximity_data[0], ambient_data[0], ambient_data[1]);
  proximity = prox_(proximity_data);
  ambient_lux = lux_(ambient_data);
  proximity_sensor->publish_state(proximity);
  ambient_light_sensor->publish_state(ambient_lux);
}

void RPR0521Sensor::setup() {
  if (interrupt_pin_) {
    interrupt_pin_->pin_mode(gpio::FLAG_INPUT | gpio::FLAG_PULLUP);
    interrupt_pin_setup_complete_ = true;
  }
  this->set_i2c_address(0x38);
  wait_until_found_();
  initial_setup_();
}

void RPR0521Sensor::loop() {}

void RPR0521Sensor::update() {
  if (interrupt_pin_setup_complete_) {
    const int lim = timeout_us_ / 100;
    for (int n = 0; (interrupt_pin_->digital_read()) && (n < lim); n++) {
      delayMicroseconds(100);
    }
    if (!interrupt_pin_->digital_read()) {
      read_and_publish_();
    }
  } else {
    read_and_publish_();
  }
}

}  // namespace rpr0521
}  // namespace esphome
