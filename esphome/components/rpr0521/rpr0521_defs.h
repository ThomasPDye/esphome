#pragma once

namespace esphome {
namespace rpr0521 {
/* registers */
static const uint8_t RPR0521_REGISTER_DUMP_START = 0x40;
static const uint8_t RPR0521_SYSTEM_CONTROL = 0x40;
static const uint8_t RPR0521_MODE_CONTROL = 0x41;
static const uint8_t RPR0521_ALS_PS_CONTROL = 0x42;
static const uint8_t RPR0521_PS_CONTROL = 0x43;
// low 8bit
static const uint8_t RPR0521_PS_DATA_LSBS = 0x44;
// high 4bit
static const uint8_t RPR0521_PS_DATA_MSBS = 0x45;
// low 8bit
static const uint8_t RPR0521_ALS_DATA0_LSBS = 0x46;
// high 8bit
static const uint8_t RPR0521_ALS_DATA0_MSBS = 0x47;
// low 8bit
static const uint8_t RPR0521_ALS_DATA1_LSBS = 0x48;
// high 8bit
static const uint8_t RPR0521_ALS_DATA1_MSBS = 0x49;
static const uint8_t RPR0521_INTERRUPT = 0x4A;
// low 8bit
static const uint8_t RPR0521_PS_TH_LSBS = 0x4B;
// high 4bit
static const uint8_t RPR0521_PS_TH_MSBS = 0x4C;
// low 8bit
static const uint8_t RPR0521_PS_TL_LSBS = 0x4D;
// high 4bit
static const uint8_t RPR0521_PS_TL_MSBS = 0x4E;
// low 8bit
static const uint8_t RPR0521_ALS_DATA0_TH_LSBS = 0x4F;
// high 8bit
static const uint8_t RPR0521_ALS_DATA0_TH_MSBS = 0x50;
// low 8bit
static const uint8_t RPR0521_ALS_DATA0_TL_LSBS = 0x51;
// high 8bit
static const uint8_t RPR0521_ALS_DATA0_TL_MSBS = 0x52;
// low 8bit
static const uint8_t RPR0521_PS_OFFSET_LSBS = 0x53;
// high 2bit
static const uint8_t RPR0521_PS_OFFSET_MSBS = 0x54;
static const uint8_t RPR0521_MANUFACT = 0x92;
static const uint8_t RPR0521_MANUFACT_VALUE = 0xE0;
static const uint8_t RPR0521_REGISTER_DUMP_END = 0x54;
/* registers bits */
static const uint8_t RPR0521_SYSTEM_CONTROL_SW_RESET_NOT_STARTED = (0x00 << 7);
static const uint8_t RPR0521_SYSTEM_CONTROL_SW_RESET_START = (0x01 << 7);
static const uint8_t RPR0521_SYSTEM_CONTROL_INT_PIN_NO_INIT = (0x00 << 6);
static const uint8_t RPR0521_SYSTEM_CONTROL_INT_PIN_HI_Z = (0x01 << 6);
static const uint8_t RPR0521_SYSTEM_CONTROL_PART_ID = (0x0A << 0);
static const uint8_t RPR0521_MODE_CONTROL_ALS_EN_FALSE = (0x00 << 7);
static const uint8_t RPR0521_MODE_CONTROL_ALS_EN_TRUE = (0x01 << 7);
static const uint8_t RPR0521_MODE_CONTROL_PS_EN_FALSE = (0x00 << 6);
static const uint8_t RPR0521_MODE_CONTROL_PS_EN_TRUE = (0x01 << 6);
static const uint8_t RPR0521_MODE_CONTROL_PS_PULSE_200US = (0x00 << 5);
static const uint8_t RPR0521_MODE_CONTROL_PS_PULSE_330US = (0x01 << 5);
static const uint8_t RPR0521_MODE_CONTROL_PS_OPERATING_MODE_NORMAL = (0x00 << 4);
static const uint8_t RPR0521_MODE_CONTROL_PS_OPERATING_MODE_DOUBLE_MEASUREMENT = (0x01 << 4);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_OFF_OFF = (0x00 << 0);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_OFF_10MS = (0x01 << 0);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_OFF_40MS = (0x02 << 0);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_OFF_100MS = (0x03 << 0);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_OFF_400MS = (0x04 << 0);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_100MS_50MS = (0x05 << 0);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_100MS_100MS = (0x06 << 0);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_100MS_400MS = (0x07 << 0);
// ALS measurement time is 100ms, sleep time is 300ms
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_400MS_50MS = (0x08 << 0);
// ALS measurement time is 100ms, sleep time is 300ms
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_400MS_100MS = (0x09 << 0);
// Measurement time 400ms, high sensitivity mode.
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_400MS_OFF = (0x0A << 0);
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_400MS_400MS = (0x0B << 0);
// Additional sw process is necessary. Check P.18
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_50MS_50MS = (0x0C << 0);
static const uint8_t RPR0521_ALS_PS_CONTROL_RESERVED67_WRITE_00 = (0x00 << 6);
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA0_GAIN_X1 = (0x00 << 4);
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA0_GAIN_X2 = (0x01 << 4);
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA0_GAIN_X64 = (0x02 << 4);
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA0_GAIN_X128 = (0x03 << 4);
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA1_GAIN_X1 = (0x00 << 2);
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA1_GAIN_X2 = (0x01 << 2);
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA1_GAIN_X64 = (0x02 << 2);
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA1_GAIN_X128 = (0x03 << 2);
static const uint8_t RPR0521_ALS_PS_CONTROL_LED_CURRENT_25MA = (0x00 << 0);
static const uint8_t RPR0521_ALS_PS_CONTROL_LED_CURRENT_50MA = (0x01 << 0);
static const uint8_t RPR0521_ALS_PS_CONTROL_LED_CURRENT_100MA = (0x02 << 0);
static const uint8_t RPR0521_ALS_PS_CONTROL_LED_CURRENT_200MA = (0x03 << 0);
static const uint8_t RPR0521_PS_CONTROL_AMBIENT_IR_FLAG_LOW = (0x00 << 6);
static const uint8_t RPR0521_PS_CONTROL_AMBIENT_IR_FLAG_HIGH = (0x01 << 6);
static const uint8_t RPR0521_PS_CONTROL_AMBIENT_IR_FLAG_TOO_HIGH = (0x02 << 6);
static const uint8_t RPR0521_PS_CONTROL_PS_GAIN_X1 = (0x00 << 4);
static const uint8_t RPR0521_PS_CONTROL_PS_GAIN_X2 = (0x01 << 4);
static const uint8_t RPR0521_PS_CONTROL_PS_GAIN_X4 = (0x02 << 4);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_DRDY = (0x00 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_1 = (0x01 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_2 = (0x02 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_3 = (0x03 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_4 = (0x04 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_5 = (0x05 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_6 = (0x06 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_7 = (0x07 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_8 = (0x08 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_9 = (0x09 << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_10 = (0x0A << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_11 = (0x0B << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_12 = (0x0C << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_13 = (0x0D << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_14 = (0x0E << 0);
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_CONSECUTIVE_15 = (0x0F << 0);
static const uint8_t RPR0521_INTERRUPT_PS_INT_STATUS_INACTIVE = (0x00 << 7);
static const uint8_t RPR0521_INTERRUPT_PS_INT_STATUS_ACTIVE = (0x01 << 7);
static const uint8_t RPR0521_INTERRUPT_ALS_INT_STATUS_INACTIVE = (0x00 << 6);
static const uint8_t RPR0521_INTERRUPT_ALS_INT_STATUS_ACTIVE = (0x01 << 6);
static const uint8_t RPR0521_INTERRUPT_INT_MODE_PS_TH_H_ACTIVE = (0x00 << 4);
static const uint8_t RPR0521_INTERRUPT_INT_MODE_PS_TH_HYSTERESIS = (0x01 << 4);
static const uint8_t RPR0521_INTERRUPT_INT_MODE_PS_TH_OUTSIDE_DETECTION = (0x02 << 4);
static const uint8_t RPR0521_INTERRUPT_INT_ASSERT_STABLE = (0x00 << 3);
static const uint8_t RPR0521_INTERRUPT_INT_ASSERT_REINT = (0x01 << 3);
static const uint8_t RPR0521_INTERRUPT_INT_LATCH_ENABLED = (0x00 << 2);
static const uint8_t RPR0521_INTERRUPT_INT_LATCH_DISABLED = (0x01 << 2);
static const uint8_t RPR0521_INTERRUPT_INT_TRIG_INACTIVE = (0x00 << 0);
static const uint8_t RPR0521_INTERRUPT_INT_TRIG_BY_PS = (0x01 << 0);
static const uint8_t RPR0521_INTERRUPT_INT_TRIG_BY_ALS = (0x02 << 0);
static const uint8_t RPR0521_INTERRUPT_INT_TRIG_BY_BOTH = (0x03 << 0);
static const uint8_t RPR0521_MANUFACT_ID_E0H = (0xE0 << 0);
/*registers bit masks */
static const uint8_t RPR0521_SYSTEM_CONTROL_SW_RESET_MASK = 0x80;
static const uint8_t RPR0521_SYSTEM_CONTROL_INT_PIN_MASK = 0x40;
static const uint8_t RPR0521_SYSTEM_CONTROL_PART_MASK = 0x3F;
static const uint8_t RPR0521_MODE_CONTROL_ALS_EN_MASK = 0x80;
static const uint8_t RPR0521_MODE_CONTROL_PS_EN_MASK = 0x40;
static const uint8_t RPR0521_MODE_CONTROL_PS_PULSE_MASK = 0x20;
static const uint8_t RPR0521_MODE_CONTROL_PS_OPERATING_MODE_MASK = 0x10;
static const uint8_t RPR0521_MODE_CONTROL_MEASUREMENT_TIME_MASK = 0x0F;

static const uint8_t RPR0521_ALS_PS_CONTROL_RESERVED67_MASK = 0xC0;
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA0_GAIN_MASK = 0x30;
static const uint8_t RPR0521_ALS_PS_CONTROL_ALS_DATA1_GAIN_MASK = 0x0C;
static const uint8_t RPR0521_ALS_PS_CONTROL_LED_CURRENT_MASK = 0x03;
static const uint8_t RPR0521_PS_CONTROL_AMBIENT_IR_FLAG_MASK = 0xC0;
static const uint8_t RPR0521_PS_CONTROL_PS_GAIN_MASK = 0x30;
static const uint8_t RPR0521_PS_CONTROL_PERSISTENCE_MASK = 0x0F;
static const uint8_t RPR0521_INTERRUPT_PS_INT_STATUS_MASK = 0x80;
static const uint8_t RPR0521_INTERRUPT_ALS_INT_STATUS_MASK = 0x40;
static const uint8_t RPR0521_INTERRUPT_INT_MODE_MASK = 0x30;
static const uint8_t RPR0521_INTERRUPT_INT_ASSERT_MASK = 0x08;
static const uint8_t RPR0521_INTERRUPT_INT_LATCH_MASK = 0x04;
static const uint8_t RPR0521_INTERRUPT_INT_TRIG_MASK = 0x03;
static const uint8_t RPR0521_MANUFACT_ID_MASK = 0xFF;
}  // namespace rpr0521
}  // namespace esphome
