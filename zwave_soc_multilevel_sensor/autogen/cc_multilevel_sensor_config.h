/**
 * @file
 * Command Class Color Switch Configuration
 * @remarks This file is auto generated
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_MULTILEVEL_SENSOR_CONFIG_API_H
#define CC_MULTILEVEL_SENSOR_CONFIG_API_H

#include <stdint.h>
#include <stdbool.h>
#include <CC_MultilevelSensor_SensorHandlerTypes.h>

bool cc_multilevel_sensor_endpoint_0_air_temperature_interface_init(void);
bool cc_multilevel_sensor_endpoint_0_air_temperature_interface_deinit(void);
bool cc_multilevel_sensor_endpoint_0_air_temperature_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale);
bool cc_multilevel_sensor_endpoint_0_humidity_interface_init(void);
bool cc_multilevel_sensor_endpoint_0_humidity_interface_deinit(void);
bool cc_multilevel_sensor_endpoint_0_humidity_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale);
bool cc_multilevel_sensor_endpoint_0_ambient_light_interface_init(void);
bool cc_multilevel_sensor_endpoint_0_ambient_light_interface_deinit(void);
bool cc_multilevel_sensor_endpoint_0_ambient_light_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale);
bool cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_init(void);
bool cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_deinit(void);
bool cc_multilevel_sensor_endpoint_0_motion_axis_x_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale);
bool cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_init(void);
bool cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_deinit(void);
bool cc_multilevel_sensor_endpoint_0_motion_axis_y_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale);
bool cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_init(void);
bool cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_deinit(void);
bool cc_multilevel_sensor_endpoint_0_motion_axis_z_interface_read_value(__attribute__((unused)) sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale);

#endif /* CC_MULTILEVEL_SENSOR_CONFIG_API_H */
