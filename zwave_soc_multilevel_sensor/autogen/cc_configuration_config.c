/*******************************************************************************
 * @file
 * Command Class Configuration Parameter
 * @remarks This file is auto generated
 * @copyright 2022 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
// -----------------------------------------------------------------------------
//                   Includes
// -----------------------------------------------------------------------------
#include <string.h>
#include <stdbool.h>
#include <ZW_typedefs.h>
#include <SizeOf.h>
#include <ZAF_file_ids.h>
#include <CC_Configuration.h>
#include <cc_configuration_config_api.h>

// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------
#define ZAF_FILE_ID_CC_CONFIGURATION_WITH_OFFSET(x) (ZAF_FILE_ID_CC_CONFIGURATION_BASE + x)

// -----------------------------------------------------------------------------
//                Static Variables
// -----------------------------------------------------------------------------

/*
 * This array must be sorted by "number". The Z-Wave Command Class Configurator (Z3C) will sort
 * the array, but if modified manually after generation, make sure to keep it sorted by "number".
 */
static const cc_config_parameter_metadata_t parameter_pool[] = {
  {
    .number            = 1,
    .next_number       = 2,
    .file_id           = ZAF_FILE_ID_CC_CONFIGURATION_WITH_OFFSET(0),
    .migration_handler = NULL,

    .attributes = {
      .name = "Minimum temperature limit",
      .info = "Minimum temperature limit celsius",
      .format = CC_CONFIG_PARAMETER_FORMAT_SIGNED_INTEGER,
      .size = CC_CONFIG_PARAMETER_SIZE_32_BIT,
      .min_value.as_int32 = -100,
      .max_value.as_int32 = 50,
      .default_value.as_int32 = 10,
      .flags.read_only = 0,
      .flags.altering_capabilities = 0,
      .flags.advanced = 0,
    },
  },
  {
    .number            = 2,
    .next_number       = 0,
    .file_id           = ZAF_FILE_ID_CC_CONFIGURATION_WITH_OFFSET(1),
    .migration_handler = NULL,

    .attributes = {
      .name = "Maximum temperature limit",
      .info = "Maximum temperature limit celsius",
      .format = CC_CONFIG_PARAMETER_FORMAT_SIGNED_INTEGER,
      .size = CC_CONFIG_PARAMETER_SIZE_32_BIT,
      .min_value.as_int32 = 10,
      .max_value.as_int32 = 100,
      .default_value.as_int32 = 35,
      .flags.read_only = 0,
      .flags.altering_capabilities = 0,
      .flags.advanced = 0,
    },
  },
};

static const cc_configuration_t default_configuration = {
  .numberOfParameters = sizeof_array(parameter_pool),
  .parameters         = parameter_pool
};

// -----------------------------------------------------------------------------
//              Public Function Definitions
// -----------------------------------------------------------------------------

cc_configuration_t const*
cc_configuration_get_configuration(void)
{
  return &default_configuration;
}
// -----------------------------------------------------------------------------
//              Static Function Definitions
// -----------------------------------------------------------------------------
