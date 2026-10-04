/*-------------------------------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                                               |
| File Name   | Can.h                                                                                                      |
| Description:|                                                                                                            |
|             | Microcontrollers: STM32F407                                                                                |
|             | Compiler        : GCC IAR GHS TASKING                                                                      |
|             | Technical Ref   : AUTOSAR_SWS_CANDriver.pdf (4.4.0)                                                        |
|--------------------------------------------------------------------------------------------------------------------------|
| COPYRIGHT                                                                                                                |
|--------------------------------------------------------------------------------------------------------------------------|
|                                                                                                                          |
|                                                                                                                          |
|                                                                                                                          |
|--------------------------------------------------------------------------------------------------------------------------|
| FILE DESCRIPTION                                                                                                         |
|--------------------------------------------------------------------------------------------------------------------------|
| File        | Can.h                                                                                                      |
| Module      | CAN                                                                                                        |
| Version     | 1.00.00                                                                                                    |
| Contents    | This module provides services for initiating transmissions and calls the callback                          |
|             | functions of the CanIf module for notifying events, independently from                                     |
|             | the hardware. Also it provides services to control the behavior and state                                  |
|             | of the CAN controllers that belong to the same CAN Hardware Unit.                                          |
|--------------------------------------------------------------------------------------------------------------------------|
| AUTHOR IDENTITY                                                                                                          |
|--------------------------------------------------------------------------------------------------------------------------|
| Author      | HaoNP                                                                                                      |
| Company     | H-Car Autosar Technology Inc.                                                                              |
| Note        | --                                                                                                         |
|--------------------------------------------------------------------------------------------------------------------------|
| REVISION CONTROL HISTORY                                                                                                 |
|--------------------------------------------------------------------------------------------------------------------------|
| V1.00.00 | 01/01/2025 | HaoNP    | [CAN-ID-001] Initial Version.                                                         |
|                                  |                                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

#ifndef CAN_H
#define CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                                                 |
|-------------------------------------------------------------------------------------------------------------------------*/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Types.h"
#include "Can_Cfg.h"
#include "Can_HW.h"
#include "Can_Externals.h"
#include "QINeS_Lite.h"

#if( CAN_USE_OS_COUNTER == TRUE )
#include "Os.h"
#endif /* #if( CAN_USE_OS_COUNTER == TRUE ) */
 
/*-------------------------------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                                                      |
|-------------------------------------------------------------------------------------------------------------------------*/
/* Common published information */
#define CAN_VENDOR_ID_H                         (0x00U)
#define CAN_MODULE_ID_H                         (0x50U)

/* Software version: 1.0.0 */
#define CAN_SW_MAJOR_VERSION_H                  (0x01U)
#define CAN_SW_MINOR_VERSION_H                  (0x00U)
#define CAN_SW_PATCH_VERSION_H                  (0x00U)

/* AUTOSAR release version: 4.4.0 */
#define CAN_AR_RELEASE_MAJOR_VERSION_H          (0x04U)
#define CAN_AR_RELEASE_MINOR_VERSION_H          (0x04U)
#define CAN_AR_RELEASE_REVISION_VERSION_H       (0x00U)

/*-------------------------------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

/*---------------ComStack_Types.h--------------------------------------------------*/

/* Check if current file and ComStack_Types.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION    != COMSTACKTYPE_AR_RELEASE_MAJOR_VERSION)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION    != COMSTACKTYPE_AR_RELEASE_MINOR_VERSION))
    #error "AUTOSAR Version Numbers of Can.h and ComStack_Types.h are different"
#endif      /* End of Autosar Version check */


/*--------------------------------------Can_Types.h-----------------------------------------------|
|-------------------------------------------------------------------------------------------------------------------------*/
/* Check if current file and Can_Types.h are of the same vendor */
#if (CAN_VENDOR_ID_H != CAN_TYPES_VENDOR_ID_H)
    #error "Can.h and Can_Types.h have different vendor ids"
#endif

/* Check if current file and Can_Types.h are the same Module Id. */
#if (CAN_MODULE_ID_H != CAN_TYPES_MODULE_ID_H)
    #error "Module ID Numbers of Can.h and Can_Types.h are different."
#endif

/* Check if current file and Can_Types.h are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_H != CAN_TYPES_SW_MAJOR_VERSION_H) || \
     (CAN_SW_MINOR_VERSION_H != CAN_TYPES_SW_MINOR_VERSION_H) || \
     (CAN_SW_PATCH_VERSION_H != CAN_TYPES_SW_PATCH_VERSION_H))
    #error "Software Version Numbers of Can.h and Can_Types.h"
#endif

/* Check if current file and Can_Types.h are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_H    != CAN_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_H    != CAN_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_AR_RELEASE_REVISION_VERSION_H != CAN_TYPES_AR_RELEASE_REVISION_VERSION_H))
    #error "AutoSar Version Numbers of Can.h and Can_Types.h"
#endif

/*---------------Can_Cfg.h--------------------------------------------------*/

