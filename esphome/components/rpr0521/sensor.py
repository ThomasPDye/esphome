import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    STATE_CLASS_MEASUREMENT,
    UNIT_METER,
    CONF_TIMEOUT,
    CONF_INTERRUPT_PIN,
)
from esphome import pins

DEPENDENCIES = ["i2c"]

rpr0521_ns = cg.esphome_ns.namespace("rpr0521")
RPR0521Sensor = rpr0521_ns.class_(
    "RPR0521Sensor", sensor.Sensor, cg.PollingComponent, i2c.I2CDevice
)

RPR0521Sensor_proximity = RPR0521Sensor.class_("proximity_sensor", sensor.Sensor)
RPR0521Sensor_ambient_light = RPR0521Sensor.class_(
    "ambient_light_sensor", sensor.Sensor
)


def check_keys(obj):
    return obj


def check_timeout(value):
    value = cv.positive_time_period_microseconds(value)
    if value.total_seconds > 60:
        raise cv.Invalid("Maximum timeout can not be greater then 60 seconds")
    return value


CONFIG_SCHEMA = cv.All(
    sensor.sensor_schema(RPR0521Sensor)
    .extend(
        sensor.sensor_schema(
            RPR0521Sensor_proximity,
            unit_of_measurement=UNIT_METER,
            accuracy_decimals=3,
            state_class=STATE_CLASS_MEASUREMENT,
        )
    )
    .extend(
        sensor.sensor_schema(
            RPR0521Sensor_ambient_light,
            unit_of_measurement=UNIT_METER,
            accuracy_decimals=3,
            state_class=STATE_CLASS_MEASUREMENT,
        )
    )
    .extend(
        {
            cv.Optional(CONF_TIMEOUT, default="1000ms"): check_timeout,
            cv.Optional(CONF_INTERRUPT_PIN): pins.gpio_input_pin_schema,
        }
    )
    .extend(cv.polling_component_schema("100ms"))
    .extend(i2c.i2c_device_schema(0x38)),
    check_keys,
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    cg.add(var.set_timeout_us(config[CONF_TIMEOUT]))

    if CONF_INTERRUPT_PIN in config:
        interrupt = await cg.gpio_pin_expression(config[CONF_INTERRUPT_PIN])
        cg.add(var.set_interrupt_pin(interrupt))

    await i2c.register_i2c_device(var, config)
