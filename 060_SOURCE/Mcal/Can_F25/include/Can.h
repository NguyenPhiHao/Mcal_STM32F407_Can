/*------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Can.h                                                                             |
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
| File        | Can.h                                                                             |
| Module      | CAN                                                                               |
| Version     | 1.00.00                                                                           |
| Contents    | This module provides services for initiating transmissions and calls the callback |
|             | functions of the CanIf module for notifying events, independently from            |
|             | the hardware. Also it provides services to control the behavior and state         |
|             | of the CAN controllers that belong to the same CAN Hardware Unit.                 |
|-------------------------------------------------------------------------------------------------|
| AUTHOR IDENTITY                                                                                 |
|-------------------------------------------------------------------------------------------------|
| Author      | HaoNP                                                                             |
| Company     | H-Car Autosar Technology Inc.                                                     |
| Note        | --                                                                                |
|-------------------------------------------------------------------------------------------------|
| REVISION CONTROL HISTORY                                                                        |
|-------------------------------------------------------------------------------------------------|
| V1.00.00 | 01/01/2025 | HaoNP    | [CAN-ID-001] Initial Version.                                |
|                                  |                                                              |
|------------------------------------------------------------------------------------------------*/

#ifndef CAN_H
#define CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                        |
|------------------------------------------------------------------------------------------------*/
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
 
/*------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|------------------------------------------------------------------------------------------------*/

/*---------------ComStack_Types.h--------------------------------------------------*/

/* Check if current file and ComStack_Types.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION    != COMSTACKTYPE_AR_RELEASE_MAJOR_VERSION)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION    != COMSTACKTYPE_AR_RELEASE_MINOR_VERSION))
    #error "AUTOSAR Version Numbers of Can.h and ComStack_Types.h are different"
#endif      /* End of Autosar Version check */


/*--------------------------------------Can_Types.h-----------------------------------------------|
|------------------------------------------------------------------------------------------------*/
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
#if ((CAN_VENDOR_ID    != CAN_70_VENDOR_ID_CFG_H))
    #error "VENDOR ID for Can.h and Can_Cfg.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID    != CAN_70_MODULE_ID_CFG_H))
    #error "MODULE ID for Can.h and Can_Cfg.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_Cfg.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION    != CAN_70_SW_MAJOR_VERSION_CFG_H) ||\
     (CAN_SW_MINOR_VERSION    != CAN_70_SW_MINOR_VERSION_CFG_H) ||\
     (CAN_SW_PATCH_VERSION    != CAN_70_SW_PATCH_VERSION_CFG_H))
    #error "Software Version Numbers of Can.h and Can_Cfg.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_Cfg.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION    != CAN_70_AR_RELEASE_MAJOR_VERSION_CFG_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION    != CAN_70_AR_RELEASE_MINOR_VERSION_CFG_H)   ||\
     (CAN_AR_RELEASE_REVISION_VERSION != CAN_70_AR_RELEASE_REVISION_VERSION_CFG_H))
    #error "AUTOSAR Version Numbers of Can.h and Can_Cfg.h are different"
#endif      /* End of Autosar Version check */



/*---------------Can_70_RL78F2X.h--------------------------------------------------*/

/* Check if current file and Can_70_RL78F2X.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID    != CAN_70_VENDOR_ID_RL78F2X_H))
    #error "VENDOR ID for Can.h and Can_70_RL78F2X.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID    != CAN_70_MODULE_ID_RL78F2X_H))
    #error "MODULE ID for Can.h and Can_70_RL78F2X.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_70_RL78F2X.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION    != CAN_70_SW_MAJOR_VERSION_RL78F2X_H) ||\
     (CAN_SW_MINOR_VERSION    != CAN_70_SW_MINOR_VERSION_RL78F2X_H) ||\
     (CAN_SW_PATCH_VERSION    != CAN_70_SW_PATCH_VERSION_RL78F2X_H))
    #error "Software Version Numbers of Can.h and Can_70_RL78F2X.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_70_RL78F2X.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION    != CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION    != CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_H)   ||\
     (CAN_AR_RELEASE_REVISION_VERSION != CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_H))
    #error "AUTOSAR Version Numbers of Can.h and Can_70_RL78F2X.h are different"
#endif      /* End of Autosar Version check */

/*---------------Can_70_HW.h--------------------------------------------------*/

