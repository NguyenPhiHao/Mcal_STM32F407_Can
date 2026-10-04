/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Can_70_RL78F2X.h                                             */
/* Version     : v1.00.01                                                     */
/* Contents    : This module provides services for initiating transmissions   */
/*               and calls the callback functions of the CanIf module for     */
/*               notifying events, independently from the hardware. Also it   */
/*               provides services to control the behavior and state of the   */
/*               CAN controllers that belong to the same CAN Hardware Unit.   */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of CAN Driver                                                */
/* R22-11                                                                     */
/******************************************************************************/

#ifndef CAN_70_RL78F2X_H
#define CAN_70_RL78F2X_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Can_70_RL78F2X_Types.h"    /* [CAN034] */
#include "Can_70_RL78F2X_Dep.h"
#include "QINeS_Lite.h"

/*----------------------------------------------------------------------------*/
/* file version information                                                   */
/*----------------------------------------------------------------------------*/
#define CAN_70_VENDOR_ID_RL78F2X_H                           ( 70U )
#define CAN_70_MODULE_ID_RL78F2X_H                           ( 80U )

#define CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_H            ( 22U )
#define CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_H            ( 11U )
#define CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_H         (  0U )

#define CAN_70_SW_MAJOR_VERSION_RL78F2X_H                    (  1U )
#define CAN_70_SW_MINOR_VERSION_RL78F2X_H                    (  0U )
#define CAN_70_SW_PATCH_VERSION_RL78F2X_H                    (  0U )

/*----------------------------------------------------------------------------*/
/* file version checks                                                        */
/*----------------------------------------------------------------------------*/

/*---------------Can_70_Types.h--------------------------------------------------*/

/* Check if current file and Can_70_RL78F2X_Types.h header file are of the same Vendor ID */
#if (CAN_70_VENDOR_ID_RL78F2X_H    != CAN_70_VENDOR_ID_RL78F2X_TYPES_H)
    #error "VENDOR ID for Can_70_RL78F2X.h and Can_70_RL78F2X_Types.h are different"
#endif      /* End of Vendor Id Version check */
#if (CAN_70_MODULE_ID_RL78F2X_H    != CAN_70_MODULE_ID_RL78F2X_TYPES_H)
    #error "MODULE ID for Can_70_RL78F2X.h and Can_70_RL78F2X_Types.h are different"
#endif      /* End of Vendor Id Version check */

/* Check if current file and Can_70_RL78F2X_Types.h header file are of the same Software version */
#if ((CAN_70_SW_MAJOR_VERSION_RL78F2X_H    != CAN_70_SW_MAJOR_VERSION_RL78F2X_TYPES_H)   || \
     (CAN_70_SW_MINOR_VERSION_RL78F2X_H    != CAN_70_SW_MINOR_VERSION_RL78F2X_TYPES_H)   || \
     (CAN_70_SW_PATCH_VERSION_RL78F2X_H    != CAN_70_SW_PATCH_VERSION_RL78F2X_TYPES_H))
    #error "Software Version Numbers of Can_70_RL78F2X.h and Can_70_RL78F2X_Types.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_70_RL78F2X_Types.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_H    != CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_TYPES_H)     || \
     (CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_H    != CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_TYPES_H)     || \
     (CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_H != CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_TYPES_H))
    #error "AUTOSAR Version Numbers of Can_70_RL78F2X.h and Can_70_RL78F2X_Types.h are different"
#endif      /* End of Autosar Version check */

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Macros to set the for registers */

#define CAN_PROCESSING_POLLING                  ( 0U )
#define CAN_PROCESSING_INTERRUPT                ( 1U )
#define CAN_PROCESSING_MIXED                    ( 2U )

#define CAN_70_RL78F2X_HWOBJECTCOUNT_HRH_0      ( 0U )
#define CAN_70_RL78F2X_HWOBJECTCOUNT_HRH_4      ( 1U )
#define CAN_70_RL78F2X_HWOBJECTCOUNT_HRH_8      ( 2U )
#define CAN_70_RL78F2X_HWOBJECTCOUNT_HRH_16     ( 3U )

