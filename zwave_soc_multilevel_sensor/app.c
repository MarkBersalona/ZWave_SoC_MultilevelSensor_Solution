/**
 * Z-Wave Application Multilevel Sensor
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "MfgTokens.h"
#include "zpal_log.h"
#include "ZAF_file_ids.h"
#include "ZAF_nvm_app.h"
#include "ZAF_nvm.h"
#include "AppTimer.h"
#include "ZW_system_startup_api.h"
#include "CC_Battery.h"
#include "CC_MultilevelSensor_Support.h"
#include "ZAF_Common_helper.h"
#include "ZAF_Common_interface.h"
#include "ZAF_network_learn.h"
#include "ZAF_network_management.h"
#include "events.h"
#include "zpal_watchdog.h"
#include "board_indicator.h"
#include "ZAF_ApplicationEvents.h"
#include "zaf_event_distributor_soc.h"
#include "zpal_misc.h"
#include "zaf_protocol_config.h"
#include "ZW_TransportEndpoint.h"
#include "ZAF_PrintAppInfo.h"

#ifdef SL_CATALOG_ZW_CLI_SLEEPING_PRESENT
#include "zw_cli_sleeping.h"
#include "zw_cli_sleeping_config.h"
#endif

#ifdef SL_CATALOG_ZW_PM_TRANSITION_EVENT_PRESENT
#include "app_pm_transition_event.h"
#endif

#include "app_hw.h"
#include <stdio.h>

void ApplicationTask(SApplicationHandles* pAppHandles);

/**
 * @brief See description for function prototype in ZW_basis_api.h.
 */
ZW_APPLICATION_STATUS
ApplicationInit(__attribute__((unused)) zpal_reset_reason_t eResetReason)
{
  SRadioConfig_t* RadioConfig;

  ZPAL_LOG_DEBUG(ZPAL_LOG_APP, "Enabling watchdog\n");
  zpal_watchdog_init();
  zpal_enable_watchdog(true);

  ZPAL_LOG_INFO(ZPAL_LOG_APP, "ApplicationInit eResetReason = %d\n", eResetReason);

  RadioConfig = zaf_get_radio_config();

#ifdef SL_CATALOG_ZW_PM_TRANSITION_EVENT_PRESENT
  // register callback from power manager transitions
  ZW_PmTransitionEventInit();
#endif

  // Read Rf region from MFG_ZWAVE_COUNTRY_FREQ
  zpal_radio_region_t regionMfg;
  ZW_GetMfgTokenDataCountryFreq((void*) &regionMfg);
  if (isRfRegionValid(regionMfg)) {
    RadioConfig->eRegion = regionMfg;
  } else {
    ZW_SetMfgTokenDataCountryRegion((void*) &RadioConfig->eRegion);
  }

  /* Register task function */
  /*************************************************************************************
  * CREATE USER TASKS  -  ZW_ApplicationRegisterTask() and ZW_UserTask_CreateTask()
  *************************************************************************************
  * Register the main APP task function.
  *
  * ATTENTION: This function is the only task that can call ZAF API functions!!!
  * Failure to follow guidelines will result in undefined behavior.
  *
  * Furthermore, this function is the only way to register Event Notification
  * Bit Numbers for associating to given event handlers.
  *
  * ZW_UserTask_CreateTask() can be used to create additional tasks.
  * @see Sensor_MultiThread example for more info.
  *************************************************************************************/
  __attribute__((unused)) bool bWasTaskCreated = ZW_ApplicationRegisterTask(
    ApplicationTask,
    EAPPLICATIONEVENT_ZWRX,
    EAPPLICATIONEVENT_ZWCOMMANDSTATUS,
    zaf_get_protocol_config()
    );
  assert(bWasTaskCreated);

  return(APPLICATION_RUNNING);
}

/**
 * A pointer to this function is passed to ZW_ApplicationRegisterTask() making it the FreeRTOS
 * application task.
 */