/* Check if current file and Can_Cfg.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID    != CAN_VENDOR_ID_CFG_H))
    #error "VENDOR ID for Can.h and Can_Cfg.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID    != CAN_MODULE_ID_CFG_H))
    #error "MODULE ID for Can.h and Can_Cfg.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_Cfg.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION    != CAN_SW_MAJOR_VERSION_CFG_H) ||\
     (CAN_SW_MINOR_VERSION    != CAN_SW_MINOR_VERSION_CFG_H) ||\
     (CAN_SW_PATCH_VERSION    != CAN_SW_PATCH_VERSION_CFG_H))
    #error "Software Version Numbers of Can.h and Can_Cfg.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_Cfg.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION    != CAN_AR_RELEASE_MAJOR_VERSION_CFG_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION    != CAN_AR_RELEASE_MINOR_VERSION_CFG_H)   ||\
     (CAN_AR_RELEASE_REVISION_VERSION != CAN_AR_RELEASE_REVISION_VERSION_CFG_H))
    #error "AUTOSAR Version Numbers of Can.h and Can_Cfg.h are different"
#endif      /* End of Autosar Version check */



/*---------------Can_RL78F2X.h--------------------------------------------------*/

/* Check if current file and Can_RL78F2X.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID    != CAN_VENDOR_ID_RL78F2X_H))
    #error "VENDOR ID for Can.h and Can_RL78F2X.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID    != CAN_MODULE_ID_RL78F2X_H))
    #error "MODULE ID for Can.h and Can_RL78F2X.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_RL78F2X.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION    != CAN_SW_MAJOR_VERSION_RL78F2X_H) ||\
     (CAN_SW_MINOR_VERSION    != CAN_SW_MINOR_VERSION_RL78F2X_H) ||\
     (CAN_SW_PATCH_VERSION    != CAN_SW_PATCH_VERSION_RL78F2X_H))
    #error "Software Version Numbers of Can.h and Can_RL78F2X.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_RL78F2X.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION    != CAN_AR_RELEASE_MAJOR_VERSION_RL78F2X_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION    != CAN_AR_RELEASE_MINOR_VERSION_RL78F2X_H)   ||\
     (CAN_AR_RELEASE_REVISION_VERSION != CAN_AR_RELEASE_REVISION_VERSION_RL78F2X_H))
    #error "AUTOSAR Version Numbers of Can.h and Can_RL78F2X.h are different"
#endif      /* End of Autosar Version check */

/*---------------Can_HW.h--------------------------------------------------*/

/* Check if current file and Can_HW.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID    != CAN_VENDOR_ID_HW_H))
    #error "VENDOR ID for Can.h and Can_HW.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID    != CAN_MODULE_ID_HW_H))
    #error "MODULE ID for Can.h and Can_HW.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_HW.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION    != CAN_SW_MAJOR_VERSION_HW_H) ||\
     (CAN_SW_MINOR_VERSION    != CAN_SW_MINOR_VERSION_HW_H) ||\
     (CAN_SW_PATCH_VERSION    != CAN_SW_PATCH_VERSION_HW_H))
    #error "Software Version Numbers of Can.h and Can_HW.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_HW.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION    != CAN_AR_RELEASE_MAJOR_VERSION_HW_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION    != CAN_AR_RELEASE_MINOR_VERSION_HW_H)   ||\
     (CAN_AR_RELEASE_REVISION_VERSION != CAN_AR_RELEASE_REVISION_VERSION_HW_H))
    #error "AUTOSAR Version Numbers of Can.h and Can_HW.h are different"
#endif      /* End of Autosar Version check */

/* Can.h version check end */

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                                             |
|-------------------------------------------------------------------------------------------------------------------------*/