#define CAN_70_RL78F2X_CHANNEL_MAX              ( ( uint8 ) 1U )
#define CAN_70_RL78F2X_AFL_MAX                  ( ( uint8 )16U )
#define CAN_70_RL78F2X_RXFIFO_MAX               ( ( uint8 ) 2U )
#define CAN_70_RL78F2X_TXBUFFER_MAX             ( ( uint8 ) 4U )
#define CAN_70_RL78F2X_TXDATAFIELD_MAX          ( ( uint8 )64U )  /* bytes */
#define CAN_70_RL78F2X_RXDATAFIELD_MAX          ( ( uint8 )64U )  /* bytes */
#define CAN_70_RL78F2X_THL_MAX                  ( ( uint8 ) 8U )
#define CAN_70_RL78F2X_INTERRUPT_FLAG_MAX       ( ( uint8 ) 8U )

#define CAN_70_MASK_CANID_EXTEND                ( ( Can_IdType )0x80000000U )
#define CAN_70_MASK_CANID_CANFD                 ( ( Can_IdType )0x40000000U )

/* Maximum number of HTHs. */
#define CAN_70_NUM_OF_HTH                       ( ( uint8 )4U )

/* Maximum number of HRHs. */
#define CAN_70_NUM_OF_HRH                       ( ( uint8 )2U )

/*----------------------------------------------------------------------------*/
/*  Type definitions                                                          */
/*----------------------------------------------------------------------------*/

typedef enum {
    CAN_70_GMODE_SLEEP,
    CAN_70_GMODE_RESET,
    CAN_70_GMODE_HALT,
    CAN_70_GMODE_OPERATION,
    CAN_70_GMODE_OTHER
} Can_70_GlobalModeType;

typedef enum {
    CAN_70_CMODE_SLEEP,
    CAN_70_CMODE_RESET,
    CAN_70_CMODE_HALT,
    CAN_70_CMODE_OPERATION,
    CAN_70_CMODE_OTHER
} Can_70_ChannelModeType;

typedef enum {
    CAN_70_TXBUFSTAT_EMP,
    CAN_70_TXBUFSTAT_SENDING,
    CAN_70_TXBUFSTAT_SENT,
    CAN_70_TXBUFSTAT_OTHER
} CAN_70_TxBufStatInfoType;

typedef struct {
    Can_70_GlobalModeType     GlobalMode;
    Can_70_ChannelModeType    ChannelMode;
    bool_t                    WakeupInterrupt;
    bool_t                    InTransition;
    bool_t                    RamInitialization;
} Can_70_ControllerStateInfoType;

typedef struct {
    struct { uint8 index; uint8 bit; } RCANxGRVC;
    struct { uint8 index; uint8 bit; } RCANxERR ;
    struct { uint8 index; uint8 bit; } RCANxWUP ;
    struct { uint8 index; uint8 bit; } RCANxCFR ;
    struct { uint8 index; uint8 bit; } RCANxTRM ;
    struct { uint8 index; uint8 bit; } RCANxGRFR;
    struct { uint8 index; uint8 bit; } RCANxGERR;
    struct { uint8 index; uint8 bit; } CRAM     ;
} Can_70_InterruptBitAssignType;

/*----------------------------------------------------------------------------*/
/* external variables                                                         */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/
extern void Can_70_RL78F2X_GetMode( uint8 Controller,
                                    Can_70_ControllerStateInfoType* CtrlStateInfo );

extern void Can_70_RL78F2X_SetGlobalMode( uint8 Controller, Can_70_GlobalModeType GlobalMode );

extern void Can_70_RL78F2X_SetChannelMode( uint8 Controller,  uint8 Channel,
                                           Can_70_ChannelModeType ChannelMode );

extern void Can_70_RL78F2X_SetClock( uint8 Controller, uint8 ClockSource );

