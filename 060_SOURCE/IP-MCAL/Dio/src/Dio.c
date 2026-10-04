/***********************************************************************************************************************
 * Project Name: HuLa STM
 * 
 * File Name: Dio.c
 *
 * Description: Implementation of Dio High Level layer
 *              
 * AutoSAR Version:         4.4.0
 *
 * Compiler: GCC IAR
 *
 * Revision:
 *              Version         Date                Change History
 *              0.9.0          07/04/2024           Initial version
 *
 **********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                                                 |
|-------------------------------------------------------------------------------------------------------------------------*/

#include "Dio.h"
#include "Dio_VersionInfo.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*-------------------------------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                                                      |
|-------------------------------------------------------------------------------------------------------------------------*/
/* Common Published Information */
#define DIO_VENDOR_ID_C                      15U
#define DIO_MODULE_ID_C                      120U

/* AUTOSAR release version information */
#define DIO_AR_RELEASE_MAJOR_VERSION_C       4U
#define DIO_AR_RELEASE_MINOR_VERSION_C       4U 
#define DIO_AR_RELEASE_REVISION_VERSION_C    0U 

/* File version information */
#define DIO_SW_MAJOR_VERSION_C               1U 
#define DIO_SW_MINOR_VERSION_C               0U 
#define DIO_SW_PATCH_VERSION_C               0U 
/*-------------------------------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Check if Dio.c and Dio_VersionInfo.h are of the same version
 */
#if ((DIO_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION) || \
     (DIO_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION) || \
     (DIO_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION))
#error "Inconsistent Software Versions of Dio.c and Dio_VersionInfo.h"
#endif

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                                             |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| EXTERN                                                                                          |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)                                                      |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| CONSTANTS                                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

#define START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/**
 * @brief  Extern variable to get data from generated config
 */
extern const Dio_ConfigType Dio_g_c_Config;
#define STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL VARIABLES                                                                                 |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| GLOBAL VARIABLES                                                                                |
|-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL FUNCTION PROTOTYPES                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

#define START_CODE
#include "MemMap.h"

#if (STD_ON == DIO_DEV_ERROR_DETECT)

static inline Std_ReturnType Dio_PortCheck( Dio_PortType para_PortId );
static inline Std_ReturnType Dio_ValidateChannel ( Dio_ChannelType para_ChannelId );
static inline Std_ReturnType Dio_Validate_Pointer_ChannelGroup ( const Dio_ChannelGroupType * ChannelGroupIdPtr );

#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#define STOP_CODE
#include "MemMap.h"

/*-------------------------------------------------------------------------------------------------------------------------|
| LOCAL FUNCTION                                                                                  |
|-------------------------------------------------------------------------------------------------------------------------*/

