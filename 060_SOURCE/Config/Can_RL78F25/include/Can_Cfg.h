/*------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Can_Cfg.h                                                                         |
| Description:|                                                                                   |
|             | Microcontrollers: STM32F407                                                       |
|             | Compiler        : GCC IAR GHS TASKING                                             |
|             | Technical Ref   : AUTOSAR_SWS_CANDriver.pdf (4.4.0)                               |
|-------------------------------------------------------------------------------------------------|
| COPYRIGHT                                                                                       |
|-------------------------------------------------------------------------------------------------|
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|-------------------------------------------------------------------------------------------------|
| FILE DESCRIPTION                                                                                |
|-------------------------------------------------------------------------------------------------|
| File        | Can_Cfg.h                                                                         |
| Module      | CAN                                                                               |
| Version     | 1.00.00                                                                           |
| Contents    | This module provides services for initiating transmissions and calls the          |
|               callback functions of the CanIf module for notifying events, independently from   |
|               the hardware. Also it provides services to control the behavior and state of the  |
|               CAN controllers that belong to the same CAN Hardware Unit.                        |
|-------------------------------------------------------------------------------------------------|
| AUTHOR IDENTITY                                                                                 |
|-------------------------------------------------------------------------------------------------|
| Author      | HaoNP                                                                             |
| Company     | Home Autosar Technology Inc.                                                      |
| Note        | --                                                                                |
|-------------------------------------------------------------------------------------------------|
| REVISION CONTROL HISTORY                                                                        |
|-------------------------------------------------------------------------------------------------|
| V1.00.00 | 01/01/2025 | HaoNP    | [CAN-ID-001] Initial Version.                                |
|                                  |                                                              |
|------------------------------------------------------------------------------------------------*/

#ifndef CAN_CFG_H
#define CAN_CFG_H

/*------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                        |
|------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"

/*------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|------------------------------------------------------------------------------------------------*/
/* Common published information */
#define CAN_VENDOR_ID_CFG_H                           ( 0x0FU )
#define CAN_MODULE_ID_CFG_H                           ( 0x50U )

/* AUTOSAR release version: 4.4.0 */
#define CAN_AR_RELEASE_MAJOR_VERSION_CFG_H            (0x04U)
#define CAN_AR_RELEASE_MINOR_VERSION_CFG_H            (0x04U)
#define CAN_AR_RELEASE_REVISION_VERSION_CFG_H         (0x00U)

/* Software version: 1.0.0 */
#define CAN_SW_MAJOR_VERSION_CFG_H                    (0x01U)
#define CAN_SW_MINOR_VERSION_CFG_H                    (0x00U)
#define CAN_SW_PATCH_VERSION_CFG_H                    (0x00U)

/*------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| MACROS                                                                                          |
|------------------------------------------------------------------------------------------------*/

/* [ECUC_Can_00064] */
#define CAN_DEV_ERROR_DETECT                ( TRUE )

/* [ECUC_Can_00496] */
#define CAN_ENABLE_SECURITY_EVENT_REPORTING ( TRUE )

/* [ECUC_Can_00482] */
#define CAN_SET_BAUDRATE_API                ( TRUE )

/* [ECUC_Can_00106] */
#define CAN_VERSION_INFO_API                ( TRUE )


/* CAN Tx processing */
/* Specify whether the controller is INTERRUPT, POLLING or MIXED */
#define CAN_TX_INTERRUPT_PROCESSING      ( FALSE )
#define CAN_TX_POLLING_PROCESSING        ( TRUE )
#define CAN_TX_MIXED_PROCESSING          ( FALSE )


/* CAN Rx processing */
/* Specify whether the controller is INTERRUPT, POLLING or MIXED */
#define CAN_RX_INTERRUPT_PROCESSING      ( FALSE )
#define CAN_RX_POLLING_PROCESSING        ( TRUE )
#define CAN_RX_MIXED_PROCESSING          ( FALSE )


/* CAN Bus off processing */
/* Specify whether the controller is INTERRUPT or POLLING */
#define CAN_BUSOFF_INTERRUPT_PROCESSING  ( FALSE )
#define CAN_BUSOFF_POLLING_PROCESSING    ( TRUE )


/* CAN Wakeup processing */
/* Specify whether the controller is INTERRUPT or POLLING */
#define CAN_WAKEUP_INTERRUPT_PROCESSING  ( FALSE )
#define CAN_WAKEUP_POLLING_PROCESSING    ( TRUE )


#define CAN_WAKEUP_SUPPORT               ( TRUE )

