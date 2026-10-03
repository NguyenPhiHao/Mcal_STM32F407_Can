/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Lin_GeneralTypes.h                                           */
/* Version     : v1.00.00                                                     */
/* Contents    : This file is LIN General Types header.                       */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of LIN Driver                                                */
/* R22-11                                                                     */
/******************************************************************************/

#ifndef LIN_GENERAL_TYPES_H
#define LIN_GENERAL_TYPES_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Std_Types.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
/*----------------------------------------------------------------------------*/
/* software version information                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/
/* [SWS_Lin_00229] */
/* This type is used to specify the Checksum model to be used for the LIN Frame. */
typedef enum {
    LIN_CLASSIC_CS  = 0,
    LIN_ENHANCED_CS = 1
} Lin_FrameCsModelType;

/* [SWS_Lin_00230] */
/* This type is used to specify whether the frame processor is required to transmit the response part of the LIN frame. */
typedef enum {
    LIN_FRAMERESPONSE_TX     = 0,
    LIN_FRAMERESPONSE_RX     = 1,
    LIN_FRAMERESPONSE_IGNORE = 2
} Lin_FrameResponseType;

/* [SWS_Lin_00233] */
/* LIN operation states for a LIN channel or frame, as returned by the API service Lin_GetStatus(). */
typedef enum {
    LIN_NOT_OK           = 0,
    LIN_TX_OK            = 1,
    LIN_TX_BUSY          = 2,
    LIN_TX_HEADER_ERROR  = 3,
    LIN_TX_ERROR         = 4,
    LIN_RX_OK            = 5,
    LIN_RX_BUSY          = 6,
    LIN_RX_ERROR         = 7,
    LIN_RX_NO_RESPONSE   = 8,
    LIN_OPERATIONAL      = 9,
    LIN_CH_SLEEP         = 10,
    LIN_CH_SLEEP_PENDING = 11,
    LIN_CH_OPERATIONAL   = 12
} Lin_StatusType;

/* [SWS_Lin_91140] */
typedef enum {
    LIN_ERR_NONE        = 0,
    LIN_ERR_HEADER      = 1,
    LIN_ERR_RESP_STOPBIT= 3,
    LIN_ERR_RESP_CHKSUM = 4,
    LIN_ERR_RESP_DATABIT= 5,
    LIN_ERR_NO_RESP     = 6,
    LIN_ERR_INC_RESP    = 7
} Lin_SlaveErrorType;

/* [SWS_Lin_00231] */
/* This type is used to specify the number of SDU data bytes to copy. */
typedef uint8 Lin_FrameDlType;

/* [SWS_Lin_00228] */
/* Represents all valid protected identifier used by Lin_SendFrame(). */
typedef uint8 Lin_FramePidType;

/* [SWS_Lin_00232] */
/* This Type is used to provide PID, checksum model, data length and SDU pointer from the LIN Interface to the LIN driver. */
typedef struct
{
    Lin_FramePidType      Pid;
    Lin_FrameCsModelType  Cs;
    Lin_FrameResponseType Drc;
    Lin_FrameDlType       Dl;
    uint8*                SduPtr;
} Lin_PduType;

/* [SWS_LinTrcv_00168] */
/* Operating modes of the LIN Transceiver Driver */
typedef uint8 LinTrcv_TrcvModeType;
#define LINTRCV_TRCV_MODE_NORMAL    ( ( uint8 )0x00U )                  /* Transceiver mode NORMAL */
#define LINTRCV_TRCV_MODE_STANDBY   ( ( uint8 )0x01U )                  /* Transceiver mode STANDBY */
#define LINTRCV_TRCV_MODE_SLEEP     ( ( uint8 )0x02U )                  /* Transceiver mode SLEEP */

/* [SWS_LinTrcv_00169] */
/* Wake up operating modes of the LIN Transceiver Driver. */
typedef uint8 LinTrcv_TrcvWakeupModeType;
#define LINTRCV_WUMODE_ENABLE       ( ( uint8 )0x00U )                  /* The notification for wakeup events is enabled on the addressed network. */
#define LINTRCV_WUMODE_DISABLE      ( ( uint8 )0x01U )                  /* The notification for wakeup events is disabled on the addressed network. */
#define LINTRCV_WUMODE_CLEAR        ( ( uint8 )0x02U )                  /* A stored wakeup event is cleared on the addressed network. */

/* [SWS_LinTrcv_00170] */
/* This type denotes the wake up reason detected by the LIN transceiver in detail. */
typedef uint8 LinTrcv_TrcvWakeupReasonType;
#define LINTRCV_WU_ERROR            ( ( uint8 )0x00U )                  /* Due to an error wake up reason was not detected. This value may only be reported when error was reported to DEM before. */
#define LINTRCV_WU_NOT_SUPPORTED    ( ( uint8 )0x01U )                  /* The transceiver does not support any information for the wake up reason. */
#define LINTRCV_WU_BY_BUS           ( ( uint8 )0x02U )                  /* The transceiver has detected, that the network has caused the wake up of the ECU. */
#define LINTRCV_WU_BY_PIN           ( ( uint8 )0x03U )                  /* The transceiver has detected a wake-up event at one of the transceiver's pins (not at the LIN bus). */
#define LINTRCV_WU_INTERNALLY       ( ( uint8 )0x04U )                  /* The transceiver has detected, that the network has been woken up by the ECU via a request to NORMAL mode. */
#define LINTRCV_WU_RESET            ( ( uint8 )0x05U )                  /* The transceiver has detected, that the wake up is due to an ECU reset. */
#define LINTRCV_WU_POWER_ON         ( ( uint8 )0x06U )                  /* The transceiver has detected, that the wake up is due to an ECU reset after power on. */

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
 
#endif /* LIN_GENERAL_TYPES_H */
 
/* EOF Lin_GeneralTypes.h *****************************************************/