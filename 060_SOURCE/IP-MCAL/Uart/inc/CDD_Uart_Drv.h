/**************************************************************************************************************************************************************/
/**
 * @file      : CDD_Uart_Drv.h
 * @brief     : CDD_Uart_Drv header file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
#ifndef UART_DRV_H
#define UART_DRV_H
 
/** @addtogroup Uart
 *  @brief Autosar R23-11 CDD_Uart_Drv header
 *  @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "CDD_Uart_Types.h"
 
/** @defgroup Public_MacroDefinition
 *  @{
 */
#define UART_DRV_VENDOR_ID_H                      0x0000U
#define UART_DRV_MODULE_ID_H                      0x0800U
#define UART_DRV_SW_MAJOR_VERSION_H               0x01U
#define UART_DRV_SW_MINOR_VERSION_H               0x00U
#define UART_DRV_SW_PATCH_VERSION_H               0x00U
#define UART_DRV_AR_RELEASE_MAJOR_VERSION_H       0x04U
#define UART_DRV_AR_RELEASE_MINOR_VERSION_H       0x09U
#define UART_DRV_AR_RELEASE_REVISION_VERSION_H    0x00U
 
/* Check if current file and CDD_Uart_Types.h are the same Vendor Id. */
#if (UART_DRV_VENDOR_ID_H != UART_TYPES_VENDOR_ID_H)
#error "Vendor ID Numbers of CDD_Uart.h and CDD_Uart_Types.h are different."
#endif
 
/* Check if current file and CDD_Uart_Types.h are the same Module Id. */
#if (UART_DRV_MODULE_ID_H != UART_TYPES_MODULE_ID_H)
#error "Module ID Numbers of CDD_Uart.h and CDD_Uart_Types.h are different."
#endif
 
/* Check if current file and CDD_Uart_Types.h are the same AUTOSAR version. */
#if ((UART_DRV_AR_RELEASE_MAJOR_VERSION_H   != UART_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_DRV_AR_RELEASE_MINOR_VERSION_H   != UART_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (UART_DRV_AR_RELEASE_REVISION_VERSION_H != UART_TYPES_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart_Drv.h and CDD_Uart_Types.h are different."
#endif
 
/* Check if current file and CDD_Uart_Types.h are the same Software version. */
#if ((UART_DRV_SW_MAJOR_VERSION_H != UART_TYPES_SW_MAJOR_VERSION_H) || \
     (UART_DRV_SW_MINOR_VERSION_H != UART_TYPES_SW_MINOR_VERSION_H) || \
     (UART_DRV_SW_PATCH_VERSION_H != UART_TYPES_SW_PATCH_VERSION_H))
#error "Software Version Numbers of CDD_Uart_Drv.h and CDD_Uart_Types.h are different."
#endif
/** @} end of Public_MacroDefinition */
 
/** @defgroup Public_TypeDefinition
 *  @{
 */
/**
 * @brief This type contains runtime status of the UART driver.
 */
typedef struct Uart_DrvHwStateType_t {
  P2CONST(uint8, TYPEDEF, AUTOMATIC) TxBuffer_ptr;        /* Buffer to store data being sent.          */
  P2VAR(uint8, TYPEDEF, AUTOMATIC)   RxBuffer_ptr;        /* Buffer to store data being received.      */
  VAR(uint32, TYPEDEF)               TxSize_u32;          /* Remaining bytes to be sent.               */
  VAR(uint32, TYPEDEF)               RxSize_u32;          /* Remaining bytes to be received.           */
  VAR(boolean, TYPEDEF)              TxBusy_bool;         /* If performing transmit status is True.    */
  VAR(boolean, TYPEDEF)              RxBusy_bool;         /* If performing receive status is True.     */
  VAR(Uart_DrvStatusType, TYPEDEF)  SendStatus_en;        /* Store status of send.                     */
  VAR(Uart_DrvStatusType, TYPEDEF)  ReceiveStatus_en;     /* Store status of receive.                  */
  VAR(uint8, TYPEDEF)                SDRPrescaleVal_u8;   /* Store SDR prescale value of UART channel. */
} Uart_DrvHwStateType;
 