void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  uint32_t unhandledEvents = 0;
  zpal_reset_reason_t resetReason;

  ZPAL_LOG_DEBUG(ZPAL_LOG_APP, "Multilevel Sensor Main App/Task started!\n");

  ZAF_Init(xTaskGetCurrentTaskHandle(), pAppHandles);

  ZAF_PrintAppInfo();

  app_hw_init();

  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// TEST MAB 2025.12.29
  /// Display DSK over serial port
  /// (see zw_cli_common.c, cli_get_dsk() for CLI routine for displaying DSK)
  // DSK starts from the 13th byte in the QR code
  #define SL_CLI_COMMON_DSK_START_INDEX   12
  #define SL_CLI_COMMON_DSK_LEN_CHAR      40
  #define SL_CLI_DSK_CHUNK_LEN_CHAR       5
  char qr_code[TOKEN_MFG_ZW_QR_CODE_SIZE];
  char qr_code_print_buffer[TOKEN_MFG_ZW_QR_CODE_SIZE + 7 /*we put - after every 5th char*/];
  char lucIntegerString[10];
  char lucDSKHexString[50];
  char lucNWIHomeIDString[50];
  char lucAuthHomeIDString[50];
  uint16_t luiTempDSKInt;
  uint16_t luiTempNWIHomeIDInt;
  uint16_t luiTempAuthHomeIDInt;

  memset(qr_code, 0, sizeof(qr_code));
  memset(qr_code_print_buffer, 0, sizeof(qr_code_print_buffer));
  memset(lucDSKHexString, 0, sizeof(lucDSKHexString));
  memset(lucNWIHomeIDString, 0, sizeof(lucNWIHomeIDString));
  memset(lucAuthHomeIDString, 0, sizeof(lucAuthHomeIDString));

  ZW_GetMfgTokenData(&qr_code, TOKEN_MFG_ZW_QR_CODE_ID, TOKEN_MFG_ZW_QR_CODE_SIZE);
  ZPAL_LOG_INFO(ZPAL_LOG_APP, "%s: \n", __FUNCTION__);
  ZPAL_LOG_INFO(ZPAL_LOG_APP, "%s:     QR code = %s\n", __FUNCTION__, qr_code);

  for (uint8_t i = SL_CLI_COMMON_DSK_START_INDEX; i < SL_CLI_COMMON_DSK_START_INDEX + SL_CLI_COMMON_DSK_LEN_CHAR; i += 5)
  {
    // Debug display hex value of 5-digit number string
    memset(lucIntegerString, 0, sizeof(lucIntegerString));
    memcpy(lucIntegerString, &qr_code[i], SL_CLI_DSK_CHUNK_LEN_CHAR);
    luiTempDSKInt = atoi(lucIntegerString);
    //ZPAL_LOG_INFO(ZPAL_LOG_APP, "%s: %05d = 0x%04X\n", __FUNCTION__, luiTempDSKInt, luiTempDSKInt);
    strcat(qr_code_print_buffer, lucIntegerString);
    memset(lucIntegerString, 0, sizeof(lucIntegerString));
    snprintf(lucIntegerString, 5, "%04X", luiTempDSKInt); // 4 hex digits plus NULL, apparently...
    strcat(lucDSKHexString, lucIntegerString);

    //if (i < (SL_CLI_COMMON_DSK_START_INDEX + SL_CLI_COMMON_DSK_LEN_CHAR) - SL_CLI_DSK_CHUNK_LEN_CHAR) {
    if (i <= (SL_CLI_COMMON_DSK_START_INDEX + SL_CLI_COMMON_DSK_LEN_CHAR) - SL_CLI_DSK_CHUNK_LEN_CHAR) {
        if (i < (SL_CLI_COMMON_DSK_START_INDEX + SL_CLI_COMMON_DSK_LEN_CHAR) - SL_CLI_DSK_CHUNK_LEN_CHAR)
          {
            strcat(qr_code_print_buffer, "-");
            strcat(lucDSKHexString, "  ");
          }

        // Process NWI HomeID
        if ( i == (SL_CLI_COMMON_DSK_START_INDEX + 4*SL_CLI_DSK_CHUNK_LEN_CHAR) )
          {
            luiTempNWIHomeIDInt = luiTempDSKInt | 0xC000;
            memset(lucIntegerString, 0, sizeof(lucIntegerString));
            snprintf(lucIntegerString, 5, "%04X", luiTempNWIHomeIDInt); // 4 hex digits plus NULL, apparently...
            strcat(lucNWIHomeIDString, lucIntegerString);
            strcat(lucNWIHomeIDString, "  ");
          }
        else if ( i == (SL_CLI_COMMON_DSK_START_INDEX + 5*SL_CLI_DSK_CHUNK_LEN_CHAR) )
          {
            luiTempNWIHomeIDInt = luiTempDSKInt & 0xFFFE;
            memset(lucIntegerString, 0, sizeof(lucIntegerString));
            snprintf(lucIntegerString, 5, "%04X", luiTempNWIHomeIDInt); // 4 hex digits plus NULL, apparently...
            strcat(lucNWIHomeIDString, lucIntegerString);
            strcat(lucNWIHomeIDString, "  ");
          }
        else if ( i == (SL_CLI_COMMON_DSK_START_INDEX + 7*SL_CLI_DSK_CHUNK_LEN_CHAR) )
          {
            //strcat(lucNWIHomeIDString, "....");
            strcat(lucNWIHomeIDString, "    ");
          }
        else
          {
            //strcat(lucNWIHomeIDString, "....  ");
            strcat(lucNWIHomeIDString, "      ");
          }

        // Process Auth HomeID
        if ( i == (SL_CLI_COMMON_DSK_START_INDEX + 6*SL_CLI_DSK_CHUNK_LEN_CHAR) )
          {
            luiTempAuthHomeIDInt = luiTempDSKInt | 0xC000;
            memset(lucIntegerString, 0, sizeof(lucIntegerString));
            snprintf(lucIntegerString, 5, "%04X", luiTempAuthHomeIDInt); // 4 hex digits plus NULL, apparently...
            strcat(lucAuthHomeIDString, lucIntegerString);
            strcat(lucAuthHomeIDString, "  ");
          }
        else if ( i == (SL_CLI_COMMON_DSK_START_INDEX + 7*SL_CLI_DSK_CHUNK_LEN_CHAR) )
          {
            luiTempNWIHomeIDInt = luiTempDSKInt & 0xFFFE;
            memset(lucIntegerString, 0, sizeof(lucIntegerString));
            snprintf(lucIntegerString, 5, "%04X", luiTempNWIHomeIDInt); // 4 hex digits plus NULL, apparently...
            strcat(lucAuthHomeIDString, lucIntegerString);
            strcat(lucAuthHomeIDString, "  ");
          }
        else
          {
            //strcat(lucAuthHomeIDString, "....  ");
            strcat(lucAuthHomeIDString, "      ");
          }
    }
  }

  ZPAL_LOG_INFO(ZPAL_LOG_APP, "%s:   \n", __FUNCTION__);
  ZPAL_LOG_INFO(ZPAL_LOG_APP, "%s:         DSK = %s\n", __FUNCTION__, qr_code_print_buffer);
  ZPAL_LOG_INFO(ZPAL_LOG_APP, "%s:     DSK hex = %s\n", __FUNCTION__, lucDSKHexString);
  ZPAL_LOG_INFO(ZPAL_LOG_APP, "%s:  NWI HomeID = %s\n", __FUNCTION__, lucNWIHomeIDString);
  ZPAL_LOG_INFO(ZPAL_LOG_APP, "%s: Auth HomeID = %s\n", __FUNCTION__, lucAuthHomeIDString);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  resetReason = GetResetReason();

  /* Re-load and process Deep Sleep persistent application timers.
   * NB: Before calling AppTimerDeepSleepPersistentLoadAll here all
   *     application timers must have been been registered with
   *     AppTimerRegister() or AppTimerDeepSleepPersistentRegister().
   *     Essentially it means that all CC handlers must be
   *     initialized first.
   */
  AppTimerDeepSleepPersistentLoadAll(resetReason);

  if (ZPAL_RESET_REASON_DEEP_SLEEP_EXT_INT == resetReason) {
    app_hw_deep_sleep_wakeup_handler();
  }

  /**
   * Set the maximum inclusion request interval for SmartStart.
   * Valid range 0 and 5-99. 0 is default value and corresponds to 512 sec.
   * The range 5-99 corresponds to 640-12672sec in units of 128sec/tick in between.
   */
  ZAF_SetMaxInclusionRequestIntervals(0);

  if (ZPAL_RESET_REASON_DEEP_SLEEP_EXT_INT != resetReason) {
    /* Enter SmartStart*/
    /* Protocol will commence SmartStart only if the node is NOT already included in the network */
    ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);
  }

  ZPAL_LOG_DEBUG(ZPAL_LOG_APP, "IsWakeupCausedByRtccTimeout=%s\n", (IsWakeupCausedByRtccTimeout()) ? "true" : "false");
  ZPAL_LOG_DEBUG(ZPAL_LOG_APP, "CompletedSleepDurationMs   =%u\n", GetCompletedSleepDurationMs());

