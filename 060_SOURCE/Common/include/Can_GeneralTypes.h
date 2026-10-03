/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Can_GeneralTypes.h                                           */
/* Version     : v1.00.00                                                     */
/* Contents    : This file is CAN General Types header.                       */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of CAN Driver                                                */
/* R22-11                                                                     */
/******************************************************************************/
#ifndef CAN_GENERAL_TYPES_H
#define CAN_GENERAL_TYPES_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------------------------------------------------------------*/
/* software version information                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/
/* [SWS_Can_00039] */
#define CAN_BUSY                     ( ( Std_ReturnType )0x02U )              /* transmit request could not be processed because no transmit object was available */

/* [SWS_CanTrcv_00163] */
/* Operating modes of the CAN Transceiver Driver. */
typedef uint8 CanTrcv_TrcvModeType;
#define CANTRCV_TRCVMODE_NORMAL      ( ( CanTrcv_TrcvModeType )0x00U )        /* Transceiver mode NORMAL */
#define CANTRCV_TRCVMODE_STANDBY     ( ( CanTrcv_TrcvModeType )0x01U )        /* Transceiver mode STANDBY */
#define CANTRCV_TRCVMODE_SLEEP       ( ( CanTrcv_TrcvModeType )0x02U )        /* Transceiver mode SLEEP */

/* [SWS_CanTrcv_00164] */
/* This type shall be used to control the CAN transceiver concerning wake up events and wake up notifications. */
typedef uint8 CanTrcv_TrcvWakeupModeType;
#define CANTRCV_WUMODE_ENABLE        ( ( CanTrcv_TrcvWakeupModeType )0x00U )  /* The notification for wakeup events is enabled on the addressed transceiver. */
#define CANTRCV_WUMODE_CLEAR         ( ( CanTrcv_TrcvWakeupModeType )0x01U )  /* A stored wakeup event is cleared on the addressed transceiver. */
#define CANTRCV_WUMODE_DISABLE       ( ( CanTrcv_TrcvWakeupModeType )0x02U )  /* The notification for wakeup events is disabled on the addressed transceiver. */

/* [SWS_CanTrcv_00165] */
/* This type denotes the wake up reason detected by the CAN transceiver in detail. */
typedef uint8 CanTrcv_TrcvWakeupReasonType;
#define CANTRCV_WU_ERROR            ( ( CanTrcv_TrcvWakeupReasonType )0x00U )  /* Due to an error wake up reason was not detected. This value may only be reported when error was reported to DET. */
#define CANTRCV_WU_BY_BUS           ( ( CanTrcv_TrcvWakeupReasonType )0x01U )  /* The transceiver has detected, that the network has caused the wake up of the ECU. */
#define CANTRCV_WU_BY_PIN           ( ( CanTrcv_TrcvWakeupReasonType )0x02U )  /* The transceiver has detected a wake-up event at one of the transceiver’s pins (not at the CAN bus). */
#define CANTRCV_WU_INTERNALLY       ( ( CanTrcv_TrcvWakeupReasonType )0x03U )  /* The transceiver has detected, that the network has woken up by the ECU via a request to NORMAL mode. */
#define CANTRCV_WU_NOT_SUPPORTED    ( ( CanTrcv_TrcvWakeupReasonType )0x04U )  /* The transceiver does not support any information for the wake up reason. */
#define CANTRCV_WU_POWER_ON         ( ( CanTrcv_TrcvWakeupReasonType )0x05U )  /* The transceiver has detected, that the "wake up" is due to an ECU reset after power on. */
#define CANTRCV_WU_RESET            ( ( CanTrcv_TrcvWakeupReasonType )0x06U )  /* The transceiver has detected, that the "wake up" is due to an ECU reset. */
#define CANTRCV_WU_BY_SYSERR        ( ( CanTrcv_TrcvWakeupReasonType )0x07U )  /* The transceiver has detected, that the wake up of the ECU was caused by a HW related device failure. */

/* [SWS_Can_00416] */
/* Represents the Identifier of an I-PDU. The two most significant bits specify the frame type: */
/* 00 CAN message with Standard CAN ID   */
/* 01 CAN FD frame with Standard CAN ID  */
/* 10 CAN message with Extended CAN ID   */
/* 11 CAN FD frame with Extended CAN ID  */
typedef uint32 Can_IdType;

/* [SWS_Can_91003] */
typedef enum {
    CAN_ERRORSTATE_ACTIVE,
    CAN_ERRORSTATE_PASSIVE,
    CAN_ERRORSTATE_BUSOFF
} Can_ErrorStateType;

/* [SWS_Can_91013] */
typedef enum {
    CAN_CS_UNINIT,
    CAN_CS_STARTED,
    CAN_CS_STOPPED,
    CAN_CS_SLEEP
} Can_ControllerStateType;

/* [SWS_Can_91021] */
typedef enum {
    CAN_ERROR_BIT_MONITORING1          = 1,
    CAN_ERROR_BIT_MONITORING0          = 2,
    CAN_ERROR_BIT                      = 3,
    CAN_ERROR_CHECK_ACK_FAILED         = 4,
    CAN_ERROR_ACK_DELIMITER            = 5,
    CAN_ERROR_ARBITRATION_LOST         = 6,
    CAN_ERROR_OVERLOAD                 = 7,
    CAN_ERROR_CHECK_FORM_FAILED        = 8,
    CAN_ERROR_CHECK_STUFFING_FAILED    = 9,
    CAN_ERROR_CHECK_CRC_FAILED         = 10,
    CAN_ERROR_BUS_LOCK                 = 11
} Can_ErrorType;

/* [SWS_Can_00415] */
/* This type unites PduId (swPduHandle), SduLength (length), SduData (sdu), and CanId (id) for any CAN L-SDU. */
typedef struct {
    VAR(PduIdType, CAN_VAR)                 swPduHandle;
    VAR(uint8, CAN_VAR)                     length;
    VAR(Can_IdType, CAN_VAR)                id;
    P2VAR(uint8, CAN_VAR, CAN_APPL_DATA)    sdu;
} Can_PduType;

/* [SWS_Can_00429] */
/* Represents the hardware object handles of a CAN hardware unit. For CAN hardware units with more than 255 Hw objects use extended range. */
#ifdef CAN_MBCOUNTEXTENSION
    #if (CAN_MBCOUNTEXTENSION == STD_ON)
    typedef uint16 Can_HwHandleType;
    #else /* CAN_MBCOUNTEXTENSION==STD_OFF */
    typedef uint8  Can_HwHandleType;
    #endif /* CAN_MBCOUNTEXTENSION==STD_ON/STD_OFF */
#else
    typedef uint8  Can_HwHandleType;
#endif

/* [SWS_CAN_00496] */
/* This type defines a data structure which clearly provides a Hardware Object Handle including */
/* its corresponding CAN Controller and therefore CanDrv as well as the specific CanId. */
typedef struct {
    Can_IdType         CanId;           /* Standard/Extended CAN ID of CAN L-PDU */
    Can_HwHandleType   Hoh;             /* ID of the corresponding Hardware Object Range */
    uint8              ControllerId;    /* ControllerId provided by CanIf clearly identify the corresponding controller */
} Can_HwType;

/* [SWS_CAN_91029] */
typedef struct {
    uint32 nanoseconds;
    uint32 seconds;
} Can_TimeStampType;

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* const data declarations                                                    */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* external variables                                                         */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* static variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* CAN_GENERAL_TYPES_H */

/* EOF Can_GeneralTypes.h *****************************************************/
