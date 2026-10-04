/*------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Port.c                                                                            |
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
| File        | Port.c                                                                            |
| Module      | PORT                                                                              |
| Version     | 1.00.00                                                                           |
| Contents    | PORT Module source                                                                |
|             | The PORT is a basic software module at the service layer of the standardized basic|
|             | software architecture of AUTOSAR.                                                 |
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

#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                        |
|------------------------------------------------------------------------------------------------*/
#include "Port.h"
#include "Port_VersionInfo.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|------------------------------------------------------------------------------------------------*/
/* Common published information */
#define PORT_VENDOR_ID_C                         (0x0FU)
#define PORT_MODULE_ID_C                         (0x7CU)

/* AUTOSAR release version: 4.4.0 */
#define PORT_AR_RELEASE_MAJOR_VERSION_C          (0x04U)
#define PORT_AR_RELEASE_MINOR_VERSION_C          (0x04U)
#define PORT_AR_RELEASE_REVISION_VERSION_C       (0x00U)

/* Software version: 1.0.0 */
#define PORT_SW_MAJOR_VERSION_C                  (0x01U)
#define PORT_SW_MINOR_VERSION_C                  (0x00U)
#define PORT_SW_PATCH_VERSION_C                  (0x00U)

/*------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|------------------------------------------------------------------------------------------------*/
/* Check Vendor ID */
#if (PORT_VENDOR_ID_C != PORT_VENDOR_ID)
#error "Port.c and Port_VersionInfo.h have different Vendor IDs"
#endif

/* Check Module ID */
#if (PORT_MODULE_ID_C != PORT_MODULE_ID)
#error "Port.c and Port_VersionInfo.h have different Module IDs"
#endif

/* Check AUTOSAR release version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_C != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_C != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_C != PORT_AR_RELEASE_REVISION_VERSION))
#error "Port.c and Port_VersionInfo.h have inconsistent AUTOSAR versions"
#endif

/* Check software version */
#if ((PORT_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_C != PORT_SW_PATCH_VERSION))
#error "Port.c and Port_VersionInfo.h have inconsistent software versions"
#endif

/*------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                    |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)                                                      |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| EXTERN                                                                                          |
|------------------------------------------------------------------------------------------------*/

 /*-----------------------------------------------------------------------------------------------|
| LOCAL CONSTANTS                                                                                 |
|------------------------------------------------------------------------------------------------*/

#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
#define START_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/* Extern variable to get data from generated config Pre-Compiler*/
extern const Port_ConfigType Port_g_c_Config;

#define STOP_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"
#endif /* #if (STD_ON == PORT_PRECOMPILE_SUPPORT) */

/*------------------------------------------------------------------------------------------------|
| LOCAL VARIABLES                                                                                 |
|------------------------------------------------------------------------------------------------*/

#define START_VAR_CLEARED_UNSPECIFIED
#include "Port_MemMap.h"

/* Static pointer to save config set of port driver when init. Post-Build */
static const Port_ConfigType *s_ConfigPtr;

#define STOP_VAR_CLEARED_UNSPECIFIED
#include "Port_MemMap.h"

/*------------------------------------------------------------------------------------------------|
| GLOBAL VARIABLES                                                                                |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL FUNCTION PROTOTYPES                                                                       |
|------------------------------------------------------------------------------------------------*/
#define START_CODE
#include "Port_MemMap.h"

static Std_ReturnType Port_ValidatePtrInit( uint8 para_CoreId_u8, const Port_ConfigType *para_Config_ptr );

#if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_RESET_PIN_MODE_API))
static Std_ReturnType Port_ValidateInitialized( uint8 ServiceID );
#endif

#if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_RESET_PIN_MODE_API))
static Std_ReturnType Port_ValidatePinId( Port_PinType PinID, uint8 ServiceID );
#endif

#define STOP_CODE
#include "Port_MemMap.h"


/*------------------------------------------------------------------------------------------------|
| LOCAL FUNCTION                                                                                  |
|------------------------------------------------------------------------------------------------*/
#define START_CODE
#include "Port_MemMap.h"

