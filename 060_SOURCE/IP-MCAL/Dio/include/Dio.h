/*------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Dio.h                                                                             |
| Description:|                                                                                   |
|             | Microcontrollers: STM32F407                                                       |
|             | Compiler        : GCC IAR GHS TASKING                                             |
|             | Technical Ref   : AUTOSAR_SWS_DIODriver.pdf (4.4.0)                               |
|-------------------------------------------------------------------------------------------------|
| COPYRIGHT                                                                                       |
|-------------------------------------------------------------------------------------------------|
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|-------------------------------------------------------------------------------------------------|
| FILE DESCRIPTION                                                                                |
|-------------------------------------------------------------------------------------------------|
| File        | Dio.h                                                                             |
| Module      | DIO                                                                               |
| Version     | 1.00.00                                                                           |
| Contents    | DIO Module header                                                                 |
|             | The DIO is a basic software module at the service layer of the standardized       |
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
| V1.00.00 | 01/01/2025 | HaoNP    | [DIO-ID-001] Initial Version.                                |
|                                  |                                                              |
|------------------------------------------------------------------------------------------------*/

#ifndef DIO_H
#define DIO_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                        |
|------------------------------------------------------------------------------------------------*/

/* SRS ID: SWS_Dio_00131
 *           Design ID: N/A
 */
#include "Dio_Ipc.h"
#include "Dio_Cfg.h"
/*------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                    |
|------------------------------------------------------------------------------------------------*/

/* --- DET Error Code Define ------------------------------------------------ */

/* The DIO module is not properly configured */
#define DIO_E_PARAM_CONFIG                      (uint8)(0xF0)
#define DIO_E_PARAM_INVALID_CHANNEL_ID          (uint8)(0x0A) /* SRS ID: WS_Dio_00175. Invalid channel name requested. */
#define DIO_E_PARAM_INVALID_PORT_ID             (uint8)(0x14) /* SRS ID: SWS_Dio_00177. Invalid port name requested. */
#define DIO_E_PARAM_INVALID_GROUP_ID            (uint8)(0x1F) /* SRS ID: SWS_Dio_00178. Invalid ChannelGroup id passed. */
#define DIO_E_PARAM_POINTER                     (uint8)(0x20) /* SRS ID: SWS_Dio_00188. API service called with a NULL pointer. */
#define DIO_E_PARAM_LEVEL                       (uint8)(0x21) /*   API service called with invalid channel level value. */


/******************************************* Service ID *************************************/

#define DIO_SID_READCHANNEL                      (uint8)(0x00) /*API service ID for Dio_ReadChannel() function. */
#define DIO_SID_WRITECHANNEL                     (uint8)(0x01) /*API service ID for Dio_WriteChannel() function. */
#define DIO_SID_FLIPCHANNEL                      (uint8)(0x11) /*API service ID for Dio_FlipChannel() function. */
#define DIO_SID_READPORT                         (uint8)(0x02) /*API service ID for Dio_ReadPort() function. */
#define DIO_SID_WRITEPORT                        (uint8)(0x03) /*API service ID for Dio_WritePort() function. */
#define DIO_SID_READCHANNELGROUP                 (uint8)(0x04) /*API service ID for Dio_ReadChannel() Group function. */
#define DIO_SID_WRITECHANNELGROUP                (uint8)(0x05) /*API service ID for Dio_WriteChannel() Group function. */
#define DIO_SID_GETVERSIONINFO                   (uint8)(0x12) /*API service ID for DIO Get Version() Info function. */
#define DIO_SID_MASKEDWRITEPORT                  (uint8)(0x13) /*API service ID for Dio_MaskedWritePort() function. */

#define DIO_INSTANCE                             ((uint8)0x00) /* Instance ID of the Dio driver. */

/**  Port_GetCoreID
 *
 */
#if (STD_ON == DIO_MULTICORE_ENABLED)
    #define Dio_GetCoreID() ((uint8)OsIf_GetCoreID())
#else
    #define Dio_GetCoreID() ((uint8)0UL)
#endif

