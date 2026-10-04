/*-------------------------------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Can.c                                                                             |
| Description:|                                                                                   |
|             | Microcontrollers: STM32F407                                                       |
|             | Compiler        : GCC IAR GHS TASKING                                             |
|             | Technical Ref   : AUTOSAR_SWS_CANDriver.pdf (4.4.0)                              |
|--------------------------------------------------------------------------------------------------------------------------|
| COPYRIGHT                                                                                       |
|--------------------------------------------------------------------------------------------------------------------------|
|                                                                                                                          |
|                                                                                                                          |
|                                                                                                                          |
|--------------------------------------------------------------------------------------------------------------------------|
| FILE DESCRIPTION                                                                                |
|--------------------------------------------------------------------------------------------------------------------------|
| File        | Can.c                                                                             |
| Module      | CAN                                                                               |
| Version     | 1.00.00                                                                           |
| Contents    | This module provides services for initiating transmissions and calls the callback | 
| Contents    | functions of the CanIf module for notifying events, independently from            |
|             | the hardware. Also it provides services to control the behavior and state of the  |
|             | CAN controllers that belong to the same CAN Hardware Unit.                        |
|--------------------------------------------------------------------------------------------------------------------------|
| AUTHOR IDENTITY                                                                                 |
|--------------------------------------------------------------------------------------------------------------------------|
| Author      | HaoNP                                                                             |
| Company     | H-Car Autosar Technology Inc.                                                     |
| Note        | --                                                                                |
|--------------------------------------------------------------------------------------------------------------------------|
| REVISION CONTROL HISTORY                                                                        |
|--------------------------------------------------------------------------------------------------------------------------|
| V1.00.00 | 01/01/2025 | HaoNP    | [CAN-ID-001] Initial Version.                                |
|                                  |                                                              |
|-------------------------------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Can.h"            /* [CAN034] */

#include "CanIf_Cbk.h"      /* [CAN036] */
#include "EcuM_Cbk.h"
#include "SchM_Can.h"       /* [CAN406] */
#include "Can_Irq.h"

#if( CAN_DEV_ERROR_DETECT != FALSE )
#include "Det.h"
#endif /* #if( CAN_DEV_ERROR_DETECT != FALSE ) */

/*-------------------------------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|-------------------------------------------------------------------------------------------------------------------------*/
/* Common published information */
#define CAN_VENDOR_ID_C                         (0x0FU)
#define CAN_MODULE_ID_C                         (0x7CU)

/* AUTOSAR release version: 4.4.0 */
#define CAN_AR_RELEASE_MAJOR_VERSION_C          (0x04U)
#define CAN_AR_RELEASE_MINOR_VERSION_C          (0x04U)
#define CAN_AR_RELEASE_REVISION_VERSION_C       (0x00U)

/* Software version: 1.0.0 */
#define CAN_SW_MAJOR_VERSION_C                  (0x01U)
#define CAN_SW_MINOR_VERSION_C                  (0x00U)
#define CAN_SW_PATCH_VERSION_C                  (0x00U)

/*-------------------------------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|-------------------------------------------------------------------------------------------------------------------------*/

/* Check if current file and Can.h header file are of the same Vendor ID */
#if (CAN_VENDOR_ID_C    != CAN_VENDOR_ID)
    #error "VENDOR ID for Can.c and Can.h are different"
#endif      /* End of Vendor Id Version check */

#if (CAN_MODULE_ID_C    != CAN_MODULE_ID)
    #error "MODULE ID for Can.c and Can.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_C    != CAN_SW_MAJOR_VERSION) ||\
     (CAN_SW_MINOR_VERSION_C    != CAN_SW_MINOR_VERSION) ||\
     (CAN_SW_PATCH_VERSION_C    != CAN_SW_PATCH_VERSION))
    #error "Software Version Numbers of Can.c and Can.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C    != CAN_AR_RELEASE_MAJOR_VERSION)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION_C    != CAN_AR_RELEASE_MINOR_VERSION)   ||\
     (CAN_AR_RELEASE_REVISION_VERSION_C != CAN_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Can.c and Can.h are different"
#endif      /* End of Autosar Version check */

#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------CanIf_Cbk.h--------------------------------------------------*/

/* Check if current file and CanIf_Cbk.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C    != CANIF_AR_RELEASE_MAJOR_VERSION_CBK_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION_C    != CANIF_AR_RELEASE_MINOR_VERSION_CBK_H))
    #error "AUTOSAR Version Numbers of Can.c and CanIf_Cbk.h are different"
#endif      /* End of Autosar Version check */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */

#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------EcuM_Cbk.h--------------------------------------------------*/

/* Check if current file and EcuM_Cbk.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C    != ECUM_AR_RELEASE_MAJOR_VERSION_CBK_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION_C    != ECUM_AR_RELEASE_MINOR_VERSION_CBK_H))
    #error "AUTOSAR Version Numbers of Can.c and EcuM_Cbk.h are different"
#endif      /* End of Autosar Version check */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */

#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------SchM_Can.h--------------------------------------------------*/

/* Check if current file and SchM_Can.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C    != RTE_AR_RELEASE_MAJOR_VERSION)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION_C    != RTE_AR_RELEASE_MINOR_VERSION))
    #error "AUTOSAR Version Numbers of Can.c and SchM_Can.h are different"
#endif      /* End of Autosar Version check */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */

/*---------------Can_Irq.h---------------------------------------------------*/

/* Check if current file and Can.h header file are of the same Vendor ID */
#if (CAN_VENDOR_ID_C    != CAN_VENDOR_ID_IRQ_H)
    #error "VENDOR ID for Can.c and Can_Irq.h are different"
#endif      /* End of Vendor Id Version check */

#if (CAN_MODULE_ID_C    != CAN_MODULE_ID_IRQ_H)
    #error "MODULE ID for Can.c and Can_Irq.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_C    != CAN_SW_MAJOR_VERSION_IRQ_H) ||\
     (CAN_SW_MINOR_VERSION_C    != CAN_SW_MINOR_VERSION_IRQ_H) ||\
     (CAN_SW_PATCH_VERSION_C    != CAN_SW_PATCH_VERSION_IRQ_H))
    #error "Software Version Numbers of Can.c and Can_Irq.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C    != CAN_AR_RELEASE_MAJOR_VERSION_IRQ_H)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION_C    != CAN_AR_RELEASE_MINOR_VERSION_IRQ_H)   ||\
     (CAN_AR_RELEASE_REVISION_VERSION_C != CAN_AR_RELEASE_REVISION_VERSION_IRQ_H))
    #error "AUTOSAR Version Numbers of Can.c and Can_Irq.h are different"
#endif      /* End of Autosar Version check */

#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------Det.h -------------------------------------------------------*/

/* Check if DET for CAN is enabled or not */
#if( CAN_DEV_ERROR_DETECT != FALSE )
/* Check if current file and Det.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C    != DET_AR_RELEASE_MAJOR_VERSION)   ||\
     (CAN_AR_RELEASE_MINOR_VERSION_C    != DET_AR_RELEASE_MINOR_VERSION))
    #error "AUTOSAR Version Numbers of Can.c and Det.h are different"
#endif      /* End of Autosar Version check */
#endif      /* #if( CAN_DEV_ERROR_DETECT != FALSE ) */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */

/* Can.c version check end */

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CAN_MODE_TRANSITION_OK   ( ( uint8 )0U )
#define CAN_MODE_TRANSITION_NG   ( ( uint8 )1U )
#define CAN_MODE_TRANSITION_SAME ( ( uint8 )2U )

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------|
| EXTERN VARIABLES                                                                                                         |
|-------------------------------------------------------------------------------------------------------------------------*/
#define CAN_START_SEC_VAR_INIT_LOCAL_UNSPECIFIED
#include "Can_MemMap.h"

const Can_ConfigType* Can_70_ConfigPtr = NULL_PTR;

#define CAN_STOP_SEC_VAR_INIT_LOCAL_UNSPECIFIED
#include "Can_MemMap.h"

/*----------------------------------------------------------------------------*/
/* static function prototypes                                                 */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* static variables                                                           */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_VAR_INIT_LOCAL_UNSPECIFIED
#include "Can_MemMap.h"

#if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE )
/* Type:Struct[MAX uint16 or uint32] / Alignment:UNSPECIFIED */
static Can_70_MultiTxHthInfoType s_MultiTxHthInfo[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_TXBUFFER_MAX ] = { 0U };
#endif /* ( CAN_MULTIPLEXED_TRANSMISSION == TRUE ) */

#define CAN_STOP_SEC_VAR_INIT_LOCAL_UNSPECIFIED
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

/* Type:Enum / Alignment:8byte */
static Can_ControllerStateType          s_ControllerStatus[ CAN_70_NUM_OF_CONTROLLER ] = { CAN_CS_UNINIT };

/* Type:Enum / Alignment:8byte */
Can_70_ControllerStatusActionType       Can_70_ControllerStatusAction[ CAN_70_NUM_OF_CONTROLLER ] = { CAN_TO_NONE };

/* Type:Base / Alignment:8byte */
static uint8                            s_DisableInterruptsCount[ CAN_70_NUM_OF_CONTROLLER ] = { 0U };

/* Type:Base / Alignment:8byte */
static uint8                            s_TxReentrant[ CAN_70_NUM_OF_CONTROLLER ] = { 0U };

/* Type:Array[uint8] / Alignment:8byte */
Can_70_HthToHwObj                       Can_70_IndxexTxHwObj[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_TXBUFFER_MAX ] = { 0U };

/* Type:Array[uint8] / Alignment:8byte */
uint8_least                             Can_70_IndxexRxHwObj[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_RXFIFO_MAX ] = { 0U };

/* Type:Array[bool_t] / Alignment:8byte */
static bool_t                           Can_70_TxBufferUsesPolling[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_TXBUFFER_MAX ] = { 0U };

/* Type:Array[bool_t] / Alignment:8byte */
static bool_t                           Can_70_RxBufferUsesPolling[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_RXFIFO_MAX ] = { 0U };

/* Type:Enum / Alignment:8byte */
static Can_70_ModuleStatusType          s_CanModuleStatus  = CAN_UNINIT;

#define CAN_STOP_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

#define CAN_START_SEC_CONST_8
#include "Can_MemMap.h"

/* Type:Array[boolean] / Alignment:8byte */
static const                            uint8 matrixTransition[4][4] = {
    {
        CAN_70_MODE_TRANSITION_NG,      /* CAN_CS_UNINIT ->CAN_CS_UNINIT  */
        CAN_70_MODE_TRANSITION_NG,      /* CAN_CS_UNINIT ->CAN_CS_STARTED */
        CAN_70_MODE_TRANSITION_NG,      /* CAN_CS_UNINIT ->CAN_CS_STOPPED */
        CAN_70_MODE_TRANSITION_NG       /* CAN_CS_UNINIT ->CAN_CS_SLEEP   */
    },
    {
        CAN_70_MODE_TRANSITION_NG,      /* CAN_CS_STARTED->CAN_CS_UNINIT  */
        CAN_70_MODE_TRANSITION_NG,      /* CAN_CS_STARTED->CAN_CS_STARTED */
        CAN_70_MODE_TRANSITION_OK,      /* CAN_CS_STARTED->CAN_CS_STOPPED */
        CAN_70_MODE_TRANSITION_NG       /* CAN_CS_STARTED->CAN_CS_SLEEP   */
    },
    {
        CAN_70_MODE_TRANSITION_NG,      /* CAN_CS_STOPPED->CAN_CS_UNINIT  */
        CAN_70_MODE_TRANSITION_OK,      /* CAN_CS_STOPPED->CAN_CS_STARTED */
        CAN_70_MODE_TRANSITION_SAME,    /* CAN_CS_STOPPED->CAN_CS_STOPPED */
        CAN_70_MODE_TRANSITION_OK       /* CAN_CS_STOPPED->CAN_CS_SLEEP   */
    },
    {
        CAN_70_MODE_TRANSITION_NG,      /* CAN_CS_SLEEP  ->CAN_CS_UNINIT  */
        CAN_70_MODE_TRANSITION_NG,      /* CAN_CS_SLEEP  ->CAN_CS_STARTED */
        CAN_70_MODE_TRANSITION_OK,      /* CAN_CS_SLEEP  ->CAN_CS_STOPPED */
        CAN_70_MODE_TRANSITION_SAME     /* CAN_CS_SLEEP  ->CAN_CS_SLEEP   */
    }
};

#define CAN_STOP_SEC_CONST_8
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )

/* Type:Array[boolean] / Alignment:8byte */
static bool_t                           s_EnableEgressTimeStamp[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_TXBUFFER_MAX ] = { 0U };

#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */

#define CAN_STOP_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_LOCAL_16
#include "Can_MemMap.h"

/* Type:Struct[MAX uin16] / Alignment:16byte */
Can_70_TxRequestInfoType                Can_70_TxRequestInfo[ CAN_70_NUM_OF_CONTROLLER ][  CAN_70_RL78F2X_TXBUFFER_MAX ] = { 0U };

/* Type:Base / Alignment:16byte */
static uint16                           s_CurrentBaudrateId[ CAN_70_NUM_OF_CONTROLLER ] = { CAN_70_NUM_OF_BAUDRATE_TABLE };

#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )

/* Type:Struct[MAX uin16] / Alignment:16byte */
Can_70_EgressTimeStampType              Can_70_EgressTimeStampData[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_TXBUFFER_MAX ][ CAN_70_NUM_OF_EGRESS ] = { 0U };

/* Type:Struct[MAX uin16] / Alignment:16byte */
Can_70_IngressTimeStampType             Can_70_IngressTimeStampData[ CAN_70_NUM_OF_CONTROLLER ][ CAN_70_RL78F2X_RXFIFO_MAX ] = { 0U };

#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */

#define CAN_STOP_SEC_VAR_INIT_LOCAL_16
#include "Can_MemMap.h"