#ifdef SL_CATALOG_ZW_CLI_SLEEPING_PRESENT
  // Stay awake to allow user to send the prevent sleeping command through the CLI
  if (GetResetReason() == ZPAL_RESET_REASON_PIN) {
    zw_cli_sleeping_util_prevent_sleeping_timeout(ZW_CLI_SLEEPING_WAKEUP_TIME_AFTER_RESET);
  }
#endif

  // Wait for and process events
  ZPAL_LOG_DEBUG(ZPAL_LOG_APP, "Multilevel Sensor Event Distributor Started\n");
  for (;; ) {
    unhandledEvents = zaf_event_distributor_distribute();
    if (0 != unhandledEvents) {
      ZPAL_LOG_DEBUG(ZPAL_LOG_APP, "Unhandled Events: 0x%08lx\n", unhandledEvents);
#ifdef UNIT_TEST
      return;
#endif
    }
  }
}

/**
 * @brief The core state machine of this sample application.
 * @param event The event that triggered the call of zaf_event_distributor_app_event_manager.
 */
void
zaf_event_distributor_app_event_manager(const uint8_t event)
{
  ZPAL_LOG_DEBUG(ZPAL_LOG_APP, "zaf_event_distributor_app_event_manager Ev: 0x%02x\r\n", event);

  switch (event) {
    case EVENT_APP_SEND_BATTERY_LEVEL_AND_SENSOR_REPORT:
      (void) CC_Battery_LevelReport_tx(NULL, ENDPOINT_ROOT, NULL);
      cc_multilevel_sensor_send_sensor_data();
      break;
    default:
      break;
  }

#ifdef SL_CATALOG_ZW_CLI_COMMON_PRESENT
  cli_log_system_events(event);
#endif
}

void
zaf_nvm_app_reset(void)
{
  AppTimerDeepSleepPersistentResetStorage();
}
