/**************************************************************************************************************************************************************/
/**
 * @file      : CDD_Uart_Types.h
 * @brief     : CDD_Uart_Types header file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
#ifndef UART_TYPES_H
#define UART_TYPES_H
 
/** @addtogroup Uart_Types
 *  @brief Autosar R23-11 CDD_Uart_Types header
 *  @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "CDD_Uart_Cfg.h"
 
/** @defgroup Public_MacroDefinition
 *  @{
 */
#define UART_TYPES_VENDOR_ID_H                    0x0000U
#define UART_TYPES_MODULE_ID_H                    0x0800U
#define UART_TYPES_SW_MAJOR_VERSION_H             0x01U
#define UART_TYPES_SW_MINOR_VERSION_H             0x00U
#define UART_TYPES_SW_PATCH_VERSION_H             0x00U
#define UART_TYPES_AR_RELEASE_MAJOR_VERSION_H     0x04U
#define UART_TYPES_AR_RELEASE_MINOR_VERSION_H     0x09U
#define UART_TYPES_AR_RELEASE_REVISION_VERSION_H  0x00U
 
/* Check if current file and CDD_Uart_Cfg.h are the same Vendor Id. */
#if (UART_TYPES_VENDOR_ID_H != UART_CFG_VENDOR_ID_H)
#error "Vendor ID Numbers of CDD_Uart_Types.h and CDD_Uart_Cfg.h are different."
#endif
 
/* Check if current file and CDD_Uart_Cfg.h are the same Module Id. */
#if (UART_TYPES_MODULE_ID_H != UART_CFG_MODULE_ID_H)
#error "Module ID Numbers of CDD_Uart_Types.h and CDD_Uart_Cfg.h are different."
#endif
 
/* Check if current file and CDD_Uart_Cfg.h are the same Software version. */
#if ((UART_TYPES_SW_MAJOR_VERSION_H != UART_CFG_SW_MAJOR_VERSION_H) || \
     (UART_TYPES_SW_MINOR_VERSION_H != UART_CFG_SW_MINOR_VERSION_H) || \
     (UART_TYPES_SW_PATCH_VERSION_H != UART_CFG_SW_PATCH_VERSION_H))
#error "Software Version Numbers of CDD_Uart_Types.h and CDD_Uart_Cfg.h are different."
#endif
 