/*----------------------------------------------------------------------------*/
/* function definitions and function style macros                             */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_CODE_LOCAL
#include "Can_MemMap.h"

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_INIT (0x00)                                          */
/* Name        : Can_Init                                                     */
/* Param       : (in) Config        Pointer to driver configuration.          */
/* Return      : void                                                         */
/* Contents    : This function initializes the module.                        */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_Init( const Can_ConfigType* Config )
{
    bool_t                                    timeOut;
    uint8_least                               index;
    uint8                                     controllerId;
    uint8                                     channelId;
    const Can_ControllerType*                 canController;
    const Can_HardwareObjectType*             canHardwareObject;
    Can_70_ControllerStateInfoType            controllerMode;
    uint8_least                               controllerIndex;
    uint8_least                               indexTxBuffer;
    uint8_least                               indexRxBuffer;
    uint8                                     CanActivatedCount;
 
#if( CAN_70_USE_OS_COUNTER == TRUE )
   
    CounterType                               counterID;
    TickType                                  tickValue;
    TickType                                  tickElapse;
    TickType                                  tickCurrent;
    TickType                                  tickTimeout;
   
#else /* #if( CAN_70_USE_OS_COUNTER == TRUE ) */
   
    uint32_least                              counter;
    uint32_least                              counterTimeout;
   
#endif /* #if( CAN_70_USE_OS_COUNTER == TRUE ) */
   
#if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE )
   
    uint16                                    hwObjectCount;
   
#endif /* #if( CAN_MULTIPLEXED_TRANSMISSION == TRUE ) */
   
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )

    uint8_least                               indexEgress;
   
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */

#if( CAN_DEV_ERROR_DETECT == TRUE )
   
    const Can_ControllerBaudrateConfigType*   controllerBaudrate;
   
#if ( CAN_70_USE_CANFD == TRUE )

    const Can_ControllerFdBaudrateConfigType* controllerFdBaudrate;
   
#endif /* #if ( CAN_70_USE_CANFD == TRUE ) */
   
    /* [SWS_Can_00026],[SWS_Can_00058],[SWS_Can_00079],[SWS_Can_00091],[SWS_Can_00234],
       [SWS_Can_00235],[SWS_BSW_00144]
    */
    /* Check parameters. */
    if ( NULL_PTR == Config ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_INIT,
                                 ( uint8 )CAN_E_PARAM_POINTER );
        return;
    } else {
        /* Nothing */
    }
   
    /* [SWS_Can_00174] */
    /* Check module status. */
    if ( CAN_UNINIT != s_CanModuleStatus ) {
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_INIT,
                                 ( uint8 ) CAN_E_TRANSITION );
        return;
    } else {
        /* Nothing */
    }
   
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        /* [SWS_Can_00408] */
        /* Check CAN controller operating mode */
        if ( CAN_CS_UNINIT != s_ControllerStatus[controllerIndex] ) {
            ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                     ( uint8 ) CAN_SID_INIT,
                                     ( uint8 ) CAN_E_TRANSITION );
            return;
        } else {
            /* Nothing */
        }
    }
 
    /* Check baud rate settings to prevent division by 0. */
    /* NOTE:The default baud rate setting is not checked because it is specified from the baud rate table. */
    canController = &( Config->CanConfigSet )->CanController[ 0U ];
    for ( index = 0U; index < CAN_70_NUM_OF_BAUDRATE_TABLE; index++ ) {
        controllerBaudrate = &( canController->CanControllerBaudRateConfig[ index ] );
        if ( 0U >= controllerBaudrate->CanControllerBaudRate ) {
            ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                     ( uint8 )CAN_SID_INIT,
                                     ( uint8 )CAN_E_INIT_FAILED );
            return;
        }
 
#if ( CAN_70_USE_CANFD == TRUE )
       
        controllerFdBaudrate = controllerBaudrate->CanControllerFdBaudrateConfig;
        if ( ( NULL_PTR != controllerFdBaudrate ) && ( 0U >= controllerFdBaudrate->CanControllerFdBaudRate ) ) {
            ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                     ( uint8 )CAN_SID_INIT,
                                     ( uint8 )CAN_E_INIT_FAILED );
            return;
        }
 
#endif /* #if ( CAN_70_USE_CANFD == TRUE ) */
 
    }
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* [SWS_Can_00103],[SWS_Can_00284],[SWS_Can_00386],[SWS_Can_00385],[SWS_Can_00291],
       [SWS_Can_00250],[SWS_Can_00436]
    */    
    /* Initializing static variables */    
    Can_70_ConfigPtr = Config;
    CanActivatedCount = 0U;
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &( Config->CanConfigSet )->CanController[ controllerIndex ];
 
        s_DisableInterruptsCount[ controllerIndex ] = 1U;
        Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_NONE;
        s_TxReentrant[ controllerIndex ] = 0U;
        s_CurrentBaudrateId[ controllerIndex ] = CAN_70_NUM_OF_BAUDRATE_TABLE;
   
        for ( index = 0U; index < CAN_70_RL78F2X_TXBUFFER_MAX; index++ ) {
           
            Can_70_TxRequestInfo[ controllerIndex ][ index ].Enable = FALSE;
            Can_70_TxRequestInfo[ controllerIndex ][ index ].CanTxPduId = 0U;
 
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
            Can_70_TxRequestInfo[ controllerIndex ][ index ].Timestamp = 0U;
            s_EnableEgressTimeStamp[ controllerIndex ][ index ] = FALSE;
            for ( indexEgress = 0U; indexEgress < CAN_70_NUM_OF_EGRESS; indexEgress++ ) {
                Can_70_EgressTimeStampData[ controllerIndex ][ index ][ indexEgress ].Enable = FALSE;
                Can_70_EgressTimeStampData[ controllerIndex ][ index ][ indexEgress ].TxPduId = 0U;
                Can_70_EgressTimeStampData[ controllerIndex ][ index ][ indexEgress ].Hth = 0U;
                Can_70_EgressTimeStampData[ controllerIndex ][ index ][ indexEgress ].TimeStamp = 0U;
            }
 
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
   
#if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE )
       
            s_MultiTxHthInfo[ controllerIndex ][ index ].Enable = FALSE;
            s_MultiTxHthInfo[ controllerIndex ][ index ].Hth = 0U;
       
#endif /* #if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE ) */
       
#if ( CAN_70_TX_POLLING_PROCESSING == TRUE )
 
            if ( CAN_PROCESSING_POLLING == canController->CanTxProcessing ) {
                Can_70_TxBufferUsesPolling[ controllerIndex ][ index ] = TRUE;
            } else {
                Can_70_TxBufferUsesPolling[ controllerIndex ][ index ] = FALSE;
            }
 
#else /* #if ( CAN_70_TX_POLLING_PROCESSING == TRUE ) */
 
            Can_70_TxBufferUsesPolling[ controllerIndex ][ index ] = FALSE;
       
#endif /* #if ( CAN_70_TX_POLLING_PROCESSING == TRUE ) */
 
            Can_70_IndxexTxHwObj[ controllerIndex ][ index ].IndexTxHwObj = CAN_70_NUM_OF_HARDWARE_OBJECT;
           
        }
   
        for ( index = 0U; index < CAN_70_RL78F2X_RXFIFO_MAX; index++ ) {
 
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
            Can_70_IngressTimeStampData[ controllerIndex ][ index ].Enable = FALSE;
            Can_70_IngressTimeStampData[ controllerIndex ][ index ].Hrh = 0U;
            Can_70_IngressTimeStampData[ controllerIndex ][ index ].TimeStamp = 0U;
       
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
#if ( CAN_70_RX_POLLING_PROCESSING == TRUE )
 
            if ( CAN_PROCESSING_POLLING == canController->CanRxProcessing ) {
                Can_70_RxBufferUsesPolling[ controllerIndex ][ index ] = TRUE;
            } else {
                Can_70_RxBufferUsesPolling[ controllerIndex ][ index ] = FALSE;
            }
 
#else /* #if ( CAN_70_RX_POLLING_PROCESSING ) */
 
            Can_70_RxBufferUsesPolling[ controllerIndex ][ index ] = FALSE;
       
#endif /* #if ( CAN_70_RX_POLLING_PROCESSING ) */
 
            Can_70_IndxexRxHwObj[ controllerIndex ][ index ] = CAN_70_NUM_OF_HARDWARE_OBJECT;
       
        }
   
#if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE )
 
   
        indexTxBuffer = 0U;
        indexRxBuffer = 0U;
        for ( index = 0U; index < CAN_70_NUM_OF_HARDWARE_OBJECT; index++ ) {
            canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ index ];
            if ( canController->CanControllerId == canHardwareObject->CanControllerRef->CanControllerId ) {
                if ( CAN_70_TRANSMIT == canHardwareObject->CanObjectType ) {
                    for ( hwObjectCount = 0U;
                          hwObjectCount < ( uint16 )canHardwareObject->CanHwObjectCount;
                          hwObjectCount++ ) {
                        if ( CAN_70_RL78F2X_TXBUFFER_MAX <= indexTxBuffer ) {
                            break;
                        } else {
                            /* Create s_MultiTxHthInfo from configuration. */
                            s_MultiTxHthInfo[ controllerIndex ][ indexTxBuffer ].Enable = TRUE;
                            s_MultiTxHthInfo[ controllerIndex ][ indexTxBuffer ].Hth = canHardwareObject->CanObjectId;
                           
                            Can_70_IndxexTxHwObj[ controllerIndex ][ indexTxBuffer ].IndexTxHwObj = index;
                            Can_70_IndxexTxHwObj[ controllerIndex ][ indexTxBuffer ].Hth = canHardwareObject->CanObjectId;
 
#if ( CAN_70_TX_MIXED_PROCESSING == TRUE )
           
                            if ( CAN_PROCESSING_MIXED == canController->CanTxProcessing ) {
                                Can_70_TxBufferUsesPolling[ controllerIndex ][ indexTxBuffer ] = canHardwareObject->CanHardwareObjectUsesPolling;
                            }
           
#endif /* #if ( CAN_70_TX_MIXED_PROCESSING == TRUE ) */
                           
                            indexTxBuffer++;
                        }
                    }
                } else {    /* CAN_70_RECEIVE  */
                    if ( CAN_70_RL78F2X_RXFIFO_MAX > indexRxBuffer ) {
                        Can_70_IndxexRxHwObj[ controllerIndex ][ indexRxBuffer ] = index;
                   
#if ( CAN_70_RX_MIXED_PROCESSING == TRUE )
           
                        if ( CAN_PROCESSING_MIXED == canController->CanRxProcessing ) {
                            Can_70_RxBufferUsesPolling[ controllerIndex ][ indexRxBuffer ] = canHardwareObject->CanHardwareObjectUsesPolling;
                        }
           
#endif /* #if ( CAN_70_RX_MIXED_PROCESSING == TRUE ) */
 
                        indexRxBuffer++;
                    }
                }
            }
        }
   
#else /* #if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE ) */
 
        indexTxBuffer = 0U;
        indexRxBuffer = 0U;
        for ( index = 0U; index < CAN_70_NUM_OF_HARDWARE_OBJECT; index++ ) {
            canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ index ];
            if ( canController->CanControllerId == canHardwareObject->CanControllerRef->CanControllerId ) {
                if ( CAN_70_TRANSMIT == canHardwareObject->CanObjectType ) {
                    if ( CAN_70_RL78F2X_TXBUFFER_MAX > indexTxBuffer ) {
                        Can_70_IndxexTxHwObj[ controllerIndex ][ indexTxBuffer ].Hth = canHardwareObject->CanObjectId;
                        Can_70_IndxexTxHwObj[ controllerIndex ][ indexTxBuffer ].IndexTxHwObj = index;
           
#if ( CAN_70_TX_MIXED_PROCESSING == TRUE )
           
                        if ( CAN_PROCESSING_MIXED == canController->CanTxProcessing ) {
                            Can_70_TxBufferUsesPolling[ controllerIndex ][ indexTxBuffer ] = canHardwareObject->CanHardwareObjectUsesPolling;
                        }
           
#endif /* #if ( CAN_70_TX_MIXED_PROCESSING == TRUE ) */
 
                        indexTxBuffer++;
                    }
                } else { /* CAN_70_RECEIVE  */
                    if ( CAN_70_RL78F2X_RXFIFO_MAX > indexRxBuffer ) {
                        Can_70_IndxexRxHwObj[ controllerIndex ][ indexRxBuffer ] = index;
                   
#if ( CAN_70_RX_MIXED_PROCESSING == TRUE )
           
                        if ( CAN_PROCESSING_MIXED == canController->CanRxProcessing ) {
                            Can_70_RxBufferUsesPolling[ controllerIndex ][ indexRxBuffer ] = canHardwareObject->CanHardwareObjectUsesPolling;
                        }
           
#endif /* #if ( CAN_70_RX_MIXED_PROCESSING == TRUE ) */
 
                        indexRxBuffer++;
                    }
                }
            }
        }
   
#endif /* #if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE ) */
   
        /* [SWS_Can_00223],[SWS_Can_00244] */
        if ( TRUE != canController->CanControllerActivation ) {
            /* Nothing */
        } else {
           
            controllerId = ( uint8 )canController->CanQChannelId;
            channelId    = 0U;  /* tentative */
               
#if( CAN_DEV_ERROR_DETECT == TRUE )
           
            /* [SWS_Can_00408] */
            /* Check CAN controller mode. */
            Can_70_HW_GetMode( controllerId, &controllerMode );
            if ( ( CAN_70_GMODE_SLEEP != controllerMode.GlobalMode )
              || ( CAN_70_CMODE_SLEEP != controllerMode.ChannelMode )
              || ( TRUE != controllerMode.RamInitialization ) ) {
                ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                         ( uint8 )CAN_SID_INIT,
                                         ( uint8 )CAN_E_TRANSITION );
                return;
            } else {
                /* Nothing */
            }
           
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
           
            /* [SWS_Can_00281] */
            /* Change global mode of CAN controller to RESET. */
            Can_70_HW_SetGlobalMode( controllerId, CAN_70_GMODE_RESET );
           
#if( CAN_70_USE_OS_COUNTER == TRUE )
           
            /* [SWS_Can_00281] */
            /* Wait until transition completes. */
            tickTimeout = ( uint32 )CAN_TIMEOUT_DURATION * ( uint32 )CAN_70_TICK_PER_MSEC;
            counterID = HARDWARE;
            timeOut = FALSE;
            tickElapse = 0U;
            tickValue = tickTimeout;
            ( void )GetCounterValue( counterID, &tickCurrent );
            while ( FALSE == timeOut ) {
                Can_70_HW_GetMode( controllerId, &controllerMode );
                if ( FALSE == controllerMode.InTransition ) {
                    break;
                } else {
                    if ( tickValue > tickElapse ) {
                        tickValue -= tickElapse;
                        ( void )GetElapsedValue( counterID, &tickCurrent, &tickElapse );
                    } else {
                        timeOut = TRUE;
                    }
                }
            }
 