#define START_CODE
#include "MemMap.h"


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | SWS_Dio_HuLa_XXXXX                                                                |
| Name        | Dio_PortCheck                                                                     |
| Contents    | Checks the specified port.                                                        |
| SRS ID      |                                                                                   |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | E_OK    : The function call is valid.                                             |
| Return      | E_NOT_OK: The function call is invalid.                                           |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
/* #if (STD_ON == DIO_DEV_ERROR_DETECT)
static inline Std_ReturnType Dio_PortCheck( Dio_PortType para_PortId )
{
    Std_ReturnType Return_Status = E_NOT_OK;

    if (((Dio_PortType)(para_PortId) >= 0U) && ((Dio_PortType)(para_PortId) <= DIO_GPIO_IP_NUM_PORTS_U16))
    {
        Return_Status = E_OK;
    }
    else
    {
        Return_Status = E_NOT_OK;
    }

    return Return_Status;
}
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#if (STD_ON == DIO_DEV_ERROR_DETECT)
Std_ReturnType Dio_PortCheck( Dio_PortType para_PortID )
{
    Std_ReturnType Return_Status = E_NOT_OK;

    Return_Status = Dio_Ipc_PortCheck(para_PortID);

    return Return_Status;
}
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
/**
 *  @brief          Checks the specified pointer ChannelGroup.
 *
 *  @details        
 *                  Service ID:        N/A
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Validate_Pointer_ChannelGroup_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelGroupType *
 *  @param[in]      ChannelGroupIdPtr        Pointer parameter to be checked.
 *
 *  @return         Std_ReturnType     
 *  @retval         E_OK               The function call is valid                                
 *  @retval         E_NOT_OK           The function call is invalid  
 *
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
 #if (STD_ON == DIO_DEV_ERROR_DETECT)

static inline Std_ReturnType Dio_Validate_Pointer_ChannelGroup( const Dio_ChannelGroupType * ChannelGroupIdPtr)
{
    Std_ReturnType Return_Status = E_NOT_OK;

    if (NULL_PTR != ChannelGroupIdPtr )
    {
        Return_Status = E_OK;
    }
    else
    {
        Return_Status = E_NOT_OK;
    }

    return Return_Status;
}

#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#define STOP_CODE
#include "MemMap.h"

/*-------------------------------------------------------------------------------------------------------------------------|
| GLOBAL FUNCTION                                                                                                          |
|-------------------------------------------------------------------------------------------------------------------------*/
#define START_CODE
#include "MemMap.h"
/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
/**
 *  @brief          This returns the value of the specified DIO channel.
 *
 *  @details        
 *                  Service ID:        0x00
 *                  SRS ID:            SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015
 *                                     SWS_Dio_00017, SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027
 *                                     SWS_Dio_00051, SWS_Dio_00060, SWS_Dio_00074, SWS_Dio_00089
 *                                     SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133, SWS_Dio_00180
 *                                     SWS_Dio_00182, SWS_Dio_00185
 *                  Design ID:         Dio_ReadChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelType
 *  @param[in]      ChannelId                Specifies the required channel id.
 *
 *  @return         Dio_LevelType            Returns the level of the corresponding pin as @p STD_HIGH or @p STD_LOW.
 *  @retval         STD_HIGH                 The logical level of the corresponding pin is 1.
 *  @retval         STD_LOW                  The logical level of the corresponding pin is 0.
 *
 *  @note           None
 *  
 *  @pre            Port_Init must have been called.
 *
 *  @post           None
 *
 **/
Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId )
{
    Std_ReturnType Return_Status_u8;
    Dio_LevelType l_ChannelLevel = (Dio_LevelType)STD_LOW;
    uint8 l_Error_Value_u8 = DIO_E_PARAM_INVALID_CHANNEL_ID;

    /* Validate ChannelId parameter */
    Return_Status_u8 = Dio_ValidateChannel(ChannelId);

    if (E_OK == Return_Status_u8)
    {
        l_ChannelLevel = Dio_Ipc_ReadChannel(ChannelId, &l_Error_Value_u8);
    }

    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        if (0U != l_Error_Value_u8)
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_READCHANNEL, l_Error_Value_u8);
        }
    #else
        /* Avoid compiler warning */
        (void)l_Error_Value_u8;
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

    return l_ChannelLevel;
}

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
/**
 *  @brief          This sets the level of a channel.
 *
 *  @details        
 *                  Service ID:        0x01
 *                  SRS ID:            SWS_Dio_00005, SWS_Dio_00006, SWS_Dio_00015, SWS_Dio_00017
 *                                     SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00028, SWS_Dio_00029
 *                                     SWS_Dio_00051, SWS_Dio_00060, SWS_Dio_00064, SWS_Dio_00070
 *                                     SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185, SWS_Dio_00134
 *                                     SWS_Dio_00079, SWS_Dio_00089, SWS_Dio_00119, SWS_Dio_00128
 *                  Design ID:         Dio_WriteChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelType
 *  @param[in]      ChannelId          Specifies the required channel id.
 *  @arg            Dio_LevelType
 *  @param[in]      Level              The level of the corresponding pin as @p STD_HIGH or @p STD_LOW.
 *
 *  @return         None            
 *  @retval         None                
 *
 *  @note           None
 *  
 *  @pre            Port_Init must have been called.
 *
 *  @post           None
 *
 **/

 /*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
void Dio_WriteChannel
(
    Dio_ChannelType ChannelId,
    Dio_LevelType Level
)
{
    Std_ReturnType Return_Status_u8;
    uint8 l_Error_Value_u8 = DIO_E_PARAM_INVALID_CHANNEL_ID;

    /* Validate ChannelId parameter */
    Return_Status_u8 = Dio_ValidateChannel(ChannelId);

    if (E_OK == Return_Status_u8)
    {
        l_Error_Value_u8 = Dio_Ipc_WriteChannel(ChannelId, Level);
    }

    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        if (0U != l_Error_Value_u8)
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_WRITECHANNEL, l_Error_Value_u8);
        }
    #else
        /* Avoid compiler warning */
        (void)l_Error_Value_u8;
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */
}

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
/**
 *  @brief          Returns the level of all channels of specified port.
 *
 *  @details        
 *                  Service ID:        0x02
 *                  SRS ID:            SWS_Dio_00051, SWS_Dio_00053, SWS_Dio_00060, SWS_Dio_00075
 *                                     SWS_Dio_00103, SWS_Dio_00104, SWS_Dio_00118, SWS_Dio_00135, SWS_Dio_00181
 *                                     SWS_Dio_00005, SWS_Dio_00012, SWS_Dio_00013, SWS_Dio_00018, SWS_Dio_00020
 *                                     SWS_Dio_00183, SWS_Dio_00186, SWS_Dio_00026, SWS_Dio_00031
 *                  Design ID:         Dio_ReadPort_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_PortType
 *  @param[in]      PortId             Specifies the required port id.
 *
 *  @return         Dio_PortLevelType  Levels of all channels of specified port.   
 *  @retval         Return_Status_u16 Value of port   
 *
 *  @note           None
 *  
 *  @pre            Port_Init must have been called.
 *
 *  @post           None
 *
 **/
