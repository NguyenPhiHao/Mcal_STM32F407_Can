/**************************************************************************************************************************************************************/
/**
 * @file      : CDD_Uart.h
 * @brief     : CDD_Uart header file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
#ifndef UART_H
#define UART_H
 
/** @addtogroup Uart
 *  @brief Autosar R23-11 CDD_Uart header
 *  @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "CDD_Uart_Types.h"
 
/** @defgroup Public_MacroDefinition
 *  @{
 */
#define UART_VENDOR_ID_H                     0x0000U
#define UART_MODULE_ID_H                     0x0800U
#define UART_SW_MAJOR_VERSION_H              0x01U
#define UART_SW_MINOR_VERSION_H              0x00U
#define UART_SW_PATCH_VERSION_H              0x00U
#define UART_AR_RELEASE_MAJOR_VERSION_H      0x04U
#define UART_AR_RELEASE_MINOR_VERSION_H      0x09U
#define UART_AR_RELEASE_REVISION_VERSION_H   0x00U
 
/* Check if current file and CDD_Uart_Types.h are the same Vendor Id. */
#if (UART_VENDOR_ID_H != UART_TYPES_VENDOR_ID_H)
#error "Vendor ID Numbers of CDD_Uart.h and CDD_Uart_Types.h are different."
#endif
 
/* Check if current file and CDD_Uart_Types.h are the same Module Id. */
#if (UART_MODULE_ID_H != UART_TYPES_MODULE_ID_H)
#error "Module ID Numbers of CDD_Uart.h and CDD_Uart_Types.h are different."
#endif
 
/* Check if current file and CDD_Uart_Types.h are the same Software version. */
#if ((UART_SW_MAJOR_VERSION_H != UART_TYPES_SW_MAJOR_VERSION_H) || \
     (UART_SW_MINOR_VERSION_H != UART_TYPES_SW_MINOR_VERSION_H) || \
     (UART_SW_PATCH_VERSION_H != UART_TYPES_SW_PATCH_VERSION_H))
#error "Software Version Numbers of CDD_Uart.h and CDD_Uart_Types.h are different."
#endif
 
/* Check if current file and CDD_Uart_Types.h are the same AUTOSAR version. */
#if ((UART_AR_RELEASE_MAJOR_VERSION_H   != UART_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_AR_RELEASE_MINOR_VERSION_H   != UART_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (UART_AR_RELEASE_REVISION_VERSION_H != UART_TYPES_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart.h and CDD_Uart_Types.h are different."
#endif
 
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
/**
 * @brief Definition of development errors in module UART.
 */
#define UART_E_UNINIT                       ((uint8)0x00U)
#define UART_E_ALREADY_INITIALIZED          ((uint8)0x01U)
#define UART_E_INIT_FAILED                  ((uint8)0x02U)
#define UART_E_INVALID_CHANNEL              ((uint8)0x03U)
#define UART_E_INVALID_DIRECTION            ((uint8)0x04U)
#define UART_E_INVALID_BAUDRATE             ((uint8)0x05U)
#define UART_E_PARAM_POINTER                ((uint8)0x06U)
#define UART_E_CHANNEL_BUSY                 ((uint8)0x07U)
#define UART_E_INVALID_STATUS               ((uint8)0x08U)
#define UART_E_INVALID_BUFFERSIZE           ((uint8)0x09U)
/**
 * @brief Definition of API ID in module UART.
 */
#define UART_INIT_ID                        ((uint8)0x01U)
#define UART_DEINIT_ID                      ((uint8)0x02U)
#define UART_SYNCSEND_ID                    ((uint8)0x03U)
#define UART_ASYNCSEND_ID                   ((uint8)0x04U)
#define UART_SYNCRECEIVE_ID                 ((uint8)0x05U)
#define UART_ASYNCRECEIVE_ID                ((uint8)0x06U)
#define UART_GETBAUDRATE_ID                 ((uint8)0x07U)
#define UART_SETBAUDRATE_ID                 ((uint8)0x08U)
#define UART_ABORT_ID                       ((uint8)0x09U)
#define UART_GETSTATUS_ID                   ((uint8)0x0AU)
#define UART_VERSIONINFO_ID                 ((uint8)0x0BU)
#endif /* (STD_ON == UART_ENABLE_DEV_ERROR_DETECT) */
/** @} end of Public_MacroDefinition */
 