#else /* #if( CAN_70_USE_OS_COUNTER == TRUE ) */
 
            /* [SWS_Can_00281] */
            /* Wait until transition completes. */
            counterTimeout = ( uint32 )CAN_TIMEOUT_DURATION * ( uint32 )CAN_70_COUNT_PER_MSEC;
            timeOut = TRUE;
            for ( counter = counterTimeout; counter > 0U; counter-- ) {
                Can_70_HW_GetMode( controllerId, &controllerMode );
                if ( FALSE == controllerMode.InTransition ) {
                    timeOut = FALSE;
                    break;
                } else {
                    /* Nothing */
                }
            }
           
#endif /* #if( CAN_70_USE_OS_COUNTER == TRUE ) */
 
            /* Timeout check. */
            if ( TRUE == timeOut ) {
               
#if( CAN_DEV_ERROR_DETECT == TRUE )
               
                ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                         ( uint8 )CAN_SID_INIT,
                                         ( uint8 )CAN_E_INIT_FAILED );
               
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
               
                return;
            } else {
                /* Nothing */
            }
 
            /* Change channel mode of CAN controller to RESET. */
            Can_70_HW_SetChannelMode( controllerId, channelId, CAN_70_CMODE_RESET );
               
#if( CAN_70_USE_OS_COUNTER == TRUE )
           
            /* Wait until transition completes. */
            timeOut = FALSE;
            tickElapse = 0U;
            tickValue = tickTimeout;
            ( void )GetCounterValue( counterID, &tickCurrent );
            while ( FALSE == timeOut ) {
                Can_70_HW_GetMode( controllerId, &controllerMode );
                if ( FALSE == controllerMode.InTransition ) {
                    break;
                } else {
                    if ( tickValue > tickElapse ) {
                        tickValue -= tickElapse;
                        ( void )GetElapsedValue( counterID, &tickCurrent, &tickElapse );
                    } else {
                        timeOut = TRUE;
                    }
                }
            }
 
#else /* #if( CAN_70_USE_OS_COUNTER == TRUE ) */
 
            /* Wait until transition completes. */
            timeOut = TRUE;
            for ( counter = counterTimeout; counter > 0U; counter-- ) {
                Can_70_HW_GetMode( controllerId, &controllerMode );
                if ( FALSE == controllerMode.InTransition ) {
                    timeOut = FALSE;
                    break;
                } else {
                    /* Nothing */
                }
            }
           
#endif /* #if( CAN_70_USE_OS_COUNTER == TRUE ) */
 
            /* Timeout check. */
            if ( TRUE == timeOut ) {
               
#if( CAN_DEV_ERROR_DETECT == TRUE )
               
                ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                         ( uint8 )CAN_SID_INIT,
                                         ( uint8 )CAN_E_INIT_FAILED );
               
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
               
                return;
            } else {
                /* Nothing */
            }
               
            /* [SWS_Can_00077],[SWS_Can_00238],[SWS_Can_00007],[SWS_Can_00021],[SWS_Can_00053],
               [SWS_Can_00056],[SWS_Can_00236],[SWS_Can_00239],[SWS_Can_00240],[SWS_Can_00245],
               [SWS_Can_00277],[SWS_Can_00407],[SWS_Can_00419],[SWS_Can_00274]
            */
            /* Initialize CanController */
            Can_70_HW_SetClock( controllerId, canController->CanQClockSource );
            Can_70_HW_SetBaudrate( controllerId, Can_70_ConfigPtr->CanConfigSet, s_CurrentBaudrateId[ controllerIndex ] );
            Can_70_HW_SetAfl( controllerId, Can_70_ConfigPtr->CanConfigSet );
            Can_70_HW_SetBuffer( controllerId, Can_70_ConfigPtr->CanConfigSet );
            Can_70_HW_SetCanCommon( controllerId );
 
#if ( CAN_70_USE_CANFD == TRUE )
           
            Can_70_HW_SetCanFd( controllerId, Can_70_ConfigPtr->CanConfigSet );
           
#endif /* #if ( CAN_70_USE_CANFD == TRUE ) */
 
            Can_70_HW_SetEcc( controllerId );
            Can_70_HW_SetRamWindow( controllerId, 1U );
           
            /* [SWS_Can_00259] */
            /* Change channel mode of CAN controller to OPERATION. */
            Can_70_HW_SetGlobalMode( controllerId, CAN_70_GMODE_OPERATION );
               
#if( CAN_70_USE_OS_COUNTER == TRUE )
           
            /* Wait until transition completes. */
            timeOut = FALSE;
            tickElapse = 0U;
            tickValue = tickTimeout;
            ( void )GetCounterValue( counterID, &tickCurrent );
            while ( FALSE == timeOut ) {
                Can_70_HW_GetMode( controllerId, &controllerMode );
                if ( FALSE == controllerMode.InTransition ) {
                    break;
                } else {
                    if ( tickValue > tickElapse ) {
                        tickValue -= tickElapse;
                        ( void )GetElapsedValue( counterID, &tickCurrent, &tickElapse );
                    } else {
                        timeOut = TRUE;
                    }
                }
            }
 
#else /* #if( CAN_70_USE_OS_COUNTER == TRUE ) */
 
            /* Wait until transition completes. */
            timeOut = TRUE;
            for ( counter = counterTimeout; counter > 0U; counter-- ) {
                Can_70_HW_GetMode( controllerId, &controllerMode );
                if ( FALSE == controllerMode.InTransition ) {
                    timeOut = FALSE;
                    break;
                } else {
                    /* Nothing */
                }
            }
           
#endif /* #if( CAN_70_USE_OS_COUNTER == TRUE ) */
 
            /* Timeout check. */
            if ( TRUE == timeOut ) {
               
#if( CAN_DEV_ERROR_DETECT == TRUE )
               
                ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                         ( uint8 )CAN_SID_INIT,
                                         ( uint8 )CAN_E_INIT_FAILED );
               
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
               
                return;
            } else {
                /* Nothing */
            }
           
            /* Enabling RxFIFO is performed when global mode is OPERATION. */
            /* See chapter F24(18.3.25) / F25(19.3.25) of HW manual. */
            Can_70_HW_EnableRxFifo( controllerId, Can_70_ConfigPtr->CanConfigSet );
               
            /* [SWS_Can_00259] */
            /* Set CAN controller state. */
            s_ControllerStatus[ controllerIndex ] = CAN_CS_STOPPED;
            Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_STOPPED;
           
            CanActivatedCount++;
        }
    }
 
    /* [SWS_Can_00246],[SWS_BSW_00071] */
    /* Set module state. */
    if ( 0U < CanActivatedCount ) {
        s_CanModuleStatus = CAN_READY;
    }
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_SETCONTROLLERMODE (0x03)                             */
/* Name        : Can_SetControllerMode                                        */
/* Param       : (in) Controller        CAN controller for which the status   */
/*                                      shall be changed.                     */
/*             : (in) Transition        Transition value to request new CAN   */
/*                                      controller state.                     */
/* Return      : Std_ReturnType         E_OK      request accepted            */
/*                                      E_NOT_OK  request not accepted,       */
/*                                               a development error occurred */
/* Contents    : This function performs software triggered state transitions  */
/*               of the CAN controller State machine.                         */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition )
{
    bool_t result;
    uint8  channelId;
    uint8  checkResult;
    uint8                                     controllerId;
    uint8_least                               controllerIndex;
    const Can_ControllerType*                 canController;
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
    /* [SWS_Can_00198] */
    /* Check module status. */
    if ( CAN_UNINIT == s_CanModuleStatus ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_SETCONTROLLERMODE,
                                 ( uint8 )CAN_E_UNINIT );
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        /* [SWS_Can_00026],[SWS_Can_00058],[SWS_Can_00079],[SWS_Can_00089],[SWS_Can_00091],[SWS_Can_00234],
           [SWS_Can_00235],[SWS_BSW_00144],[SWS_Can_00199],[SWS_Can_00089] */
        /* Check parameters. */
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
        if ( Controller == canController->CanControllerId ) {
            controllerId = canController->CanQChannelId;
            break;
        } else {
            canController = NULL_PTR;
        }
    }
 
 
    if ( ( NULL_PTR == canController )
     ||  ( TRUE != canController->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_SETCONTROLLERMODE,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
    /* [SWS_Can_00200],[SWS_Can_00409],[SWS_Can_00411] */
    /* Check parameters.Check whether operation mode transition is possible. */
    checkResult = matrixTransition[ s_ControllerStatus[ controllerIndex ] ][ Transition ];
    if ( CAN_70_MODE_TRANSITION_NG == checkResult ) {
       
#if( CAN_DEV_ERROR_DETECT == TRUE )
       
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_SETCONTROLLERMODE,
                                 ( uint8 )CAN_E_TRANSITION );
       
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
       
        return E_NOT_OK;
   
    } else if ( CAN_70_MODE_TRANSITION_SAME == checkResult ) {
        /* If the value of matrixTransition is CAN_70_MODE_TRANSITION_SAME, return E_OK and exit  */
        return E_OK;
    } else {
        /* Nothing */
    }
   
    /* [SWS_Can_00409],[SWS_Can_00411] */
    /* Check operation mode transition information. */
    if ( CAN_TO_NONE != Can_70_ControllerStatusAction[ controllerIndex ] ) {
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
    /* [SWS_Can_00372] */
    /* Change the status during operation mode transition. */
    if ( CAN_CS_STOPPED == Transition ) {
        Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_STOPPED;
    } else if ( CAN_CS_STARTED == Transition ) {
        Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_STARTED;
    } else {
        /* CAN_CS_SLEEP */
        Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_SLEEP;
    }
   
    /* [SWS_Can_00294] */
    /* Disable interrupts. */
    if ( 0U == s_DisableInterruptsCount[ controllerIndex ] ) {
        /* Disable interrupts during operation mode transitions. */
        Can_70_HW_DisableInterrupt( controllerId );
    } else {
        /* Nothing */
    }
   
    /* [SWS_Can_00077],[SWS_Can_00238],[SWS_Can_00048] */
    /* Check wakeup detection.Check bus off detection. */
    channelId = 0U;  /* tentative */
    result = FALSE;
    if ( CAN_CS_SLEEP == s_ControllerStatus[ controllerIndex ] ) {
       
#if ( CAN_70_WAKEUP_SUPPORT == TRUE )
 
        if ( TRUE == canController->CanWakeupSupport ) {
            result = Can_70_HW_CheckWakeup( controllerId, channelId );
        } else {
            /* do nothing */
        }
       
#endif /* #if ( CAN_70_WAKEUP_SUPPORT == TRUE ) */
       
    } else if ( CAN_CS_STARTED == s_ControllerStatus[ controllerIndex ] ) {
        result = Can_70_HW_CheckBusoff( controllerId, channelId );
    } else {
        /* Nothing */
    }
   
    if ( TRUE == result ) {
        if ( 0U == s_DisableInterruptsCount[ controllerIndex ] )  {
            Can_70_HW_EnableInterrupt( controllerId, Can_70_ConfigPtr->CanConfigSet, s_ControllerStatus[ controllerIndex ], Can_70_TxBufferUsesPolling[ controllerIndex ], Can_70_RxBufferUsesPolling[ controllerIndex ] );
        } else {
            /* Nothing */
        }
        Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_NONE;
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
    /* [SWS_Can_00017],[SWS_Can_00384],[SWS_Can_00196],[SWS_Can_00425],[SWS_Can_00197],
       [SWS_Can_00426],[SWS_Can_00257],[SWS_Can_00261],[SWS_Can_00262],[SWS_Can_00263],
       [SWS_Can_00264],[SWS_Can_00265],[SWS_Can_00266],[SWS_Can_00268],[SWS_Can_00282],
       [SWS_Can_00398]
    */
    /* Change CAN controller mode. */
    if ( CAN_CS_STOPPED == Transition ) {
        Can_70_HW_SetChannelMode( controllerId, channelId, CAN_70_CMODE_RESET );
    } else if ( CAN_CS_STARTED == Transition ) {
        Can_70_HW_SetBaudrate( controllerId, Can_70_ConfigPtr->CanConfigSet, s_CurrentBaudrateId[ controllerIndex ] );
        Can_70_HW_SetChannelMode( controllerId, channelId, CAN_70_CMODE_OPERATION );
    } else {
        /* CAN_CS_SLEEP */
        /* Nothing */
    }
 
    return E_OK;
}
 
 
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_DISABLECONTROLLERINTERRUPT (0x04)                    */
/* Name        : Can_DisableControllerInterrupts                              */
/* Param       : (in) Controller     CAN controller for which interrupts      */
/*                                   shall be disabled.                       */
/* Return      : void                                                         */
/* Contents    : This function disables all interrupts for                    */
/*               this CAN controller.                                         */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_DisableControllerInterrupts( uint8 Controller )
{
    uint8                                     controllerId;
    uint8_least                               controllerInedx;
    const Can_ControllerType*                 controllerCfg;
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_00205] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_DISABLECONTROLLERINTERRUPT,
                                 ( uint8 ) CAN_E_UNINIT );
        return;
    }
   
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        /* Check parameters. */
        controllerCfg = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerInedx ];
        if ( Controller == controllerCfg->CanControllerId ) {
            controllerId = controllerCfg->CanQChannelId;
            break;
        } else {
            controllerCfg = NULL_PTR;
        }
    }
 
    if ( ( NULL_PTR == controllerCfg )
     ||  ( TRUE != controllerCfg->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
        /* [SWS_Can_00206] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_DISABLECONTROLLERINTERRUPT,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return;
    }
   
    /* [SWS_Can_00049] */
    /* If the operation mode is in transition, only the interrupts counter is updated without interrupt control. */
    if ( CAN_TO_NONE == Can_70_ControllerStatusAction[ controllerInedx ] ) {
       
        /* Disable the CAN interrupt. */
        if ( 0U == s_DisableInterruptsCount[ controllerInedx ] ) {
            Can_70_HW_DisableInterrupt( controllerId );
        }
 
    }
   
    /* [SWS_Can_00202] */
    /* Update interrupts counter. */
    if ( 255U > s_DisableInterruptsCount[ controllerInedx ] ) {
        s_DisableInterruptsCount[ controllerInedx ]++;
    }
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_ENABLECONTROLLERINTERRUPT (0x05)                     */
/* Name        : Can_EnableControllerInterrupts                               */
/* Param       : (in) Controller     CAN controller for which interrupts      */
/*                                   shall be re-enabled                      */
/* Return      : void                                                         */
/* Contents    : This function enables all allowed interrupts.                */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_EnableControllerInterrupts( uint8 Controller )
{
    uint8                                     controllerId;
    uint8_least                               controllerInedx;
    const Can_ControllerType*                 controllerCfg;
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_00209] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_ENABLECONTROLLERINTERRUPT,
                                 ( uint8 ) CAN_E_UNINIT );
        return;
    }
 
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    /* Check parameters. */
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        controllerCfg = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerInedx ];
        if ( Controller == controllerCfg->CanControllerId ) {
            controllerId = controllerCfg->CanQChannelId;
            break;
        } else {
            controllerCfg = NULL_PTR;
        }
    }
 
    if ( ( NULL_PTR == controllerCfg )
     ||  ( TRUE != controllerCfg->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
        /* [SWS_Can_00210] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_ENABLECONTROLLERINTERRUPT,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return;
    }
 
    /* [SWS_Can_00050] */
    /* If the operation mode is in transition, only the interrupts counter is updated without interrupt control. */
    if ( CAN_TO_NONE == Can_70_ControllerStatusAction[ controllerInedx ] ) {
   
        /* Enable the CAN interrupt. */
        if ( 1U == s_DisableInterruptsCount[ controllerInedx ] ) {
            Can_70_HW_EnableInterrupt( controllerId, Can_70_ConfigPtr->CanConfigSet, s_ControllerStatus[ controllerInedx ], Can_70_TxBufferUsesPolling[ controllerInedx ], Can_70_RxBufferUsesPolling[ controllerInedx ] );
        }
       
    }
   
    /* [SWS_Can_00208] */
    /* Update interrupts counter. */
    if ( 1U <= s_DisableInterruptsCount[ controllerInedx ] ) {
        s_DisableInterruptsCount[ controllerInedx ]--;
    }
}
 
#if(CAN_70_WAKEUP_SUPPORT == TRUE)
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_CHECKWAKEUP (0x0b)                                   */
/* Name        : Can_CheckWakeup                                              */
/* Param       : (in) Controller     Controller to be checked for a wakeup.   */
/* Return      : Std_ReturnType      E_OK      API call has been accepted     */
/*                                   E_NOT_OK  API call has not been accepted */
/* Contents    : This function checks if a wakeup has occurred for the given  */
/*               controller.                                                  */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_CheckWakeup( uint8 Controller )
{
    const Can_ControllerType* controllerCfg;
    Std_ReturnType            ret;
    EcuM_WakeupSourceType     wakeUpSource;
    bool_t                    retVal;
    uint8                     channelId;
    uint8                     controllerId;
    uint8_least               controllerInedx;
   
    ret = E_NOT_OK;
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_UNINIT == s_CanModuleStatus ) {
        /* [SWS_Can_00362] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                         ( uint8 ) CAN_SID_CHECKWAKEUP, ( uint8 ) CAN_E_UNINIT );
    } else
 
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    {
        for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
            controllerCfg = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerInedx ];
            if ( Controller == controllerCfg->CanControllerId ) {
                controllerId = controllerCfg->CanQChannelId;
                break;
            } else {
                controllerCfg = NULL_PTR;
            }
        }
 
        if ( ( NULL_PTR == controllerCfg )
         ||  ( TRUE != controllerCfg->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
            /* [SWS_Can_00363] */
            /* Check parameters. */
            ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                     ( uint8 )CAN_SID_CHECKWAKEUP,
                                     ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        } else  {
            /* [SWS_Can_00361] */
            /* Check wakeup */
            channelId = 0U;  /* tentative */
            retVal = Can_70_HW_CheckWakeup( controllerId, channelId );
            if ( FALSE != retVal ) {
                /* call EcuM in case of a wakeup event */
                wakeUpSource = controllerCfg->CanWakeupSourceRef;
                EcuM_SetWakeupEvent( wakeUpSource );
            }
           
            ret = E_OK;
        }
    }
   
    return ret;
}
#endif  /* #if(CAN_70_WAKEUP_SUPPORT == TRUE) */
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_WRITE (0x06)                                         */
/* Name        : Can_Write                                                    */
/* Param       : (in) Hth     Controller to be checked for a wakeup.          */
/*             : (in) PduInfo     information which HW-transmit handle shall  */
/*                                be used for transmit. Implicitly this is    */
/*                                also the information about the controller   */
/*                                to use because the Hth numbers are unique   */
/*                                inside one hardware unit.                   */
/* Return      : Std_ReturnType     E_OK      Write command has been accepted */
/*                                  E_NOT_OK  Nodevelopment error occurred    */
/*                                  CAN_BUSY  No TX hardware buffer available */
/*                                            or pre-emptive call of          */
/*                                            Can_Write that can't be         */
/*                                            implemented  re-entrant         */
/* Contents    : This function is used to send the CAN message on the         */
/*               CAN bus. It also compares the Transmit Id priority and       */
/*               sends the higher priority message on the bus if              */
/*               CAN_HW_TRANSMIT_CANCELLATION is TRUE                         */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType* PduInfo )
{
    const Can_HardwareObjectType*           canHardwareObject;
    uint8                                   txBufNo;
    Std_ReturnType                          result;
    PduInfoType                             pduInfoData;
    Can_PduType                             canPdu;
    bool_t                                  timeStamp;
    bool_t                                  rateSwitch;
    uint8                                   paddingValue;
    uint8                                   controllerId;
    uint8_least                             controllerIndex;
    uint8_least                             index;
 
#if( CAN_70_USE_CANFD == TRUE )
 
    const Can_ControllerType*               controllerCfg;
    const Can_ControllerBaudrateConfigType* baudrateCfg;
 
#endif /* #if( CAN_70_USE_CANFD == TRUE ) */        
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* [SWS_Can_00216] */
    /* Check module state. */
    if ( CAN_UNINIT == s_CanModuleStatus ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_WRITE,
                                 ( uint8 )CAN_E_UNINIT );
        return E_NOT_OK;
    }
   
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    /* Select Tx Buffer Number. */
    txBufNo = CAN_70_RL78F2X_TXBUFFER_MAX;
   
