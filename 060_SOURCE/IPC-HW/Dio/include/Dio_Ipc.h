/***********************************************************************************************************************
 * Project Name: HuLa STM
 * 
 * File Name: Dio_Ipc.h
 *
 * Description: Implementation of Dio_Ipc IPC Level layer
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

#ifndef DIO_IPC_H
#define DIO_IPC_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                        |
|------------------------------------------------------------------------------------------------*/

#include "Dio_Gpio_Ip.h"
#include "Dio_Ipc_Cfg.h"

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
    DIO_IPC_CONFIG_PC
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
|------------------------------------------------------------------------------------------------*/

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
/**
 *  @brief          This sets the level of a channel.
 *
 *  @details        
 *                  Service ID:        None
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_WriteChannel_Activity
 *
 **/
Std_ReturnType Dio_Ipc_PortCheck( Dio_PortType Ipc_PortID );

/*------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                    |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| GLOBAL FUNCTION                                                                                 |
|------------------------------------------------------------------------------------------------*/

#define START_CODE
#include "MemMap.h"

/**
 *  @brief          This returns the value of the DIO channel and Error code.
 *
 *  @details        
 *                  Service ID:        None
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_ReadChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Non Reentrant
 *
 *  @arg            Dio_Ipc_ChannelType_u16    
 *  @param[in]      para_ChannelId                    Channel ID.
 *  @arg            uint8*    
 *  @param[in]      para_ErrorCode_ptr                Pointer to get Error code.
 *
 *  @return         Dio_Ipc_LevelType_u8              Returns the level of the corresponding pin as @p STD_HIGH or @p STD_LOW.
 *  @retval         STD_HIGH                          The logical level of the corresponding pin is 1.
 *  @retval         STD_LOW                           The logical level of the corresponding pin is 0.
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
Dio_Ipc_LevelType_u8 Dio_Ipc_ReadChannel(
    Dio_Ipc_ChannelType_u16 para_ChannelId,
    uint8 *para_ErrorCode_ptr
);

/**
 *  @brief          This sets the level of a channel.
 *
 *  @details        
 *                  Service ID:        None
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_WriteChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_Ipc_ChannelType_u16
 *  @param[in]      para_ChannelId_u16          Specifies the required channel id.
 *  @arg            Dio_Ipc_LevelType_u8
 *  @param[in]      para_Level_u8              The level of the corresponding pin as @p STD_HIGH or @p STD_LOW.
 *
 *  @return         uint8            
 *  @retval         l_ErrorCode_u8     Return Error code for HLD layer.                
 *
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
uint8 Dio_Ipc_WriteChannel(
    Dio_Ipc_ChannelType_u16 para_ChannelId_u16, 
    Dio_Ipc_LevelType_u8 para_Level_u8
);

/**
 *  @brief          This returns the value of the DIO port and Error code.
 *
 *  @details        
 *                  Service ID:        None
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_ReadPort_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Non Reentrant
 *
 *  @arg            Dio_Ipc_PortType_u8    
 *  @param[in]      para_PortId                       Port ID.
 *  @arg            uint8*    
 *  @param[in]      para_ErrorCode_ptr                Pointer to get Error code.
 *
 *  @return         Dio_Ipc_PortLevelType_u16         Levels of all channels of specified port. 
 *  @retval         l_PortLevel_Value_u16
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
Dio_Ipc_PortLevelType_u16 Dio_Ipc_ReadPort(
    Dio_Ipc_PortType_u8 para_PortId,
    uint8 *para_ErrorCode_ptr
);

/**
 *  @brief          Service to set a value of the port.
 *
 *  @details        
 *                  Service ID:        N/A
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_WritePort_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_Ipc_PortType_u8
 *  @param[in]      para_PortId_u8                  Specifies the required port id.
 *  @arg            Dio_Ipc_PortLevelType_u16
 *  @param[in]      para_PortLevel_u16              Specifies the required levels for the port pins.
 *
 *  @return         uint8     
 *  @retval         l_ErrorCode_Value_u8            Return Error code for HLD layer.   
 *
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
uint8 Dio_Ipc_WritePort(
    Dio_Ipc_PortType_u8 para_PortId_u8, 
    Dio_Ipc_PortLevelType_u16 para_PortLevel_u16
);

/**
 *  @brief          This service reads a subset of the adjoining bits of a port
 *
 *  @details        
 *                  Service ID:        N/A
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_ReadChannelGroup_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_Ipc_ChannelGroupType*
 *  @param[in]      ChannelGroupIdPtr              Pointer to ChannelGroup
 *  @arg            uint8 *
 *  @param[in]      para_ErrorCode_ptr             Pointer to get ErrorCode
 *
 *  @return         Dio_Ipc_PortLevelType_u16      Level of a subset of the adjoining bits of a port
 *  @retval         l_Return_Value_u16             Port level
 *
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
Dio_Ipc_PortLevelType_u16 Dio_Ipc_ReadChannelGroup(
    const Dio_Ipc_ChannelGroupType *c_ChannelGroupId_ptr,
    uint8 *para_ErrorCode_ptr
);


/**
 *  @brief          Service to set a subset of the adjoining bits of a port to a specified level.
 *
 *  @details        
 *                  Service ID:        N/A
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_WriteChannelGroup_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_Ipc_ChannelGroupType*
 *  @param[in]      ChannelGroupIdPtr              Pointer to ChannelGroup
 *  @arg            Dio_Ipc_PortLevelType_u16
 *  @param[in]      para_Level_u16                 Level to write channel group
 *
 *  @return         uint8      
 *  @retval         l_ErrorCode_Value_u8           Return to get ErrorCode
 *
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
uint8 Dio_Ipc_WriteChannelGroup(
    const Dio_Ipc_ChannelGroupType *c_ChannelGroupId_ptr ,
    Dio_Ipc_PortLevelType_u16  para_Level_u16
);

#if (STD_ON == DIO_IPC_FLIP_CHANNEL_API)
/**
 *  @brief          Service to Inverts the level of a channel.
 *
 *  @details        
 *                  Service ID:        None
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_FlipChannel_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Non Reentrant
 *
 *  @arg            Dio_Ipc_ChannelType_u16    
 *  @param[in]      para_ChannelId                    Channel ID.
 *  @arg            uint8*    
 *  @param[in]      para_ErrorCode_ptr                Pointer to get Error code.
 *
 *  @return         Dio_Ipc_LevelType_u8              Returns the level of the corresponding pin as @p STD_HIGH or @p STD_LOW.
 *  @retval         STD_HIGH                          The logical level of the corresponding pin is 1.
 *  @retval         STD_LOW                           The logical level of the corresponding pin is 0.
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
Dio_Ipc_LevelType_u8 Dio_Ipc_FlipChannel(
    Dio_Ipc_ChannelType_u16 para_ChannelId,
    uint8 *para_ErrorCode_ptr
);
#endif /* (STD_ON == DIO_IPC_FLIP_CHANNEL_API) */