/* Check if current file and Can_70_HW.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID    != CAN_70_VENDOR_ID_HW_H))
    #error "VENDOR ID for Can.h and Can_70_HW.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID    != CAN_70_MODULE_ID_HW_H))
    #error "MODULE ID for Can.h and Can_70_HW.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_70_HW.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION    != CAN_70_SW_MAJOR_VERSION_HW_H) ||\
     (CAN_SW_MINOR_VERSION    != CAN_70_SW_MINOR_VERSION_HW_H) ||\
     (CAN_SW_PATCH_VERSION    != CAN_70_SW_PATCH_VERSION_HW_H))
    #error "Software Version Numbers of Can.h and Can_70_HW.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_70_HW.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION    != CAN_70_AR_RELEASE_MAJOR_VERSION_HW_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION    != CAN_70_AR_RELEASE_MINOR_VERSION_HW_H)   ||\
     (CAN_AR_RELEASE_REVISION_VERSION != CAN_70_AR_RELEASE_REVISION_VERSION_HW_H))
    #error "AUTOSAR Version Numbers of Can.h and Can_70_HW.h are different"
#endif      /* End of Autosar Version check */

/* Can.h version check end */

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/

/* API service IDs */
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

/* Development Errors */
/* [SWS_Can_91019] */
#define CAN_E_PARAM_POINTER                   ( ( uint8 )0x01U )
#define CAN_E_PARAM_HANDLE                    ( ( uint8 )0x02U )
#define CAN_E_PARAM_DATA_LENGTH               ( ( uint8 )0x03U )
#define CAN_E_PARAM_CONTROLLER                ( ( uint8 )0x04U )
#define CAN_E_UNINIT                          ( ( uint8 )0x05U )
#define CAN_E_TRANSITION                      ( ( uint8 )0x06U )
#define CAN_E_PARAM_BAUDRATE                  ( ( uint8 )0x07U )
#define CAN_E_INIT_FAILED                     ( ( uint8 )0x09U )
#define CAN_E_PARAM_LPDU                      ( ( uint8 )0x0AU )

/* Runtime Errors */
/* [SWS_Can_91020] */
#define CAN_E_DATALOST                        ( ( uint8 )0x01U )

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* external variables                                                         */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

extern uint8_least                          Can_70_IndxexRxHwObj[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_RXFIFO_MAX ];

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
/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_CODE_LOCAL
#include "Can_MemMap.h"

extern void Can_Init( const Can_ConfigType* Config );

#if ( ( CAN_70_TX_POLLING_PROCESSING == TRUE ) || ( CAN_70_TX_MIXED_PROCESSING == TRUE ) )
extern void Can_MainFunction_Write( void );
#endif  /* #if ( ( CAN_70_TX_POLLING_PROCESSING == TRUE ) || ( CAN_70_TX_MIXED_PROCESSING == TRUE ) ) */

extern Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition );
extern void Can_DisableControllerInterrupts( uint8 Controller );
extern void Can_EnableControllerInterrupts( uint8 Controller );
extern Std_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType* PduInfo );
extern void Can_GetVersionInfo( Std_VersionInfoType* versioninfo );

#if ( ( CAN_70_RX_POLLING_PROCESSING == TRUE ) || ( CAN_70_RX_MIXED_PROCESSING == TRUE ) )
extern void Can_MainFunction_Read( void );
#endif /* #if ( ( CAN_70_RX_POLLING_PROCESSING == TRUE ) || ( CAN_70_RX_MIXED_PROCESSING == TRUE ) ) */

#if ( CAN_70_BUSOFF_POLLING_PROCESSING == TRUE )
extern void Can_MainFunction_BusOff( void );
#endif  /* #if ( CAN_70_BUSOFF_POLLING_PROCESSING == TRUE ) */

extern void Can_MainFunction_Wakeup( void );
extern void Can_DeInit( void );
extern Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr );
extern Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType* ControllerModePtr );

#if ( CAN_70_WAKEUP_SUPPORT == TRUE )
extern Std_ReturnType Can_CheckWakeup( uint8 Controller );
#endif  /* #if ( CAN_70_WAKEUP_SUPPORT == TRUE ) */

extern void Can_MainFunction_Mode( void );
extern Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
extern Std_ReturnType Can_GetControllerRxErrorCounter( uint8 ControllerId, uint8* RxErrorCounterPtr );
extern Std_ReturnType Can_GetControllerTxErrorCounter( uint8 ControllerId, uint8* TxErrorCounterPtr );
extern Std_ReturnType Can_GetCurrentTime( uint8 ControllerId, Can_TimeStampType* timeStampPtr );
extern void Can_EnableEgressTimeStamp( Can_HwHandleType Hth );
extern Std_ReturnType Can_GetEgressTimeStamp( PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType* timeStampPtr );
extern Std_ReturnType Can_GetIngressTimeStamp( Can_HwHandleType Hrh, Can_TimeStampType* timeStampPtr );

#define CAN_STOP_SEC_CODE_LOCAL
#include "Can_MemMap.h"

#endif  /* #ifndef CAN_H */
/* EOF Can.h ****************************************************************/