#if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE )
   
    /* Search for empty Tx buffer with matching Hth from s_MultiTxHthInfo. */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        for ( index = 0U; index < CAN_70_RL78F2X_TXBUFFER_MAX; index++ ) {
            if ( ( TRUE          == s_MultiTxHthInfo[ controllerIndex ][ index ].Enable )
              && ( ( uint8 )Hth  == s_MultiTxHthInfo[ controllerIndex ][ index ].Hth ) ) {
                txBufNo = ( uint8 )index;
                if ( FALSE == Can_70_TxRequestInfo[ controllerIndex ][ index ].Enable ) {
                    break;
                }
            }
        }
        if ( CAN_70_RL78F2X_TXBUFFER_MAX != txBufNo ) {
            break;
        }
    }
   
#else /* #if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE ) */
   
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        for ( index = 0U; index < CAN_70_RL78F2X_TXBUFFER_MAX; index++ ) {
            if ( ( uint8 )Hth == Can_70_IndxexTxHwObj[ controllerIndex ][ index ].Hth ) {
                txBufNo = ( uint8 )index;
                break;
            }
        }
        if ( CAN_70_RL78F2X_TXBUFFER_MAX != txBufNo ) {
            break;
        }
    }
   
#endif /* #if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE ) */
   
    /* Parameter Hth check. */
    if ( ( CAN_70_RL78F2X_TXBUFFER_MAX   == txBufNo )
      || ( CAN_70_NUM_OF_HARDWARE_OBJECT == Can_70_IndxexTxHwObj[ controllerIndex ][ txBufNo ].IndexTxHwObj ) ) {
        /* [SWS_Can_00217] */
#if( CAN_DEV_ERROR_DETECT == TRUE )
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_WRITE,
                                 ( uint8 )CAN_E_PARAM_HANDLE );
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
        return E_NOT_OK;
    }
   
    /* Get Hardware Object. */
    canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ Can_70_IndxexTxHwObj[ controllerIndex ][ txBufNo ].IndexTxHwObj ];
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
    /* [SWS_Can_00505] */
    /* Check : PduInfo->sdu */
    if ( ( FALSE    == canHardwareObject->CanTriggerTransmitEnable )
      && ( NULL_PTR == PduInfo->sdu ) ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_WRITE,
                                 ( uint8 )CAN_E_PARAM_POINTER );
        return E_NOT_OK;
       
    }
   
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    /* [SWS_Can_00026] */
    /* Check operation mode transition information. */
    if ( CAN_TO_NONE != Can_70_ControllerStatusAction[ controllerIndex ] ) {
        return E_NOT_OK;
    }
 
    /* [SWS_Can_00261] */
    /* Check CAN controller state. */
    if ( CAN_CS_STARTED != s_ControllerStatus[ controllerIndex ] ) {
        return E_NOT_OK;
    }
   
    /* [SWS_Can_00213],[SWS_Can_00100],[SWS_Can_00100],[SWS_Can_00401],[SWS_Can_00402],[SWS_Can_00403],[SWS_Can_00039]*/
    /* Check the free status of the Tx buffer */
    if ( TRUE == Can_70_TxRequestInfo[ controllerIndex ][ txBufNo ].Enable ) {
        return CAN_BUSY;
    }
 
    /* [SWS_Can_00214] */
    /* Check reentrancy. */
    if ( 0U != ( ( s_TxReentrant[ controllerIndex ] >> txBufNo ) & 1U )  ) {
        return CAN_BUSY;
    } else {
        /* Set reentrancy. */
        s_TxReentrant[ controllerIndex ] |= ( uint8 )( 1U << txBufNo );
    }
   
    /* [SWS_Can_00504],[SWS_Can_00506],[SWS_Can_00222] */
    /* Trigger transmission. */
    if ( ( TRUE     == canHardwareObject->CanTriggerTransmitEnable )
      && ( NULL_PTR == PduInfo->sdu ) ) {
        result = CanIf_TriggerTransmit( PduInfo->swPduHandle, &pduInfoData);
        if ( E_OK !=  result ) {
            return E_NOT_OK;
        } else {
            canPdu.swPduHandle = PduInfo->swPduHandle;
            canPdu.length = ( uint8 )pduInfoData.SduLength;
            canPdu.id = ( Can_IdType )pduInfoData.MetaDataPtr[ 0U ]
                    | ( ( Can_IdType )pduInfoData.MetaDataPtr[ 1U ] << 8U )
                    | ( ( Can_IdType )pduInfoData.MetaDataPtr[ 2U ] << 16U )
                    | ( ( Can_IdType )pduInfoData.MetaDataPtr[ 3U ] << 24U );
            canPdu.sdu = pduInfoData.SduDataPtr;
        }
    } else {
        canPdu.swPduHandle = PduInfo->swPduHandle;
        canPdu.length = PduInfo->length;
        canPdu.id = PduInfo->id;
        canPdu.sdu = PduInfo->sdu;
    }
 
    rateSwitch = FALSE;
    paddingValue = 0U;
   
    /* [SWS_Can_00218] */
    /* Check : DLC */
#if( CAN_70_USE_CANFD == TRUE )
 
    /* CAN FD Mode */
   
    /* Get CAN controller configuration. */
    controllerCfg = canHardwareObject->CanControllerRef;
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
 
    if ( ( NULL_PTR == controllerCfg )
      || ( FALSE == controllerCfg->CanControllerActivation ) ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_WRITE,
                                 ( uint8 )CAN_E_PARAM_DATA_LENGTH );
        return E_NOT_OK;
    }
   
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* Get Baudrate configuration. */
    if ( CAN_70_NUM_OF_BAUDRATE_TABLE == s_CurrentBaudrateId[ controllerIndex ] ) {
        baudrateCfg = controllerCfg->CanControllerDefaultBaudrate;
    } else {
        baudrateCfg = &controllerCfg->CanControllerBaudRateConfig[ s_CurrentBaudrateId[ controllerIndex ] ];
    }
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
    if ( NULL_PTR == baudrateCfg ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_WRITE,
                                 ( uint8 )CAN_E_PARAM_DATA_LENGTH );
        return E_NOT_OK;
    }
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    if ( NULL_PTR == baudrateCfg->CanControllerFdBaudrateConfig ) {
       
        /* Can Controller : Classical-CAN Mode */
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
       
        if ( 8U < canPdu.length ) {
            ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                     ( uint8 )CAN_SID_WRITE,
                                     ( uint8 )CAN_E_PARAM_DATA_LENGTH );
            return E_NOT_OK;
        }
       
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    } else {
       
        /* Can Controller : CAN FD Mode */
       
#if( CAN_DEV_ERROR_DETECT == TRUE )
       
        if ( 0U != ( CAN_70_MASK_CANID_CANFD & canPdu.id ) ) {
            /* PDU : CAN FD */
            if ( 64U < canPdu.length ) {
                ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                         ( uint8 )CAN_SID_WRITE,
                                         ( uint8 )CAN_E_PARAM_DATA_LENGTH );
                return E_NOT_OK;
            }                
        } else {
            /* PDU : Classical-CAN */
            if ( 8U < canPdu.length ) {
                ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                         ( uint8 )CAN_SID_WRITE,
                                         ( uint8 )CAN_E_PARAM_DATA_LENGTH );
                return E_NOT_OK;
            }
        }
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        /* GetCanControllerTxBitRateSwitch */
        rateSwitch =  ( baudrateCfg->CanControllerFdBaudrateConfig )->CanControllerTxBitRateSwitch;
 
        /* CanFdPaddingValue */
        paddingValue = canHardwareObject->CanFdPaddingValue;
    }
   
#else /* #if( CAN_70_USE_CANFD == TRUE ) */
 
    /* CAN Only Mode */
   
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    if ( 8U < canPdu.length ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_WRITE,
                                 ( uint8 )CAN_E_PARAM_DATA_LENGTH );
        return E_NOT_OK;
    }
   
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
#endif /* #if( CAN_70_USE_CANFD == TRUE ) */        
       
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
    timeStamp = s_EnableEgressTimeStamp[ controllerIndex ][ txBufNo ];
 