/*------------------------------------------------------------------------------------------------|
| LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)                                                      |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| EXTERN                                                                                          |
|------------------------------------------------------------------------------------------------*/

 /*-----------------------------------------------------------------------------------------------|
| LOCAL CONSTANTS                                                                                 |
|------------------------------------------------------------------------------------------------*/

#define START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
    DIO_CONFIG_PC
#define STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

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
| LOCAL MACROS                                                                                    |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| GLOBAL FUNCTION                                                                                 |
|------------------------------------------------------------------------------------------------*/
#define START_CODE
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------|
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
|------------------------------------------------------------------------------------------------*/
/**
          This returns the value of the specified DIO channel.
 *
 *  @details        
 *                  Service ID:       0x00
 *                  SRS ID:           SWS_Dio_00005, SWS_Dio_00011, SWS_Dio_00012, SWS_Dio_00015
 *                                     SWS_Dio_00017, SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00027
 *                                     SWS_Dio_00051, SWS_Dio_00060, SWS_Dio_00074, SWS_Dio_00089
 *                                     SWS_Dio_00118, SWS_Dio_00128, SWS_Dio_00133, SWS_Dio_00180
 *                                     SWS_Dio_00182, SWS_Dio_00185
 *                  Design ID:        Dio_ReadChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelType
 *  @param[in]      ChannelId                Specifies the required channel id.
 *
 *  @return         Dio_LevelType            Returns the level of the corresponding pin as STD_HIGH or STD_LOW.
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
Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId );

/**
          This sets the level of a channel.
 *
 *  @details        
 *                  Service ID:       0x01
 *                  SRS ID:           SWS_Dio_00005, SWS_Dio_00006, SWS_Dio_00015, SWS_Dio_00017
 *                                     SWS_Dio_00023, SWS_Dio_00026, SWS_Dio_00028, SWS_Dio_00029
 *                                     SWS_Dio_00051, SWS_Dio_00060, SWS_Dio_00064, SWS_Dio_00070
 *                                     SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185, SWS_Dio_00134
 *                                     SWS_Dio_00079, SWS_Dio_00089, SWS_Dio_00119, SWS_Dio_00128
 *                  Design ID:        Dio_WriteChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelType
 *  @param[in]      ChannelId          Specifies the required channel id.
 *  @arg            Dio_LevelType
 *  @param[in]      Level              The level of the corresponding pin as STD_HIGH or STD_LOW.
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
void Dio_WriteChannel
(
    Dio_ChannelType ChannelId,
    Dio_LevelType Level
);


/**
          Returns the level of all channels of specified port.
 *
 *  @details        
 *                  Service ID:       0x02
 *                  SRS ID:           SWS_Dio_00051, SWS_Dio_00053, SWS_Dio_00060, SWS_Dio_00075
 *                                     SWS_Dio_00103, SWS_Dio_00104, SWS_Dio_00118, SWS_Dio_00135, SWS_Dio_00181
 *                                     SWS_Dio_00005, SWS_Dio_00012, SWS_Dio_00013, SWS_Dio_00018, SWS_Dio_00020
 *                                     SWS_Dio_00183, SWS_Dio_00186, SWS_Dio_00026, SWS_Dio_00031
 *                  Design ID:        Dio_ReadPort_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_PortType
 *  @param[in]      PortId             Specifies the required port id.
 *
 *  @return         Dio_PortLevelType  Levels of all channels of specified port.   
 *  @retval         l_Return_Value_u16 Value of port   
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
);

/**
          Reset the port pin mode.
 *
 *  @details        
 *                  Service ID:       0x03
 *                  SRS ID:           SWS_Dio_00004, SWS_Dio_00005, SWS_Dio_00007, SWS_Dio_00018
 *                                     SWS_Dio_00020, SWS_Dio_00026, SWS_Dio_00070, SWS_Dio_00183
 *                                     SWS_Dio_00186, SWS_Dio_00075, SWS_Dio_00103, SWS_Dio_00105
 *                                     SWS_Dio_00108, SWS_Dio_00119, SWS_Dio_00181
 *                  Design ID:        Dio_WritePort_Activity
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
);

/**
          This service reads a subset of the adjoining bits of a port
 *
 *  @details        
 *                  Service ID:       0x04
 *                  SRS ID:           SWS_Dio_00005, SWS_Dio_00012, SWS_Dio_00014, SWS_Dio_00021
 *                                     SWS_Dio_00022, SWS_Dio_00024, SWS_Dio_00184, SWS_Dio_00186
 *                                     SWS_Dio_00026, SWS_Dio_00037, SWS_Dio_00051,  SWS_Dio_00056
 *                                     SWS_Dio_00060, SWS_Dio_00092, SWS_Dio_00093, SWS_Dio_00114
 *                                     SWS_Dio_00118, SWS_Dio_00137
 *                  Design ID:        Dio_ReadChannelGroup_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelGroupType*
 *  @param[in]      ChannelGroupIdPtr              Pointer to ChannelGroup
 *
 *  @return         Dio_PortLevelType              Level of a subset of the adjoining bits of a port
 *  @retval         l_Return_Value_u16             Port level
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
);

/**
          Service to set a subset of the adjoining bits of a port to a specified level.
 *
 *  @details        
 *                  Service ID:       0x05
 *                  SRS ID:           SWS_Dio_00005, SWS_Dio_00008, SWS_Dio_00021, SWS_Dio_00022
 *                                     SWS_Dio_00138, SWS_Dio_00184, SWS_Dio_00186, SWS_Dio_00070 
 *                                     SWS_Dio_00090, SWS_Dio_00091, SWS_Dio_00114, SWS_Dio_00024
 *                                     SWS_Dio_00026, SWS_Dio_00039, SWS_Dio_00040, SWS_Dio_00051
 *                                     SWS_Dio_00056, SWS_Dio_00060, SWS_Dio_00064, SWS_Dio_00119
 *                  Design ID:        Dio_WriteChannelGroup_Activity
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
);


#if (STD_ON == DIO_VERSION_INFO_API)
/**
          Returns the version information of this module.
 *
 *  @details        
 *                  Service ID:       0x12
 *                  SRS ID:           SWS_Dio_00051, SWS_Dio_00139, SWS_Dio_00189, SWS_Dio_00118
 *                  Design ID:        Dio_GetVersionInfo_Activity
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
);
#endif /*(STD_ON == PORT_VERSION_INFO_API)*/