/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_INIT_ID (0x00)                                                               |
| Name        | Port_ValidatePtrInit                                                              |
| Contents    | The function will validate Port_g_c_Config parameter.                             |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | para_CoreId_u8  : Core current                                                    |
|             | para_Config_ptr : Pointer to a Port_ConfigType structure                          |
| Param [out] | None                                                                              |
| Return      | E_OK               The function call is valid                                     |
|             | E_NOT_OK           The function call is invalid                                   |                                       
| SWS ID:     | None                                                                              |
| Vender ID:  | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                          |
| Sync/Async  | Synchronous                                                                       |
|------------------------------------------------------------------------------------------------*/
static Std_ReturnType Port_ValidatePtrInit( uint8 para_CoreId_u8, const Port_ConfigType *para_Config_ptr )
{
    Std_ReturnType Error_Status = E_NOT_OK;

    const Port_ConfigType *Local_ConfigPtr = para_Config_ptr;

#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
    /* Check if Local_ConfigPtr parameter is valid in Pre-Compile */
    if (NULL_PTR != Local_ConfigPtr)
#else
    /* Check if Local_ConfigPtr parameter is valid in Post_Build */
    if (NULL_PTR == Local_ConfigPtr)
#endif /*STD_ON == PORT_PRECOMPILE_SUPPORT*/
    {
        /* Report PORT_E_INIT_FAILED error to DET */
        #if (STD_ON == PORT_DEV_ERROR_DETECT)
        (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_INIT, PORT_E_INIT_FAILED);
        #endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
    else
    {
        #if (STD_ON == PORT_PRECOMPILE_SUPPORT)
        /* Assign generated global variable in Pre-Compile to Local_ConfigPtr */
        Local_ConfigPtr = &Port_g_c_Config;
        #endif


        #if (STD_ON == PORT_MULTICORE_SUPPORT)
        /* Check if exist core Id in core list */
        if ((uint8)0x01U != Local_ConfigPtr->CoreList_ptr[para_CoreId_u8])
        {
            /* Report PORT_E_WRONG_CORE error to DET */
            #if (STD_ON == PORT_DEV_ERROR_DETECT)
            (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_INIT, PORT_E_WRONG_CORE);
            #endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
        }
        #else

        /* Check if don't exist core id in core list */
        if ((uint8)0 != Local_ConfigPtr->CoreList_ptr[para_CoreId_u8])
        {
            /* Report PORT_E_WRONG_CORE error to DET */
            #if (STD_ON == PORT_DEV_ERROR_DETECT)
            (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_INIT, PORT_E_WRONG_CORE);
            #endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
        }
        #endif /*STD_ON == PORT_MULTICORE_SUPPORT*/
        
        else
        {
            /* Success */
            Error_Status = E_OK;
        }
    }

    /* Avoid Misra violation */
    (void)para_CoreId_u8;
    (void)Local_ConfigPtr;
    return Error_Status;
}

/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_INIT_ID (0x00)                                                               |
| Name        | Port_ValidateInitialized                                                          |
| Contents    | The function will validate Input parameter of Port_SetPinDirection,               |
|             | Port_SetPinMode and Port_ResetPinMode.                                            |
| SRS ID      |                                                                                   |
| Author      | HaoNP                                                                             |
| Param [in]  | para_Pin_u8       : Port Pin ID number                                            |
| Param [in]  | para_ServiceId_u8 : API Function Service Identifier                               |
| Param [out] | None                                                                              |
| Return      | E_OK     : The function call is valid                                             |
|             | E_NOT_OK : The function call is invalid                                           |
| SWS ID:     | None                                                                              |
| Vender ID:  |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|------------------------------------------------------------------------------------------------*/
#if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_RESET_PIN_MODE_API))

static Std_ReturnType Port_ValidateInitialized( uint8 ServiceID )
{
    Std_ReturnType Error_Status = E_NOT_OK;

    if (NULL_PTR == s_ConfigPtr)
    {
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        (void)Det_ReportError( (uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, ServiceID, (uint8)PORT_E_UNINIT );
#endif
    }
    else
    {
        Error_Status = E_OK;
    }

#if (STD_OFF == PORT_DEV_ERROR_DETECT)
    (void)ServiceID;
#endif

    return Error_Status;
}
#endif /* #if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_RESET_PIN_MODE_API)) */

/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_INIT_ID (0x00)                                                               |
| Name        | Port_ValidatePinId                                                                |
| Contents    | The function Port_ValidatePinId will validate Input parameter of                  |
|             |                                                                                   |
| SRS ID      |                                                                                   |
| Author      | HaoNP                                                                             |
| Param [in]  | para_Pin_u8       : Port Pin ID number                                            |
| Param [in]  | para_ServiceId_u8 : API Function Service Identifier                               |
| Param [out] | None                                                                              |
| Return      | E_OK     : The function call is valid                                             |
|             | E_NOT_OK : The function call is invalid                                           |
| SWS ID:     | None                                                                              |
| Vender ID:  |                                                                                   |
| Sync/Async  | Synchronous                                                                       |
|------------------------------------------------------------------------------------------------*/
#if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_RESET_PIN_MODE_API))
static Std_ReturnType Port_ValidatePinId( Port_PinType PinID, uint8 ServiceID )
{
    Std_ReturnType Error_Status = E_NOT_OK;

    if (PinID >= PORT_NUM_PINS)
    {
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        (void)Det_ReportError( (uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, ServiceID, (uint8)PORT_E_PARAM_PIN );
#endif
    }
    else
    {
        Error_Status = E_OK;
    }

#if (STD_OFF == PORT_DEV_ERROR_DETECT)
    (void)ServiceID;
#endif

    return Error_Status;
}
#endif /* #if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_RESET_PIN_MODE_API)) */
#define STOP_CODE
#include "Port_MemMap.h"

/*------------------------------------------------------------------------------------------------|
| GLOBAL FUNCTION                                                                                 |
|------------------------------------------------------------------------------------------------*/
#define START_CODE
#include "Port_MemMap.h"

/*------------------------------------------------------------------------------------------------|
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
|------------------------------------------------------------------------------------------------*/
void Port_Init( const Port_ConfigType *ConfigPtr )
{
    const Port_ConfigType *l_ConfigPtr = NULL_PTR;
    Std_ReturnType l_ValidationResult;
    uint8 l_CoreId;

    l_CoreId = Port_GetCoreID();

    l_ValidationResult = Port_ValidatePtrInit( l_CoreId, ConfigPtr );

    if (E_OK == l_ValidationResult)
    {
#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
        l_ConfigPtr = &Port_g_c_Config;
#else
        l_ConfigPtr = ConfigPtr;
#endif

        if ((NULL_PTR != l_ConfigPtr) && (NULL_PTR != l_ConfigPtr->PortIpcConfig_ptr))
        {
            Port_Ipc_Init( l_ConfigPtr->PortIpcConfig_ptr );

            s_ConfigPtr = l_ConfigPtr;
        }
        else
        {
#if (STD_ON == PORT_DEV_ERROR_DETECT)
            (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SID_INIT, (uint8)PORT_E_INIT_FAILED );
#endif
        }
    }
}


/*------------------------------------------------------------------------------------------------|
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
|------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    Std_ReturnType Validation_Init_Result = E_NOT_OK;
    Std_ReturnType Validation_Pin_Result = E_NOT_OK;
    uint8 Error_Status = 0x00U;


    /* Validate general condition */
    Validation_Init_Result = Port_ValidateInitialized(PORT_SID_SET_PIN_DIRECTION);

    if (E_OK == Validation_Init_Result)
    {
        Validation_Pin_Result = Port_ValidatePinId( Pin, PORT_SID_SET_PIN_DIRECTION);
    }


    if (E_OK == Validation_Pin_Result)
    {
        /* Set new port pin direction */
        Error_Status = Port_Ipc_SetPinDirection(Pin, Direction);
    
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        /* Check if direction is set successfully */
        if (E_OK != Error_Status)
        {
            (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SET_PIN_DIRECTION, Error_Status);
        }
#else
        (void)Error_Status;
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    }


}
#endif /*(STD_ON == PORT_SET_PIN_DIRECTION_API)*/


/*------------------------------------------------------------------------------------------------|
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
|------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_REFRESH_PORT_DIRECTION_API)
void Port_RefreshPortDirection( void )
{
    Std_ReturnType Validation_Init_Result = E_NOT_OK;

    /* Validate general condition */
    Validation_Init_Result = Port_ValidateInitialized( PORT_SID_REFRESH_PORT_DIRECTION );

    if (E_OK  == Validation_Init_Result )
    {
        /* Refresh port pin direction */
        (void)Port_Ipc_RefreshPortDirection();
    }
}
#endif /* #if (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) */

/*------------------------------------------------------------------------------------------------|
| Module ID   | PORT_MODULE_ID (124)                                                              |
| Service ID  | PORT_GET_VERSION_INFO_ID (0x03)                                                   |
| Name        | Port_GetVersionInfo                                                               |
| Contents    | Returns the version information of this module.                                   |
| SRS ID      | [SWS_Port_00143]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | versionInfo : Std Version Info Type                                               |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Port_00077, SWS_Port_00087, SWS_Port_00129, SWS_Port_00143, SWS_Port_00146,   |
|             | SWS_Port_00225                                                                    |
| Vender ID   | SWS_Port_HuLa_00004                                                               |
| Sync/Async  | Synchronous                                                                       |
|------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_VERSION_INFO_API)
void Port_GetVersionInfo( Std_VersionInfoType *VersionInfo )
{
    if (NULL_PTR == VersionInfo)
    {
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SID_GET_VERSION_INFO, (uint8)PORT_E_PARAM_POINTER );
#endif
    }
    else
    {
        VersionInfo->vendorID = (uint16)PORT_VENDOR_ID;
        VersionInfo->moduleID = (uint16)PORT_MODULE_ID;
        VersionInfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif /* #if (STD_ON == PORT_VERSION_INFO_API) */


/*------------------------------------------------------------------------------------------------|
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
|------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_SET_PIN_MODE_API)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    Std_ReturnType Validation_Init_Result = E_NOT_OK;
    Std_ReturnType Validation_Pin_Result  = E_NOT_OK;
    uint8 Error_Status = 0x00U;

    /* Validate general condition */
    Validation_Init_Result = Port_ValidateInitialized( PORT_SID_SET_PIN_MODE );

    if (E_OK == Validation_Init_Result)
    {
        Validation_Pin_Result = Port_ValidatePinId( Pin, PORT_SID_SET_PIN_MODE );
    }
    

    if (E_OK == Validation_Pin_Result)
    {
        /* Set new port pin mode */
        Error_Status = Port_Ipc_SetPinMode(Pin, (uint32)Mode);

#if (STD_ON == PORT_DEV_ERROR_DETECT)
        /* Check if Port set pin mode successfully */
        if (E_OK != Error_Status)
        {
            (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SET_PIN_MODE, Error_Status);
        }
#else
        (void)Error_Status;
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    }

}
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */


/*------------------------------------------------------------------------------------------------|
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
|------------------------------------------------------------------------------------------------*/
#if (STD_ON == PORT_RESET_PIN_MODE_API)
void Port_ResetPinMode( Port_PinType  Pin )
{
    Std_ReturnType Validation_Init_Result = E_NOT_OK;
    Std_ReturnType Validation_Pin_Result  = E_NOT_OK;
    uint8 Error_Status = 0x00U;

    /* Validate general condition */
    Validation_Init_Result = Port_ValidateInitialized( PORT_SID_RESET_PIN_MODE );

    
    if (E_OK == Validation_Init_Result)
    {
        Validation_Pin_Result = Port_ValidatePinId( Pin, PORT_SID_RESET_PIN_MODE );
    }
    

    if (E_OK == Validation_Pin_Result)
    {
        /* Refresh port pin direction */
        Error_Status = Port_Ipc_ReSetPinMode(Pin);

#if (STD_ON == PORT_DEV_ERROR_DETECT)
        /* Check if Port reset pin mode successfully */
        if (E_OK != Error_Status)
        {
            (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_RESET_PIN_MODE, Error_Status);
        }
#else
        (void)Error_Status;
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
}
#endif /*(STD_ON == PORT_RESET_PIN_MODE_API)*/


#define STOP_CODE
#include "Port_MemMap.h"


#ifdef __cplusplus
}
#endif

/*--------------------------------------------------- End Of File -----------------------------------------------------*/