/* API CAN Function Service Identifier */
#define CAN_SID_INIT                          ( ( uint8 )0x00U )
#define CAN_SID_MAINFUNCTION_WRITE            ( ( uint8 )0x01U )
#define CAN_SID_SETCONTROLLERMODE             ( ( uint8 )0x03U )
#define CAN_SID_DISABLECONTROLLERINTERRUPT    ( ( uint8 )0x04U )
#define CAN_SID_ENABLECONTROLLERINTERRUPT     ( ( uint8 )0x05U )
#define CAN_SID_WRITE                         ( ( uint8 )0x06U )
#define CAN_SID_GETVERSIONINFO                ( ( uint8 )0x07U )
#define CAN_SID_MAINFUNCTION_READ             ( ( uint8 )0x08U )
#define CAN_SID_MAINFUNCTION_BUSOFF           ( ( uint8 )0x09U )
#define CAN_SID_MAINFUNCTION_WAKEUP           ( ( uint8 )0x0AU )
#define CAN_SID_DEINIT                        ( ( uint8 )0x10U )
#define CAN_SID_GETCONTROLLERERRORSTATE       ( ( uint8 )0x11U )
#define CAN_SID_GETCONTROLLERMODE             ( ( uint8 )0x12U )
#define CAN_SID_CHECKWAKEUP                   ( ( uint8 )0x0BU )
#define CAN_SID_MAINFUNCTION_MODE             ( ( uint8 )0x0CU )
#define CAN_SID_SETBAUDRATE                   ( ( uint8 )0x0FU )
#define CAN_SID_GETCONTROLLERRXERRORCOUNTER   ( ( uint8 )0x30U )
#define CAN_SID_GETCONTROLLERTXERRORCOUNTER   ( ( uint8 )0x31U )
#define CAN_SID_GETCURRENTTIME                ( ( uint8 )0x32U )
#define CAN_SID_ENABLEEGRESSTIMESTAMP         ( ( uint8 )0x33U )
#define CAN_SID_GETEGRESSTIMESTAMP            ( ( uint8 )0x34U )
#define CAN_SID_GETINGRESSTIMESTAMP           ( ( uint8 )0x35U )

#define CAN_SID_INIT_ID                          ((uint8)0x00U)
#define CAN_SID_SET_CONTROLLER_MODE_ID           ((uint8)0x03U)
#define CAN_SID_DISABLE_CONTROLLER_INTERRUPTS_ID ((uint8)0x04U)
#define CAN_SID_ENABLE_CONTROLLER_INTERRUPTS_ID  ((uint8)0x05U)
#define CAN_SID_WRITE_ID                         ((uint8)0x06U)
#define CAN_SID_GET_VERSION_INFO_ID              ((uint8)0x07U)
#define CAN_SID_MAIN_FUNCTION_READ_ID            ((uint8)0x08U)
#define CAN_SID_CHECK_WAKEUP_ID                  ((uint8)0x0BU)
#define CAN_SID_SET_BAUDRATE_ID                  ((uint8)0x0FU)
#define CAN_SID_DEINIT_ID                        ((uint8)0x10U)
#define CAN_SID_GET_CONTROLLER_ERROR_STATE_ID    ((uint8)0x11U)
#define CAN_SID_GET_CONTROLLER_MODE_ID           ((uint8)0x12U)
#define CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER  ((uint8)0x30U)
#define CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER  ((uint8)0x31U)
#define CAN_SID_GET_CURRENT_TIME                 ((uint8)0x32U)
#define CAN_SID_ENABLE_EGRESS_TIMESTAMP          ((uint8)0x33U)
#define CAN_SID_GET_EGRESS_TIMESTAMP             ((uint8)0x34U)
#define CAN_SID_GET_INGRESS_TIMESTAMP            ((uint8)0x35U)
#define CAN_SID_LOOPBACKTEST_ID                  ((uint8)0x7FU)


/* [SWS_Can_91019] Definition of development errors in module Can. */
#if (STD_ON == CAN_DEV_ERROR_DETECT)
#define CAN_E_PARAM_POINTER                  ((uint8)0x01U) /* API Service called with wrong parameter */
#define CAN_E_PARAM_HANDLE                   ((uint8)0x02U) /* API Service called with wrong parameter */
#define CAN_E_PARAM_DATA_LENGTH              ((uint8)0x03U) /* API Service called with wrong parameter */
#define CAN_E_PARAM_CONTROLLER               ((uint8)0x04U) /* API Service called with wrong parameter */
#define CAN_E_UNINIT                         ((uint8)0x05U) /* API Service used without initialization */
#define CAN_E_TRANSITION                     ((uint8)0x06U) /* Invalid transition for the current mode */
#define CAN_E_PARAM_BAUDRATE                 ((uint8)0x07U) /* Parameter Baudrate has an invalid value */
#define CAN_E_INIT_FAILED                    ((uint8)0x09U) /* Invalid configuration set selection     */
#define CAN_E_PARAM_LPDU                     ((uint8)0x0AU) /* API service called with invalid PDU ID  */
#endif /* (STD_ON == CAN_DEV_ERROR_DETECT) */
 
/*-------------------------------------------------------------------------------------------------------------------------|
| EXTERN VARIABLES                                                                                                         |
|-------------------------------------------------------------------------------------------------------------------------*/
#define CAN_START_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

extern uint8_least                          Can_IndxexRxHwObj[ CAN_NUM_OF_CONTROLLER ][ CAN_RL78F2X_RXFIFO_MAX ];

#define CAN_STOP_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

/*----------------------------------------------------------------------------*/
/* global constants                                                           */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Can_MemMap.h"

extern const Can_ConfigType    Can_Config;

#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Can_MemMap.h"

