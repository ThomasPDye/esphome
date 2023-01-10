import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_ID,
    CONF_TIMEOUT,
    CONF_INTERRUPT_PIN,
)
from esphome import pins

DEPENDENCIES = ["i2c"]

rpr0521_ns = cg.esphome_ns.namespace("rpr0521")
RPR0521Sensor = rpr0521_ns.class_(
    "RPR0521Sensor", sensor.Sensor, cg.PollingComponent, i2c.I2CDevice
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
        {
            cv.Required("proximity"): sensor.sensor_schema(),
            cv.Required("ambient"): sensor.sensor_schema(),
        }
    )
    .extend(
        {
            cv.Optional(CONF_TIMEOUT, default="100ms"): check_timeout,
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
    confpx = config["proximity"]
    confamb = config["ambient"]
    px = cg.Pvariable(confpx[CONF_ID], var.proximity_sensor)
    amb = cg.Pvariable(confamb[CONF_ID], var.ambient_light_sensor)
    await sensor.register_sensor(px, confpx)
    await sensor.register_sensor(amb, confamb)

    if CONF_INTERRUPT_PIN in config:
        interrupt = await cg.gpio_pin_expression(config[CONF_INTERRUPT_PIN])
        cg.add(var.set_interrupt_pin(interrupt))

    await i2c.register_i2c_device(var, config)
