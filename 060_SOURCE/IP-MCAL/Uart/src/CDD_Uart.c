/**************************************************************************************************************************************************************/
/**
 * @file      : CDD_Uart.c
 * @brief     : CDD_Uart source file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
/** @addtogroup Uart
 *  @brief Autosar R23-11 CDD_Uart source code
 *  @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "CDD_Uart.h"
#include "CDD_Uart_Drv.h"
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  #include "Det.h"
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
#if (STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS)
  #include "Dem.h"
#endif /* STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS */
 
/** @defgroup Private_MacroDefinition
 *  @{
 */
#define UART_VENDOR_ID_C                   0x0000U
#define UART_SW_MAJOR_VERSION_C            0x01U
#define UART_SW_MINOR_VERSION_C            0x00U
#define UART_SW_PATCH_VERSION_C            0x00U
#define UART_AR_RELEASE_MAJOR_VERSION_C    0x04U
#define UART_AR_RELEASE_MINOR_VERSION_C    0x09U
#define UART_AR_RELEASE_REVISION_VERSION_C 0x00U
 
/* Check if current file and CDD_Uart.h are the same Vendor Id */
#if (UART_VENDOR_ID_C != UART_VENDOR_ID_H)
#error "Vendor Id of CDD_Uart.c and CDD_Uart.h are different"
#endif
 
/* Check if current file and CDD_Uart.h are the same Software version */
#if ((UART_SW_MAJOR_VERSION_C != UART_SW_MAJOR_VERSION_H) || \
     (UART_SW_MINOR_VERSION_C != UART_SW_MINOR_VERSION_H) || \
     (UART_SW_PATCH_VERSION_C != UART_SW_PATCH_VERSION_H))
#error "Software Version Numbers of CDD_Uart.c and CDD_Uart.h are different"
#endif
 
/* Check if current file and CDD_Uart.h are the same Software version */
#if ((UART_AR_RELEASE_MAJOR_VERSION_C    != UART_AR_RELEASE_MAJOR_VERSION_H   ) || \
     (UART_AR_RELEASE_MINOR_VERSION_C    != UART_AR_RELEASE_MINOR_VERSION_H   ) || \
     (UART_AR_RELEASE_REVISION_VERSION_C != UART_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart.c and CDD_Uart.h are different"
#endif
 
/* Check if current file and CDD_Drv_Uart.h are the same Vendor Id */
#if (UART_VENDOR_ID_C != UART_DRV_VENDOR_ID_H)
#error "Vendor Id of CDD_Uart.c and CDD_Drv_Uart.h are different"
#endif
 
/* Check if current file and CDD_Drv_Uart.h are the same Software version */
#if ((UART_SW_MAJOR_VERSION_C != UART_DRV_SW_MAJOR_VERSION_H) || \
     (UART_SW_MINOR_VERSION_C != UART_DRV_SW_MINOR_VERSION_H) || \
     (UART_SW_PATCH_VERSION_C != UART_DRV_SW_PATCH_VERSION_H))
#error "Software Version Numbers of CDD_Uart.c and CDD_Drv_Uart.h are different"
#endif
 