/*-------------------------------------------------------------------------------------------------------------------------|
| GLOBAL FUNCTION                                                                                                          |
|-------------------------------------------------------------------------------------------------------------------------*/
#define CAN_START_SEC_CODE_LOCAL
#include "Can_MemMap.h"

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_INIT_ID (0x00)                                                                                         |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_00223]                                                                                            |
|             |                                                                                                            |
| Name        | Can_Init                                                                                                   |
|             |                                                                                                            |
| Sync/Async  | Synchronous                                                                                                |
|             |                                                                                                            |
| Contents    | This function initializes the Can module.                                                                  |
|             |                                                                                                            |
| Details     | Initializes the CAN module with the provided configuration parameters. This function sets up initial       |
|             | settings for the CAN controller, allocates necessary resources, and prepares the module for operation.     |
|             |                                                                                                            |
| Param [in]  | Config: Pointer to driver configuration.                                                                   |
|             |                                                                                                            |
| Param [out] | None.                                                                                                      |
|             |                                                                                                            |
| Return      | None.                                                                                                      |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
void Can_Init( const Can_ConfigType* Config );




/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | PORT_GET_VERSION_INFO_ID (0x07)                                                                            |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_00224]                                                                                            |
|             |                                                                                                            |
| Name        | Can_GetVersionInfo                                                                                         |
|             |                                                                                                            |
| Sync/Async  | Synchronous                                                                                                |
|             |                                                                                                            |
| Contents    | This function returns the version information of this Can module.                                          |
|             |                                                                                                            |
| Details     | Returns the version information of the CAN module. Typically includes software version, vendor ID, and     |
|             | other relevant details about the implementation.                                                           |
|             |                                                                                                            |
| Param [in]  | Versioninfo: Pointer to where to store the version information of this module.                             |
|             |                                                                                                            |
| Param [out] | None                                                                                                       |
|             |                                                                                                            |
| Return      | None                                                                                                       |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == CAN_VERSION_INFO_API)
void Can_GetVersionInfo( Std_VersionInfoType* Versioninfo );
#endif /* (STD_ON == CAN_VERSION_INFO_API) */


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_DEINIT_ID (0x10)                                                                                       |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_91002]                                                                                            |
|             |                                                                                                            |
| Name        | Can_DeInit                                                                                                 |
|             |                                                                                                            |
| Sync/Async  | Synchronous                                                                                                |
|             |                                                                                                            |
| Contents    | This function de-initializes the Can module.                                                               |
|             |                                                                                                            |
| Details     | De-initializes and releases the CAN module. This function resets the controller to its default state,      |
|             | frees allocated resources, and stops alL CAN-related activities.                                           |
|             |                                                                                                            |
| Param [in]  | None                                                                                                       |
|             |                                                                                                            |
| Param [out] | None                                                                                                       |
|             |                                                                                                            |
| Return      | None                                                                                                       |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
void Can_DeInit( void );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_SET_BAUDRATE_ID (0x0F)                                                                                 |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_00491]                                                                                            |
|             |                                                                                                            |
| Name        | Can_SetBaudrate                                                                                            |
|             |                                                                                                            |
| Sync/Async  | Synchronous                                                                                                |
|             |                                                                                                            |
| Contents    | This service shall set the baud rate configuration of the CAN controller. Depending on necessary baud rate |
|             |  modifications the controller might.                                                                       |
|             |                                                                                                            |
| Details     | Sets or changes the baud rate configuration of the CAN controller. Allows dynamic adjustment of the CAN    |
|             | network communication speed.                                                                               |
|             |                                                                                                            |
|             |                                                                                                            |
| Param [in]  | Controller: CAN controller, whose baud rate shall be set.                                                  |
|             |                                                                                                            |
| Param [in]  | BaudRateConfigID: References a baud rate configuration by ID                                               |
|             |                                                                                                            |
| Return      | Std_ReturnType.                                                                                            |
|             | E_OK: Service request accepted, setting of (new) baud rate started.                                        |
|             | E_NOT_OK: Service request not accepted.                                                                    |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == CAN_SET_BAUDRATE_API)
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
#endif /* STD_ON == CAN_SET_BAUDRATE_API */


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_SET_CONTROLLER_MODE_ID (0x03)                                                                          |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_00230]                                                                                            |
|             |                                                                                                            |
| Name        | Can_SetControllerMode                                                                                      |
|             |                                                                                                            |
| Sync/Async  | Asynchronous                                                                                               |
|             |                                                                                                            |
| Contents    | This function performs software triggered state transitions of the CAN controller  State machine.          |
|             |                                                                                                            |
| Details     | Performs software-triggered state transitions of the CAN controller, such as switching between Start,      |
|             | Stop, or Sleep modes.                                                                                      |
|             |                                                                                                            |
| Param [in]  | Controller: CAN controller for which the status shall be changed.                                          |
|             |                                                                                                            |
| Param [in]  | Transition: Transition value to request new CAN controller state.                                          |
|             |                                                                                                            |
| Return      | Std_ReturnType.                                                                                            |
|             | E_OK: Service request accepted, setting of (new) baud rate started.                                        |
|             | E_NOT_OK: Service request not accepted.                                                                    |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_DISABLE_CONTROLLER_INTERRUPTS_ID (0x04)                                                                |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_00231]                                                                                            |
|             |                                                                                                            |
| Sync/Async  | Synchronous                                                                                                |
|             |                                                                                                            |
| Name        | Can_DisableControllerInterrupts                                                                            |
|             |                                                                                                            |
| Contents    | This function disables all interrupts for this CAN controller.                                             |
|             |                                                                                                            |
| Details     | Disables all interrupts for the specified CAN controller. Used to protect critical operations from being   |
|             |  interrupted.                                                                                              |
|             |                                                                                                            |
| Param [in]  | Controller: CAN controller for which interrupts shall be disabled.                                         |
|             |                                                                                                            |
| Return      | None.                                                                                                      |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
extern void Can_DisableControllerInterrupts( uint8 Controller );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_ENABLE_CONTROLLER_INTERRUPTS_ID (0x05)                                                                 |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_00232]                                                                                            |
|             |                                                                                                            |
| Name        | Can_EnableControllerInterrupts                                                                             |
|             |                                                                                                            |
| Sync/Async  | Synchronous                                                                                                |
|             |                                                                                                            |
| Contents    | This function enables all allowed interrupts.                                                              |
|             |                                                                                                            |
| Details     | Enables all allowed interrupts for the specified CAN controller, allowing the controller to respond to     |
|             | real-time events.                                                                                          |
|             |                                                                                                            |
| Param [in]  | Controller: CAN controller for which interrupts shall be disabled.                                         |
|             |                                                                                                            |
| Return      | None.                                                                                                      |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
extern void Can_EnableControllerInterrupts( uint8 Controller );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_CHECK_WAKEUP_ID (0x0B)                                                                                 |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_00360]                                                                                            |
|             |                                                                                                            |
| Name        | Can_CheckWakeup                                                                                            |
|             |                                                                                                            |
| Sync/Async  | Synchronous                                                                                                |
|             |                                                                                                            |
| Contents    | This function checks if a wakeup has occurred for the given controller.                                    |
|             |                                                                                                            |
| Details     | Checks if a wakeup event has occurred for the given CAN controller, typically to detect external triggers  |
|             | that bring the controller out of Sleep mode.                                                               |
|             |                                                                                                            |
| Param [in]  | Controller: CAN controller for which interrupts shall be disabled.                                         |
|             |                                                                                                            |
| Return      | Std_ReturnType.                                                                                            |
|             | E_OK: API call has been accepted.                                                                          |
|             | E_NOT_OK: API call has not been accepted.                                                                  |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == CAN_WAKEUP_SUPPORT)
Std_ReturnType Can_CheckWakeup( uint8 Controller );
#endif  /* (STD_ON == CAN_WAKEUP_SUPPORT) */


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_GET_CONTROLLER_ERROR_STATE_ID (0x11)                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_91004]                                                                                            |
|             |                                                                                                            |
| Name        | Can_GetControllerErrorState                                                                                |
|             |                                                                                                            |
| Sync/Async  | Synchronous                                                                                                |
|             |                                                                                                            |
| Contents    | This service obtains the error state of the CAN controller.                                                |
|             |                                                                                                            |
| Details     | Obtains the current error state of the CAN controller, including conditions like Bus-off, Error Passive,   |
|             | or Error Warning.                                                                                          | 
|             |                                                                                                            |
| Param [in]  | ControllerId: Abstracted CanIf ControllerId which is assigned to a CAN controller, which is requested for  |
|             |               ErrorState.                                                                                  |
|             |                                                                                                            |
| Param [in]  | ErrorStatePtr: Pointer to a memory location, where the error state of the CAN controller will be stored.   |
|             |                                                                                                            |
| Return      | Std_ReturnType.                                                                                            |
|             | E_OK: Error state request has been accepted.                                                               |
|             | E_NOT_OK:  Error state request has not been accepted.                                                      |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_GET_CONTROLLER_MODE_ID (0x12)                                                                          |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_91014]                                                                   |
|             |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|             |                                                                                   |
| Name        | Can_GetControllerMode                                                             |
|             |                                                                                   |
| Contents    | This service reports about the current status of the requested CAN controller.    |
|             |                                                                                   |
| Details     | Reports the current operating mode of the requested CAN controller, such as       |
|             | Active, Stopped, or Sleeping.                                                     |
|             |                                                                                   |
| Param [in]  | Controller: CAN controller for which interrupts shall be disabled.                |
|             |                                                                                   |
| Param [out] | ControllerModePtr: Pointer to a memory location, where the current mode of the    |
|             | CAN controller will be stored.                                                    |
|             |                                                                                   |
| Return      | Std_ReturnType.                                                                   |
|             | E_OK: Description.                                                                |
|             | E_NOT_OK: Description.                                                            |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType* ControllerModePtr );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_GET_CONTROLLER_RX_ERROR_COUNTER_ID (0x30)                                     |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_00511]                                                                   |
|             |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|             |                                                                                   |
| Name        | Can_GetControllerRxErrorCounter                                                   |
|             |                                                                                   |
| Contents    | Returns the Rx error counter for a CAN controller. This value might not be        |
|             | available for all CAN controllers, in which case E_NOT_OK would be returned.      |
|             |                                                                                   |
| Details     | Returns the value of the receive (Rx) error counter for the CAN controller.       |
|             | Useful for diagnosing problems with data reception. Please note that the value    |
|             | of the counter might not be correct at the moment the API returns it, because     |
|             | the Rx counter is handled asynchronously in hardware. Applications should not     |
|             | trust this value for any assumption about the current bus state.                  |
|             |                                                                                   |
| Param [in]  | ControllerId: CAN controller, whose current Rx error counter shall be acquired.   |
|             |                                                                                   |
| Param [out] | RxErrorCounterPtr: Pointer to a memory location, where the current Rx error       |
|             | counter of the CAN controller will be stored.                                     |
|             |                                                                                   |
| Return      | Std_ReturnType.                                                                   |
|             | E_OK: Rx error counter available.                                                 |
|             | E_NOT_OK: Wrong ControllerId, or Rx error counter not available.                  |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_GetControllerRxErrorCounter( uint8 ControllerId, uint8* RxErrorCounterPtr );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_GET_CONTROLLER_TX_ERROR_COUNTER_ID (0x31)                                     |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_Can_00516]                                                                   |
|             |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|             |                                                                                   |
| Name        | Can_GetControllerTxErrorCounter                                                   |
|             |                                                                                   |
| Contents    | Returns the Tx error counter for a CAN controller. This value might not be        |
|             | available for all CAN controllers, in which case E_NOT_OK would be returned.      |
|             |                                                                                   |
| Details     | Returns the value of the transmit (Tx) error counter for the CAN controller.      |
|             | Helps monitor and analyze transmission issues. Please note that the value of      |
|             | the counter might not be correct at the moment the API returns it, because        |
|             | the Tx counter is handled asynchronously in hardware. Applications should not     |
|             | trust this value for any assumption about the current bus state.                  |
|             |                                                                                   |
| Param [in]  | ControllerId: CAN controller, whose current Rx error counter shall be acquired.   |
|             |                                                                                   |
| Param [out] | TxErrorCounterPtr: Pointer to a memory location, where the current Tx error       |
                counter of the CAN controller will be stored.                                     |