/** @defgroup Public_TypeDefinition
 *  @{
 */
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
/**
 * @brief   List of UART Driver State.
 * @details Provides information about the current state of the UART driver.
 */
typedef enum {
  UART_INITIALIZED = 0U,  /* UART Driver is Initialized   */
  UART_UNINIT      = 1U   /* UART Driver is Un-Initialized */
} Uart_DriverStateType;
#endif /* (STD_ON == UART_ENABLE_DEV_ERROR_DETECT) */
/** @} end of group Public_TypeDefinition */
 
/** @defgroup Global_VariableDeclaration
 *  @{
 */
#if (STD_ON == UART_PRECOMPILE_SUPPORT)
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
extern CONST(Uart_ConfigType, UART_CONFIG_DATA) Uart_PreCompileConfig_st;
#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
#endif /* (STD_ON == UART_PRECOMPILE_SUPPORT) */
 
/**
 * @brief  Extern Post-Build configurations.
 */
#if (STD_OFF == UART_PRECOMPILE_SUPPORT)
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
UART_CONFIG_EXT
#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
#endif /* (STD_OFF == UART_PRECOMPILE_SUPPORT) */
 
/** @} end of group Global_VariableDeclaration */
 
/** @defgroup Public_FunctionDeclaration
 *  @{
 */
#define UART_START_SEC_CODE_SLOW
#include "Uart_MemMap.h"
/**
 * @brief     This function initializes the Uart driver with the given configuration.
 * @details   The function shall initialize the Uart module (i.e. static variables,
 *            including flags and Uart HW Unit global hardware settings), as well as the Uart channels.
 *
 * @param[in] Config: Represents the pointer to the configuration set.
 *
 * @return    None.
 *
 * @note      Uart_Init() must be called before all other Uart Driver module's functions (except Uart_GetVersionInfo()).
 *
 * @Design    SDD_UART_001, SDD_UART_012, SDD_UART_013, SDD_UART_052, SDD_UART_053, SDD_UART_054, SDD_UART_055, SDD_UART_056.
 */
FUNC(void, UART_CODE_SLOW) Uart_Init(P2CONST(Uart_ConfigType, AUTOMATIC, UART_APPL_DATA) Config);
 
#if (STD_ON == UART_DEINIT_API)
/**
 * @brief     This function performs software de-initialization of UART driver.
 *            It shall de-initialize the Uart hardware peripheral for each channel.
 *
 * @param[in] None.
 *
 * @return    Std_ReturnType.
 *            E_OK: de-initialization command has been accepted.
 *            E_NOT_OK: de-initialization command has not been accepted.
 *
 * @note      Uart_DeInit() shall be called after Uart_Init()
 *
 * @Design    SDD_UART_002, SDD_UART_012, SDD_UART_013, SDD_UART_052, SDD_UART_053, SDD_UART_054, SDD_UART_055, SDD_UART_056.
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_DeInit(void);
#endif /* (STD_ON == UART_DEINIT_API) */
 