/* Check if current file and CDD_Uart_Drv.h are the same Software version */
#if ((UART_AR_RELEASE_MAJOR_VERSION_C    != UART_DRV_AR_RELEASE_MAJOR_VERSION_H   ) || \
     (UART_AR_RELEASE_MINOR_VERSION_C    != UART_DRV_AR_RELEASE_MINOR_VERSION_H   ) || \
     (UART_AR_RELEASE_REVISION_VERSION_C != UART_DRV_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart.c and CDD_Uart_Drv.h are different"
#endif
 
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
/* Check if current file and Det.h are the same Software version */
#if ((UART_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION_H))
#error "Software Version Numbers of CDD_Uart.c and Det.h are different"
#endif
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
#if (STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS)
/* Check if current file and Dem.h are the same Software version */
#if ((UART_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION_H))
#error "Software Version Numbers of CDD_Uart.c and Dem.h are different"
#endif
#endif /* STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS */
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
 
/** @} end of group Private_MacroDefinition */
 
/** @defgroup Private_TypeDefinition
 *  @{
 */
 
/** @} end of group Private_TypeDefinition */
 
/** @defgroup Global_VariableDefinition
 *  @{
 */
 
/** @} end of group Global_VariableDefinition */
 
/** @defgroup Private_VariableDefinition
 *  @{
 */
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
#define UART_START_SEC_VAR_INIT_8
#include "Uart_MemMap.h"
/**
 * @brief  Variable to store UART driver state.
 */
static VAR(Uart_DriverStateType, UART_VAR_INIT) Uart_l_DriverState_en = UART_UNINIT;
#define UART_STOP_SEC_VAR_INIT_8
#include "Uart_MemMap.h"
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
#if ((UART_ENABLE_DEV_ERROR_DETECT == STD_ON) || (UART_DEINIT_API == STD_ON) || (UART_GET_BAUDRATE_API == STD_ON))
#define UART_START_SEC_VAR_CLEARED_PTR
#include "Uart_MemMap.h"
/**
 * @brief Local variable used for storing the UART driver configuration data.
 */
static P2CONST(Uart_ConfigType, UART_VAR_CLEAR, UART_APPL_CONST) Uart_l_Config_ptr;
#define UART_STOP_SEC_VAR_CLEARED_PTR
#include "Uart_MemMap.h"
#endif /* ((UART_ENABLE_DEV_ERROR_DETECT == STD_ON) || (UART_DEINIT_API == STD_ON) || (UART_GET_BAUDRATE_API == STD_ON)) */
/** @} end of group Private_VariableDefinition */
 
/** @defgroup Private_FunctionDeclaration
 *  @{
 */
#define UART_START_SEC_CODE_SLOW
#include "Uart_MemMap.h"
static FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_StartSyncTransmitData(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                                      P2CONST(Uart_SyncSendType, AUTOMATIC, UART_APPL_DATA) p_SyncSendInfo_ptr,
                                                                      VAR(uint32, AUTOMATIC) p_Timeout_u32);
 
static FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_StartAsyncTransmitData(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                                        VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                                        P2CONST(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr);
 
static FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_StartSyncReceiveData(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                                      VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                                      P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr,
                                                                      VAR(uint32, AUTOMATIC) p_Timeout_u32);
 
static FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_StartAsyncReceiveData(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                                      VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                                      P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr);
/** @} end of group Private_FunctionDeclaration */
 
/** @defgroup Private_FunctionDefinition
 *  @{
 */
/**
 * @brief This function performs a synchronous transmission of data on the specified UART channel.
 *        It checks the status of the UART channel and initiates the transmission if the channel is not busy.
 *        If the transmission times out, it reports an error using the Dem module (if enabled).
 *
 * @param[in] p_Channel_u8: Numeric identifier of the UART channel.
 * @param[in] p_SyncSendInfo_ptr: Pointer to the structure contains information used for synchronous transmit data.
 * @param[in] p_Timeout_u32: Timeout value in milliseconds for the synchronous transmission.
 *
 * @return    Std_ReturnType
 *            E_OK: The data was transmitted successfully without any errors or timeouts.
 *            E_NOT_OK: An error occurred during the transmission (e.g., timeout or busy channel).
 *
 * @Design  SDD_UART_017, SDD_UART_052, SDD_UART_053, SDD_UART_055.
 */
static FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_StartSyncTransmitData(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                                      P2CONST(Uart_SyncSendType, AUTOMATIC, UART_APPL_DATA) p_SyncSendInfo_ptr,
                                                                      VAR(uint32, AUTOMATIC) p_Timeout_u32) {
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
  /* This variable stored status of the specified channel. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
 
  /* Init return value. */
  f_RetVal_u8 = E_NOT_OK;
  /* Get status of the transmitter. */
  f_ChStatus_en = Uart_DrvGetStatus(p_Channel_u8, NULL_PTR, UART_SEND);
 
  if (UART_CH_BUSY == f_ChStatus_en) {
#if (UART_ENABLE_DEV_ERROR_DETECT == STD_ON)
    /* Reporting a development error with the error ID is UART_E_CHANNEL_BUSY can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCSEND_ID, UART_E_CHANNEL_BUSY);
#endif  /* (UART_ENABLE_DEV_ERROR_DETECT == STD_ON) */
 
  } else {
    /* Call f_ChStatus_en API to start the UART transmission */
    f_ChStatus_en = Uart_DrvSyncSend(p_Channel_u8, p_SyncSendInfo_ptr, p_Timeout_u32);
 
    /* Check if the UART status times out */
    if (UART_CH_TIMEOUT == f_ChStatus_en) {
#if ((UART_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) && (STD_ON == UART_ENABLE_TIMEOUT_DETECT))
      /* Reporting a production error to DEM with the error ID is UART_E_TIMEOUT. */
      (void)Dem_SetEventStatus(UART_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
#endif  /* ((UART_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) && (STD_ON == UART_ENABLE_TIMEOUT_DETECT)) */
 
    } else {
      /* Set return value to E_OK. */
      f_RetVal_u8 = E_OK;
    }
 
  }
  return f_RetVal_u8;
}
 
/**
 * @brief     This function starts an asynchronous transmit data operation on the specified UART channel.
 *
 * @param[in] p_Channel_u8: Numeric identifier of the Uart channel.
 * @param[in] p_BufferSize_u32: Size of data is sent in bytes.
 * @param[in] p_DataBuffer_ptr: Pointer to data is sent.
 *
 * @return    Std_ReturnType.
 *            E_OK: the asynchronous transmit data operation has been accepted
 *            E_NOT_OK: the asynchronous transmit data operation has not been accepted
 *
 * @Design  SDD_UART_018, SDD_UART_052, SDD_UART_053, SDD_UART_055.
 */
static FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_StartAsyncTransmitData(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                                        VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                                        P2CONST(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr) {
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
  /* This variable stored status of the specified channel. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
 
  /* Init return value. */
  f_RetVal_u8 = E_NOT_OK;
  /* Get status of the transmitter. */
  f_ChStatus_en = Uart_DrvGetStatus(p_Channel_u8, NULL_PTR, UART_SEND);
  /* Check if UART channel is busy. */
  if (UART_CH_BUSY == f_ChStatus_en) {
 
#if (UART_ENABLE_DEV_ERROR_DETECT == STD_ON)
    /* Reporting a development error with the error ID is UART_E_CHANNEL_BUSY can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCSEND_ID, UART_E_CHANNEL_BUSY);
#endif  /* (UART_ENABLE_DEV_ERROR_DETECT == STD_ON) */
 
  } else {
    /* Call Uart_DrvAsyncSend() to Send. */
    f_ChStatus_en = Uart_DrvAsyncSend(p_Channel_u8, p_BufferSize_u32, p_DataBuffer_ptr);
 
    /* Check the UART return status */
    if (UART_CH_COMPLETE == f_ChStatus_en) {
      /* Set return value to E_OK. */
      f_RetVal_u8 = E_OK;
    } else {
      /* Do nothing*/
    }
 
  }
  return f_RetVal_u8;
}
 
/**
 * @brief This function performs a synchronous receive operation on the specified UART channel.
 *        It checks the status of the UART channel and initiates the receive if the channel is not busy.
 *        If the receive times out, it reports an error using the Dem module (if enabled).
 *
 * @param[in] p_Channel_u8: Numeric identifier of the UART channel.
 * @param[in] p_BufferSize_u32: Size of the data buffer to receive data into, in bytes.
 * @param[out] p_DataBuffer_ptr: Pointer to the buffer where received data will be stored.
 * @param[in] p_Timeout_u32: value in milliseconds for the synchronous receive operation.
 *
 * @return    Std_ReturnType
 *            E_OK: The data was received successfully without any errors or timeouts.
 *            E_NOT_OK: An error occurred during the receive (e.g., timeout or busy channel).
 *
 * @Design  SDD_UART_019, SDD_UART_052, SDD_UART_053, SDD_UART_056.
 */
static FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_StartSyncReceiveData(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                                      VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                                      P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr,
                                                                      VAR(uint32, AUTOMATIC) p_Timeout_u32) {
    /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
  /* This variable stored status of the specified channel. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
 
  /* Init return value. */
  f_RetVal_u8 = E_NOT_OK;
  /* Get status of the receiver. */
  f_ChStatus_en = Uart_DrvGetStatus(p_Channel_u8, NULL_PTR, UART_RECEIVE);
  /* Check if UART is busy. */
  if (UART_CH_BUSY == f_ChStatus_en) {
 
#if (UART_ENABLE_DEV_ERROR_DETECT == STD_ON)
    /* Reporting a development error with the error ID is UART_E_CHANNEL_BUSY can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCRECEIVE_ID, UART_E_CHANNEL_BUSY);
#endif  /* (UART_ENABLE_DEV_ERROR_DETECT == STD_ON) */
 
  } else {
    /* Call Uart_DrvSyncReceive to Receive data. */
    f_ChStatus_en = Uart_DrvSyncReceive(p_Channel_u8, p_BufferSize_u32, p_DataBuffer_ptr, p_Timeout_u32);
 
    if (UART_CH_TIMEOUT == f_ChStatus_en) {
#if ((UART_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) && (STD_ON == UART_ENABLE_TIMEOUT_DETECT))
      /* Reporting a production error to DEM with the error ID is UART_E_TIMEOUT. */
      (void)Dem_SetEventStatus(UART_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
#endif  /* ((UART_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) && (STD_ON == UART_ENABLE_TIMEOUT_DETECT)) */
    } else {
      /* Set return value to E_OK. */
      f_RetVal_u8 = E_OK;
    }
 
  }
 
  return f_RetVal_u8;
}
 
/**
 * @brief     This function starts an asynchronous receive data operation on the specified UART channel.
 *
 * @param[in] p_Channel_u8: Numeric identifier of the Uart channel.
 * @param[in] p_BufferSize_u32: Size of data to be received in bytes.
 * @param[out] p_DataBuffer_ptr: Pointer to the buffer where received data will be stored.
 *
 * @return  Std_ReturnType.
 *          E_OK: the asynchronous receive data operation has been accepted
 *          E_NOT_OK: the asynchronous receive data operation has not been accepted
 *
 * @Design  SDD_UART_020, SDD_UART_052, SDD_UART_053, SDD_UART_056.
 */
static FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_StartAsyncReceiveData(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                                                      VAR(uint32, AUTOMATIC) p_BufferSize_u32,
                                                                      P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr) {
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
  /* This variable stored status of the specified channel. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
 
  /* Init return value. */
  f_RetVal_u8 = E_NOT_OK;
  /* Get status of receiver. */
  f_ChStatus_en = Uart_DrvGetStatus(p_Channel_u8, NULL_PTR, UART_RECEIVE);
  /* Check if UART channel is busy. */
  if (UART_CH_BUSY == f_ChStatus_en) {
#if (UART_ENABLE_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCRECEIVE_ID, UART_E_CHANNEL_BUSY);
#endif  /* (UART_ENABLE_DEV_ERROR_DETECT == STD_ON) */
 
  } else {
    /* Call Uart_DrvAsyncReceive API to Receive. */
    f_ChStatus_en = Uart_DrvAsyncReceive(p_Channel_u8, p_BufferSize_u32, p_DataBuffer_ptr);
 
    /* Check the UART channel return status */
    if (UART_CH_COMPLETE == f_ChStatus_en) {
      /* Set return value to E_OK */
      f_RetVal_u8 = E_OK;
    } else {
      /* Do nothing*/
    }
 
  }
  return f_RetVal_u8;
}
/** @} end of group Private_FunctionDefinition */
 
/** @defgroup Public_FunctionDefinition
 *  @{
 */
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
FUNC(void, UART_CODE_SLOW) Uart_Init(P2CONST(Uart_ConfigType, AUTOMATIC, UART_APPL_DATA) Config) {
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Return value */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
 
  /* Check if the Uart driver has already been initialized. */
  if (UART_UNINIT != Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_ALREADY_INITIALIZED can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_INIT_ID, UART_E_ALREADY_INITIALIZED);
 
  } else {
#if (STD_ON == UART_PRECOMPILE_SUPPORT)
    if (NULL_PTR == Config) {
#else
    if (NULL_PTR != Config) {
#endif /* STD_ON == UART_PRECOMPILE_SUPPORT */
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
#if ((UART_ENABLE_DEV_ERROR_DETECT == STD_ON) || (UART_DEINIT_API == STD_ON) || (UART_GET_BAUDRATE_API == STD_ON))
#if (STD_ON == UART_PRECOMPILE_SUPPORT)
      Uart_l_Config_ptr = &Uart_PreCompileConfig_st;
      /* Fix warning. */
      (void)Config;
#else
      Uart_l_Config_ptr = Config;
#endif /* STD_ON == UART_PRECOMPILE_SUPPORT */
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
      /* Initialize the Uart controllers. */
      f_RetVal_u8 = Uart_DrvInit(Uart_l_Config_ptr);
 
      if (E_OK == f_RetVal_u8) {
        /* Set the UART driver state to UART_INITIALIZED. */
        Uart_l_DriverState_en = UART_INITIALIZED;
      } else {
        /* Do nothing */
      }
#else
      (void)Uart_DrvInit(Uart_l_Config_ptr);
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
#elif ((UART_ENABLE_DEV_ERROR_DETECT == STD_OFF) || (UART_DEINIT_API == STD_OFF) || (UART_GET_BAUDRATE_API == STD_OFF))
#if (STD_ON == UART_PRECOMPILE_SUPPORT)
      (void)Uart_DrvInit(&Uart_PreCompileConfig_st);
#else
      (void)Uart_DrvInit(Config);
#endif /* STD_ON == UART_PRECOMPILE_SUPPORT */
#else
  /* Do nothing. */
#endif
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
    } else {
      /* Reporting a development error with the error ID is UART_E_INIT_FAILED can safely ignore the return value. */
      (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_INIT_ID, UART_E_INIT_FAILED);
    }
  }
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
}
 
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
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_DeInit(void) {
  /* Temp variable to loop through uart configuration sets. */
  VAR(uint8, AUTOMATIC) f_Index_u8;
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
  /* UART sending channel status */
  VAR(Uart_StatusType, AUTOMATIC) f_SendStatus_en;
  /* UART Receiving channel status */
  VAR(Uart_StatusType, AUTOMATIC) f_ReceiveStatus_en;
  /* UART all channels status */
  VAR(boolean, AUTOMATIC) f_AllChannelsIdle_bool;
 
  /* Init return value*/
  f_RetVal_u8 = E_NOT_OK;
#if (UART_ENABLE_DEV_ERROR_DETECT == STD_ON)
  if (UART_UNINIT != Uart_l_DriverState_en) {
#endif  /* (UART_ENABLE_DEV_ERROR_DETECT == STD_ON) */
 
    for (f_Index_u8 = UART_U8_DAT_0; f_Index_u8 < UART_CH_MAX_CONFIG; f_Index_u8++) {
      /* Gets the status of the UART driver for a specific channel and sending direction. */
      f_SendStatus_en = Uart_DrvGetStatus(f_Index_u8, NULL_PTR, UART_SEND);
      /* Gets the status of the UART driver for a specific channel and receiving direction. */
      f_ReceiveStatus_en = Uart_DrvGetStatus(f_Index_u8, NULL_PTR, UART_RECEIVE);
 
      /* Checks if the UART channel is busy. */
      if ((UART_CH_BUSY == f_SendStatus_en) || (UART_CH_BUSY == f_ReceiveStatus_en)) {
        f_AllChannelsIdle_bool = UART_FALSE;
        break;
      } else {
        /* Set f_AllChannelsIdle_bool is TRUE */
        f_AllChannelsIdle_bool = UART_TRUE;
      }
 
    }
 
    /* Checks if all UART channels are idle. */
    if (UART_TRUE == f_AllChannelsIdle_bool) {
 
      for (f_Index_u8 = UART_U8_DAT_0; f_Index_u8 < UART_CH_MAX_CONFIG; f_Index_u8++) {
        /* Call Uart_DrvDeInit to deinit all Uart channel. */
        Uart_DrvDeInit(f_Index_u8);
      }
 
      /* Clear stored pointer to NULL_PTR. */
        Uart_l_Config_ptr = NULL_PTR;
        /* Set return value of function to E_OK. */
        f_RetVal_u8 = E_OK;
#if (UART_ENABLE_DEV_ERROR_DETECT == STD_ON)
        /* Change status of driver to uninit. */
        Uart_l_DriverState_en = UART_UNINIT;
#endif /* (UART_ENABLE_DEV_ERROR_DETECT == STD_ON) */
    } else {
      /* Do nothing */
    }
#if (UART_ENABLE_DEV_ERROR_DETECT == STD_ON)
 
  } else {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_DEINIT_ID, UART_E_UNINIT);
  }
#endif  /* (UART_ENABLE_DEV_ERROR_DETECT == STD_ON) */
 
  return f_RetVal_u8;
}
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
 *
 */
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_SyncSend(VAR(uint8, AUTOMATIC) Channel,
                                                  P2CONST(Uart_SyncSendType, AUTOMATIC, UART_APPL_DATA) SyncSendInfoPtr,
                                                  VAR(uint32, AUTOMATIC) Timeout) {
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Init return value. */
  f_RetVal_u8 = E_NOT_OK;
 
  /* Check if Uart driver has been initialized. */
  if (UART_UNINIT == Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value.             */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCSEND_ID, UART_E_UNINIT);
 
  /* Check whether the input parameter Channel is valid or not. */
  } else if (UART_CH_MAX_CONFIG <= Channel) {
    /* Reporting a development error with the error ID is UART_E_INVALID_CHANNEL can safely ignore the return value.    */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCSEND_ID, UART_E_INVALID_CHANNEL);
 
  /* Check whether the input parameter BufferSize is valid or not. */
  } else if ((UART_U32_DAT_0 == SyncSendInfoPtr->TxBufferSize_u32)) {
    /* Reporting a development error with the error ID is UART_E_INVALID_BUFFERSIZE can safely ignore the return value.  */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCSEND_ID, UART_E_INVALID_BUFFERSIZE);
 
  /* Check whether the input parameter TxDataBuffer_ptr different from NULL_PTR. */
  } else if (NULL_PTR == SyncSendInfoPtr->TxDataBuffer_ptr) {
    /* Reporting a development error with the error ID is UART_E_PARAM_POINTER can safely ignore the return value.       */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCSEND_ID, UART_E_PARAM_POINTER);
 
  } else {
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
    /* Call Uart_StartSyncTransmitData API. */
    f_RetVal_u8 = Uart_StartSyncTransmitData(Channel, SyncSendInfoPtr, Timeout);
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  }
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
  return f_RetVal_u8;
}
 
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
                                                    P2CONST(uint8, AUTOMATIC, UART_APPL_DATA) DataBufferPtr) {
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8 = E_NOT_OK;
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Check if UART driver has been initialized. */
  if (UART_UNINIT == Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value.             */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCSEND_ID, UART_E_UNINIT);
 
  /* Check whether the input parameter Channel is valid or not. */
  } else if (UART_CH_MAX_CONFIG <= Channel) {
    /* Reporting a development error with the error ID is UART_E_INVALID_CHANNEL can safely ignore the return value.    */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCSEND_ID, UART_E_INVALID_CHANNEL);
 
  /* Check whether the input parameter BufferSize is valid or not. */
  } else if (UART_U32_DAT_0 == BufferSize) {
    /* Reporting a development error with the error ID is UART_E_INVALID_BUFFERSIZE can safely ignore the return value.  */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCSEND_ID, UART_E_INVALID_BUFFERSIZE);
 
  /* Check whether the input parameter DataBufferPtr different from NULL_PTR. */
  } else if (NULL_PTR == DataBufferPtr) {
    /* Reporting a development error with the error ID is UART_E_PARAM_POINTER can safely ignore the return value.       */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCSEND_ID, UART_E_PARAM_POINTER);
 
  } else {
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
    /* Call Uart_StartAsyncTransmitData API. */
    f_RetVal_u8 = Uart_StartAsyncTransmitData(Channel, BufferSize, DataBufferPtr);
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  }
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
  return f_RetVal_u8;
}
 
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
                                                      VAR(uint32, AUTOMATIC) Timeout) {
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Init return value. */
  f_RetVal_u8 = E_NOT_OK;
 
/* Check if Uart driver has been initialized. */
  if (UART_UNINIT == Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value.             */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCRECEIVE_ID, UART_E_UNINIT);
 
  /* Check whether the input parameter Channel is valid or not. */
  } else if (UART_CH_MAX_CONFIG <= Channel) {
    /* Reporting a development error with the error ID is UART_E_INVALID_CHANNEL can safely ignore the return value.    */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCRECEIVE_ID, UART_E_INVALID_CHANNEL);
 
  /* Check whether the input parameter BufferSize is valid or not. */
  } else if (UART_U32_DAT_0 == BufferSize) {
    /* Reporting a development error with the error ID is UART_E_INVALID_BUFFERSIZE can safely ignore the return value.  */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCRECEIVE_ID, UART_E_INVALID_BUFFERSIZE);
 
  /* Check whether the input parameter DataBufferPtr different from NULL_PTR. */
  } else if (NULL_PTR ==DataBufferPtr) {
    /* Reporting a development error with the error ID is UART_E_PARAM_POINTER can safely ignore the return value.       */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SYNCRECEIVE_ID, UART_E_PARAM_POINTER);
 
  } else {
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
    /* Call Uart_StartSyncReceiveData API. */
    f_RetVal_u8 = Uart_StartSyncReceiveData(Channel, BufferSize, DataBufferPtr, Timeout);
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  }
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
  return f_RetVal_u8;
}
 
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
                                                      P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) DataBufferPtr) {
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8 = E_NOT_OK;
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Check if Uart driver has been initialized. */
  if (UART_UNINIT == Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value.             */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCRECEIVE_ID, UART_E_UNINIT);
 
  /* Check whether the input parameter Channel is valid or not. */
  } else if (UART_CH_MAX_CONFIG <= Channel) {
    /* Reporting a development error with the error ID is UART_E_INVALID_CHANNEL can safely ignore the return value.    */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCRECEIVE_ID, UART_E_INVALID_CHANNEL);
 
  /* Check whether the input parameter BufferSize is valid or not. */
  } else if (UART_U32_DAT_0 == BufferSize) {
    /* Reporting a development error with the error ID is UART_E_INVALID_BUFFERSIZE can safely ignore the return value.  */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCRECEIVE_ID, UART_E_INVALID_BUFFERSIZE);
 
  /* Check whether the input parameter DataBufferPtr different from NULL_PTR. */
  } else if (NULL_PTR == DataBufferPtr) {
    /* Reporting a development error with the error ID is UART_E_PARAM_POINTER can safely ignore the return value.       */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ASYNCRECEIVE_ID, UART_E_PARAM_POINTER);
 
  } else {
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
    /* Call Uart_StartAsyncReceiveData API. */
    f_RetVal_u8 = Uart_StartAsyncReceiveData(Channel, BufferSize, DataBufferPtr);
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  }
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
  return f_RetVal_u8;
}
 
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
FUNC(void, UART_CODE_SLOW) Uart_GetBaudrate(VAR(uint8, AUTOMATIC) Channel, P2VAR(uint32, AUTOMATIC, UART_APPL_DATA) BaudratePtr) {
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Check if Uart driver has been initialized. */
  if (UART_UNINIT == Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value.          */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_GETBAUDRATE_ID, UART_E_UNINIT);
 
  /* Check whether the input parameter Channel is valid or not. */
  } else if (UART_CH_MAX_CONFIG <= Channel) {
    /* Reporting a development error with the error ID is UART_E_INVALID_CHANNEL can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_GETBAUDRATE_ID, UART_E_INVALID_CHANNEL);
 
   /* Check whether the input parameter BaudratePtr is different from NULL_PTR */
  } else if (NULL_PTR == BaudratePtr) {
    /* Reporting a development error with the error ID is UART_E_PARAM_POINTER can safely ignore the return value.   */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_GETBAUDRATE_ID, UART_E_PARAM_POINTER);
 
  } else {
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT*/
 
    /* Call Uart_DrvGetBaudrate API to change baudrate of the Uart channel. */
    Uart_DrvGetBaudrate(Channel, BaudratePtr, Uart_l_Config_ptr->ChannelConfig_ptr[Channel].ClockFrequency_u32);
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  }
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT*/
 
}
#endif  /* (STD_ON == UART_GET_BAUDRATE_API) */
 
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
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_SetBaudrate(VAR(uint8, AUTOMATIC) Channel, VAR(Uart_BaudrateType, AUTOMATIC) Baudrate) {
  /* Return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
  /* Temp variable to store UART receiving status. */
  VAR(Uart_StatusType, AUTOMATIC) f_ReceiveStatus_en;
  /* Temp variable to store UART sending status. */
  VAR(Uart_StatusType, AUTOMATIC) f_SendStatus_en;
 
  /* Init return value. */
  f_RetVal_u8 = E_NOT_OK;
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Check if Uart driver has been initialized. */
  if (UART_UNINIT == Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value.          */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SETBAUDRATE_ID, UART_E_UNINIT);
 
  /* Check whether the input parameter Channel is valid or not. */
  } else if (UART_CH_MAX_CONFIG <= Channel) {
    /* Reporting a development error with the error ID is UART_E_INVALID_CHANNEL can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SETBAUDRATE_ID, UART_E_INVALID_CHANNEL);
 
  /* Check whether the input parameter Baudrate is valid or not. */
  } else if (((uint32)UART_BAUDRATE_1843200 < (uint32)Baudrate) || \
            (UART_U8_DAT_0 == Uart_l_Config_ptr->ChannelConfig_ptr[Channel].HwConfig_ptr->ClockPrescale_ptr[Baudrate].SDRPrescaleVal_u8))  {
    /* Reporting a development error with the error ID is UART_E_INVALID_BAUDRATE can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SETBAUDRATE_ID, UART_E_INVALID_BAUDRATE);
 
  } else {
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
    /* Call Uart_DrvGetStatus API to get UART receiving status. */
    f_ReceiveStatus_en = Uart_DrvGetStatus(Channel, NULL_PTR, UART_RECEIVE);
    /* Call Uart_DrvGetStatus API to get UART sending status. */
    f_SendStatus_en = Uart_DrvGetStatus(Channel, NULL_PTR, UART_SEND);
    /* Check if the status of the channel is valid for changing the baud rate. */
    if ((UART_CH_BUSY == f_ReceiveStatus_en) || (UART_CH_BUSY == f_SendStatus_en)) {
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
      (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_SETBAUDRATE_ID, UART_E_INVALID_STATUS);
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
    } else {
      /* Call Uart_DrvSetBaudrate API to change baudrate of the UART channel. */
      f_RetVal_u8 = Uart_DrvSetBaudrate(Channel, Baudrate);
 
    }
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  }
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
  return f_RetVal_u8;
}
 
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
FUNC(void, UART_CODE_SLOW) Uart_Abort(VAR(uint8, AUTOMATIC) Channel, VAR(Uart_DataDirectionType, AUTOMATIC) Direction) {
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Check if Uart driver has been initialized. */
  if (UART_UNINIT == Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value.             */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ABORT_ID, UART_E_UNINIT);
 
  /* Check if input parameter Channel is valid or not. */
  } else if (UART_CH_MAX_CONFIG <= Channel) {
    /* Reporting a development error with the error ID is UART_E_INVALID_CHANNEL can safely ignore the return value.    */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ABORT_ID, UART_E_INVALID_CHANNEL);
 
  /* Check whether the input parameter Direction is valid or not. */
  } else if ((UART_SEND != Direction) && (UART_RECEIVE != Direction)) {
    /* Reporting a development error with the error ID is UART_E_INVALID_DIRECTION can safely ignore the return value.  */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_ABORT_ID, UART_E_INVALID_DIRECTION);
 
  } else {
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
    /* Call Uart_DrvAbort to abort the ongoing UART transmission or reception operation. */
    Uart_DrvAbort(Channel, Direction);
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  }
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
}
 
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
                                                    VAR(Uart_DataDirectionType, AUTOMATIC) Direction) {
  /* This variable used to store UART channel status. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  /* Init return value. */
  f_ChStatus_en = UART_CH_ERROR;
 
  /* Check if UART driver has been initialized. */
  if (UART_UNINIT == Uart_l_DriverState_en) {
    /* Reporting a development error with the error ID is UART_E_UNINIT can safely ignore the return value.            */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_GETSTATUS_ID, UART_E_UNINIT);
 
  /* Check if input parameter Channel is valid or not. */
  } else if (UART_CH_MAX_CONFIG <= Channel) {
    /* Reporting a development error with the error ID is UART_E_INVALID_CHANNEL can safely ignore the return value.   */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_GETSTATUS_ID, UART_E_INVALID_CHANNEL);
 
  /* Check whether the input parameter BytesTransaction is different from NULL_PTR */
  } else if (NULL_PTR == BytesTransactionPtr) {
    /* Reporting a development error with the error ID is UART_E_PARAM_POINTER can safely ignore the return value.     */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_GETSTATUS_ID, UART_E_PARAM_POINTER);
 
  /* Check if input parameter Direction is valid or not. */
  } else if ((UART_SEND != Direction) && (UART_RECEIVE != Direction)) {
    /* Reporting a development error with the error ID is UART_E_INVALID_DIRECTION can safely ignore the return value. */
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_GETSTATUS_ID, UART_E_INVALID_DIRECTION);
 
  } else {
#endif /*  STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
    /* Call Uart_DrvGetStatus() API to get status. */
    f_ChStatus_en = Uart_DrvGetStatus(Channel, BytesTransactionPtr, Direction);
 
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
  }
