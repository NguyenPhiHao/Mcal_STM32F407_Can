/*-------------------------------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Port.h                                                                            |
| Description:|                                                                                   |
|             | Microcontrollers: STM32F407                                                       |
|             | Compiler        : GCC IAR GHS TASKING                                             |
|             | Technical Ref   : AUTOSAR_SWS_PORTDriver.pdf (4.4.0)                              |
|-------------------------------------------------------------------------------------------------|
| COPYRIGHT                                                                                       |
|-------------------------------------------------------------------------------------------------|
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|-------------------------------------------------------------------------------------------------|
| FILE DESCRIPTION                                                                                |
|-------------------------------------------------------------------------------------------------|
| File        | Port.h                                                                            |
| Module      | PORT                                                                              |
| Version     | 1.00.00                                                                           |
| Contents    | PORT Module header                                                                |
|             | The PORT is a basic software module at the service layer of the standardized      |
|             | basic software architecture of AUTOSAR.                                           |
|-------------------------------------------------------------------------------------------------|
| AUTHOR IDENTITY                                                                                 |
|-------------------------------------------------------------------------------------------------|
| Author      | HaoNP                                                                             |
| Company     | H-Car Autosar Technology Inc.                                                     |
| Note        | --                                                                                |
|-------------------------------------------------------------------------------------------------|
| REVISION CONTROL HISTORY                                                                        |
|-------------------------------------------------------------------------------------------------|
| V1.00.00 | 01/01/2025 | HaoNP    | [PORT-ID-001] Initial Version.                               |
|                                  |                                                              |
|-------------------------------------------------------------------------------------------------------------------------*/

#ifndef PORT_H
#define PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                                                 |
|-------------------------------------------------------------------------------------------------------------------------*/
#include "Port_Ipc.h"
#include "Port_Cfg.h"

/*-------------------------------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                                                      |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| SOURCE VERSION CHECK                                                                            |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                                             |
|-------------------------------------------------------------------------------------------------------------------------*/
#define PORT_INSTANCE_ID                    ( 0x00U )

/* Error Codes Autosar */
#define PORT_E_PARAM_PIN                    ( 0x0AU ) /* Invalid Port Pin ID requested */
#define PORT_E_DIRECTION_UNCHANGEABLE       ( 0x0BU ) /* Port Pin not configured as changeable */
#define PORT_E_INIT_FAILED                  ( 0x0CU ) /* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_INVALID_MODE           ( 0x0DU ) /* API Port_SetPinMode service called when mode is invalid */
#define PORT_E_MODE_UNCHANGEABLE            ( 0x0EU ) /* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_UNINIT                       ( 0x0FU ) /* API service called without module initialization */
#define PORT_E_PARAM_POINTER                ( 0x10U ) /* APIs called with a Null Pointer */

/* Error Codes Vendor */
#define PORT_E_WRONG_CORE                   ( 0x11U ) /* API Port_Init service called when core ID is invalid. */
#define PORT_E_PARAM_INVALID_DIRECTION      ( 0x12U ) /* API Port_SetPinDirection service called when direction is invalid */

/* API PORT Function Service Identifier */
#define PORT_SID_INIT                       ( 0x00U ) /* API service ID for Port_Init function */
#define PORT_SID_SET_PIN_DIRECTION          ( 0x01U ) /* API service ID for Port_SetPinDirection function */
#define PORT_SID_REFRESH_PORT_DIRECTION     ( 0x02U ) /* API service ID for Port_RefreshPortDirection function */
#define PORT_SID_GET_VERSION_INFO           ( 0x03U ) /* API service ID for Port_GetVersionInfo function */
#define PORT_SID_SET_PIN_MODE               ( 0x04U ) /* API service ID for Port_SetPinMode function */
#define PORT_SID_RESET_PIN_MODE             ( 0x05U ) /* API service ID for Port_ResetPinMode function */

/* API Get CoreID Function */
#if (STD_ON == PORT_MULTICORE_SUPPORT)
    #define Port_GetCoreID() ((uint8)OsIf_GetCoreID())
#else
    #define Port_GetCoreID() ((uint8)0UL)
#endif

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)                                                      |
|-------------------------------------------------------------------------------------------------------------------------*/

/**
 *  @brief   Possible directions of a port pin.
 *  @details SRS ID:     SWS_Port_00046,SWS_Port_HuLa_00001,SWS_Port_HuLa_00006
 *           Design ID:  Port_PinDirectionType_Enumeration
 */
typedef enum
{
    PORT_PIN_IN  = 0,    /* Sets port pin as input */
    PORT_PIN_OUT = 1,    /* Sets port pin as output */
    PORT_PIN_INOUT,      /* Sets port pin as in-output */
} Port_PinDirectionType;

/*
 *  @brief   Data type for the symbolic name of a port pin.
 *  @details SRS ID:     SWS_Port_00013,SWS_Port_00207,SWS_Port_00208
 *                       SWS_Port_00219,SWS_Port_00229
 *           Design ID:  Port_PinType_Class
 */
typedef uint8 Port_PinType;

/*
 *  @brief   Port pin modes.
 *  @details SRS ID:     SWS_Port_00124,SWS_Port_00212,SWS_Port_00214
 *                       SWS_Port_00221,SWS_Port_00231
 *           Design ID:  Port_PinModeType_Class
 */
typedef uint32 Port_PinModeType;

/*-------------------------------------------------------------------------------------------------------------------------|
| EXTERN                                                                                          |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL CONSTANTS                                                                                 |
|-------------------------------------------------------------------------------------------------------------------------*/