/**
 * @brief     This function performs a synchronous send operation on the specified UART channel.
 *            It sends data and waits until the transmission is complete or a timeout occurs.
 *
 * @param[in] Channel: Numeric identifier of the Uart channel.
 * @param[in] SyncSendInfoPtr: Pointer to the structure contains information used for synchronous transmit data.
 * @param[in] Timeout: Timeout value in milliseconds for the send operation.
 *
 * @return    Std_ReturnType.
 *            E_OK: the synchronous send operation has been completed successfully.
 *            E_NOT_OK: the synchronous send operation has failed due to an error or timeout.
 *
 * @note      Uart_SyncSend() shall be called after Uart_Init().
 *
 * @Design    SDD_UART_003, SDD_UART_012, SDD_UART_052, SDD_UART_053, SDD_UART_055.
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_SyncSend(VAR(uint8, AUTOMATIC) Channel,
                                                  P2CONST(Uart_SyncSendType, AUTOMATIC, UART_APPL_DATA) SyncSendInfoPtr,
                                                  VAR(uint32, AUTOMATIC) Timeout);
 
/**
 * @brief     This function performs an asynchronous send operation on the specified UART channel.
 *
 * @param[in] Channel: Numeric identifier of the Uart channel.
 * @param[in] BufferSize: Size of data is sent in bytes.
 * @param[in] DataBufferPtr: Pointer to data is sent.
 *
 * @return    Std_ReturnType.
 *            E_OK: the asynchronous send operation has been accepted
 *            E_NOT_OK: the asynchronous send operation has not been accepted
 *
 * @note      Uart_AsyncSend() shall be called after Uart_Init().
 *
 * @Design    SDD_UART_004, SDD_UART_012, SDD_UART_052, SDD_UART_053, SDD_UART_055.
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_AsyncSend(VAR(uint8, AUTOMATIC) Channel,
                                                    VAR(uint32, AUTOMATIC) BufferSize,
                                                    P2CONST(uint8, AUTOMATIC, UART_APPL_DATA) DataBufferPtr);
 
/**
 * @brief     This function performs a synchronous receive operation on the specified UART channel.
 *            It waits until the specified number of bytes are received or a timeout occurs.
 *
 * @param[in] Channel: Numeric identifier of the UART channel.
 * @param[in] BufferSize: Size of the data buffer to receive data into, in bytes.
 * @param[out] DataBufferPtr: Pointer to the buffer where received data will be stored.
 * @param[in] Timeout: Timeout value in milliseconds for the synchronous receive operation.
 *
 * @return    Std_ReturnType.
 *            E_OK: the synchronous receive operation has been completed successfully.
 *            E_NOT_OK: the synchronous receive operation has failed due to an error or timeout.
 *
 * @note      Uart_SyncReceive() shall be called after Uart_Init().
 *
 * @Design    SDD_UART_005, SDD_UART_012, SDD_UART_052, SDD_UART_053, SDD_UART_056.
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_SyncReceive(VAR(uint8, AUTOMATIC) Channel,
                                                      VAR(uint32, AUTOMATIC) BufferSize,
                                                      P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) DataBufferPtr,
                                                      VAR(uint32, AUTOMATIC) Timeout);
 
/**
 * @brief     This function service to receive a number of bytes in an asynchronous manner .
 *
 * @param[in] Channel: Numeric identifier of the UART channel.
 * @param[in] BufferSize: Size of data is sent in bytes.
 * @param[out] DataBufferPtr: Pointer to the buffer where received data will be stored.
 *
 * @return    Std_ReturnType.
 *            E_OK: the asynchronous receive operation has been accepted
 *            E_NOT_OK: the asynchronous receive operation has not been accepted
 *
 * @note      Uart_AsyncReceive() shall be called after Uart_Init().
 *
 * @Design    SDD_UART_006, SDD_UART_012, SDD_UART_052, SDD_UART_053, SDD_UART_056.
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_AsyncReceive(VAR(uint8, AUTOMATIC) Channel,
                                                      VAR(uint32, AUTOMATIC) BufferSize,
                                                      P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) DataBufferPtr);
 
#if (STD_ON == UART_GET_BAUDRATE_API)
/**
 * @brief     This function retrieves the baud rate of the UART driver for a specific channel.
 *
 * @param[in] Channel: Numeric identifier of the UART channel.
 * @param[out] BaudratePtr: A pointer where the baud rate will be written.
 *
 * @return    None.
 *
 * @note      Uart_GetBaudrate() shall be called after Uart_Init().
 *
 * @Design    SDD_UART_007, SDD_UART_012, SDD_UART_013, SDD_UART_052, SDD_UART_053.
 */