/* [ECUC_Can_00498] */
#define CAN_GLOBAL_TIME_SUPPORT             ( FALSE )

/* [ECUC_Can_00473] */
#define CAN_USE_CANFD                    ( FALSE )

/* [ECUC_Can_00095] */
#define CAN_MULTIPLEXED_TRANSMISSION        ( FALSE )


/* Use the OS counter function for timeout monitoring. */
#define CAN_USE_OS_COUNTER               ( FALSE )

/* [ECUC_Can_00320] */
#define CAN_INDEX                           ( ( uint8 )0x00U )

/* [ECUC_Can_00355] */
/* This parameter is defined as float in Autosar SWS with unit as seconds.
 * However for ease of calculations unit and value is converted to ms. */
#define CAN_MAINFUNCTION_BUSOFF_PERIOD      ( ( uint8 )10U )   /* Unit:[ms] */

/* [ECUC_Can_00376] */
/* This parameter is defined as float in Autosar SWS with unit as seconds.
 * However for ease of calculations unit and value is converted to ms. */
#define CAN_MAINFUNCTION_MODE_PERIOD        ( ( uint8 )10U )   /* Unit:[ms] */

/* [ECUC_Can_00357] */
/* This parameter is defined as float in Autosar SWS with unit as seconds.
 * However for ease of calculations unit and value is converted to ms. */
#define CAN_MAINFUNCTION_WAKEUP_PERIOD      ( ( uint8 )10U )   /* Unit:[ms] */

/* [ECUC_Can_00113] */
#define CAN_TIMEOUT_DURATION                ( ( uint16_least )1000U )

/* [ECUC_Can_00468] */
#define CAN_NUM_OF_FILTER_MASK           ( 0x01U )

/* [ECUC_Can_00354] */
#define CAN_NUM_OF_CONTROLLER            ( ( uint8 )0x01U )

/* [ECUC_Can_00437] */
#define CAN_NUM_OF_MAIN_FUNCTION_PERIODS ( ( uint8 )1U )

/* [ECUC_Can_00324] */
/* Maximum number of Hardware objects configured */
#define CAN_NUM_OF_HARDWARE_OBJECT       ( ( uint8 )0x2U )

/* [ECUC_Can_00387] */
/* Number of different Baudrates configured */
#define CAN_NUM_OF_BAUDRATE_TABLE        ( ( uint16 )0x1U )

/* [ECUC_Can_00473] */
/* Number of different FD Baudrates configured */
#define CAN_NUM_OF_FD_BAUDRATE_TABLE     ( ( uint16 )0x0U )

/* CanIf-config uses these defines */
#define CanConf_CanController_CanController_0               (0U)    /* CAN0 Controller ID */
#define CanConf_CanHardwareObject_CanHardwareObject_CAN0_RX (0)     /* HrH */
#define CanConf_CanHardwareObject_CanHardwareObject_CAN0_TX (0)     /* HtH */

#define CanConf_CanController_CanController             (0U)    /* CAN Controller ID */
#define CanConf_CanHardwareObject_CanHardwareObject_RX  (0)     /* HrH */
#define CanConf_CanHardwareObject_CanHardwareObject_TX  (0)     /* HtH */

/* CanIf-config uses these defines */
#define CanGeneralSetControllerMode                     Can_SetControllerMode
#define CanGeneralCheckWakeup                           Can_CheckWakeup
#define CanGeneralDisableControllerInterrupts           Can_DisableControllerInterrupts
#define CanGeneralEnableControllerInterrupts            Can_EnableControllerInterrupts
#define CanGeneralWrite                                 Can_Write


#if( CAN_USE_OS_COUNTER == TRUE )
/* Sets the number of tick counters per millisecond. */
#define CAN_TICK_PER_MSEC     ( ( uint16 ) 5U )
#else /* #if( CAN_USE_OS_COUNTER == TRUE ) */
/* Set the number of counters per millisecond. */
#define CAN_COUNT_PER_MSEC    ( ( uint16 )10U )
#endif /* #if( CAN_USE_OS_COUNTER == TRUE ) */

/* Number of PDUs to keep in the egress timestamp buffer. */
#define CAN_NUM_OF_EGRESS     ( ( uint8 )16U )

/* [SWS_Can_00443] */
#define CAN_LPDU_RECEIVE_CALLOUT_FUNCTION   ( ( LPDU_CALLOUT_TYPE )NULL_PTR )

#endif  /* #ifndef CAN_CFG_H */
/* EOF Can_Cfg.h ****************************************************************/