#else /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
    timeStamp = FALSE;
   
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
    /* [SWS_Can_00212],[SWS_Can_00486],[SWS_Can_00011],[SWS_Can_00502],[SWS_Can_00059],
     * [SWS_Can_00077],[SWS_Can_00238]
     */
    /* Send request to CAN controller. */
    controllerId = ( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ].CanQChannelId;
    Can_70_HW_SendRequest( controllerId,
                           txBufNo,
                           &canPdu,
                           timeStamp,
                           rateSwitch,
                           paddingValue );
 
    /* [SWS_Can_00275],[SWS_Can_00276],[SWS_Can_00016] */
    /* Set transmission request information. */
    Can_70_TxRequestInfo[ controllerIndex ][txBufNo].Enable = TRUE;
   
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
 
    Can_70_TxRequestInfo[ controllerIndex ][txBufNo].Timestamp = timeStamp;
   
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
    Can_70_TxRequestInfo[ controllerIndex ][txBufNo].CanTxPduId = canPdu.swPduHandle;
   
    /* [SWS_Can_00214] */
    /* Release reentrancy. */
    s_TxReentrant[ controllerIndex ] &= ~( 1U << txBufNo );
   
    return E_OK;
}
 
#if ( ( CAN_70_TX_MIXED_PROCESSING == TRUE ) || ( CAN_70_TX_POLLING_PROCESSING == TRUE ) )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_MAINFUNCTION_WRITE (0x01)                            */
/* Name        : Can_MainFunction_Write                                       */
/* Param       : void                                                         */
/* Return      : void                                                         */
/* Contents    : This function performs the polling of TX confirmation and    */
/*               TX cancellation                                              */
/*               confirmation when CAN_TX_PROCESSING is set to POLLING.       */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_MainFunction_Write( void )
{
    uint8                         controllerId;
    uint8_least                   index;
    const Can_HardwareObjectType* canHardwareObject;
    CAN_70_TxBufStatInfoType      result;
    uint8_least                   controllerIndex;
    const Can_ControllerType*     canController;
 
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
    uint8                         channelId;
    uint8                         objectId[CAN_70_RL78F2X_THL_MAX];
    uint16                        timeStampCounter[CAN_70_RL78F2X_THL_MAX];
    uint8                         timeStampNum;
    uint8                         txBufNo;
    PduIdType                     txPduId;
    uint16                        timeStamp;
    Can_70_EgressTimeStampType*   pEgress;
    Can_70_EgressTimeStampType    egressWork[ CAN_70_NUM_OF_EGRESS ];
    uint8_least                   indexEgress;
    uint8_least                   indexEgressWork;
   
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
    /* [SWS_BSW_00037] */
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        return;
    }
 
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
 
#if ( CAN_70_TX_INTERRUPT_PROCESSING == TRUE )
 
        /* Skip processing if using interrupt.  */
        if ( CAN_PROCESSING_INTERRUPT == canController->CanTxProcessing ) {
            continue;
        }
 
#endif /* #if ( CAN_70_TX_INTERRUPT_PROCESSING == TRUE ) */
 
        controllerId = canController->CanQChannelId;
 
        for ( index = 0U; index < CAN_70_RL78F2X_TXBUFFER_MAX; index++ ) {
           
            /* Get Hardware Object. */
            if ( CAN_70_NUM_OF_HARDWARE_OBJECT > Can_70_IndxexTxHwObj[ controllerIndex ][ index ].IndexTxHwObj  ) {
                canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ Can_70_IndxexTxHwObj[ controllerIndex ][ index ].IndexTxHwObj ];
 
#if ( CAN_70_TX_MIXED_PROCESSING == TRUE )
               
                /* Skip processing if not using polling.  */
                if ( CAN_PROCESSING_MIXED == canController->CanTxProcessing ) {
                    if ( FALSE == canHardwareObject->CanHardwareObjectUsesPolling ) {
                        canHardwareObject = NULL_PTR;
                    }
                }
 
#endif /* #if ( CAN_70_TX_MIXED_PROCESSING == TRUE ) */
 
            } else {
                canHardwareObject = NULL_PTR;
            }
       
            /* Check if the HTH is confirmed. */
            if ( NULL_PTR != canHardwareObject ) {
               
                /* Check the send buffer status. */
                result = Can_70_HW_GetTxBufferStatus( controllerId, ( uint8 )index );
                if ( CAN_70_TXBUFSTAT_SENT == result ) {
                   
                    /* Clear the send buffer status. */
                    Can_70_HW_ClearTxBufferStatus( controllerId, ( uint8 )index );
           
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
                    /* Check send request information. */
                    if ( ( FALSE == Can_70_TxRequestInfo[ controllerIndex ][ index ].Timestamp )
                      && ( TRUE  == Can_70_TxRequestInfo[ controllerIndex ][ index ].Enable ) ) {
             
#else /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
       
                    /* Check send request information. */
                    if ( TRUE  == Can_70_TxRequestInfo[ controllerIndex ][ index ].Enable ) {
             
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
                        /* Notify completion of sending. */
                        CanIf_TxConfirmation( Can_70_TxRequestInfo[ controllerIndex ][ index ].CanTxPduId );
 
                        /* Clear send request information. */
                        Can_70_TxRequestInfo[ controllerIndex ][ index ].Enable = FALSE;
                    }
                } else if ( CAN_70_TXBUFSTAT_OTHER == result ) {
                   
                    /* See detailed design document. */
                    Can_70_HW_ClearTxBufferStatus( controllerId, ( uint8 )index );
                   
                } else {
                    /* Nothing */
                }
            }
        }
   
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
        /* Get sending history information. */
        channelId = 0U;  /* tentative */
        Can_70_HW_GetSendHistory( controllerId, channelId,
                                  &objectId[ 0U ], &timeStampCounter[ 0U ], &timeStampNum );
        for ( index = 0U; index < timeStampNum; index++ ) {
           
            /* Get Hardware Object. */
            txBufNo = objectId[ index ];
            if ( CAN_70_NUM_OF_HARDWARE_OBJECT > Can_70_IndxexTxHwObj[ controllerIndex ][ txBufNo ].IndexTxHwObj  ) {
                canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ Can_70_IndxexTxHwObj[ controllerIndex ][ txBufNo ].IndexTxHwObj ];
       
#if ( CAN_70_TX_MIXED_PROCESSING == TRUE )
 
                /* Skip processing if not using polling.  */
                if ( CAN_PROCESSING_MIXED == canController->CanTxProcessing ) {
                    if ( FALSE == canHardwareObject->CanHardwareObjectUsesPolling ) {
                        canHardwareObject = NULL_PTR;
                    }
                }
       
#endif /* #if ( CAN_70_TX_MIXED_PROCESSING == TRUE ) */
 
            } else {
                canHardwareObject = NULL_PTR;
            }
       
            /* Check if the HTH is confirmed. */
            if ( ( NULL_PTR != canHardwareObject )
              && ( TRUE == Can_70_TxRequestInfo[ controllerIndex ][ txBufNo ].Enable ) ) {
                txPduId = Can_70_TxRequestInfo[ controllerIndex ][ txBufNo ].CanTxPduId;
                timeStamp = timeStampCounter[ index ];
               
                /* Add timestamp information to Can_70_EgressTimeStampData. */
                /* See detailed design document. */
               
                /* Initialize egressWork. */
                for ( indexEgressWork = 0U; indexEgressWork < CAN_70_NUM_OF_EGRESS; indexEgressWork++ ) {
                    egressWork[ indexEgressWork ].Enable = FALSE;
                    egressWork[ indexEgressWork ].TxPduId = 0U;
                    egressWork[ indexEgressWork ].TimeStamp = 0U;
                }
               
                /* Copy records in Can_70_EgressTimeStampData to egressWork. ( excluding the same PduId record ) */
                indexEgressWork = 0U;
                for ( indexEgress = 0U; indexEgress < CAN_70_NUM_OF_EGRESS; indexEgress++ ) {
                   
                    pEgress = &Can_70_EgressTimeStampData[ controllerIndex ][ txBufNo ][ indexEgress ];
                   
                    if ( TRUE == pEgress->Enable ) {
                        if ( txPduId != pEgress->TxPduId ) {
                            egressWork[ indexEgressWork ].Enable = pEgress->Enable;
                            egressWork[ indexEgressWork ].TxPduId = pEgress->TxPduId;
                            egressWork[ indexEgressWork ].TimeStamp = pEgress->TimeStamp;
                            indexEgressWork++;
                        }
                    } else {
                        break;
                    }
                }
               
                /* Copy records in EgressWork to Can_70_EgressTimeStampData. */
                if ( CAN_70_NUM_OF_EGRESS <= indexEgressWork ) {
                    indexEgress = 0U;
                    for ( indexEgressWork = 1U; indexEgressWork < CAN_70_NUM_OF_EGRESS; indexEgressWork++ ) {
                        pEgress = &Can_70_EgressTimeStampData[ controllerIndex ][ txBufNo ][ indexEgress ];
                        pEgress->Enable = egressWork[ indexEgressWork ].Enable;
                        pEgress->TxPduId = egressWork[ indexEgressWork ].TxPduId;
                        pEgress->TimeStamp = egressWork[ indexEgressWork ].TimeStamp;
                        indexEgress++;
                    }
                } else {
                    for ( indexEgress = 0U; indexEgress < indexEgressWork; indexEgress++ ) {
                        pEgress = &Can_70_EgressTimeStampData[ controllerIndex ][ txBufNo ][ indexEgress ];
                        pEgress->Enable = egressWork[ indexEgress ].Enable;
                        pEgress->TxPduId = egressWork[ indexEgress ].TxPduId;
                        pEgress->TimeStamp = egressWork[ indexEgress ].TimeStamp;
                    }
                }
               
                /* Add a record. */
                pEgress = &Can_70_EgressTimeStampData[ controllerIndex ][ txBufNo ][ indexEgress ];
                pEgress->Enable = TRUE;
                pEgress->TxPduId = txPduId;
                pEgress->TimeStamp = timeStamp;
               
                /* Notify completion of sending. */
                CanIf_TxConfirmation( Can_70_TxRequestInfo[ controllerIndex ][ txBufNo ].CanTxPduId );
 
                /* Clear send request information. */
                Can_70_TxRequestInfo[ controllerIndex ][ txBufNo ].Enable = FALSE;
               
            }
        }
 
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
    }
}
#endif  /* #if ( ( CAN_70_TX_MIXED_PROCESSING == TRUE ) || ( CAN_70_TX_POLLING_PROCESSING == TRUE ) ) */
 
#if( ( CAN_70_RX_MIXED_PROCESSING == TRUE ) || ( CAN_70_RX_POLLING_PROCESSING == TRUE ) )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_MAINFUNCTION_READ (0x08)                             */
/* Name        : Can_MainFunction_Read                                        */
/* Param       : void                                                         */
/* Return      : void                                                         */
/* Contents    : This function performs the polling of RX indications when    */
/*               CAN_RX_PROCESSING is set to POLLING.                         */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_MainFunction_Read( void )
{
    const Can_HardwareObjectType* canHardwareObject;
    uint8_least                   index;
    uint8                         controllerId;
    uint8                         channelId;
    uint8                         canObjectId;
    uint32                        id;
    uint8                         dlc;
    uint16                        rxTimestamp;
    uint8*                        pRxBuffer;
    uint8                         rxSize;
    bool_t                        resultLpduCallout;
    bool_t                        existRxData;
    Can_HwType                    mailBox;
    PduInfoType                   pduInfo;
    uint8_least                   controllerIndex;
    const Can_ControllerType*     canController;
    uint8                         bufNo;
   
 
    /* [SWS_BSW_00037] */
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        return;
    }
   
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
 
#if( CAN_70_RX_INTERRUPT_PROCESSING == TRUE )
 
        if ( CAN_PROCESSING_INTERRUPT == canController->CanRxProcessing ) {
            continue;
        }
 
#endif /* #if( CAN_70_RX_INTERRUPT_PROCESSING == TRUE ) */
 
        controllerId = canController->CanQChannelId;
        channelId = 0U;  /* tentative */
       
        /* [SWS_Can_00060],[SWS_Can_00237],[SWS_Can_00279],[SWS_Can_00299],[SWS_Can_00300],
           [SWS_Can_00396],[SWS_Can_00423],[SWS_Can_00489],[SWS_Can_00490],[SWS_Can_00501],
           [SWS_Can_00077],[SWS_Can_00222],[SWS_Can_00234],[SWS_Can_00238],[SWS_Can_00281],
           [SWS_Can_00436],[SWS_Can_00443],[ SWS_Can_00444]
        */
        for ( index = 0U; index < CAN_70_RL78F2X_RXFIFO_MAX; index++ ) {
           
            /* Get Hardware Object. */
            if ( CAN_70_NUM_OF_HARDWARE_OBJECT > Can_70_IndxexRxHwObj[ controllerIndex ][ index ]  ) {
                canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ Can_70_IndxexRxHwObj[ controllerIndex ][ index ] ];
       
#if( CAN_70_RX_MIXED_PROCESSING == TRUE )
 
                /* Skip processing if not using polling. */
                if ( CAN_PROCESSING_MIXED == canController->CanRxProcessing ) {
                    if ( FALSE == canHardwareObject->CanHardwareObjectUsesPolling ) {
                        canHardwareObject = NULL_PTR;
                    }
                }
       
#endif /* #if( CAN_70_RX_MIXED_PROCESSING == TRUE ) */
 
            } else {
                canHardwareObject = NULL_PTR;
            }
       
            /* Check if the HRH is confirmed. */
            if ( NULL_PTR !=  canHardwareObject ) {
               
                /* Check if there is data in the Rx FIFO. */
                canObjectId = canHardwareObject->CanObjectId;
                bufNo = ( uint8 )index;
                existRxData = Can_70_HW_CheckRxBuffer( controllerId, channelId, bufNo );
               
                while ( TRUE == existRxData ) {
                   
                    /* Initialize */
                    pRxBuffer = NULL_PTR;
                    id = 0U;
                    dlc = 0U;
                    rxTimestamp = 0U;
                   
                    /* Get received data. */
                    rxSize = CAN_70_RL78F2X_RXDATAFIELD_MAX;
                    Can_70_HW_GetRxBuffer( controllerId, channelId, bufNo,
                                                &id, &dlc, &rxTimestamp, &pRxBuffer, &rxSize );
                   
                    /* If a callout function is set in the configuration, execute the callout function. */
                    /* Do not process if the return value of the callout function is FALSE. */
                    resultLpduCallout = TRUE;
                    if ( NULL_PTR != CAN_LPDU_RECEIVE_CALLOUT_FUNCTION ) {                  
                        resultLpduCallout = ( *CAN_LPDU_RECEIVE_CALLOUT_FUNCTION )( canObjectId,
                                                                                    ( Can_IdType )id,
                                                                                    rxSize,
                                                                                    pRxBuffer ) ;
                    } else {
                        /* Nothing */
                    }
                   
                    if ( TRUE == resultLpduCallout ) {
                   
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
                        /* Set timestamp data. */
                        Can_70_IngressTimeStampData[ controllerIndex ][ bufNo ].Enable = TRUE;
                        Can_70_IngressTimeStampData[ controllerIndex ][ bufNo ].Hrh = ( Can_HwHandleType )canObjectId;
                        Can_70_IngressTimeStampData[ controllerIndex ][ bufNo ].TimeStamp = rxTimestamp;
 
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
                   
                        /* Set parameters of CanIf_RxIndication function. */
                        mailBox.CanId = ( Can_IdType )id;
                        mailBox.Hoh = ( Can_HwHandleType )canObjectId;
                        mailBox.ControllerId = canController->CanControllerId;
                        pduInfo.SduDataPtr = pRxBuffer;
                        pduInfo.MetaDataPtr = ( uint8* )( &id );
                        pduInfo.SduLength = rxSize;
                       
                        /*  Notify completion of receiving. */
                        CanIf_RxIndication( &mailBox, &pduInfo);
                       
                    }
                   
                    /* Change to next received data. */
                    Can_70_HW_UpdateRxBuffer( controllerId, channelId, bufNo );
                   
                    /* Check if there is data in the Rx FIFO. */
                    existRxData = Can_70_HW_CheckRxBuffer( controllerId, channelId, bufNo );
                }
            }
        }
    }
}
#endif /* #if( ( CAN_70_RX_MIXED_PROCESSING == TRUE ) || ( CAN_70_RX_POLLING_PROCESSING == TRUE ) ) */
 
