/*------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Port_Ipc.h                                                                        |
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
| File        | Port_Ipc.h                                                                        |
| Module      | PORT                                                                              |
| Version     | 1.00.00                                                                           |
| Contents    | Implementation of Port_Ipc IPC Level layer                                        |
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
|------------------------------------------------------------------------------------------------*/

#ifndef PORT_IPC_H
#define PORT_IPC_H

#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                        |
|------------------------------------------------------------------------------------------------*/
#include "Port_Gpio_Ip.h"
#include "Port_Ipc_Cfg.h"


#include "Port_Cfg.h" // Temp
#include "Std_Types.h" // Temp
/*------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                    |
|------------------------------------------------------------------------------------------------*/

#define START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/**
 * @brief   Export IPC configurations.
 */
PORT_IPC_CONFIG_EXT
#define STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------|
| LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)                                                      |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| EXTERN                                                                                          |
|------------------------------------------------------------------------------------------------*/

 /*-----------------------------------------------------------------------------------------------|
| LOCAL CONSTANTS                                                                                 |
|-----------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL VARIABLES                                                                                 |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| GLOBAL VARIABLES                                                                                |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL FUNCTION PROTOTYPES                                                                       |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL FUNCTION                                                                                  |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| MACROS                                                                                          |
|------------------------------------------------------------------------------------------------*/
#define PORT_IPC_SET_PIN_DIRECTION_API          PORT_SET_PIN_DIRECTION_API      /* Adds / removes the service Port_SetPinDirection() from the code */
#define PORT_IPC_REFRESH_PORT_DIRECTION_API     PORT_REFRESH_PORT_DIRECTION_API /* Adds / removes the service Port_RefreshPortDirection() from the code */
#define PORT_IPC_SET_PIN_MODE_API               PORT_SET_PIN_MODE_API           /* Adds / removes the service Port_SetPinMode() from the code */
#define PORT_IPC_RESET_PIN_MODE_API             PORT_RESET_PIN_MODE_API         /* [ECUC_Dio_xxxxx] */


/*------------------------------------------------------------------------------------------------|
| MACROS AUTOSAR ->IPC                                                                                         |
|------------------------------------------------------------------------------------------------*/
#define PORT_GPIO_IPC_PROCESS_SUCCESS         PORT_GPIO_PROCESS_SUCCESS       /* API Port called with no error. */
#define PORT_GPIO_IPC_INVALID_MODE            PORT_GPIO_INVALID_MODE          /* API Port_Gpio__SetPinMode service called when mode is invalid. */
#define PORT_GPIO_IPC_MODE_UNCHANGEABLE       PORT_GPIO_MODE_UNCHANGEABLE     /* API Port_Gpio_SetPinMode service called when mode is unchangeable. */
#define PORT_GPIO_IPC_DIRECTION_UNCHANGEABLE  PORT_GPIO_DIRECTION_UNCHANGEABLE/* API Port_Gpio_SetPinDirection service called when direction is unchangeable. */
#define PORT_GPIO_IPC_CONFIG                  PORT_GPIO_CONFIG                /* API Port service called when PinId is not existed in config set. */
#define PORT_GPIO_IPC_INVALID_DIRECTION       PORT_GPIO_INVALID_DIRECTION     /* API Port_Gpio_SetPinDirection service called when direction is invalid. */
#define PORT_GPIO_IPC_UNINIT                  PORT_GPIO_UNINIT                /* API service called when port driver haven't initialized before. */
/*------------------------------------------------------------------------------------------------|
| GLOBAL FUNCTION                                                                                 |
|------------------------------------------------------------------------------------------------*/

#define START_CODE
#include "MemMap.h"
/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  |                                                                                   |
| Name        | Port_Ipc_Init                                                                     |
| Contents    | Initializes the Port Driver module.                                               |
| SRS ID      |                                                                                   |
| Author      | HaoNP                                                                             |
| Param [in]  |                                                                                   |
| Param [out] |                                                                                   |
| Return      |                                                                                   |
| Vender ID:  |                                                                                   |
|------------------------------------------------------------------------------------------------*/
void Port_Ipc_Init( const Port_Ipc_ConfigType *para_c_PortIpcConfig_ptr );


/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  |                                                                                   |
| Name        | Port_Ipc_SetPinDirection                                                          |
| Contents    | Initializes the Port Driver module.                                               |
| SRS ID      |                                                                                   |
| Author      | HaoNP                                                                             |
| Param [in]  |                                                                                   |
| Param [out] |                                                                                   |
| Return      |                                                                                   |
| Vender ID:  |                                                                                   |
|------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_IPC_SET_PIN_DIRECTION_API)
uint8 Port_Ipc_SetPinDirection( uint8 IPC_Pin, uint8 IPC_Direction );
#endif /*(STD_ON == PORT_IPC_SET_PIN_DIRECTION_API)*/



/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  |                                                                                   |
| Name        | Port_Ipc_RefreshPortDirection                                                     |
| Contents    | Initializes the Port Driver module.                                               |
| SRS ID      |                                                                                   |
| Author      | HaoNP                                                                             |
| Param [in]  |                                                                                   |
| Param [out] |                                                                                   |
| Return      |                                                                                   |
| Vender ID:  |                                                                                   |
|------------------------------------------------------------------------------------------------*/
#if ( STD_ON == PORT_IPC_REFRESH_PORT_DIRECTION_API)
void Port_Ipc_RefreshPortDirection( void );
#endif /* #if ( STD_ON == PORT_IPC_REFRESH_PORT_DIRECTION_API) */

/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  |                                                                                   |
| Name        | Port_Ipc_SetPinDirection                                                          |
| Contents    | Initializes the Port Driver module.                                               |
| SRS ID      |                                                                                   |
| Author      | HaoNP                                                                             |
| Param [in]  |                                                                                   |
| Param [out] |                                                                                   |
| Return      |                                                                                   |
| Vender ID:  |                                                                                   |
|------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_IPC_SET_PIN_MODE_API)
uint8 Port_Ipc_SetPinMode( uint8 para_Pin_u8, uint32 para_Mode_u32 );
#endif /*(STD_ON == PORT_IPC_SET_PIN_MODE_API)*/



/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  |                                                                                   |
| Name        | Port_Ipc_ReSetPinMode                                                             |
| Contents    | Initializes the Port Driver module.                                               |
| SRS ID      |                                                                                   |
| Author      | HaoNP                                                                             |
| Param [in]  |                                                                                   |
| Param [out] |                                                                                   |
| Return      |                                                                                   |
| Vender ID:  |                                                                                   |
|------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_IPC_RESET_PIN_MODE_API)
uint8 Port_Ipc_ReSetPinMode( uint8 Pin );
#endif /*(STD_ON == PORT_IPC_RESET_PIN_MODE_API)*/


#define STOP_CODE
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* PORT_IPC_H */

/*--------------------------------------------------- End Of File -----------------------------------------------------*/