FUNC(void, UART_CODE_SLOW) Uart_GetBaudrate(VAR(uint8, AUTOMATIC) Channel, P2VAR(uint32, AUTOMATIC, UART_APPL_DATA) BaudratePtr);
#endif /* (STD_ON == UART_GET_BAUDRATE_API) */
/**
 * @brief     This function sets the baud rate of the UART driver for a specific channel.
 *
 * @param[in] Channel: Numeric identifier of the Uart channel.
 * @param[in] Baudrate: Baudrate is defined in config.
 *
 * @return    Std_ReturnType.
 *            E_OK: the baud rate has been set successfully
 *            E_NOT_OK: the baud rate has not been set successfully
 *
 * @note      Uart_SetBaudrate() shall be called after Uart_Init().
 *
 * @Design    SDD_UART_008, SDD_UART_012, SDD_UART_013, SDD_UART_052, SDD_UART_053.
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_SetBaudrate(VAR(uint8, AUTOMATIC) Channel, VAR(Uart_BaudrateType, AUTOMATIC) Baudrate);
 
/**
 * @brief     This function aborts the ongoing UART transmission or reception operation.
 *
 * @param[in] Channel: Numeric identifier of the Uart channel.
 * @param[in] Direction: The type of transaction (send or receive).
 *
 * @return    None.
 *
 * @note      Uart_Abort() shall be called after Uart_Init().
 *
 * @Design    SDD_UART_009, SDD_UART_012, SDD_UART_052, SDD_UART_053, SDD_UART_055, SDD_UART_056.
 */
FUNC(void, UART_CODE_SLOW) Uart_Abort(VAR(uint8, AUTOMATIC) Channel, VAR(Uart_DataDirectionType, AUTOMATIC) Direction);
 
#if (STD_ON == UART_GET_STATUS_API)
/**
 * @brief     This function retrieves the status of the UART driver for a specific channel and direction.
 *
 * @param[in] Channel: Numeric identifier of the UART channel.
 * @param[out] BytesTransactionPtr: A pointer where the number of remaining bytes will be written or number of received bytes.
 * @param[in] Direction: Represents the data direction (send or receive).
 *
 * @return    Uart_StatusType.
 *            UART_CH_IDLE: Channel is idle state.
 *            UART_CH_BUSY: Channel is busy state.
 *            UART_CH_ERROR: Channel encountered errors during sending or receiving.
 *            UART_CH_COMPLETE: Finished transaction without errors.
 *            UART_CH_ABORTED: UART operation is aborted.
 *            UART_CH_TIMEOUT: timeout occurred.
 *
 * @note      Uart_GetStatus() shall be called after Uart_Init().
 *
 * @Design    SDD_UART_010, SDD_UART_012, SDD_UART_052, SDD_UART_053.
 */
FUNC(Uart_StatusType, UART_CODE_SLOW) Uart_GetStatus(VAR(uint8, AUTOMATIC) Channel,
                                                    P2VAR(uint32, AUTOMATIC, UART_APPL_DATA) BytesTransactionPtr,
                                                    VAR(Uart_DataDirectionType, AUTOMATIC) Direction);
#endif /* (STD_ON == UART_GET_STATUS_API) */
 
#if (STD_ON == UART_VERSION_INFO_API)
/**
 * @brief     This function retrieves the version information of the UART driver.
 *
 * @param[out] versioninfo: A pointer where the version information will be written.
 *
 * @return    None.
 *
 * @note      Uart_GetVersionInfo() can be called at any time.
 *
 * @Design    SDD_UART_011, SDD_UART_012, SDD_UART_052, SDD_UART_053.
 */
FUNC(void, UART_CODE_SLOW) Uart_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, UART_APPL_DATA) versioninfo);
#endif /* (STD_ON == UART_VERSION_INFO_API) */
#define UART_STOP_SEC_CODE_SLOW
#include "Uart_MemMap.h"
/** @} end of group Public_FunctionDeclaration */
 
#ifdef __cplusplus
}
#endif
 
/** @} end of group Uart */
 
#endif /* UART_H */
 