#if (STD_ON == DIO_FLIP_CHANNEL_API)
/**
          Service to Inverts the level of a channel.
 *
 *  @details        
 *                  Service ID:       0x11
 *                  SRS ID:           SWS_Dio_00005, SWS_Dio_00015, SWS_Dio_00017, SWS_Dio_00023
 *                                     SWS_Dio_00026, SWS_Dio_00051, SWS_Dio_00064, SWS_Dio_00074
 *                                     SWS_Dio_00089, SWS_Dio_00092, SWS_Dio_00191, SWS_Dio_00192
 *                                     SWS_Dio_00193, SWS_Dio_00093, SWS_Dio_00118, SWS_Dio_00119
 *                                     SWS_Dio_00180, SWS_Dio_00182, SWS_Dio_00185, SWS_Dio_00190
 *                  Design ID:        Dio_FlipChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_ChannelType
 *  @param[in]      ChannelId          Specifies the required channel id.
 *
 *  @return         Dio_LevelType      Returns the level of the corresponding pin as STD_HIGH or STD_LOW.
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
);
#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */


#if (STD_ON == DIO_MASKEDWRITEPORT_API)
/**
          DIO Mask write port using mask.
 *
 *  @details        
 *                  Service ID:       0x13
 *                  SRS ID:           SWS_Dio_00200, SWS_Dio_00201, SWS_Dio_00202, SWS_Dio_00203
 *                                     SWS_Dio_00300, SWS_Dio_00075, SWS_Dio_00177
 *                  Design ID:        Port_ReSetPinMode_Activity
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
);
#endif /* (STD_ON == DIO_MASKEDWRITEPORT_API) */

#define STOP_CODE
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* DIO_H */

/* EOF Port.h -----------------------------------------------------------------------------------*/