/** @} end of group Public_TypeDefinition */
 
/** @defgroup Global_VariableDeclaration
 *  @{
 */
 
/** @} end of group Global_VariableDeclaration */
 
/** @defgroup Public_FunctionDeclaration
 *  @{
 */
#define UART_START_SEC_CODE_SLOW
#include "Uart_MemMap.h"
/**
 * @brief       This function configures the UART with the options provided in the given structure.
 * @details     This function will initialize the UART driver and interact directly with the register.
 *
 * @param[in]   p_Config_ptr:  Specifies the pointer to the configuration set.
 *
 * @return      Std_ReturnType.
 *              E_OK: The UART driver was initialized successfully.
 *              E_NOT_OK: The UART driver was initialized unsuccessfully.
 *
 * @Design      SDD_UART_015, SDD_UART_016, SDD_UART_021, SDD_UART_055, SDD_UART_056.
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_DrvInit(P2CONST(Uart_ConfigType, AUTOMATIC, UART_APPL_DATA) p_Config_ptr);
 
#if (STD_ON == UART_DEINIT_API)
/**
 * @brief     Deinitialize the UART driver.
 * @details   This function is used to deinitialize the UART driver.
 *
 * @param[in] p_Channel_u8: Specifies UART channel ID
 *
 * @return    None.
 *
 * @Design    SDD_UART_015, SDD_UART_016, SDD_UART_022, SDD_UART_052, SDD_UART_055, SDD_UART_056.
 */
FUNC(void, UART_CODE_SLOW) Uart_DrvDeInit(CONST(uint8, AUTOMATIC) p_Channel_u8);
#endif /* (STD_ON == UART_DEINIT_API) */
 
/**
 * @brief       Asynchronously send data over the specified UART channel.
 * @details     This function initiates an asynchronous data send operation over the given UART channel.
 *              It checks whether the UART channel is not in the busy status before starting the send operation.
 *              If the conditions are met, it calls the appropriate function to start sending data and enables the UART for transmission.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel ID.
 * @param[in]   p_BufferSize_u32: Specifies the size of the data buffer to be sent.
 * @param[in]   p_DataBuffer_ptr: A pointer to the data buffer containing the data to be sent.
 *
 * @return      Uart_StatusType    Status of the asynchronous send operation.
 *              UART_CH_COMPLETE: Finished trigger transaction without errors.
 *              UART_CH_BUSY: The UART channel is in busy state.
 *
 * @Design      SDD_UART_016, SDD_UART_024, SDD_UART_055.
 */