/* Check if current file and CDD_Uart_Cfg.h are the same AUTOSAR version. */
#if ((UART_TYPES_AR_RELEASE_MAJOR_VERSION_H    != UART_CFG_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_TYPES_AR_RELEASE_MINOR_VERSION_H    != UART_CFG_AR_RELEASE_MINOR_VERSION_H) || \
     (UART_TYPES_AR_RELEASE_REVISION_VERSION_H != UART_CFG_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart_Types.h and CDD_Uart_Cfg.h are different."
#endif
 
 
/**
* @brief Define number macros uint8.
*/
#define UART_U8_DAT_0                ((uint8)0x00U)  /*!< Num 0 cast type uint8  */
#define UART_U8_DAT_1                ((uint8)0x01U)  /*!< Num 1 cast type uint8  */
#if (UART_SCI2_ISR_USED == STD_ON)
#define UART_U8_DAT_2                ((uint8)0x02U)  /*!< Num 2 cast type uint8  */
#endif
#if (UART_SCI3_ISR_USED == STD_ON)
#define UART_U8_DAT_3                ((uint8)0x03U)  /*!< Num 3 cast type uint8  */
#endif
/**
* @brief Define number macros uint16.
*/
#define UART_U16_DAT_0               ((uint16)0x00U)  /*!< Num 0 cast type uint16  */
 
/**
* @brief Define number macros uint32.
*/
#define UART_U32_DAT_0               ((uint32)0x00U)  /*!< Num 0 cast type uint32  */
#define UART_U32_DAT_1               ((uint32)0x01U)  /*!< Num 1 cast type uint32  */
#define UART_U32_DAT_2               ((uint32)0x02U)  /*!< Num 2 cast type uint32  */
 
#define UART_TRUE                    ((boolean)TRUE)  /*!< TRUE value cast type boolean */
#define UART_FALSE                   ((boolean)FALSE) /*!< FALSE value cast type boolean */
#define UART_BAUDRATE_COUNT          ((uint8)15U)
 
/** @} end of Public_MacroDefinition */
 
/** @defgroup Public_TypeDefinition
 *  @{
 */
/**
 * @brief   Type of transaction.
 * @details Definition for type of transaction (SEND or RECEIVE).
 */
typedef enum Uart_DataDirectionType_t {
  UART_SEND    = 0U,              /*!< Data direction type is sending.   */
  UART_RECEIVE = 1U               /*!< Data direction type is reception. */
} Uart_DataDirectionType;
 
/**
 * @brief This type specifies the parity mode that can be configured for a UART channel of the SCI hardware IP.
 * @details Specifies the parity of the Uart channel.
 */
typedef enum Uart_ParityType_t {
  UART_PARITY_DISABLED  = 0U,     /*!< Parity of the Uart channel is disable.       */
  UART_PARITY_ZERO      = 1U,     /*!< Parity of the Uart channel bit always is 0.  */
  UART_PARITY_EVEN      = 2U,     /*!< Uart channel used odd parity.                */
  UART_PARITY_ODD       = 3U      /*!< Uart channel used even parity.               */
} Uart_ParityType;
 
/**
 * @brief   This type contains the bit order used by the Uart channel on the SCI hardware IP.
 * @details Specifies the bit order (MSB-first or LSB-first) for data transmission and reception on the UART channel.
 * @Design
 */
typedef enum Uart_SignificantSelectType_t {
  UART_LSB_FIRST_MODE = 0U,       /*!< Uart channel transfer LSB first.  */
  UART_MSB_FIRST_MODE = 1U        /*!< Uart channel transfer MSB first.  */
} Uart_SignificantSelectType;
 
/**
 * @brief   This type contains the stop bit length that can be configured for the Uart channel by the SCI hardware IP.
 * @details Stop bit length of the Uart channel.
 * @note    Can only be change when transmit/receive disabled.
 */
typedef enum Uart_StopBitLengthType_t {
  UART_ONE_STOP_BIT  = 0U,        /*!< Number of stop bit is 1. */
  UART_TWO_STOP_BIT  = 1U         /*!< Number of stop bit is 2. */
} Uart_StopBitLengthType;
 
/**
 * @brief   This type contains the data length that can be configured for the Uart channel by the SCI hardware IP.
 * @details Transmit/Receive Data Length of the Uart channel.
 * @note    Can only be change when transmit/receive disabled.
 */
typedef enum Uart_DataLengthType_t {
  UART_7_BITS_DATA_LENGTH   = 0U,    /*!< Uart channel frame have 7 bits data length.   */
  UART_8_BITS_DATA_LENGTH   = 1U,    /*!< Uart channel frame have 8 bits data length.   */
  UART_9_BITS_DATA_LENGTH   = 2U,    /*!< Uart channel frame have 9 bits data length.   */
  UART_16_BITS_DATA_LENGTH  = 3U     /*!< Uart channel frame have 16 bits data length.  */
} Uart_DataLengthType;
 
/**
 * @brief This type contains the baudrate can be used for the Uart channel of SCI hardware IP.
 */
typedef enum Uart_BaudrateType_t {
  UART_BAUDRATE_1200    = 0U,   /*!< Baudrate of the Uart channel is 1200.    */
  UART_BAUDRATE_2400    = 1U,   /*!< Baudrate of the Uart channel is 2400.    */
  UART_BAUDRATE_4800    = 2U,   /*!< Baudrate of the Uart channel is 4800.    */
  UART_BAUDRATE_7200    = 3U,   /*!< Baudrate of the Uart channel is 7200.    */
  UART_BAUDRATE_9600    = 4U,   /*!< Baudrate of the Uart channel is 9600.    */
  UART_BAUDRATE_14400   = 5U,   /*!< Baudrate of the Uart channel is 14400.   */
  UART_BAUDRATE_19200   = 6U,   /*!< Baudrate of the Uart channel is 19200.   */
  UART_BAUDRATE_28800   = 7U,   /*!< Baudrate of the Uart channel is 28800.   */
  UART_BAUDRATE_38400   = 8U,   /*!< Baudrate of the Uart channel is 38400.   */
  UART_BAUDRATE_57600   = 9U,   /*!< Baudrate of the Uart channel is 57600.   */
  UART_BAUDRATE_115200  = 10U,  /*!< Baudrate of the Uart channel is 115200.  */
  UART_BAUDRATE_230400  = 11U,  /*!< Baudrate of the Uart channel is 230400.  */
  UART_BAUDRATE_460800  = 12U,  /*!< Baudrate of the Uart channel is 460800.  */
  UART_BAUDRATE_921600  = 13U,  /*!< Baudrate of the Uart channel is 921600.  */
  UART_BAUDRATE_1843200 = 14U   /*!< Baudrate of the Uart channel is 1843200. */
} Uart_BaudrateType;
 
/**
 * @brief This type contains the transfer mode of the Uart channel on SCI hardware IP.
 */
typedef enum Uart_TransferModeType_t {
  UART_TRANSMIT_MODE    = 0U,             /*!< The Uart channel is configured for transmission only.        */
  UART_RECEIVE_MODE     = 1U,             /*!< The Uart channel is configured for reception only.           */
  UART_FULLDUPLEX_MODE  = 2U              /*!< The Uart channel supports both transmission and reception.   */
} Uart_TransferModeType;
 
 
/**
 * @brief This type contains the Uart hardware channel of the SCI hardware IP.
 */
typedef enum Uart_HwChannelType_t {
  UART_SCI0   = 0U,                  /*!< The UART of the hardware SCI 0 is used.  */
  UART_SCI1   = 1U,                  /*!< The UART of the hardware SCI 1 is used.  */
  UART_SCI2   = 2U,                  /*!< The UART of the hardware SCI 2 is used.  */
  UART_SCI3   = 3U                   /*!< The UART of the hardware SCI 3 is used.  */
} Uart_HwChannelType;
 
/**
 * @brief Notification for all peripherals which support UART features
 */
typedef P2FUNC(void, TYPEDEF, Uart_NotificationType)(void);
 
/**
 * @brief UART Driver status type.
 */
typedef enum Uart_DrvStatusType_t {
  UART_STATUS_IDLE              = 0U,   /* Status is set IDLE.                                                       */
  UART_STATUS_BUSY              = 1U,   /* Status is Busy when perform send/receive.                                 */
  UART_STATUS_ERROR             = 2U,   /* Status is Error when perform not success.                                 */
  UART_STATUS_RX_OVERFLOW       = 3U,   /* Status is RX OverFlow when occur OverRun in receive.                      */
  UART_STATUS_RX_FRAMING_ERROR  = 4U,   /* Status is RX Framing error when occur Framing error in receive.           */
  UART_STATUS_RX_PARITY_ERROR   = 5U,   /* Status is RX Verifying error when occur Parity error in receive.          */
  UART_STATUS_MULTIPLE_ERROR    = 6U,   /* Multiple error.                                                           */
  UART_STATUS_SUCCESS           = 7U,   /* Status is success when perform send/receive/other operation success.      */
  UART_STATUS_ABORTED           = 8U,   /* Status is success when perform abort.                                     */
  UART_STATUS_TIMEOUT           = 9U    /* Status is timeout when perform send/receive/other operation over timeout. */
} Uart_DrvStatusType;
 
/**
 * @brief UART Channel status type.
 */
typedef enum Uart_StatusType_t {
  UART_CH_IDLE          = 0U,   /*!< Channel is idle.                                                                               */
  UART_CH_BUSY          = 1U,   /*!< Channel is busy with a transmission or reception.                                              */
  UART_CH_ERROR         = 2U,   /*!< An error occurred during transmission or reception.                                            */
  UART_CH_COMPLETE      = 3U,   /*!< Synchronous transmission/reception or asynchronous transmission/reception trigger is complete. */
  UART_CH_ABORTED       = 4U,   /*!< Transmission or reception was aborted.                                                         */
  UART_CH_TIMEOUT       = 5U    /*!< Transmission or reception timed out.                                                           */
} Uart_StatusType;
 
/**
 * @brief This type contains information used for synchronous data transmission.
 */
typedef struct Uart_SyncSendType_t {
  VAR(uint32, TYPEDEF)               TxBufferSize_u32;         /*!< Specifies the size of data is sent in bytes.             */
  P2VAR(uint32, TYPEDEF, AUTOMATIC)  RxBufferSize_ptr;         /*!< Pointer to where store size of data is receive in bytes. */
  P2CONST(uint8, TYPEDEF, AUTOMATIC) TxDataBuffer_ptr;         /*!< Pointer to where store data is send.                     */
  P2VAR(uint8, TYPEDEF, AUTOMATIC)   RxDataBuffer_ptr;         /*!< Pointer to where store received data.                    */
} Uart_SyncSendType;
 
/**
 * @brief This type contains information for configuring the prescale of the UART module based on the desired input baudrate.
 */
typedef struct Uart_ClockPrescaleType_t {
  VAR(uint8, TYPEDEF) SPSPrescaleVal_u8;          /*!< Specifies the prescale value used to generate the FMCK for the UART module. */
  VAR(uint8, TYPEDEF) SDRPrescaleVal_u8;          /*!< Specifies the internal prescale of the UART module used to generate the expected baud rate. */
} Uart_ClockPrescaleType;
 
/**
 * @brief UART hardware configuration structure
 */
typedef struct Uart_HwConfigType_t {
  VAR(Uart_DataLengthType, TYPEDEF)                    DataLength_en;        /*!< Specifies data length of the Uart channel.                     */
  VAR(Uart_StopBitLengthType, TYPEDEF)                 StopBit_en;           /*!< Specifies stop bit length of the Uart channel.                 */
  VAR(Uart_ParityType, TYPEDEF)                        Parity_en;            /*!< Specifies the Parity format.                                   */
  VAR(Uart_SignificantSelectType, TYPEDEF)             SignificantSelect_en; /*!< Specifies the bit order for data transfer of the Uart channel. */
  VAR(boolean, TYPEDEF)                                InvertOutput_bool;    /*!< Output data be invert or not.                                  */
  VAR(Uart_TransferModeType, TYPEDEF)                  TransferMode_en;      /*!< Select transfer mode of the UART channel.                      */
  P2CONST(Uart_ClockPrescaleType, TYPEDEF, AUTOMATIC)  ClockPrescale_ptr;    /*!< Pointer to clock prescale set for each baudrate.               */
} Uart_HwConfigType;
 
/**
 * @brief UART user configuration structure definition.
 */
typedef struct Uart_ChannelConfigType_t {
  VAR(Uart_HwChannelType, TYPEDEF)                HwChannel_en;        /*!< Specifies Uart Hardware Channel                                          */
  VAR(Uart_BaudrateType, TYPEDEF)                 Baudrate_en;         /*!< Specifies baudrate of the Uart channel.                                  */
  VAR(Uart_NotificationType, TYPEDEF)             RxNotification_ptr;  /*!< Callback function name for Rx event notification of the UART channel.    */
  VAR(Uart_NotificationType, TYPEDEF)             TxNotification_ptr;  /*!< Callback function name for Tx event notification of the UART channel.    */
  VAR(Uart_NotificationType, TYPEDEF)             ErrNotification_ptr; /*!< Callback function name for Error event notification of the UART channel. */
  VAR(uint32, TYPEDEF)                            ClockFrequency_u32;  /*!< The clock frequency supplied for the UART channel.                       */
  P2CONST(Uart_HwConfigType, TYPEDEF, AUTOMATIC)  HwConfig_ptr;        /*!< UART hardware configuration.                                             */
} Uart_ChannelConfigType;
 
/**
 * @brief This type contains UART configuration structure.
 */
typedef struct Uart_ConfigType_t {
  P2CONST(Uart_ChannelConfigType, TYPEDEF, AUTOMATIC)  ChannelConfig_ptr;    /*!< Uart channel configuration set. */
} Uart_ConfigType;
 
/** @} end of group Public_TypeDefinition */
 
/** @defgroup Global_VariableDeclaration
 *  @{
 */
 
/** @} end of group Global_VariableDeclaration */
 
/** @defgroup Public_FunctionDeclaration
 *  @{
 */
 
 
 
/** @} end of group Public_FunctionDeclaration */
 
#ifdef __cplusplus
}
#endif
 
/** @} end of group Uart_Types */
 
#endif /* UART_TYPES_H */
 