|             |                                                                                   |
| Return      | Std_ReturnType.                                                                   |
|             | E_OK: Tx error counter available.                                                 |
|             | E_NOT_OK: Wrong ControllerId, or Tx error counter not available.                  |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_GetControllerTxErrorCounter( uint8 ControllerId, uint8* TxErrorCounterPtr );


/* Check the Hardware Timestamping function. */
#if ((0x16 == CAN_AR_RELEASE_MAJOR_VERSION_H) && (0x0B == CAN_AR_RELEASE_MINOR_VERSION_H) && (0X00 ==CAN_AR_RELEASE_REVISION_VERSION_H ))
#if (STD_ON == CAN_GLOBAL_TIME_SUPPORT)

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_GET_CURRENT_TIME_ID (0x31)                                                    |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | []                                                                                |
|             |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|             |                                                                                   |
| Name        | Can_GetCurrentTime                                                                |
|             |                                                                                   |
| Contents    | Returns a time value out of the HW registers according to the capability of the HW|
|             |                                                                                   |
| Details     | Retrieves a time value from the hardware registers, often used for timestamping   |
|             | functions within CAN communication. Can_GetCurrentTime may be called within an    |
|             | exclusive area.                                                                   |
|             |                                                                                   |
| Param [in]  | ControllerId: Index of the addresses CAN controller.                              |
|             |                                                                                   |
| Param [out] | timeStampPtr: Current time stamp.                                                 |
|             |                                                                                   |
| Return      | Std_ReturnType.                                                                   |
|             | E_OK: Successful.                                                                 |
|             | E_NOT_OK: Failed.                                                                 |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_GetCurrentTime( uint8 ControllerId, Can_TimeStampType* timeStampPtr );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_ENABLE_EGRESS_TIME_STAMP_ID (0x33)                                            |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_91025]                                                                   |
|             |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|             |                                                                                   |
| Name        | Can_EnableEgressTimeStamp                                                         |
|             |                                                                                   |
| Contents    | Activates egress time stamping on a dedicated HTH.                                |
|             |                                                                                   |
| Details     | Activates egress (transmit) timestamping on a dedicated HTH. Some HW does store   |
|             | once the egress time stamp marker and some HW needs it always before transmission.|
|             | There will be no ""disable"" functionality, due to the fact, that the message     |
|             | type is always ""time stamped"" by network design.                                |
|             |                                                                                   |
| Param [in]  | Hth: The information which HW-transmit handle shall be used for enabling          |
|             |      the time stamp.                                                              |
|             |                                                                                   |
| Return      | None.                                                                             |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
void Can_EnableEgressTimeStamp( Can_HwHandleType Hth );


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_GET_EGRESS_TIME_STAMP_ID (0x34)                                               |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_91027]                                                                   |
|             |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|             |                                                                                   |
| Name        | Can_GetEgressTimeStamp                                                            |
|             |                                                                                   |
| Contents    | Reads back the egress time stamp on a dedicated message object. It needs to be    |
|             | called within the TxConfirmation() function.                                      |
|             |                                                                                   |
| Details     | Reads back the egress timestamp from a dedicated message object, providing the    |
|             | time that a specific message was transmitted.                                     |
|             |                                                                                   |
| Param [in]  | TxPduId: L-PDU handle of CAN L-PDU for which the time stamp shall be returned.    |
|             |                                                                                   |
| Param [in]  | Hth: HW-transmit handle for which the egress timestamp shall be retrieved.        |
|             |                                                                                   |
| Param [out] | timeStampPtr: Current time stamp.                                                 |
|             |                                                                                   |
| Return      | Std_ReturnType.                                                                   |
|             | E_OK: Success.                                                                    |
|             | E_NOT_OK: Failed to read time stamp.                                              |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_GetEgressTimeStamp( PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType* timeStampPtr );



