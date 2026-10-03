/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Can_Irq.h                                                    */
/* Version     : v1.00.02                                                     */
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
#ifndef CAN_IRQ_H
#define CAN_IRQ_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "QiNeS_Lite.h"
#include "Can_Irq_Dep.h"

/*----------------------------------------------------------------------------*/
/* file version information                                                   */
/*----------------------------------------------------------------------------*/
#define CAN_70_VENDOR_ID_IRQ_H                    ( 70U )
#define CAN_70_MODULE_ID_IRQ_H                    ( 80U )

#define CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_H      ( 22U )
#define CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_H      ( 11U )
#define CAN_70_AR_RELEASE_REVISION_VERSION_IRQ_H   ( 0U )

#define CAN_70_SW_MAJOR_VERSION_IRQ_H              ( 1U )
#define CAN_70_SW_MINOR_VERSION_IRQ_H              ( 0U )
#define CAN_70_SW_PATCH_VERSION_IRQ_H              ( 0U )

/*----------------------------------------------------------------------------*/
/* file version checks                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* external variables                                                         */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_VAR_INIT_LOCAL_UNSPECIFIED
#include "Can_MemMap.h"

extern const Can_ConfigType*    Can_70_ConfigPtr;

#define CAN_STOP_SEC_VAR_INIT_LOCAL_UNSPECIFIED
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

extern Can_70_HthToHwObj                    Can_70_IndexToHwObj[CAN_70_NUM_OF_CONTROLLER][CAN_70_RL78F2X_TXBUFFER_MAX];

#define CAN_STOP_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_LOCAL_16
#include "Can_MemMap.h"

extern Can_70_TxRequestInfoType             Can_70_TxRequestInfo[CAN_70_NUM_OF_CONTROLLER][CAN_70_RL78F2X_TXBUFFER_MAX];
extern Can_70_ControllerStatusActionType    Can_70_ControllerStatusAction[CAN_70_NUM_OF_CONTROLLER];

#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )

extern Can_70_IngressTimeStampType          Can_70_IngressTimeStampData[CAN_70_NUM_OF_CONTROLLER][CAN_70_RL78F2X_RXFIFO_MAX];
extern Can_70_EgressTimeStampType           Can_70_EgressTimeStampData[CAN_70_NUM_OF_CONTROLLER][CAN_70_RL78F2X_TXBUFFER_MAX][CAN_70_NUM_OF_EGRESS];

#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */

#define CAN_STOP_SEC_VAR_INIT_LOCAL_16
#include "Can_MemMap.h"

/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_CODE_LOCAL
#include "Can_MemMap.h"

extern void Can_70_Isr_Reception_CANX   ( uint8 canChannel );
extern void Can_70_Isr_GlobalError_CANX ( uint8 canChannel );
extern void Can_70_Isr_Transmission_CANX( uint8 canChannel );
extern void Can_70_Isr_ChannelError_CANX( uint8 canChannel );
extern void Can_70_Isr_Wakeup_CANX      ( uint8 canChannel );
extern void Can_70_Isr_CanRamEcc        ( void );

#define CAN_STOP_SEC_CODE_LOCAL
#include "Can_MemMap.h"

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/

#endif /* #ifndef CAN_IRQ_H */
/* EOF Can_Irq.h **************************************************************/