FUNC(Uart_StatusType, UART_CODE_SLOW) Uart_DrvAsyncSend(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                       VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                       P2CONST(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr);
/**
 * @brief       Perform a synchronous send operation on the specified UART channel.
 * @details     This function is used to send data synchronously through a given UART channel.
 *              It checks if the UART channel is not busy, then starts sending the data and waits
 *              until the transmission is complete or a timeout occurs. The function interacts directly
 *              with the UART hardware registers to perform the send operation.
 *
 * @param[in]   p_Channel_u8: Numeric identifier of the UART channel.
 * @param[in]   p_SyncSendInfo_ptr: Pointer to the structure contains information used for synchronous transmit data.
 * @param[in]   p_Timeout_u32: Timeout value in milliseconds for the synchronous send operation.
 *
 * @return      Uart_StatusType: Status of the asynchronous send operation.
 *              UART_CH_COMPLETE: Finished transaction without errors.
 *              UART_CH_BUSY: The UART channel is in busy state.
 *              UART_CH_TIMEOUT: Timeout occurs.
 *
 * @Design      SDD_UART_014, SDD_UART_015, SDD_UART_016, SDD_UART_023, SDD_UART_052, SDD_UART_055.
 */
FUNC(Uart_StatusType, UART_CODE_SLOW) Uart_DrvSyncSend(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                       P2CONST(Uart_SyncSendType, AUTOMATIC, UART_APPL_DATA) p_SyncSendInfo_ptr,
                                                       VAR(uint32, AUTOMATIC) p_Timeout_u32);
/**
 * @brief       Asynchronously receive data over the specified UART channel.
 * @details     This function initiates an asynchronous data receive operation over the given UART channel.
 *              It checks if the UART channel is not busy and then configures the UART to start receiving data.
 *              It sets the buffer size and pointer for the received data, enables the receive function.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel ID.
 * @param[in]   p_BufferSize_u32: Specifies the size of the data buffer to receive.
 * @param[out]  p_DataBuffer_ptr: A pointer to the data buffer where the received data will be stored.
 *
 * @return      Uart_StatusType: Status of the asynchronous receive operation.
 *              UART_CH_COMPLETE: Finished trigger transaction without errors.
 *              UART_CH_BUSY: The UART channel is in busy state.
 *
 * @Design      SDD_UART_016, SDD_UART_026, SDD_UART_056.
 */
FUNC(Uart_StatusType, UART_CODE_SLOW) Uart_DrvAsyncReceive(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                           VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                           P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr);
 
/**
 * @brief       Synchronously receive data over the specified UART channel.
 * @details     This function is used to receive data synchronously through a given UART channel.
 *              It checks if the UART channel is not busy, then starts receiving the data and waits
 *              until the reception is complete or a timeout occurs. The function interacts directly
 *              with the UART hardware registers to perform the receive operation.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel ID.
 * @param[in]   p_BufferSize_u32: Specifies the size of the data buffer to be receive.
 * @param[in]   p_DataBuffer_ptr: A pointer to the data buffer containing the data to be receive.
 * @param[in]   p_Timeout_u32: Timeout value in milliseconds for the synchronous receive operation.
 *
 * @return      Uart_StatusType: Status of the asynchronous receive operation.
 *              UART_CH_COMPLETE: Finished transaction without errors.
 *              UART_CH_BUSY: The UART channel is in busy state.
 *              UART_CH_TIMEOUT: Timeout occurs.
 *
 * @Design      SDD_UART_014, SDD_UART_015, SDD_UART_016, SDD_UART_025, SDD_UART_052, SDD_UART_056.
 */
FUNC(Uart_StatusType, UART_CODE_SLOW) Uart_DrvSyncReceive(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                          VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                          P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr,
                                                          VAR(uint32, AUTOMATIC) p_Timeout_u32);
 
#if (STD_ON == UART_GET_BAUDRATE_API)
/**
 * @brief       Get the current baud rate of the specified UART channel.
 * @details     This function retrieves the current baud rate of the given UART channel and stores it in the provided pointer.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel ID.
 * @param[out]  p_Baudrate_ptr: A pointer where the current baud rate will be written.
 * @param[in]   p_ClockFrequency_u32: Specifies the clock frequency of the UART channel.
 *
 * @return      None.
 *
 * @Design      SDD_UART_027.
 */
FUNC(void, UART_CODE_SLOW) Uart_DrvGetBaudrate(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                              P2VAR(uint32, AUTOMATIC, UART_APPL_DATA) p_Baudrate_ptr,
                                              VAR(uint32, AUTOMATIC) p_ClockFrequency_u32);
#endif /* STD_ON == UART_GET_BAUDRATE_API */
 
/**
 * @brief       Set the baud rate of the specified UART channel.
 * @details     This function sets the baud rate of the given UART channel
 *              based on the provided baud rate value and channel clock frequency.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel ID.
 * @param[in]   p_Baudrate_en: Specifies the desired baud rate.
 *
 * @return      Std_ReturnType.
 *              E_OK: The input baudrate was set successfully.
 *              E_NOT_OK: Failed to set the input baudrate.
 *
 * @Design      SDD_UART_015, SDD_UART_028.
 *
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_DrvSetBaudrate(VAR(uint8, AUTOMATIC) p_Channel_u8, VAR(Uart_BaudrateType, AUTOMATIC) p_Baudrate_en);
 
/**
 * @brief       Abort the UART transmission or reception operation.
 * @details     This function is used to abort the UART transmission or reception operation
 *              based on the specified data direction. It disables the corresponding interrupt
 *              and sets the status of the UART channel to aborted.
 *
 * @param[in]   p_Channel_u8: Numeric identifier of the Uart channel.
 * @param[in]   p_Direction_en: The type of transaction (send or receive).
 *
 * @return      None.
 *
 * @Design      SDD_UART_016, SDD_UART_029, SDD_UART_055, SDD_UART_056.
 */
FUNC(void, UART_CODE_SLOW) Uart_DrvAbort(VAR(uint8, AUTOMATIC) p_Channel_u8, VAR(Uart_DataDirectionType, AUTOMATIC) p_Direction_en);
 
/**
 * @brief       Get the status of the corresponding UART channel.
 * @details     This function retrieves the status of the UART driver, including the status code
 *              and the number of bytes remaining for transmission or reception.
 *
 * @param[in]   p_Channel_u8: Numeric identifier of the UART channel.
 * @param[out]  p_BytesTransaction_ptr: A pointer where the number of remaining bytes will be written or number of received bytes.
 * @param[in]   p_Direction_en: Specifies the data direction (send or receive).
 *
 * @return      Uart_StatusType : Status of the corresponding channel.
 *              UART_CH_IDLE: The UART channel is in idle state.
 *              UART_CH_BUSY: The UART channel is in busy state.
 *              UART_CH_ERROR: The UART channel encountered errors during receiving data.
 *              UART_CH_COMPLETE: The UART channel finished transaction without errors.
 *              UART_CH_ABORTED: The UART operation is aborted.
 *              UART_CH_TIMEOUT: Timeout occurs.
 *
 * @Design      SDD_UART_016, SDD_UART_030.
 */
FUNC(Uart_StatusType, UART_CODE_SLOW) Uart_DrvGetStatus(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                        P2VAR(uint32, AUTOMATIC, UART_APPL_DATA) p_BytesTransaction_ptr,
                                                        VAR(Uart_DataDirectionType, AUTOMATIC) p_Direction_en);
#define UART_STOP_SEC_CODE_SLOW
#include "Uart_MemMap.h"
 
#define UART_START_SEC_CODE_FAST
#include "Uart_MemMap.h"
#if ((UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON))
/**
 * @brief       This function used to handler transmit interrupt.
 *
 * @param[in]   p_HwChannel_u8: Specifies the UART hardware channel occurs interrupt.
 *
 * @return      None.
 *
 * @Design      SDD_UART_015, SDD_UART_016, SDD_UART_032.
 */
FUNC(void, UART_CODE_FAST) Uart_DrvTxIrqHandler(VAR(uint8, AUTOMATIC) p_HwChannel_u8);
#endif /* ((UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON)) */
 
#if ((UART_SCI0_ISR_RX_USED == STD_ON) || (UART_SCI1_ISR_RX_USED == STD_ON) || (UART_SCI2_ISR_RX_USED == STD_ON) || (UART_SCI3_ISR_RX_USED == STD_ON))
/**
 * @brief     This function used to handler transmit interrupt.
 *
 * @param[in] p_HwChannel_u8: Specifies the UART hardware channel occurs interrupt.
 *
 * @return    None.
 *
 * @Design    SDD_UART_014, SDD_UART_015, SDD_UART_016, SDD_UART_033.
 */
FUNC(void, UART_CODE_FAST) Uart_DrvRxIrqHandler(VAR(uint8, AUTOMATIC) p_HwChannel_u8);
#endif /* ((UART_SCI0_ISR_RX_USED == STD_ON) || (UART_SCI1_ISR_RX_USED == STD_ON) || (UART_SCI2_ISR_RX_USED == STD_ON) || (UART_SCI3_ISR_RX_USED == STD_ON)) */
#define UART_STOP_SEC_CODE_FAST
#include "Uart_MemMap.h"
#ifdef __cplusplus
}
#endif
 
/** @} end of group Uart */
 
#endif /* UART_DRV_H */
 