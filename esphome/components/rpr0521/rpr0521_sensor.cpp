#include "rpr0521_sensor.h"
#include "esphome/core/log.h"
#include "rpr0521_defs.h"

namespace esphome {
namespace rpr0521 {

static const char *const TAG = "rpr0521";

std::list<RPR0521Sensor *> RPR0521Sensor::rpr0521_sensors;
bool RPR0521Sensor::interrupt_pin_setup_complete = false;

RPR0521Sensor::RPR0521Sensor() { RPR0521Sensor::rpr0521_sensors.push_back(this); };

uint8_t RPR0521Sensor::readId() {
  uint8_t id;

  if (!read_bytes(RPR0521_MANUFACT, &id, 1)) {
    LOG_D(TAG, "%s", "Manufacturer read failed.\n\r");
    return 255;
  } else {
    uint8_t part_id;

    LOG_D(TAG, "Manufacturer: %u\n\r", id);
    if (!read_bytes(RPR0521_SYSTEM_CONTROL, &id, 1)) {
      LOG_D(TAG, "%s", "Part ID read failed.\n\r");
      return 255;
    } else {
      LOG_D(TAG, "Part ID: %u\n\r", (partid & 0x3f));
      return part_id;
    }
  }
}

void RPR0521Sensor::wait_until_found() {
  uint8_t id;

  id = readId();
  while (id == 255) {
    delayMicroseconds(100);
    id = readId();
  }
  return;
}

void RPR0521Sensor::soft_reset() { reg(RPR0521_SYSTEM_CONTROL) = RPR0521_SYSTEM_CONTROL_SW_RESET_START; }

void RPR0521Sensor::clear_interrupt() { reg(RPR0521_SYSTEM_CONTROL) = RPR0521_SYSTEM_CONTROL_INT_PIN_HI_Z; }

void RPR0521Sensor::initial_setup() {
  reg(RPR0521_ALS_PS_CONTROL) = (RPR0521_ALS_PS_CONTROL_ALS_DATA0_GAIN_X1 | RPR0521_ALS_PS_CONTROL_ALS_DATA1_GAIN_X1 |
                                 RPR0521_ALS_PS_CONTROL_LED_CURRENT_25MA);
  reg(RPR0521_PS_CONTROL) = (RPR0521_PS_CONTROL_PS_GAIN_X1 | RPR0521_PS_CONTROL_PERSISTENCE_DRDY);
  reg(RPR0521_MODE_CONTROL) =
      (RPR0521_MODE_CONTROL_ALS_EN_TRUE | RPR0521_MODE_CONTROL_PS_EN_TRUE | RPR0521_MODE_CONTROL_PS_PULSE_200US |
       RPR0521_MODE_CONTROL_PS_OPERATING_MODE_NORMAL | RPR0521_MODE_CONTROL_MEASUREMENT_TIME_100MS_100MS);
}

bool RPR0521Sensor::read_data(uint16_t *data16) {
#define RPR0521_DATA_LEN 6
  uint8_t data[RPR0521_DATA_LEN];
  if (read_bytes(RPR0521_PS_DATA_LSBS, &data[0], RPR0521_DATA_LEN)) {
    data16[0] = (data[0]) | (data[1] << 8);  // ps_data
    data16[1] = (data[2]) | (data[3] << 8);  // als_data0
    data16[2] = (data[4]) | (data[5] << 8);  // als_data1
    return true;
  } else {
    LOG_D(TAG, "Read error.\n\r");
    return false;
  }
}

void RPR0521Sensor::setup() {
  this->set_i2c_address(0x38);
  initial_setup();
}

void RPR0521Sensor::loop() {}

void RPR0521Sensor::update() {}

}  // namespace rpr0521
}  // namespace esphome