/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_GET_INGRESS_TIME_STAMP_ID (0x35)                                              |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_91028]                                                                   |
|             |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|             |                                                                                   |
| Name        | Can_GetIngressTimeStamp                                                           |
|             |                                                                                   |
| Contents    | Reads back the ingress time stamp on a dedicated message object. It needs to be   |
|             | called within the RxIndication() function.                                        |
|             |                                                                                   |
| Details     | Reads back the ingress (receive) timestamp from a dedicated message object,       |
|             | useful for analyzing message arrival times.                                       |
|             |                                                                                   |
| Param [in]  | Hrh: HW-receive handle for which the ingress timestamp shall be retrieved.        |
|             |                                                                                   |
| Param [out] | timeStampPtr: Current time stamp.                                                 |
|             |                                                                                   |
| Return      | Std_ReturnType.                                                                   |
|             | E_OK: Success.                                                                    |
|             | E_NOT_OK: Failed to read time stamp.                                              |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_GetIngressTimeStamp( Can_HwHandleType Hrh, Can_TimeStampType* timeStampPtr );


#endif /* STD_ON == CAN_GLOBAL_TIME_SUPPORT */
#endif /* Check the Hardware Timestamping function. */


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_WRITE_ID (0x06)                                                               |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_00233]                                                                   |
|             |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|             |                                                                                   |
| Name        | Can_Write                                                                         |
|             |                                                                                   |
| Contents    | This function is called by CanIf to pass a CAN message to CanDrv for transmission.|
|             |                                                                                   |
| Details     | Called by CanIf to pass a CAN message to CanDrv for transmission. Ensures the     |
|             | message is sent through the correct controller and handled appropriately.         |
|             |                                                                                   |
| Param [in]  | Hth: information which HW-transmit handle shall be used for transmit. Implicitly  |
|             | this is also the information about the controller to use because the Hth numbers  |
|             | are unique inside one hardware unit.                                              |
|             |                                                                                   |
| Param [in]  | PduInfo: Pointer to SDU user memory, Data Length and Identifier.                  |
|             |                                                                                   |
| Return      | Std_ReturnType.                                                                   |
|             | E_OK: Write command has been accepted.                                            |
|             | E_NOT_OK: development error occurred.                                             |
|             | CAN_BUSY: No TX hardware buffer available or pre-emptive call of Can_Write that   |
|             |           can't be implemented re-entrant (see Can_ReturnType)                    |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
Std_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType* PduInfo );