extern void Can_70_RL78F2X_SetBaudrate( uint8 Controller, const Can_ConfigSetType* CanConfigSet,
                                        uint16 BaudRateConfigID );

extern uint8 Can_70_RL78F2X_GetRxErrorCounter( uint8 Controller, uint8 Channel );

extern uint8 Can_70_RL78F2X_GetTxErrorCounter( uint8 Controller, uint8 Channel );

extern void Can_70_RL78F2X_SetAfl( uint8 Controller, const Can_ConfigSetType* CanConfigSet );

extern void Can_70_RL78F2X_SetBuffer( uint8 Controller, const Can_ConfigSetType* CanConfigSet );

extern void Can_70_RL78F2X_SetCanCommon( uint8 Controller );

extern uint16 Can_70_RL78F2X_GetTimestampCounter( uint8 Controller );

extern void Can_70_RL78F2X_SendRequest( uint8 Controller, uint8 TxBufNo, const Can_PduType* PduInfo,
                                        bool_t TimeStamp, bool_t RateSwitch, uint8 PaddingValue );

extern void Can_70_RL78F2X_SwReset( uint8 Controller );

extern void Can_70_RL78F2X_ClearWakeup( uint8 Controller, uint8 Channel );

extern void Can_70_RL78F2X_DisableInterrupt( uint8 Controller );

extern void Can_70_RL78F2X_EnableInterrupt( uint8 Controller, const Can_ConfigSetType* CanConfigSet,
                                            Can_ControllerStateType ControllerStatus,
                                            const bool_t* TxBufferUsesPolling,
                                            const bool_t* RxBufferUsesPolling );

extern void Can_70_RL78F2X_SetRamWindow( uint8 Controller, uint16 Page );

extern void Can_70_RL78F2X_EnableRxFifo( uint8 Controller, const Can_ConfigSetType* CanConfigSet );

#if ( CAN_70_WAKEUP_SUPPORT == TRUE )

extern bool_t Can_70_RL78F2X_CheckWakeup( uint8 Controller, uint8 Channel );

#endif /* #if ( CAN_70_WAKEUP_SUPPORT == TRUE ) */

extern CAN_70_TxBufStatInfoType Can_70_RL78F2X_GetTxBufferStatus( uint8 Controller, uint8 TxBufNo );

extern void Can_70_RL78F2X_GetErrorStatus( uint8 Controller, uint8 Channel,
                                            bool_t* comStatus, bool_t* errorPassiveStatus );

extern bool_t Can_70_RL78F2X_CheckBusoff( uint8 Controller, uint8 Channel );

extern void Can_70_RL78F2X_SetEcc( uint8 Controller );

extern void Can_70_RL78F2X_ClearTxBufferStatus( uint8 Controller, uint8 TxBufNo );

#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )

extern void Can_70_RL78F2X_GetSendHistory( uint8 Controller, uint8 Channel, uint8* ObjectId,
                                           uint16* timeStampCounter, uint8* timeStampNum );

#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */

extern bool_t Can_70_RL78F2X_CheckRxBuffer( uint8 Controller, uint8 Channel, uint8 ObjectId );
extern void Can_70_RL78F2X_GetRxBuffer( uint8 Controller, uint8 Channel, uint8 ObjectId, uint32* id,
                                        uint8* dlc, uint16* rxTimestamp,
                                        uint8** rxBuffer, uint8* size  );
extern void Can_70_RL78F2X_UpdateRxBuffer( uint8 Controller, uint8 Channel, uint8 ObjectId );

#if ( CAN_70_USE_CANFD == TRUE )

extern void Can_70_RL78F2X_SetCanFd( uint8 Controller, const Can_ConfigSetType* CanConfigSet );

#endif /* #if ( CAN_70_USE_CANFD == TRUE ) */

#endif  /* #ifndef CAN_70_RL78F2X_H */
/* EOF Can_70_RL78F2X.h ****************************************************************/