Dio_PortLevelType Dio_ReadPort
(
    Dio_PortType PortId
)
{
    Std_ReturnType Return_Status_u8;
    Dio_PortLevelType l_PortLevel;
    uint8 l_Error_Value_u8 = DIO_E_PARAM_INVALID_PORT_ID;

    /* Validate PortId parameter */
    Return_Status_u8 = Dio_PortCheck(PortId);

    if (E_OK == Return_Status_u8)
    {
        l_PortLevel = Dio_Ipc_ReadPort(PortId, &l_Error_Value_u8);
    }

    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        if (0U != l_Error_Value_u8)
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_READPORT, l_Error_Value_u8);
        }
    #else
        /* Avoid compiler warning */
        (void)l_Error_Value_u8;
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

    return l_PortLevel;
}
/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
/**
 *  @brief          Service to set a value of the port.
 *
 *  @details        
 *                  Service ID:        0x03
 *                  SRS ID:            SWS_Dio_00004, SWS_Dio_00005, SWS_Dio_00007, SWS_Dio_00018
 *                                     SWS_Dio_00020, SWS_Dio_00026, SWS_Dio_00070, SWS_Dio_00183
 *                                     SWS_Dio_00186, SWS_Dio_00075, SWS_Dio_00103, SWS_Dio_00105
 *                                     SWS_Dio_00108, SWS_Dio_00119, SWS_Dio_00181, SWS_Dio_00136
 *                  Design ID:         Dio_WritePort_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_PortType
 *  @param[in]      PortId             Specifies the required port id.
 *  @arg            Dio_PortLevelType
 *  @param[in]      Level              Specifies the required levels for the port pins.
 *
 *  @return         None     
 *  @retval         None   
 *
 *  @note           None
 *  
 *  @pre            Port_Init must have been called.
 *
 *  @post           None
 *
 **/