// Check lại điều kiện
/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_MAIN_FUNCTION_WRITE_ID (0x01)                                                 |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_00225]                                                                   |
|             |                                                                                   |
| Name        | Can_MainFunction_Write                                                            |
|             |                                                                                   |
| Contents    | This function performs the polling of TX confirmation when CAN_TX_PROCESSING is   |
|             | set to POLLING.                                                                   |
|             |                                                                                   |
| Details     | Performs polling for TX (transmit) confirmation events when CAN_TX_PROCESSING is  |
|             | configured for polling mode. This function checks for completed transmissions     |
|             | and reports them to higher layers.                                                |
|             |                                                                                   |
| Param [in]  | None.                                                                             |
|             |                                                                                   |
| Param [out] | None.                                                                             |
|             |                                                                                   |
| Return      | None.                                                                             |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
// #if ( ( CAN_TX_POLLING_PROCESSING == TRUE ) || ( CAN_TX_MIXED_PROCESSING == TRUE ) )
extern void Can_MainFunction_Write( void );
// #endif  // Check lại điều kiện



// Check lại điều kiện
/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_MAIN_FUNCTION_READ_ID (0x08)                                                  |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_00226]                                                                   |
|             |                                                                                   |
| Name        | Can_MainFunction_Read                                                             |
|             |                                                                                   |
| Contents    | This function performs the polling of RX indications when CAN_RX_PROCESSING is    |
|             | set to POLLING.                                                                   |
|             |                                                                                   |
| Details     | Performs polling for RX (receive) indication events when CAN_RX_PROCESSING is     |
|             | configured for polling. This function scans for received CAN messages and         |
|             | notifies higher layers.                                                           |
|             |                                                                                   |
| Param [in]  | None.                                                                             |
|             |                                                                                   |
| Param [out] | None.                                                                             |
|             |                                                                                   |
| Return      | None.                                                                             |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
// #if ( ( CAN_RX_POLLING_PROCESSING == TRUE ) || ( CAN_RX_MIXED_PROCESSING == TRUE ) )
void Can_MainFunction_Read( void );
// #endif  // Check lại điều kiện