#if ( CAN_70_BUSOFF_POLLING_PROCESSING == TRUE )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_MAINFUNCTION_BUSOFF (0x09)                           */
/* Name        : Can_MainFunction_BusOff                                      */
/* Param       : void                                                         */
/* Return      : void                                                         */
/* Contents    : This function performs the polling of bus-off events that    */
/*               are configured                                               */
/*               statically as 'to be polled'.                                */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_MainFunction_BusOff( void )
{
    uint8  controllerId;
    uint8  channelId;
    bool_t retVal;
    uint8_least                   controllerIndex;
    const Can_ControllerType*     canController;
   
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_BSW_00037] */
        /* Check the module status. */
        return;
    }
 
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        if ( CAN_CS_STARTED != s_ControllerStatus[ controllerIndex ] ) {
            /* [SWS_Can_00020] */
            /* Check CAN controller operating mode */
            continue;
        } else if ( CAN_TO_NONE != Can_70_ControllerStatusAction[ controllerIndex ] ) {
            /* [SWS_Can_00026] */
            /* Check operation mode transition information. */
            continue;
        }
 
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
 
#if ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE )
 
        if ( CAN_PROCESSING_INTERRUPT == canController->CanBusoffProcessing ) {
            continue;
        }
 
#endif /* #if ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE ) */
   
        /* [SWS_Can_00272],[SWS_Can_00109] */
        /* Check busoff */
        controllerId = canController->CanQChannelId;
        channelId = 0U;  /* tentative */
        retVal = Can_70_HW_CheckBusoff( controllerId, channelId );
        if ( TRUE == retVal ) {
            /* Operation mode transition */
            Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_BUSOFF;
            /* Disable interrupts during operation mode transitions. */
            Can_70_HW_DisableInterrupt( controllerId );
            /* Clears busoff related registers by transitioning to channel reset mode. */
            Can_70_HW_SetChannelMode( controllerId, channelId, CAN_70_CMODE_RESET );
        }
    }
}
#endif  /* #if ( CAN_70_BUSOFF_POLLING_PROCESSING == TRUE ) */
 
#if ( ( CAN_70_WAKEUP_SUPPORT == TRUE ) && ( CAN_70_WAKEUP_POLLING_PROCESSING == TRUE ) )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_MAINFUNCTION_WAKEUP (0x0a)                           */
/* Name        : Can_MainFunction_Wakeup                                      */
/* Param       : void                                                         */
/* Return      : void                                                         */
/* Contents    : This function performs the polling of wake-up events that    */
/*               are configured statically as 'to be polled'.                 */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_MainFunction_Wakeup( void )
{
    uint8                 controllerId;
    uint8                 channelId;
    bool_t                retVal;
    EcuM_WakeupSourceType wakeupSource;
    uint8_least                   controllerInedx;
    const Can_ControllerType*     canController;
   
   
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_BSW_00037] */
        /* Check module status. */
        return;
    }
 
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        if ( CAN_CS_SLEEP != s_ControllerStatus[ controllerInedx ] ) {
            /* [SWS_Can_00270] */
            /* Check CAN controller operating mode */
            continue;
        } else if ( CAN_TO_NONE != Can_70_ControllerStatusAction[ controllerInedx ] ) {
            /* [SWS_Can_00026] */
            /* Check operation mode transition information */
            continue;
        }
 
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerInedx ];
        if ( ( FALSE == canController->CanWakeupSupport )
 
#if ( CAN_70_WAKEUP_INTERRUPT_PROCESSING == TRUE )
 
         ||  ( CAN_PROCESSING_INTERRUPT == canController->CanWakeupProcessing )
 
#endif /* #if ( CAN_70_WAKEUP_INTERRUPT_PROCESSING == TRUE ) */
 
        ) {
            continue;
        }
   
        /* [SWS_Can_00112] */
        /* Check wakeup */
        controllerId = canController->CanQChannelId;
        channelId = 0U; /* tendative */
        retVal = Can_70_HW_CheckWakeup( controllerId, channelId );
        if ( TRUE == retVal ) {
            /* [SWS_Can_00364],[SWS_Can_00271] */
            /* Notify EcuM of CAN controller wakeup. */
            wakeupSource = canController->CanWakeupSourceRef;
            EcuM_CheckWakeup( wakeupSource );
               
            /* [SWS_Can_00270] */
            /* Clear wakeup flag. */
            /* Clear flag after notification according to AUTOSAR wakeup sequence.  */
            /* See AUTOSAR EcuM SWS Figure 9.5: CAN controller wake up by interrupt */
            Can_70_HW_ClearWakeup( controllerId, channelId );
            /* Operation mode transition */
            Can_70_ControllerStatusAction[ controllerInedx ] = CAN_TO_WAKEUP;
            /* Disable interrupts during operation mode transitions. */
            Can_70_HW_DisableInterrupt( controllerId );
        }
    }
}
#endif /* #if ( ( CAN_70_WAKEUP_SUPPORT == TRUE ) && ( CAN_70_WAKEUP_POLLING_PROCESSING == TRUE ) ) */
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_MAINFUNCTION_MODE (0x0c)                             */
/* Name        : Can_MainFunction_Mode                                        */
/* Param       : void                                                         */
/* Return      : void                                                         */
/* Contents    : This function performs the polling of CAN controller mode    */
/*               transitions.                                                 */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_MainFunction_Mode( void )
{
    Can_70_ControllerStateInfoType controllerStateInfo;
    Can_ControllerStateType        controllerState;
    uint8                          canControllerId = 0U;
    uint8                          channelId;
    uint8_least                    index;
    bool_t                         busoffNotification;
    uint8_least                    controllerIndex;
    uint8                          controllerId;
   
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        /* Initialize to not call CanIf_ControllerBusOff. */
        busoffNotification = FALSE;
       
        /* [SWS_BSW_00037] */
        /* Check module status. */
        if ( CAN_READY != s_CanModuleStatus ) {
           
            /* [SWS_BSW_00037] */
            /* In the case of CAN_TO_UNINIT, the operation mode is being changed by Can_DeInit. */
            /* Therefore, it does not return because CanIf_ControllerModeIndication is called. */
            if ( CAN_TO_UNINIT != Can_70_ControllerStatusAction[ controllerIndex ] ) {
                continue;
            }
           
        } else {
           
            /* [SWS_Can_00026] */
            /* Check operation mode transition information */
            if ( CAN_TO_NONE == Can_70_ControllerStatusAction[ controllerIndex ] ) {
                continue;
            }
           
            /* [SWS_Can_00077],[SWS_Can_00238],[SWS_Can_00369] */
            /* Check the completion of CAN controller mode transition. */
            canControllerId = ( (Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ] ).CanControllerId;
            controllerId = ( (Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ] ).CanQChannelId;
            Can_70_HW_GetMode( controllerId, &controllerStateInfo );
            if ( TRUE == controllerStateInfo.InTransition ) {
                return;
            }
 
           
            /* Executes operation mode transition processing. */
            /* See detailed design document. */    
            if ( CAN_TO_STARTED == Can_70_ControllerStatusAction[ controllerIndex ] ) {
                controllerState = CAN_CS_STARTED;
            } else if ( CAN_TO_SLEEP == Can_70_ControllerStatusAction[ controllerIndex ] ){
                controllerState = CAN_CS_SLEEP;
            } else { /* CAN_TO_STOPPED,CAN_TO_WAKEUP,CAN_TO_BUSOFF */
                controllerState = CAN_CS_STOPPED;
            }
           
            /* Decide whether to notify of bus off. */
            if ( CAN_TO_BUSOFF == Can_70_ControllerStatusAction[ controllerIndex ] ) {
                busoffNotification = TRUE;
            }
           
            if ( CAN_CS_STOPPED == controllerState ) {
                for ( index = 0U; index < CAN_70_RL78F2X_TXBUFFER_MAX; index++ ) {
                    /* Clear transmission request information by transitioning to stop mode. */
                    Can_70_TxRequestInfo[ controllerIndex ][ index ].Enable = FALSE;
                }
            } else if ( CAN_CS_SLEEP == controllerState ) {
                /* Clear wakeup flag by transitioning to sleep mode. */
                channelId = 0U;  /* tentative */
                Can_70_HW_ClearWakeup( controllerId, channelId );
            }
           
            if (0U == s_DisableInterruptsCount[ controllerIndex ] ) {
                /* Change interrupt settings to match the operating mode. */
                Can_70_HW_EnableInterrupt( controllerId, Can_70_ConfigPtr->CanConfigSet, controllerState, Can_70_TxBufferUsesPolling[ controllerIndex ], Can_70_RxBufferUsesPolling[ controllerIndex ] );
            }
           
            /* Set CAN controller state. */
            s_ControllerStatus[ controllerIndex ] = controllerState;
           
        }
 
        /* Disable polling mode transition processing. */
        Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_NONE;
 
        /* [SWS_Can_00058],[SWS_Can_00234],[SWS_Can_00370],[SWS_Can_00373] */
        /* Notifies completion of operation mode transition. */
        CanIf_ControllerModeIndication( canControllerId, s_ControllerStatus[ controllerIndex ] );
 
        /* [SWS_Can_00020] */
        /* Executes busoff detection processing. */
        if ( TRUE == busoffNotification ) {
            CanIf_ControllerBusOff( canControllerId );
        }
    }
}
 
