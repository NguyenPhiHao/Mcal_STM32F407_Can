/***********************************************************************************************************************
 * Project Name: HuLa STM
 * 
 * File Name: Dio_Types.h
 *
 * Description: Implementation of Dio_Types High Level layer
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

#ifndef DIO_TYPES_H
#define DIO_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                        |
|------------------------------------------------------------------------------------------------*/

#include "Dio_Ipc_Types.h"

/*------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                    |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)                                                      |
|------------------------------------------------------------------------------------------------*/

/**
 * @brief  Type of a DIO channel representation.
 * @details SRS ID:    SWS_Dio_00182
 *          Design ID: Dio_ChannelType_Class  
 */
typedef uint16 Dio_ChannelType;

/**
 * @brief  Type of a DIO channel levels representation.
 * @details SRS ID:    SWS_Dio_00185
 *          Design ID: Dio_LevelType_Class 
 */
typedef uint8 Dio_LevelType;

/**
 * @brief  Type of a DIO port representation.
 * @details SRS ID:    SWS_Dio_00183
 *          Design ID: Dio_PortType_Class  
 */
typedef uint8 Dio_PortType;

/**
 * @brief   Type of a DIO port levels representation.
 */
typedef uint16 Dio_PortLevelType;

/**
 * @brief   Type for the definition of a channel group, which consists of several adjoining channels within a port
 * @details SRS ID:    SWS_Dio_00184
 *          Design ID: Dio_ChannelGroupType_Class     
 */
typedef struct 
{
    Dio_PortType       port;      /* This is the port address offset on which the channel group works. */
    uint8              offset;    /* This is the position of the channel group on the port counted from the LSB */
    Dio_PortLevelType  mask;      /* This is the mask which defines the positions of the channel group */
} Dio_ChannelGroupType;

/**
 * @brief   Type of the external data structure containing the initialization data for this module.
 * @details SRS ID:    SWS_Dio_HuLa_XXXXX
 *          Design ID: Dio_ConfigType_Temp_Class
 */
typedef struct
{
    uint8 NumChannelGroups_u8;                                  /* Number of channel groups in configuration */
    const Dio_ChannelGroupType *Dio_c_ChannelGroupList_ptr;     /* Pointer to list of channel groups in configuration */
    const uint32 *Dio_c_ChannelToPartitionMap_u32_ptr;          /* Pointer to channel to partition mapping */
    const uint32 *Dio_c_PortToPartitionMap_u32_ptr;             /* Pointer to port to partition mapping */
} Dio_ConfigType_Owner;

/**
 * @brief   Type of the external data structure containing the initialization data for this module.
 * @details SRS ID:    SWS_Dio_HuLa_XXXXX
 *          Design ID: Dio_ConfigType_Class
 */
typedef struct
{
    const Dio_Ipc_ConfigType *Dio_c_Config_ptr;  /* Structure contain information of Dio Ipc config set. */
} Dio_ConfigType;

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

/*------------------------------------------------------------------------------------------------|
| LOCAL MACROS                                                                                    |
|------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------|
| GLOBAL FUNCTION                                                                                 |
|------------------------------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* DIO_TYPES_H */

/*--------------------------------------------------- EOF -----------------------------------------------------*/