/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_MAIN_FUNCTION_BUS_OFF_ID (0x09)                                               |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_00227]                                                                   |
|             |                                                                                   |
| Name        | Can_MainFunction_BusOff                                                           |
|             |                                                                                   |
| Contents    | This function performs the polling of bus-off events that are configured          |
|             | statically as 'to be polled'.                                                     |
|             |                                                                                   |
| Details     | Performs polling for bus-off events that are statically configured to be polled.  |
|             | This function monitors the CAN controller for bus-off status and handles recovery |
|             | or notification as required.                                                      |
|             |                                                                                   |
| Param [in]  | None.                                                                             |
|             |                                                                                   |
| Param [out] | None.                                                                             |
|             |                                                                                   |
| Return      | None.                                                                             |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
#if ( CAN_BUSOFF_POLLING_PROCESSING == TRUE )
void Can_MainFunction_BusOff( void );
#endif  /* (STD_ON == CAN_BUSOFF_POLLING_PROCESSING) */


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                              |
|             |                                                                                   |
| Service ID  | CAN_MAIN_FUNCTION_WAKEUP_ID (0x0A)                                                |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_00228]                                                                   |
|             |                                                                                   |
| Name        | Can_MainFunction_Wakeup                                                           |
|             |                                                                                   |
| Contents    | This function performs the polling of wake-up events that are configured          |
|             | statically as 'to be polled'.                                                     |
|             |                                                                                   |
| Details     | Performs polling for wake-up events that are statically configured to be polled.  |
|             | This function detects if the CAN controller has been woken up from sleep mode and |
|             | reports the event.                                                                |
|             |                                                                                   |
| Param [in]  | None.                                                                             |
|             |                                                                                   |
| Param [out] | None.                                                                             |
|             |                                                                                   |
| Return      | None.                                                                             |
|             |                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == CAN_WAKEUP_SUPPORT)
void Can_MainFunction_Wakeup( void );
#endif /* STD_ON == CAN_WAKEUP_SUPPORT */


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | CAN_MODULE_ID (0x50)                                                                                       |
|             |                                                                                                            |
| Service ID  | CAN_MAIN_FUNCTION_MODE_ID (0x0C)                                                                           |
|             |                                                                                                            |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID      | [SWS_CAN_00368]                                                                                            |
|             |                                                                                                            |
| Name        | Can_MainFunction_Mode                                                                                      |
|             |                                                                                                            |
| Contents    | This function performs the polling of CAN controller mode transitions.                                     |
|             |                                                                                                            |
| Details     | Performs polling for CAN controller mode transitions. This function checks for changes in the controller's |
|             | operating mode (such as Start, Stop, or Sleep) and notifies upper layers.                                  |
|             |                                                                                                            |
| Param [in]  | None.                                                                                                      |
|             |                                                                                                            |
| Param [out] | None.                                                                                                      |
|             |                                                                                                            |
| Return      | None.                                                                                                      |
|             |                                                                                                            |
|--------------------------------------------------------------------------------------------------------------------------|
| SWS ID:     |                                                                                                            |
|             |                                                                                                            |
|             |                                                                                                            |
| Vender ID:  |                                                                                                            |
|             |                                                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/
extern void Can_MainFunction_Mode( void );

#define CAN_STOP_SEC_CODE_LOCAL
#include "Can_MemMap.h"

#endif  /* #ifndef CAN_H */
/* EOF Can.h ****************************************************************/