#if( CAN_VERSION_INFO_API == TRUE)
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : 0x07                                                         */
/* Name        : Can_GetVersionInfo                                           */
/* Param       : (out) versioninfo      Pointer to where to store the version */
/*                                      information of this module.           */
/* Return      : void                                                         */
/* Contents    : This function returns the version information of this module.*/
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
#if( CAN_DEV_ERROR_DETECT == TRUE )
    /* [SWS_Can_00177] */
    if ( NULL_PTR == versioninfo ) {
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                         ( uint8 ) CAN_SID_GETVERSIONINFO, ( uint8 ) CAN_E_PARAM_POINTER );
    } else
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
    {
        /* [SWS_BSW_00052] */
        versioninfo->vendorID         = ( uint16 ) CAN_VENDOR_ID;           /* Vendor ID        */
        versioninfo->moduleID         = ( uint16 ) CAN_MODULE_ID;           /* Module ID        */
        versioninfo->sw_major_version = ( uint8 ) CAN_SW_MAJOR_VERSION;     /* Sw Major Version */
        versioninfo->sw_minor_version = ( uint8 ) CAN_SW_MINOR_VERSION;     /* Sw Minor Version */
        versioninfo->sw_patch_version = ( uint8 ) CAN_SW_PATCH_VERSION;     /* Sw Patch Version */
    }
}
#endif  /* #if( CAN_VERSION_INFO_API == TRUE) */
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_GETCONTROLLERRXERRORCOUNTER (0x30)                   */
/* Name        : Can_GetControllerRxErrorCounter                              */
/* Param       : (in) ControllerId   CAN controller, whose current Rx error   */
/*                                   counter shall be acquired.               */
/*               (out) RxErrorCounterPtr Pointer to a memory location, where  */
/*                                       the current Rx error counter of the  */
/*                                       CAN controller will be stored.       */
/* Return      : Std_ReturnType     E_OK      Rx error counter available.     */
/*                                  E_NOT_OK  ControllerId, or Rx error       */
/*                                            counter not available.          */
/* Contents    : Returns the Rx error counter for a CAN controller.           */
/*               This value might not be available for all CAN controllers,   */
/*               in which case E_NOT_OK would be returned. Please note that   */
/*               the value of the counter might not be correct at the moment  */
/*               the API returns it, because the Rx counter is handled        */
/*               asynchronously in hardware. Applications should not trust    */
/*               this value for any assumption about the current bus state.   */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_GetControllerRxErrorCounter( uint8 ControllerId, uint8* RxErrorCounterPtr )
{
    uint8                       channelId;
    uint8                       controllerId;
    uint8_least                 controllerIndex;
    const Can_ControllerType*   controllerCfg;
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_00512] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETCONTROLLERRXERRORCOUNTER,
                                 ( uint8 ) CAN_E_UNINIT );
        return E_NOT_OK;
    }
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* Check parameters. */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        controllerCfg = &( Can_70_ConfigPtr->CanConfigSet->CanController[ controllerIndex ] );
        if ( ControllerId == controllerCfg->CanControllerId ) {
            controllerId = controllerCfg->CanQChannelId;
            break;
        } else {
            controllerCfg = NULL_PTR;
        }
    }
 
    if ( ( NULL_PTR == controllerCfg )
     || ( TRUE != controllerCfg->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
        /* [SWS_Can_00513] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_GETCONTROLLERRXERRORCOUNTER,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return E_NOT_OK;
    }
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
    if ( NULL_PTR == RxErrorCounterPtr ) {
        /* [SWS_Can_00514] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETCONTROLLERRXERRORCOUNTER,
                                 ( uint8 ) CAN_E_PARAM_POINTER );
        return E_NOT_OK;
    }
   
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* [SWS_Can_00515] */
    /* Get RX error counter */
    channelId = 0U;  /* tentative */
    *RxErrorCounterPtr = Can_70_HW_GetRxErrorCounter( controllerId, channelId );
   
    return E_OK;
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_GETCONTROLLERTXERRORCOUNTER (0x31)                   */
/* Name        : Can_GetControllerTxErrorCounter                              */
/* Param       : (in) ControllerId   CAN controller, whose current Tx error   */
/*                                   counter shall be acquired.               */
/*               (out) RxErrorCounterPtr Pointer to a memory location, where  */
/*                                       the current Tx error counter of the  */
/*                                       CAN controller will be stored.       */
/* Return      : Std_ReturnType     E_OK      Tx error counter available.     */
/*                                  E_NOT_OK  ControllerId, or Tx error       */
/*                                            counter not available.          */
/* Contents    : Returns the Tx error counter for a CAN controller.           */
/*               This value might not be available for all CAN controllers,   */
/*               in which case E_NOT_OK would be returned. Please note that   */
/*               the value of the counter might not be correct at the moment  */
/*               the API returns it, because the Tx counter is handled        */
/*               asynchronously in hardware. Applications should not trust    */
/*               this value for any assumption about the current bus state.   */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_GetControllerTxErrorCounter( uint8 ControllerId, uint8* TxErrorCounterPtr )
{
    uint8                       channelId;
    uint8                       controllerId;
    uint8_least                 controllerInedx;
    const Can_ControllerType*   controllerCfg;
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_00517] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETCONTROLLERTXERRORCOUNTER,
                                 ( uint8 ) CAN_E_UNINIT );
        return E_NOT_OK;
    }
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        /* Check parameters. */
        controllerCfg = &( Can_70_ConfigPtr->CanConfigSet->CanController[ controllerInedx ] );
        if ( ControllerId == controllerCfg->CanControllerId ) {
            controllerId = controllerCfg->CanQChannelId;
            break;
        } else {
            controllerCfg = NULL_PTR;
        }
    }
 
    if ( ( NULL_PTR == controllerCfg )
     ||  ( TRUE != controllerCfg->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
        /* [SWS_Can_00518] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_GETCONTROLLERTXERRORCOUNTER,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return E_NOT_OK;
    }
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
    if ( NULL_PTR == TxErrorCounterPtr ) {
        /* [SWS_Can_00519] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETCONTROLLERTXERRORCOUNTER,
                                 ( uint8 ) CAN_E_PARAM_POINTER );
        return E_NOT_OK;
    }
   
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* [SWS_Can_00520] */
    /* Get TX error counter */
    channelId = 0U;  /* tentative */
    *TxErrorCounterPtr = Can_70_HW_GetTxErrorCounter( controllerId, channelId );
   
    return E_OK;
}
 
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_GETCURRENTTIME (0x32)                                */
/* Name        : Can_GetCurrentTime                                           */
/* Param       : (in) ControllerId   Index of the addresses CAN controller.   */
/*                                   counter shall be acquired.               */
/*               (out) timeStampPtr  current time stamp                       */
/* Return      : Std_ReturnType     E_OK      successful                      */
/*                                  E_NOT_OK  failed                          */
/* Contents    : Returns a time value out of the HW registers according to    */
/*               the capability of the HW Important Note: Can_GetCurrentTime  */
/*               may be called within an exclusive area.                      */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_GetCurrentTime( uint8 ControllerId, Can_TimeStampType* timeStampPtr )
{    
    uint8                       canChId;
    uint8_least                 controllerInedx;
    const Can_ControllerType*   controllerCfg;
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_00521] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETCURRENTTIME,
                                 ( uint8 ) CAN_E_UNINIT );
        return E_NOT_OK;
    }
 
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        /* Check parameters. */
        controllerCfg = &( Can_70_ConfigPtr->CanConfigSet->CanController[ controllerInedx ] );
        if ( ControllerId == controllerCfg->CanControllerId ) {
            canChId = controllerCfg->CanQChannelId;
            break;
        } else {
            controllerCfg = NULL_PTR;
        }
    }
 
    if ( ( NULL_PTR == controllerCfg )
      || ( TRUE != controllerCfg->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
        /* [SWS_CAN_00522] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_GETCURRENTTIME,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return E_NOT_OK;
    }
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
    if ( NULL_PTR == timeStampPtr ) {
        /* [SWS_Can_00523] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETCURRENTTIME,
                                 ( uint8 ) CAN_E_PARAM_POINTER );
        return E_NOT_OK;
    }
   
#endif  /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* Get Time stamp counter */
    /* Note: Refer to Chapter 4.1 "Constraints" in the detailed design document. */
    timeStampPtr->nanoseconds = ( uint32 )Can_70_HW_GetTimestampCounter( canChId );
    timeStampPtr->seconds = 0U;
   
    return E_OK;
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_ENABLEEGRESSTIMESTAMP (0x33)                         */
/* Name        : Can_EnableEgressTimeStamp                                    */
/* Param       : (in) Hth   information which HW-transmit handle shall be     */
/*                          used for enabling the time stamp. Note: This is   */
/*                          the smallest granularity which can be added for   */
/* Return      : Std_ReturnType     E_OK      successful                      */
/*                                  E_NOT_OK  failed                          */
/* Contents    : Activates egress time stamping on a dedicated HTH. Some HW   */
/*               does store once the egress time stamp marker and some HW     */
/*               needs it always before transmission. There will be no        */
/*               "disable" functionality, due to the fact, that the message   */
/*               type is always "time stamped" by network design.             */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_EnableEgressTimeStamp( Can_HwHandleType Hth )
{
    uint8_least                   controllerInedx;
    uint8_least                   bufNum;
   
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    uint8_least                   hwObjCnt;
    const Can_HardwareObjectType* hardwareObjectCfg;
   
    hardwareObjectCfg = &( Can_70_ConfigPtr->CanConfigSet->CanHardwareObject[ 0U ] );
   
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_00525] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_ENABLEEGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_UNINIT );
        return;
    }
   
    /* Check parameters. */
    for ( hwObjCnt = 0U; hwObjCnt < CAN_70_NUM_OF_HARDWARE_OBJECT; hwObjCnt++ ) {
        if ( ( CAN_70_TRANSMIT == hardwareObjectCfg[ hwObjCnt ].CanObjectType )
          && ( Hth == hardwareObjectCfg[ hwObjCnt ].CanObjectId ) ) {
            break;
        }
    }
    /* If HTH is not found */
    if ( CAN_70_NUM_OF_HARDWARE_OBJECT <= hwObjCnt ) {
        /* [SWS_Can_00526] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_ENABLEEGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_PARAM_HANDLE );
        return;
    }
   
#endif
   
#if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE )
   
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        for ( bufNum = 0U; bufNum < CAN_70_RL78F2X_TXBUFFER_MAX; bufNum++ ) {
            /* Check TX Buffer Number */
            if ( ( TRUE == s_MultiTxHthInfo[ controllerInedx ][ bufNum ].Enable )
              && ( Hth  == s_MultiTxHthInfo[ controllerInedx ][ bufNum ].Hth ) ) {
                /* Enable eggress time stamp */
                s_EnableEgressTimeStamp[ controllerInedx ][ bufNum ] = TRUE;
            }
        }
    }
   
#else
 
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        for ( bufNum = 0U; bufNum < CAN_70_RL78F2X_TXBUFFER_MAX; bufNum++ ) {
            if ( Hth == Can_70_IndxexTxHwObj[ controllerInedx ][ bufNum ].Hth ) {
                /* Enable eggress time stamp */
                s_EnableEgressTimeStamp[ controllerInedx ][ bufNum ] = TRUE;
                break;
            }
        }
        if ( bufNum != CAN_70_RL78F2X_TXBUFFER_MAX ) {
            break;
        }
    }
   
#endif
 
   
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_GETEGRESSTIMESTAMP (0x34)                            */
/* Name        : Can_EnableEgressTimeStamp                                    */
/* Param       : (in) TxPduId  L-PDU handle of CAN L-PDU for which the time   */
/*                             stamp shall be returned.                       */
/*               (in) Hth      HW-transmit handle for which the egress        */
/*                             timestamp shall be retrieved                   */
/*               (out) timeStampPtr  current time stamp                       */
/* Return      : Std_ReturnType     E_OK      success                         */
/*                                  E_NOT_OK  failed to read time stamp.      */
/* Contents    : Reads back the egress time stamp on a dedicated message      */
/*               object. It needs to be called within the TxConfirmation()    */
/*               function.                                                    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_GetEgressTimeStamp( PduIdType TxPduId, Can_HwHandleType Hth,
                                       Can_TimeStampType* timeStampPtr )
{
    uint8_least                   egressCnt;
    Std_ReturnType                ret;
   
    bool_t                        isFound = FALSE;
    uint8_least                   bufNum;
   
    uint8_least                   controllerInedx;
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    uint8_least                   hwObjCnt;
    const Can_HardwareObjectType* hardwareObjectCfg;
   
    hardwareObjectCfg = &( Can_70_ConfigPtr->CanConfigSet->CanHardwareObject[ 0U ] );
 
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_00529] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETEGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_UNINIT );
        return E_NOT_OK;
    }
   
    /* Check parameters. */
    for ( hwObjCnt = 0U; hwObjCnt < CAN_70_NUM_OF_HARDWARE_OBJECT; hwObjCnt++ ) {
        if ( ( CAN_70_TRANSMIT == hardwareObjectCfg[ hwObjCnt ].CanObjectType )
          && ( Hth == hardwareObjectCfg[ hwObjCnt ].CanObjectId ) ) {
            break;
        }
    }
    /* If HTH is not found */
    if ( CAN_70_NUM_OF_HARDWARE_OBJECT <= hwObjCnt ) {
        /* [SWS_Can_00531] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETEGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_PARAM_HANDLE );
        return E_NOT_OK;
    }
   
    if ( NULL_PTR == timeStampPtr ) {
        /* [SWS_Can_00532] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETEGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_PARAM_POINTER );
        return E_NOT_OK;
    }
   
#endif
   
    ret = E_NOT_OK;
   
#if ( CAN_MULTIPLEXED_TRANSMISSION == TRUE )
   
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        for ( bufNum = 0U; bufNum < CAN_70_RL78F2X_TXBUFFER_MAX; bufNum++ ) {
            /* Check TX Buffer Number */
            if ( ( TRUE == s_MultiTxHthInfo[ controllerInedx ][ bufNum ].Enable )
              && ( Hth  == s_MultiTxHthInfo[ controllerInedx ][ bufNum ].Hth ) ) {
                for ( egressCnt = 0U; egressCnt < CAN_70_NUM_OF_EGRESS; egressCnt++ ) {
                    if ( ( TRUE    == Can_70_EgressTimeStampData[ controllerInedx ][ bufNum ][ egressCnt ].Enable )
                      && ( TxPduId == Can_70_EgressTimeStampData[ controllerInedx ][ bufNum ][ egressCnt ].TxPduId ) ) {
                        /* Get Time stamp counter */
                        /* Note: Refer to Chapter 4.1 "Constraints" in the detailed design document. */
                        timeStampPtr->nanoseconds = Can_70_EgressTimeStampData[ controllerInedx ][ bufNum ][ egressCnt ].TimeStamp;
                        timeStampPtr->seconds = 0U;
                        isFound = TRUE;
                        ret = E_OK;
                        break;
                    }
                }
            }
            if ( TRUE == isFound ) {
                break;
            }
        }
        if ( TRUE == isFound ) {
            break;
        }
    }
   
#else
   
    /* [SWS_CAN_91029][SWS_CAN_91027] */
    /* Find egress timestamp from Can_70_EgressTimeStampData and set it in parameter timeStampPtr. */
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        for ( bufNum = 0U; bufNum < CAN_70_RL78F2X_TXBUFFER_MAX; bufNum++ ) {
            if ( Hth == Can_70_IndxexTxHwObj[ controllerInedx ][ bufNum ].Hth ) {
                /* Enable eggress time stamp */
                for ( egressCnt = 0U; egressCnt < CAN_70_NUM_OF_EGRESS; egressCnt++ ) {
                    if ( ( TRUE == Can_70_EgressTimeStampData[ controllerInedx ][ bufNum ][ egressCnt ].Enable )
                      && ( TxPduId == Can_70_EgressTimeStampData[ controllerInedx ][ bufNum ][ egressCnt ].TxPduId ) ) {
                        /* Get Time stamp counter */
                        /* Note: Refer to Chapter 4.1 "Constraints" in the detailed design document. */
                        timeStampPtr->nanoseconds = Can_70_EgressTimeStampData[ controllerInedx ][ bufNum ][ egressCnt ].TimeStamp;
                        timeStampPtr->seconds = 0U;
                        isFound = TRUE;
                        ret = E_OK;
                        break;
                    }
                }
            }
            if ( TRUE == isFound ) {
                break;
            }
        }
        if ( TRUE == isFound ) {
            break;
        }
    }