void Dio_WritePort
(
    Dio_PortType PortId,
    Dio_PortLevelType Level
)
{
    Std_ReturnType Return_Status_u8;
    uint8 l_Error_Value_u8 = DIO_E_PARAM_INVALID_PORT_ID;

    /* Validate PortId parameter */
    Return_Status_u8 = Dio_PortCheck(PortId);

    if (E_OK == Return_Status_u8)
    {
        l_Error_Value_u8 = Dio_Ipc_WritePort(PortId, Level);
    }

    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        if (0U != l_Error_Value_u8)
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_WRITEPORT, l_Error_Value_u8);
        }
    #else
        /* Avoid compiler warning */
        (void)l_Error_Value_u8;
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */
}


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
/**
 *  @brief          This service reads a subset of the adjoining bits of a port
 *
 *  @details        
 *                  Service ID:        0x04
 *                  SRS ID:            SWS_Dio_00005, SWS_Dio_00012, SWS_Dio_00014, SWS_Dio_00021
 *                                     SWS_Dio_00022, SWS_Dio_00024, SWS_Dio_00184, SWS_Dio_00186
 *                                     SWS_Dio_00026, SWS_Dio_00037, SWS_Dio_00051,  SWS_Dio_00056
 *                                     SWS_Dio_00060, SWS_Dio_00092, SWS_Dio_00093, SWS_Dio_00114
 *                                     SWS_Dio_00118, SWS_Dio_00137
 *                  Design ID:         Dio_ReadChannelGroup_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelGroupType*
 *  @param[in]      ChannelGroupIdPtr              Pointer to ChannelGroup
 *
 *  @return         Dio_PortLevelType              Level of a subset of the adjoining bits of a port
 *  @retval         Return_Status_u16             Port level
 *
 *  @note           None
 *  
 *  @pre            Port_Init must have been called.
 *
 *  @post           None
 *
 **/
Dio_PortLevelType Dio_ReadChannelGroup
(
    const Dio_ChannelGroupType * ChannelGroupIdPtr
)
{
    Dio_PortLevelType l_PortLevel;

#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    uint8 l_Error_Value_u8;
    Std_ReturnType Return_Status_u8 = DIO_E_PARAM_INVALID_GROUP_ID;

    /* Validate PortId parameter */
    Return_Status_u8 = Dio_Validate_Pointer_ChannelGroup(ChannelGroupIdPtr);

    if (E_OK == Return_Status_u8)
    {
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
        l_PortLevel = Dio_Ipc_ReadChannelGroup((const Dio_Ipc_ChannelGroupType *)ChannelGroupIdPtr, &l_Error_Value_u8);
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    }

    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        if (0U != l_Error_Value_u8)
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_READCHANNELGROUP, l_Error_Value_u8);
        }
    #else
        /* Avoid compiler warning */
        (void)l_Error_Value_u8;
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */

    return l_PortLevel;
}


/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/

/**
 *  @brief          Service to set a subset of the adjoining bits of a port to a specified level.
 *
 *  @details        
 *                  Service ID:        0x05
 *                  SRS ID:            SWS_Dio_00005, SWS_Dio_00008, SWS_Dio_00021, SWS_Dio_00022
 *                                     SWS_Dio_00138, SWS_Dio_00184, SWS_Dio_00186, SWS_Dio_00070 
 *                                     SWS_Dio_00090, SWS_Dio_00091, SWS_Dio_00114, SWS_Dio_00024
 *                                     SWS_Dio_00026, SWS_Dio_00039, SWS_Dio_00040, SWS_Dio_00051
 *                                     SWS_Dio_00056, SWS_Dio_00060, SWS_Dio_00064, SWS_Dio_00119
 *                  Design ID:         Dio_WriteChannelGroup_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelGroupType*
 *  @param[in]      ChannelGroupIdPtr                Pointer to Channel Group
 *  @arg            Dio_PortLevelType
 *  @param[in]      Level                            Value to be written
 *
 *  @return         None     
 *  @retval         None   
 *
 *  @note           None
 *  
 *  @pre            Port_Init must have been called.
 *
 *  @post           None
 *
 **/