#endif
 
  return f_ChStatus_en;
}
 
#endif /* (STD_ON == UART_GET_STATUS_API) */
 
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
#if (STD_ON == UART_VERSION_INFO_API)
FUNC(void, UART_CODE_SLOW) Uart_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, UART_APPL_DATA) versioninfo) {
  /* Check if input pointer versioninfo is NULL_PTR. */
  if (NULL_PTR == versioninfo) {
#if (STD_ON == UART_ENABLE_DEV_ERROR_DETECT)
    (void)Det_ReportError(UART_MODULE_ID_H, UART_MODULE_INSTANCE, UART_VERSIONINFO_ID, UART_E_PARAM_POINTER);
#endif /* STD_ON == UART_ENABLE_DEV_ERROR_DETECT */
 
  } else {
    (versioninfo)->vendorID         = (uint16)UART_CFG_VENDOR_ID_H;
    (versioninfo)->moduleID         = (uint16)UART_CFG_MODULE_ID_H;
    (versioninfo)->sw_major_version = (uint8)UART_CFG_SW_MAJOR_VERSION_H;
    (versioninfo)->sw_minor_version = (uint8)UART_CFG_SW_MINOR_VERSION_H;
    (versioninfo)->sw_patch_version = (uint8)UART_CFG_SW_PATCH_VERSION_H;
  }
}
#endif /* (STD_ON == UART_VERSION_INFO_API) */
/** @} end of group Public_FunctionDefinition */
#define UART_STOP_SEC_CODE_SLOW
#include "Uart_MemMap.h"
#ifdef __cplusplus
}
#endif
 
/** @} end of group Uart */
 
 