#endif
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Timestamp for parameter TxPduId was not found. */
    if ( E_NOT_OK == ret ) {
        /* [SWS_Can_00530] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETEGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_PARAM_LPDU );
    }
   
#endif
   
    return ret;
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_GETINGRESSTIMESTAMP (0x35)                           */
/* Name        : Can_GetIngressTimeStamp                                      */
/* Param       : (in) Hrh  HW-receive handle for which the ingress timestamp  */
/*                         shall be retrieved                                 */
/*               (out) timeStampPtr  current time stamp                       */
/* Return      : Std_ReturnType     E_OK      success                         */
/*                                  E_NOT_OK  failed to read time stamp.      */
/* Contents    : Reads back the ingress time stamp on a dedicated message     */
/*               object. It needs to be called within the RxIndication()      */
/*               function.                                                    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_GetIngressTimeStamp( Can_HwHandleType Hrh, Can_TimeStampType* timeStampPtr )
{
    uint8_least    bufNo;
    Std_ReturnType ret;
    uint8_least    controllerInedx;
   
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    uint8_least hwObjCnt;
    const Can_HardwareObjectType* hardwareObjectCfg;
   
    hardwareObjectCfg = &( Can_70_ConfigPtr->CanConfigSet->CanHardwareObject[ 0U ] );
   
#endif
   
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_00535] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETINGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_UNINIT );
        return E_NOT_OK;
    }
   
    /* Check parameters. */
    for ( hwObjCnt = 0U; hwObjCnt < CAN_70_NUM_OF_HARDWARE_OBJECT; hwObjCnt++ ) {
        if ( ( CAN_70_RECEIVE == hardwareObjectCfg[ hwObjCnt ].CanObjectType )
          && ( Hrh == hardwareObjectCfg[ hwObjCnt ].CanObjectId ) ) {
            break;
        }
    }
    /* If HRH is not found */
    if ( CAN_70_NUM_OF_HARDWARE_OBJECT <= hwObjCnt ) {
        /* [SWS_Can_00536] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETINGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_PARAM_HANDLE );
        return E_NOT_OK;
    }
   
    if ( NULL_PTR == timeStampPtr ) {
        /* [SWS_Can_00537] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETINGRESSTIMESTAMP,
                                 ( uint8 ) CAN_E_PARAM_POINTER );
        return E_NOT_OK;
    }
   
#endif
   
    ret = E_NOT_OK;
 
    /* [SWS_CAN_91029][SWS_CAN_91028] */
    /* Find ingress timestamp from Can_70_IngressTimeStampData and set it in parameter timeStampPtr. */
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        for ( bufNo = 0U; bufNo < CAN_70_RL78F2X_RXFIFO_MAX; bufNo++ ) {
            if ( ( TRUE == Can_70_IngressTimeStampData[ controllerInedx ][ bufNo ].Enable )
              && ( Hrh  == Can_70_IngressTimeStampData[ controllerInedx ][ bufNo ].Hrh ) ) {
                /* Get Time stamp counter */
                /* Note: Refer to Chapter 4.1 "Constraints" in the detailed design document. */
                timeStampPtr->nanoseconds = Can_70_IngressTimeStampData[ controllerInedx ][ bufNo ].TimeStamp;
                timeStampPtr->seconds = 0U;
                ret = E_OK;
                break;
            }
        }
        if ( bufNo < CAN_70_RL78F2X_RXFIFO_MAX ) {
            break;
        }
    }
   
    return ret;
}
 
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_DEINIT (0x10)                                        */
/* Name        : Can_DeInit                                                   */
/* Param       : (in) void                                                    */
/* Return      : void                                                         */
/* Contents    : This function de-initializes the module.                     */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_DeInit( void )
{
    const Can_ControllerType* canController;
    uint8                     controllerId;
    uint8_least               controllerInedx;
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_91011] */
        /* Check module status. */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_DEINIT,
                                 ( uint8 ) CAN_E_TRANSITION );
        return;
    }
 
#endif /* #if ( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
 
        if ( CAN_CS_STARTED == s_ControllerStatus[ controllerInedx ] ) {
 
            /* [SWS_Can_91012] */
            /* Check CAN controller mode. */
            ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                     ( uint8 ) CAN_SID_DEINIT,
                                     ( uint8 ) CAN_E_TRANSITION );
            continue;
        }
   
#endif /* #if ( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        canController =  &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerInedx ];
        controllerId = canController->CanQChannelId;
   
        /* [SWS_Can_91009] */
        /* Set module state before de-initializing. */
        s_CanModuleStatus = CAN_UNINIT;
   
        /* Set CAN controller state. */
        s_ControllerStatus[ controllerInedx ] = CAN_CS_UNINIT;
       
        /* Set operation mode transition information. */
        Can_70_ControllerStatusAction[ controllerInedx ] = CAN_TO_UNINIT;
 
        /* Register SW reset */
        Can_70_HW_SwReset( controllerId );
    }
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_GETCONTROLLERMODE (0x12)                             */
/* Name        : Can_GetControllerMode                                        */
/* Param       : (in) Controller  CAN controller for which the status shall   */
/*                                be requested.                               */
/*               (out) ControllerModePtr  Pointer to a memory location, where */
/*                                        the current mode of the CAN         */
/*                                        controller will be stored.          */
/* Return      : Std_ReturnType     E_OK      Controller mode request         */
/*                                            has been accepted.              */
/*                                  E_NOT_OK  Controller mode request has     */
/*                                            not been accepted.              */
/* Contents    : This service reports about the current status of the         */
/*               requested CAN controller.                                    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType* ControllerModePtr )
{
    Std_ReturnType                 ret;
    Can_70_ControllerStateInfoType controllerMode;
    uint8                          controllerId;
    uint8_least                    controllerInedx;
    const Can_ControllerType*      canController;
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_UNINIT == s_CanModuleStatus ) {
        /* [SWS_Can_91016] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_GETCONTROLLERMODE,
                                 ( uint8 )CAN_E_UNINIT );
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        /* Check parameters. */
        canController =  &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerInedx ];
        if ( Controller == canController->CanControllerId ) {
            controllerId = canController->CanQChannelId;
            break;
        } else {
            canController = NULL_PTR;
        }
    }
 
    if ( ( NULL_PTR == canController )
      || ( TRUE != canController->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
        /* [SWS_Can_91017] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_GETCONTROLLERMODE,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
    if ( NULL_PTR == ControllerModePtr ) {
        /* [SWS_Can_91018] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID,
                                 ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_GETCONTROLLERMODE,
                                 ( uint8 )CAN_E_PARAM_POINTER );
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
#endif /* #if( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* [SWS_Can_91015] */
    /* Get operating mode information. */
    ret = E_NOT_OK;
    Can_70_HW_GetMode( controllerId, &controllerMode );
   
    /* Analyze the operating mode of the CAN controller from the operating mode information. */
    /* See detailed design document. */
    if ( CAN_70_GMODE_OPERATION == controllerMode.GlobalMode ) {
        if ( CAN_70_CMODE_RESET == controllerMode.ChannelMode ) {
            if ( FALSE == controllerMode.WakeupInterrupt ) {
                if ( ( CAN_CS_STOPPED == s_ControllerStatus[ controllerInedx ] )
                  || ( CAN_CS_SLEEP   == s_ControllerStatus[ controllerInedx ] ) ) {
                    /* In the case of polling, it is not possible to determine whether the operating mode is STOPPED or SLEEP. */
                    ( *ControllerModePtr ) = s_ControllerStatus[ controllerInedx ];
                    ret = E_OK;
                } else {
                    /* Nothing */
                }
            } else {
                ( *ControllerModePtr ) = CAN_CS_SLEEP;
                ret = E_OK;
            }
        } else if ( CAN_70_CMODE_OPERATION == controllerMode.ChannelMode ) {
            if ( FALSE == controllerMode.WakeupInterrupt ) {
                ( *ControllerModePtr ) = CAN_CS_STARTED;
                ret = E_OK;
            } else {
                /* Nothing */
            }
        } else {
            /* Nothing */
        }
    } else if ( CAN_70_GMODE_SLEEP == controllerMode.GlobalMode ) {
        ( *ControllerModePtr ) = CAN_CS_UNINIT;
        ret = E_OK;
    } else {
        /* Nothing */
    }
   
    return ret;
 
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_GETCONTROLLERERRORSTATE (0x11)                       */
/* Name        : Can_GetControllerErrorState                                  */
/* Param       : (in) ControllerId  Abstracted CanIf ControllerId which is    */
/*                                  assigned to a CAN controller, which is    */
/*                                  requested for ErrorState.                 */
/*               (out) ErrorStatePtr  Pointer to a memory location, where     */
/*                                    the error state of the CAN controller   */
/*                                    will be stored.                         */
/* Return      : Std_ReturnType     E_OK      Error state request has been    */
/*                                            accepted.                       */
/*                                            has been accepted.              */
/*                                  E_NOT_OK  Error state request has not     */
/*                                            been accepted.                  */
/* Contents    : This service obtains the error state of the CAN controller.  */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr )
{
    bool_t                    comStatus;
    bool_t                    errorPassiveStatus;
    bool_t                    busoffStatus;
    uint8                     controllerId;
    uint8_least               controllerInedx;
    const Can_ControllerType* controllerCfg;
   
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* Check module status. */
    if ( CAN_READY != s_CanModuleStatus ) {
        /* [SWS_Can_91005] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETCONTROLLERERRORSTATE,
                                 ( uint8 ) CAN_E_UNINIT );
        return E_NOT_OK;
    }
   
#endif /* #if ( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        /* Check parameters. */
        controllerCfg = &( Can_70_ConfigPtr->CanConfigSet->CanController[ controllerInedx ] );
        if ( ControllerId == controllerCfg->CanControllerId ) {
            controllerId = controllerCfg->CanQChannelId;
            break;
        } else {
            controllerCfg = NULL_PTR;
        }
    }
 
    if ( ( NULL_PTR == controllerCfg )
      || ( TRUE != controllerCfg->CanControllerActivation ) ) {
 
#if( CAN_DEV_ERROR_DETECT == TRUE )
 
        /* [SWS_Can_91006] */
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_GETCONTROLLERERRORSTATE,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif /* #if ( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return E_NOT_OK;
    }
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
 
    if ( NULL_PTR == ErrorStatePtr ) {
        /* [SWS_Can_91007] */
        ( void )Det_ReportError( ( uint16 ) CAN_MODULE_ID, ( uint8 ) CAN_INDEX,
                                 ( uint8 ) CAN_SID_GETCONTROLLERERRORSTATE,
                                 ( uint8 ) CAN_E_PARAM_POINTER );
        return E_NOT_OK;
    }
   
#endif /* #if ( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* Get error status */
    Can_70_HW_GetErrorStatus( controllerId, 0U, &comStatus, &errorPassiveStatus );
    busoffStatus = Can_70_HW_CheckBusoff( controllerId, 0U );
   
    /* Check error state active */
    if ( ( TRUE == comStatus ) && ( FALSE == errorPassiveStatus ) && ( FALSE == busoffStatus ) ) {
        *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
    /* Check error state passive */
    } else if ( ( TRUE == comStatus ) && ( TRUE == errorPassiveStatus )
             && ( FALSE == busoffStatus ) ) {
        *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
    /* Check error state busoff */
    } else {
        *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
    }
   
    return E_OK;
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : CAN_SID_SETBAUDRATE (0x0F)                                   */
/* Name        : Can_SetBaudrate                                              */
/* Param       : (in) Controller        CAN controller, whose baud rate shall */
/*                                      be set.                               */
/*               (in) BaudRateConfigID  references a baud rate configuration  */
/*                                      by ID.                                */
/*                                      (see CanControllerBaudRateConfigID)   */
/* Return      : Std_ReturnType         E_OK      Service request accepted,   */
/*                                                setting of (new) baud rate  */
/*                                                started.                    */
/*                                      E_NOT_OK  Service request not         */
/*                                                accepted.                   */
/* Contents    : This service shall set the baud rate configuration of the    */
/*               CAN controller.                                              */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
#if ( CAN_SET_BAUDRATE_API == TRUE )
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{
    uint16_least                            indexID;
    Can_70_ControllerStateInfoType          controllerMode;
    const Can_ControllerType*               canController;
    const Can_ControllerBaudrateConfigType* baudrateConfig;
    uint8                                   controllerId;
    uint8_least                             controllerInedx;
   
#if ( CAN_DEV_ERROR_DETECT == TRUE )
   
    /* [SWS_Can_00492] */
    /* Check module status. */
    if ( CAN_UNINIT == s_CanModuleStatus ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_SETBAUDRATE,
                                 ( uint8 )CAN_E_UNINIT );
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
#endif /* #if ( CAN_DEV_ERROR_DETECT == TRUE ) */
 
    for ( controllerInedx = 0U; controllerInedx < CAN_70_NUM_OF_CONTROLLER; controllerInedx++ ) {
        canController =  &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerInedx ];
        if ( Controller == canController->CanControllerId ) {
            controllerId = canController->CanQChannelId;
            break;
        } else {
            canController = NULL_PTR;
        }
    }
 
    /* [SWS_Can_00494] */
    /* Check parameters. */
    if ( ( NULL_PTR == canController )
      || ( TRUE != canController->CanControllerActivation ) ) {
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
 
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_SETBAUDRATE,
                                 ( uint8 )CAN_E_PARAM_CONTROLLER );
 
#endif /* #if ( CAN_DEV_ERROR_DETECT == TRUE ) */
 
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
    /* Search baud rate config index. */
    for ( indexID = 0U; indexID < CAN_70_NUM_OF_BAUDRATE_TABLE; indexID++ ) {
        baudrateConfig =  &( canController->CanControllerBaudRateConfig[ indexID ] );
        if ( BaudRateConfigID == baudrateConfig->CanControllerBaudRateConfigID ) {
            break;
        } else {
            /* Nothing */
        }
    }
 
#if ( CAN_DEV_ERROR_DETECT == TRUE )
 
    /* [SWS_Can_00493] */
    /* Check parameters. */
    if ( CAN_70_NUM_OF_BAUDRATE_TABLE <= indexID ) {
        ( void )Det_ReportError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                 ( uint8 )CAN_SID_SETBAUDRATE,
                                 ( uint8 )CAN_E_PARAM_BAUDRATE );
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
#endif /* #if ( CAN_DEV_ERROR_DETECT == TRUE ) */
   
    /* [SWS_Can_00256] */
    /* Check operation mode transition information. */
    if ( CAN_TO_NONE != Can_70_ControllerStatusAction[ controllerInedx ] ) {
        return E_NOT_OK;
    } else {
        /* Nothing */
    }
   
    /* [SWS_Can_00422] */
    /* Check CAN controller operating mode. */
    if ( CAN_CS_STOPPED != s_ControllerStatus[ controllerInedx ] ) {
        return E_NOT_OK;
    } else {
        Can_70_HW_GetMode( controllerId, &controllerMode );
        if ( ( CAN_70_GMODE_OPERATION != controllerMode.GlobalMode )
          || ( CAN_70_CMODE_RESET != controllerMode.ChannelMode ) ) {
            return E_NOT_OK;
        } else {
            /*Nothing  */
        }
    }
   
    /* [SWS_Can_00062],[SWS_Can_00255],[SWS_Can_00260],[SWS_Can_00077],[SWS_Can_00238] */
    /* Change the baud rate setting of the CAN controller. */
    Can_70_HW_SetBaudrate( controllerId,  Can_70_ConfigPtr->CanConfigSet, indexID );
   
    /* [SWS_Can_00384] */
    /* Update the index number of the current baud rate ID.  */
    s_CurrentBaudrateId[ controllerInedx ] = indexID;
   
    return E_OK;
}
#endif /* #if ( CAN_SET_BAUDRATE_API == TRUE ) */
 
#define CAN_STOP_SEC_CODE_LOCAL
#include "Can_MemMap.h"
/* EOF Can.c ****************************************************************/