void Dio_WriteChannelGroup
(
    const Dio_ChannelGroupType * ChannelGroupIdPtr,
    Dio_PortLevelType Level
)
{
    
    uint8 l_Error_Value_u8 = DIO_E_PARAM_INVALID_GROUP_ID;

#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    Std_ReturnType Return_Status_u8;

    /* Validate ChannelGroupId pointer parameter */
    Return_Status_u8 = Dio_Validate_Pointer_ChannelGroup(ChannelGroupIdPtr);

    if (E_OK == Return_Status_u8)
    {
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
        l_Error_Value_u8 = Dio_Ipc_WriteChannelGroup((const Dio_Ipc_ChannelGroupType *)ChannelGroupIdPtr, Level);
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    }

    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        if (0U != l_Error_Value_u8)
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_WRITECHANNELGROUP, l_Error_Value_u8);
        }
    #else
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
        /* Avoid compiler warning */
        (void)l_Error_Value_u8;
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
}

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == DIO_VERSION_INFO_API)
/**
 *  @brief          Returns the version information of this module.
 *
 *  @details        
 *                  Service ID:        0x12
 *                  SRS ID:            SWS_Dio_00051, SWS_Dio_00139, SWS_Dio_00189, SWS_Dio_00118
 *                  Design ID:         Dio_GetVersionInfo_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Versioninfo *
 *  @param[in]      versioninfo        Pointer to where to store the version information of this module.
 *
 *  @return         None     
 *  @retval         None    
 *
 *  @note           None
 *
 *  @pre            None
 *
 *  @post           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
void Dio_GetVersionInfo(
    Std_VersionInfoType *versioninfo
)
{
    /* Validate Versioninfo parameter */
    if (NULL_PTR != versioninfo)
    {
        /* Copy version information to output pointer */
        (versioninfo)->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
        (versioninfo)->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
        (versioninfo)->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
        (versioninfo)->vendorID         = (uint16)DIO_VENDOR_ID;
        (versioninfo)->moduleID         = (uint16)DIO_MODULE_ID;
    }
    else
    {
        #if (STD_ON == DIO_DEV_ERROR_DETECT)
            /* Report DIO_E_PARAM_POINTER error to DET */
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_GETVERSIONINFO, DIO_E_PARAM_POINTER);
        #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */
    }

}
#endif /*(STD_ON == PORT_VERSION_INFO_API)*/

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == DIO_FLIP_CHANNEL_API)
/**
 *  @brief          Service to Inverts the level of a channel.
 *
 *  @details        
 *                  Service ID:        0x11
 *                  SRS ID:            SWS_Dio_00005, SWS_Dio_00015, SWS_Dio_00017, SWS_Dio_00023
 *                                     SWS_Dio_00026, SWS_Dio_00051, SWS_Dio_00064, SWS_Dio_00074
 *                                     SWS_Dio_00089, SWS_Dio_00092, SWS_Dio_00191, SWS_Dio_00192
 *                                     SWS_Dio_00193, SWS_Dio_00093, SWS_Dio_00118, SWS_Dio_00119
 *                                     SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185, SWS_Dio_00190
 *                  Design ID:         Dio_FlipChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelType
 *  @param[in]      ChannelId          Specifies the required channel id.
 *
 *  @return         Dio_LevelType      Returns the level of the corresponding pin as @p STD_HIGH or @p STD_LOW.
 *  @retval         STD_HIGH           The logical level of the corresponding pin is 1.   
 *  @retval         STD_LOW            The logical level of the corresponding pin is 10.   
 *
 *  @note           None
 *  
 *  @pre            Port_Init must have been called.
 *
 *  @post           None
 *
 **/
