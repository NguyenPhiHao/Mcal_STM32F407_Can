/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Can_70_HW.h                                                  */
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

#ifndef CAN_70_HW_H
#define CAN_70_HW_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "ComStack_Types.h"
#include "QINeS_Lite.h"
#include "Can_Cfg.h"

/*----------------------------------------------------------------------------*/
/* file version information                                                   */
/*----------------------------------------------------------------------------*/
#define CAN_70_VENDOR_ID_HW_H                      ( 70U )
#define CAN_70_MODULE_ID_HW_H                      ( 80U )

#define CAN_70_AR_RELEASE_MAJOR_VERSION_HW_H       ( 22U )
#define CAN_70_AR_RELEASE_MINOR_VERSION_HW_H       ( 11U )
#define CAN_70_AR_RELEASE_REVISION_VERSION_HW_H    (  0U )

#define CAN_70_SW_MAJOR_VERSION_HW_H               (  1U )
#define CAN_70_SW_MINOR_VERSION_HW_H               (  0U )
#define CAN_70_SW_PATCH_VERSION_HW_H               (  0U )

/*----------------------------------------------------------------------------*/
/* file version checks                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/
/* The below macros are used to create a wrapper between the Hw independent source code
 * and the Hw dependant source code. */

#define Can_70_HW_GetMode( Controller, CtrlStateInfo ) \
                Can_70_RL78F2X_GetMode( ( Controller), ( CtrlStateInfo ) )

#define Can_70_HW_SetGlobalMode( Controller, GlobalMode ) \
                Can_70_RL78F2X_SetGlobalMode( ( Controller ), ( GlobalMode ) )

#define Can_70_HW_SetChannelMode( Controller, Channel, ChannelMode ) \
                Can_70_RL78F2X_SetChannelMode( ( Controller ), ( Channel ), ( ChannelMode ) )

#define Can_70_HW_SetClock( Controller, ClockSource ) \
                Can_70_RL78F2X_SetClock( ( Controller ), ( ClockSource ) )

#define Can_70_HW_SetBaudrate( Controller, CanConfigSet, BaudRateConfigID ) \
                Can_70_RL78F2X_SetBaudrate( ( Controller ), ( CanConfigSet ), ( BaudRateConfigID ) )

#define Can_70_HW_SetAfl( Controller, CanConfigSet ) \
                Can_70_RL78F2X_SetAfl( ( Controller ), ( CanConfigSet ) )

#define Can_70_HW_SetBuffer( Controller, CanConfigSet ) \
                Can_70_RL78F2X_SetBuffer( ( Controller ), ( CanConfigSet ) )

#define Can_70_HW_GetRxErrorCounter( Controller, Channel ) \
                Can_70_RL78F2X_GetRxErrorCounter( ( Controller ), ( Channel ) )

#define Can_70_HW_GetTxErrorCounter( Controller, Channel ) \
                Can_70_RL78F2X_GetTxErrorCounter( ( Controller ), ( Channel ) )

#define Can_70_HW_SetCanCommon( Controller ) \
                Can_70_RL78F2X_SetCanCommon( Controller )

#define Can_70_HW_GetTimestampCounter( ControllerId ) \
                Can_70_RL78F2X_GetTimestampCounter( ControllerId )

#define Can_70_HW_SendRequest( Controller, TxBufNo, PduInfo, TimeStamp, RateSwitch, PaddingValue ) \
                Can_70_RL78F2X_SendRequest( ( Controller ), ( TxBufNo ), ( PduInfo ), ( TimeStamp ), ( RateSwitch ), ( PaddingValue ) )

#define Can_70_HW_SwReset( Controller ) \
                Can_70_RL78F2X_SwReset( ( Controller ) )

#define Can_70_HW_ClearWakeup( Controller, Channel ) \
                Can_70_RL78F2X_ClearWakeup( ( Controller ), ( Channel ) )

#define Can_70_HW_DisableInterrupt( Controller ) \
                Can_70_RL78F2X_DisableInterrupt( ( Controller) )

#define Can_70_HW_EnableInterrupt( Controller, CanConfigSet, ControllerStatus, TxBufferUsesPolling, RxBufferUsesPolling ) \
                Can_70_RL78F2X_EnableInterrupt( ( Controller ), ( CanConfigSet ), ( ControllerStatus ), ( TxBufferUsesPolling ), ( RxBufferUsesPolling ) )

#define Can_70_HW_SetRamWindow( Controller, Page ) \
                Can_70_RL78F2X_SetRamWindow( ( Controller ), ( Page ) )

#define Can_70_HW_EnableRxFifo( Controller, CanConfigSet ) \
                Can_70_RL78F2X_EnableRxFifo( ( Controller ), ( CanConfigSet ) )

#if ( CAN_70_WAKEUP_SUPPORT == TRUE )

#define Can_70_HW_CheckWakeup( Controller, Channel ) \
                Can_70_RL78F2X_CheckWakeup( ( Controller ), ( Channel ) )

#endif /* #if ( CAN_70_WAKEUP_SUPPORT == TRUE ) */

#define Can_70_HW_GetTxBufferStatus( Controller, TxBufNo ) \
                Can_70_RL78F2X_GetTxBufferStatus( ( Controller ), ( TxBufNo ) )

#define Can_70_HW_GetErrorStatus( Controller, Channel, comStatus, errorPassiveStatus ) \
                Can_70_RL78F2X_GetErrorStatus( ( Controller ), ( Channel ), \
                                                  ( comStatus ), ( errorPassiveStatus ) )

#define Can_70_HW_CheckBusoff( Controller, Channel ) \
                Can_70_RL78F2X_CheckBusoff( ( Controller ), ( Channel ) )

#define Can_70_HW_SetEcc( Controller ) \
                Can_70_RL78F2X_SetEcc( ( Controller ) )

#define Can_70_HW_ClearTxBufferStatus( Controller, TxBufNo ) \
                Can_70_RL78F2X_ClearTxBufferStatus( ( Controller ), ( TxBufNo ) )

#define Can_70_HW_CheckRxBuffer( Controller, Channel, ObjectId ) \
                Can_70_RL78F2X_CheckRxBuffer( ( Controller ), ( Channel ), ( ObjectId ) )

#define Can_70_HW_GetRxBuffer( Controller, Channel, ObjectId, id, dlc, rxTimestamp, rxBuffer, size ) \
                Can_70_RL78F2X_GetRxBuffer( ( Controller ), ( Channel ), ( ObjectId ), ( id ), ( dlc ), ( rxTimestamp ), ( rxBuffer ), ( size ) )

#define Can_70_HW_UpdateRxBuffer( Controller, Channel, ObjectId ) \
                Can_70_RL78F2X_UpdateRxBuffer( Controller, Channel, ObjectId )

#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )

#define Can_70_HW_GetSendHistory( Controller, Channel, ObjectId, timeStampCounter, timeStampNum ) \
                Can_70_RL78F2X_GetSendHistory( ( Controller ), ( Channel ), ( ObjectId ), ( timeStampCounter ), ( timeStampNum ) )

#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */

#if ( CAN_70_USE_CANFD == TRUE )

#define Can_70_HW_SetCanFd( Controller, CanConfigSet ) \
                Can_70_RL78F2X_SetCanFd( ( Controller ), ( CanConfigSet ) )

#endif /* #if ( CAN_70_USE_CANFD == TRUE ) */

/*----------------------------------------------------------------------------*/
/* Type definitions                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/

#endif  /* #ifndef CAN_70_HW_H */
/* EOF Can_70_HW.h ************************************************************/
