/**
 * @file
 * Command Class Color Switch Configuration
 * @remarks This file is auto generated
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include <cc_multilevel_sensor_config.h>

#include <cc_multilevel_sensor_config_api.h>
#include <CC_MultilevelSensor_SensorHandler.h>
#include <CC_MultilevelSensor_SensorHandlerTypes.h>
#include <ZW_typedefs.h>

#define MULTILEVEL_SENSORS_NUM       (6)

static sensor_interface_t cc_multilevel_sensors[MULTILEVEL_SENSORS_NUM] = {
  {
    .endpoint = 0
  },
  {
    .endpoint = 0
  },
  {
    .endpoint = 0
  },
  {
    .endpoint = 0
  },
  {
    .endpoint = 0
  },
  {
    .endpoint = 0
  },
};

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_air_temperature_interface_init(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_air_temperature_interface_deinit(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_air_temperature_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  return false;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_humidity_interface_init(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_humidity_interface_deinit(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_humidity_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  return false;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_ambient_light_interface_init(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_ambient_light_interface_deinit(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_ambient_light_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  return false;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_init(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_deinit(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  return false;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_init(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_deinit(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  return false;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_init(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_deinit(void)
{
  return true;
}

ZW_WEAK bool
cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  return false;
}

void
cc_multilevel_sensor_config_register_instances(void)
{
  cc_multilevel_sensor_init_interface(&cc_multilevel_sensors[0], SENSOR_NAME_AIR_TEMPERATURE);
  cc_multilevel_sensor_add_supported_scale_interface(&cc_multilevel_sensors[0], SENSOR_SCALE_CELSIUS);
  cc_multilevel_sensor_add_supported_scale_interface(&cc_multilevel_sensors[0], SENSOR_SCALE_FAHRENHEIT);
  cc_multilevel_sensors[0].endpoint = 0;
  cc_multilevel_sensors[0].init = cc_multilevel_sensor_endpoint_0_air_temperature_interface_init;
  cc_multilevel_sensors[0].deinit = cc_multilevel_sensor_endpoint_0_air_temperature_interface_deinit;
  cc_multilevel_sensors[0].read_value = cc_multilevel_sensor_endpoint_0_air_temperature_interface_read_value;
  cc_multilevel_sensor_registration(&cc_multilevel_sensors[0]);

  cc_multilevel_sensor_init_interface(&cc_multilevel_sensors[1], SENSOR_NAME_HUMIDITY);
  cc_multilevel_sensor_add_supported_scale_interface(&cc_multilevel_sensors[1], SENSOR_SCALE_PERCENTAGE);
  cc_multilevel_sensors[1].endpoint = 0;
  cc_multilevel_sensors[1].init = cc_multilevel_sensor_endpoint_0_humidity_interface_init;
  cc_multilevel_sensors[1].deinit = cc_multilevel_sensor_endpoint_0_humidity_interface_deinit;
  cc_multilevel_sensors[1].read_value = cc_multilevel_sensor_endpoint_0_humidity_interface_read_value;
  cc_multilevel_sensor_registration(&cc_multilevel_sensors[1]);

  cc_multilevel_sensor_init_interface(&cc_multilevel_sensors[2], SENSOR_NAME_ILLUMINANCE);
  cc_multilevel_sensor_add_supported_scale_interface(&cc_multilevel_sensors[2], SENSOR_SCALE_LUX);
  cc_multilevel_sensors[2].endpoint = 0;
  cc_multilevel_sensors[2].init = cc_multilevel_sensor_endpoint_0_ambient_light_interface_init;
  cc_multilevel_sensors[2].deinit = cc_multilevel_sensor_endpoint_0_ambient_light_interface_deinit;
  cc_multilevel_sensors[2].read_value = cc_multilevel_sensor_endpoint_0_ambient_light_interface_read_value;
  cc_multilevel_sensor_registration(&cc_multilevel_sensors[2]);

  cc_multilevel_sensor_init_interface(&cc_multilevel_sensors[3], SENSOR_NAME_ACCELERATION_X);
  cc_multilevel_sensor_add_supported_scale_interface(&cc_multilevel_sensors[3], SENSOR_SCALE_METER_SQUARE_SECOND);
  cc_multilevel_sensors[3].endpoint = 0;
  cc_multilevel_sensors[3].init = cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_init;
  cc_multilevel_sensors[3].deinit = cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_deinit;
  cc_multilevel_sensors[3].read_value = cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_read_value;
  cc_multilevel_sensor_registration(&cc_multilevel_sensors[3]);

  cc_multilevel_sensor_init_interface(&cc_multilevel_sensors[4], SENSOR_NAME_ACCELERATION_Y);
  cc_multilevel_sensor_add_supported_scale_interface(&cc_multilevel_sensors[4], SENSOR_SCALE_METER_SQUARE_SECOND);
  cc_multilevel_sensors[4].endpoint = 0;
  cc_multilevel_sensors[4].init = cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_init;
  cc_multilevel_sensors[4].deinit = cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_deinit;
  cc_multilevel_sensors[4].read_value = cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_read_value;
  cc_multilevel_sensor_registration(&cc_multilevel_sensors[4]);

  cc_multilevel_sensor_init_interface(&cc_multilevel_sensors[5], SENSOR_NAME_ACCELERATION_Z);
  cc_multilevel_sensor_add_supported_scale_interface(&cc_multilevel_sensors[5], SENSOR_SCALE_METER_SQUARE_SECOND);
  cc_multilevel_sensors[5].endpoint = 0;
  cc_multilevel_sensors[5].init = cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_init;
  cc_multilevel_sensors[5].deinit = cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_deinit;
  cc_multilevel_sensors[5].read_value = cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_read_value;
  cc_multilevel_sensor_registration(&cc_multilevel_sensors[5]);

}

ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_SENSOR_MULTILEVEL, &cc_multilevel_sensors[0], 0);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_SENSOR_MULTILEVEL, &cc_multilevel_sensors[1], 1);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_SENSOR_MULTILEVEL, &cc_multilevel_sensors[2], 2);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_SENSOR_MULTILEVEL, &cc_multilevel_sensors[3], 3);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_SENSOR_MULTILEVEL, &cc_multilevel_sensors[4], 4);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_SENSOR_MULTILEVEL, &cc_multilevel_sensors[5], 5);
