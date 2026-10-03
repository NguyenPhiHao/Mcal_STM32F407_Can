/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : ComStack_Types.h                                             */
/* Version     : v1.00.00                                                     */
/* Contents    : This file is ComStack’s type header.                         */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of Communication Stack Types                                 */
/* R22-11                                                                     */
/******************************************************************************/


#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "ComStack_Cfg.h"

#define COMSTACKTYPE_AR_RELEASE_MAJOR_VERSION   (22U)
#define COMSTACKTYPE_AR_RELEASE_MINOR_VERSION   (11U)
#define COMSTACKTYPE_AR_RELEASE_REVISION_VERSION (0U)

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/
/* General Codes - COMTYPE018 */
#define NTFRSLT_OK                      ( ( NotifResultType )0x00U )    /* Successfully */
#define NTFRSLT_E_NOT_OK                ( ( NotifResultType )0x01U )    /* Not successfully */
#define NTFRSLT_E_TIMEOUT_A             ( ( NotifResultType )0x02U )    /* Time-out N_Asmax/N_Armax */
#define NTFRSLT_E_TIMEOUT_BS            ( ( NotifResultType )0x03U )    /* Time-out N_Bsmax */
#define NTFRSLT_E_TIMEOUT_CR            ( ( NotifResultType )0x04U )    /* Time-out N_Crmax */
#define NTFRSLT_E_WRONG_SN              ( ( NotifResultType )0x05U )    /* Unexpected sequence Number */
#define NTFRSLT_E_INVALID_FS            ( ( NotifResultType )0x06U )    /* Invalid FlowStatus */
#define NTFRSLT_E_UNEXP_PDU             ( ( NotifResultType )0x07U )    /* Unexpected PDU */
#define NTFRSLT_E_WFT_OVRN              ( ( NotifResultType )0x08U )    /* WAIT frame over-run */
#define NTFRSLT_E_ABORT                 ( ( NotifResultType )0x09U )    /* Abort */
#define NTFRSLT_E_NO_BUFFER             ( ( NotifResultType )0x0AU )    /* No Buffer */
#define NTFRSLT_E_CANCELATION_OK        ( ( NotifResultType )0x0BU )    /* Cancellation has been executed */
#define NTFRSLT_E_CANCELATION_NOT_OK    ( ( NotifResultType )0x0CU )    /* Cancellation has not been executed */
#define NTFRSLT_PARAMETER_OK            ( ( NotifResultType )0x0DU )    /* Parameter change been executed */
#define NTFRSLT_E_PARAMETER_NOT_OK      ( ( NotifResultType )0x0EU )    /* Parameter change not been executed */
#define NTFRSLT_E_RX_ON                 ( ( NotifResultType )0x0FU )    /* Ongoing reception */
#define NTFRSLT_E_VALUE_NOT_OK          ( ( NotifResultType )0x10U )    /* Wrong value */

/* General Codes - COMTYPE021 */
#define BUSTRCV_E_OK                    ( ( BusTrcvErrorType )0x00U )   /* Successfully */
#define BUSTRCV_E_ERROR                 ( ( BusTrcvErrorType )0x01U )   /* Not successfully */

#define boolean                 bool_t

/* 8 API specification */
/* [SWS_COMTYPE_00011] */
struct PduInfoType_tag {
    uint8*          SduDataPtr;
    uint8*          MetaDataPtr;
    PduLengthType   SduLength;
};

typedef struct PduInfoType_tag    PduInfoType;

/* Chapter 8.1.4 */
typedef uint8             TPParameterType;
#define TP_STMIN           ( ( TPParameterType )0x00U )
#define TP_BS              ( ( TPParameterType )0x01U )
#define TP_BC              ( ( TPParameterType )0x02U )

/* BufReq_ReturnType - COMTYPE012 */
typedef uint8             BufReq_ReturnType;
#define BUFREQ_E_OK        ( ( BufReq_ReturnType )0x00U )   /* Successful */
#define BUFREQ_E_NOT_OK    ( ( BufReq_ReturnType )0x01U )   /* Not successful */
#define BUFREQ_E_BUSY      ( ( BufReq_ReturnType )0x02U )   /* Busy */
#define BUFREQ_E_OVFL      ( ( BufReq_ReturnType )0x03U )   /* Overflow */

/* Chapter 8.1.6: Result status of a notification */
typedef uint8             NotifResultType;

/* BusTrcvErrorType - COMTYPE020 */
typedef uint8             BusTrcvErrorType;
/*
 * 0x00 - 0x1E: General return codes
 * 0x1F - 0x3C: Error notification: CAN Transceiver Driver
 * 0x3D - 0x5A: Error notification: Lin Interface
 * 0x5B - 0x78: Error notification: FlexRay Transceiver Driver
 * >  0x78: Currently values in this range are invalid
 */

/* TpDataStateType - COMTYPE027 */
typedef uint8             TpDataStateType;
#define TP_DATACONF        ( 0x00U )
#define TP_DATARETRY       ( 0x01U )
#define TP_CONFPENDING     ( 0x02U )

struct RetryInfoType_tag {
    TpDataStateType TpDataState;    /* The enum type to be used to store the state of Tp buffer */
    PduLengthType   TxTpDataCnt;    /* length of the SDU in bytes */
};

typedef struct RetryInfoType_tag RetryInfoType;

/* NetworkHandleType */
typedef uint8 NetworkHandleType;   /* Variables of the type NetworkHandleType */

/* Addon, could be triggered to a later version of comstack_types */
/* Chapter x.y.z: Used to store the identifier of a partial network cluster. */
typedef uint8 PNCHandleType;

/* [SWS_COMTYPE_00039] */
/* Name        : IcomConfigIdType
 * Type        : uint8
 * Description : IcomConfigIdType defines the configuration ID. An ID of 0 is the default
 *               configuration. An ID greater than 0 shall identify a configuration for
 *               Pretended Networking. There is more than 1 configuration possible.
 */
typedef uint8 IcomConfigIdType;

/* [SWS_COMTYPE_00040] */
/* Name        : IcomSwitch_ErrorType
 * Type        : uint8
 * Description : IcomSwitch_ErrorType defines the errors which can occur when activating
 *               or deactivating Pretended Networking.
 * Range       : ICOM_SWITCH_E_OK:     The activation of Pretended Networking was successful.
 *               ICOM_SWITCH_E_FAILED: The activation of Pretended Networking was not successful.
 */
typedef enum {
    ICOM_SWITCH_E_OK     = 0,
    ICOM_SWITCH_E_FAILED
} IcomSwitch_ErrorType;

#endif /* COMSTACK_TYPES_H_ */

/* EOF ComStack_Types.h ***************************************************/