#if (STD_OFF == PORT_PRECOMPILE_SUPPORT)
    #define START_CONFIG_DATA_UNSPECIFIED
    #include "Port_MemMap.h"
        PORT_CONFIG_EXT
    #define STOP_CONFIG_DATA_UNSPECIFIED
    #include "Port_MemMap.h"
#endif
/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL VARIABLES                                                                                 |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| GLOBAL VARIABLES                                                                                |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL FUNCTION PROTOTYPES                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL FUNCTION                                                                                  |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                                             |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| GLOBAL FUNCTION                                                                                                          |
|-------------------------------------------------------------------------------------------------------------------------*/

#define START_CODE
#include "Port_MemMap.h"

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_INIT_ID (0x00)                                                               |
| Name        | Port_Init                                                                         |
| Contents    | Initializes the Port Driver module.                                               |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Port_00001, SWS_Port_00002, SWS_Port_00079, SWS_Port_00081, SWS_Port_00005,   |
|             | SWS_Port_00140, SWS_Port_00041, SWS_Port_00042, SWS_Port_00043, SWS_Port_00004,   |
|             | SWS_Port_00121, SWS_Port_00232, SWS_Port_00113, SWS_Port_00051, SWS_Port_00087,   |
|             | SWS_Port_CONSTR_00233.                                                            |
| Vender ID:  | SWS_Port_HuLa_00003, SWS_Port_HuLa_00007,SWS_Port_00075                           |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
void Port_Init( const Port_ConfigType  *ConfigPtr);


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_SET_PIN_DIRECTION_ID (0x01)                                                  |
| Name        | Port_SetPinDirection                                                              |
| Contents    | Set the Port pin Direction Processing.                                            |
| SRS ID      | [SWS_Port_00141]                                                                  |
| Author      | --                                                                                |
| Param [in]  | Pin       : Port_PinType                                                          |
|             | Direction : Port_PinDirectionType                                                 |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Port_00051, SWS_Port_00054, SWS_Port_00063, SWS_Port_00077, SWS_Port_00086,   |
|             | SWS_Port_00087, SWS_Port_00137, SWS_Port_00138, SWS_Port_00141, SWS_Port_00146,   |
| Vender ID   | SWS_Port_HuLa_00002, SWS_Port_HuLa_00005                                          |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction);
#endif /*(STD_ON == PORT_SET_PIN_DIRECTION_API)*/


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_REFRESH_PORT_DIRECTION_ID (0x02)                                             |
| Name        | Port_RefreshPortDirection                                                         |
| Contents    | The module shall refresh the direction of all configured ports according to their |
|             | configured directions.                                                            |
| SRS ID      | [SWS_Port_00142]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | None                                                                              |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Port_00060, SWS_Port_00061, SWS_Port_00066, SWS_Port_00077,SWS_Port_00087,    |
|             | SWS_Port_00142, SWS_Port_00146                                                    |
| Vender ID   | --                                                                                |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
#if ( STD_ON == PORT_REFRESH_PORT_DIRECTION_API)
void Port_RefreshPortDirection( void );
#endif /* #if ( STD_ON == PORT_REFRESH_PORT_DIRECTION_API) */


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_GET_VERSION_INFO_ID (0x03)                                                   |
| Name        | Port_GetVersionInfo                                                               |
| Contents    | Returns the version information of this module.                                   |
| SRS ID      | [SWS_Port_00143]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | VersionInfo : Std Version Info Type                                               |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Port_00077, SWS_Port_00087, SWS_Port_00129, SWS_Port_00143, SWS_Port_00146,   |
|             | SWS_Port_00225                                                                    |
| Vender ID   | SWS_Port_HuLa_00004                                                               |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_VERSION_INFO_API)
void Port_GetVersionInfo( Std_VersionInfoType *VersionInfo );
#endif /*(STD_ON == PORT_VERSION_INFO_API)*/


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_SET_PIN_MODE_ID (0x04)                                                       |
| Name        | Port_SetPinMode                                                                   |
| Contents    | Shall set the port pin mode or the referenced pin during runtime.                 |
| SRS ID      | [SWS_Port_00145]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | Pin  : Port Pin ID number                                                         |
|             | Mode : The module shall set the specified Port Pin to the requested Port Pin mode.|
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Port_00051, SWS_Port_00077, SWS_Port_00087, SWS_Port_00125, SWS_Port_00128,   |
|             | SWS_Port_00145, SWS_Port_00146, SWS_Port_00212, SWS_Port_00214, SWS_Port_00223,   |
| Vender ID   | SWS_Port_HuLa_00004                                                               |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

#if (STD_ON == PORT_SET_PIN_MODE_API)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif /*(STD_ON == PORT_SET_PIN_MODE_API)*/


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_RESET_PIN_MODE_ID (0x05)                                                     |
| Name        | Port_ResetPinMode                                                                 |
| Contents    | The module shall reset the specified Port Pin mode to its configured default mode.|
| SRS ID      | [SWS_Port_HuLa_00008]                                                             |
| Author      | HaoNP                                                                             |
| Param [in]  | Pin  : Port Pin ID number                                                         |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | None                                                                              |
| Vender ID   | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_RESET_PIN_MODE_API)
void Port_ResetPinMode( Port_PinType Pin );
#endif /*(STD_ON == PORT_RESET_PIN_MODE_API)*/


#define STOP_CODE
#include "Port_MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* PORT_H */

/* EOF Port.h -----------------------------------------------------------------------------------*/