#if (STD_ON == DIO_IPC_MASKEDWRITEPORT_API)
/**
 *  @brief          DIO Mask write port using mask.
 *
 *  @details        
 *                  Service ID:        N/A
 *                  SRS ID:            SWS_Dio_HuLa_XXXXX
 *                  Design ID:         Dio_Ipc_MaskedWritePort_Activity
 *                  Sync/Async:        Synchronous
 *                  Reentrancy:        Reentrant
 *
 *  @arg            Dio_Ipc_PortType_u8
 *  @param[in]      para_PortId_u8              Specifies the required port id.
 *  @arg            Dio_Ipc_PortLevelType_u16
 *  @param[in]      para_Level_u16              Specifies the required levels for the port pins.
 *  @arg            Dio_Ipc_PortLevelType_u16
 *  @param[in]      para_Mask_u16               Specifies the Mask value of the port.
 *
 *  @return         uint8     
 *  @retval         l_ErrorCode_u8              Return Error code.   
 *
 *  @note           None
 *  
 *  @pre            None
 *
 *  @post           None
 *
 **/
uint8 Dio_Ipc_MaskedWritePort
(
    Dio_Ipc_PortType_u8 para_PortId_u8,
    Dio_Ipc_PortLevelType_u16 para_Level_u16,
    Dio_Ipc_PortLevelType_u16 para_Mask_u16
);
#endif /* (STD_ON == DIO_IPC_MASKEDWRITEPORT_API) */

#define STOP_CODE
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* DIO_IPC_H */

/* EOF Port.h -----------------------------------------------------------------------------------*/