Dio_LevelType Dio_FlipChannel
(
    Dio_ChannelType ChannelId
)
{
    Std_ReturnType Return_Status_u8;
    Dio_LevelType l_ChannelLevel = (Dio_LevelType)STD_LOW;
    uint8 l_Error_Value_u8 = DIO_E_PARAM_INVALID_CHANNEL_ID;

    /* Validate ChannelId parameter */
    Return_Status_u8 = Dio_ValidateChannel(ChannelId);

    if (E_OK == Return_Status_u8)
    {
        l_ChannelLevel = Dio_Ipc_FlipChannel(ChannelId, &l_Error_Value_u8);
    }

    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        if (0U != l_Error_Value_u8)
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_FLIPCHANNEL, l_Error_Value_u8);
        }
    #else
        /* Avoid compiler warning */
        (void)l_Error_Value_u8;
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

    return l_ChannelLevel;
}
#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */

/*-------------------------------------------------------------------------------------------------------------------------|
| Module ID   | DIO_MODULE_ID (120)                                                               |
| Service ID  | DIO_REDCHANNEL_ID (0x00)                                                          |
| Name        | Dio_ReadChannel                                                                   |
| Contents    | This returns the value of the specified DIO channel.                              |
| SRS ID      | [SWS_Port_00140]                                                                  |
| Author      | HaoNP                                                                             |
| Param [in]  | ConfigType : Port Config Type Table Pointer                                       |
| Param [out] | None                                                                              |
| Return      | None                                                                              |
| SWS ID:     | SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015, SWS_Dio_00017,        |
                SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027, SWS_Dio_00051, SWS_Dio_00060,        |
                SWS_Dio_00074, SWS_Dio_00089, SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133,        |
                SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185                                       |
| Vender ID:  | None                                                                              |
| Sync/Async  | Synchronous                                                                       |
|-------------------------------------------------------------------------------------------------------------------------*/
#if (STD_ON == DIO_MASKEDWRITEPORT_API)
/**
 *  @brief          DIO Mask write port using mask.
 *
 *  @details        
 *                  Service ID:        0x13
 *                  SRS ID:            SWS_Dio_00200, SWS_Dio_00201, SWS_Dio_00202, SWS_Dio_00203
 *                                     SWS_Dio_00300, SWS_Dio_00075, SWS_Dio_00177
 *                  Design ID:         Dio_MaskedWritePort_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_PortType
 *  @param[in]      PortId             Specifies the required port id.
 *  @arg            Dio_PortLevelType
 *  @param[in]      Level              Specifies the required levels for the port pins.
 *  @arg            Dio_PortLevelType
 *  @param[in]      Mask               Specifies the Mask value of the port.
 *
 *  @return         None     
 *  @retval         None   
 *
 *  @note           None
 *  
 *  @pre            Port_Init must have been called.
 *
 *  @post           None
 *
 **/
void Dio_MaskedWritePort
(
    Dio_PortType PortId,
    Dio_PortLevelType Level,
    Dio_PortLevelType Mask
)
{
    uint8 l_Error_Value_u8 = DIO_E_PARAM_INVALID_PORT_ID;

    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        Std_ReturnType Return_Status_u8;

        /* Validate PortId parameter */
        Return_Status_u8 = Dio_PortCheck(PortId);

        if (E_OK == Return_Status_u8)
        {
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */
            l_Error_Value_u8 = Dio_Ipc_MaskedWritePort(PortId, Level, Mask);
    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        }

        if (0U != l_Error_Value_u8)
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE, DIO_SID_MASKEDWRITEPORT, l_Error_Value_u8);
        }
    #else
        /* Avoid compiler warning */
        (void)l_Error_Value_u8;
    #endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */
}
#endif /* (STD_ON == DIO_MASKEDWRITEPORT_API) */

#define STOP_CODE
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/* EOF Port.h -----------------------------------------------------------------------------------*/