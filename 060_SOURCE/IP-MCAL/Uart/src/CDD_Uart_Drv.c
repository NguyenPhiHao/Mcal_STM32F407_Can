/**************************************************************************************************************************************************************/
/**
 * @file      : CDD_Uart_Drv.c
 * @brief     : CDD_Uart_Drv source file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
/** @addtogroup Uart
 *  @brief Autosar R23-11 CDD_Uart_Drv source code
 *  @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "CDD_Uart_Drv.h"
#include "BAT32A259.h"
#if (STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS)
  #include "Dem.h"
#endif
#include "Os.h"
#include "SchM_Uart.h"
#include "Div_Drv.h"
 
/** @defgroup Private_MacroDefinition
 *  @{
 */
#define UART_DRV_VENDOR_ID_C                      0x0000U
#define UART_DRV_SW_MAJOR_VERSION_C               0x01U
#define UART_DRV_SW_MINOR_VERSION_C               0x00U
#define UART_DRV_SW_PATCH_VERSION_C               0x00U
#define UART_DRV_AR_RELEASE_MAJOR_VERSION_C       0x04U
#define UART_DRV_AR_RELEASE_MINOR_VERSION_C       0x09U
#define UART_DRV_AR_RELEASE_REVISION_VERSION_C    0x00U
 
/* Check if current file and CDD_Uart_Drv.h are the same Vendor Id */
#if (UART_DRV_VENDOR_ID_C != UART_DRV_VENDOR_ID_H)
#error "Vendor Id of CDD_Uart_Drv.c and CDD_Uart_Drv.h are different"
#endif
 
/* Check if current file and CDD_Uart_Drv.h are the same Software version. */
#if ((UART_DRV_SW_MAJOR_VERSION_C != UART_DRV_SW_MAJOR_VERSION_H) || \
     (UART_DRV_SW_MINOR_VERSION_C != UART_DRV_SW_MINOR_VERSION_H) || \
     (UART_DRV_SW_PATCH_VERSION_C != UART_DRV_SW_PATCH_VERSION_H))
#error "Software Version Numbers of CDD_Uart_Drv.c and CDD_Uart_Drv.h are different."
#endif
 
/* Check if current file and CDD_Uart_Drv.h are the same AUTOSAR version. */
#if ((UART_DRV_AR_RELEASE_MAJOR_VERSION_C    != UART_DRV_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_DRV_AR_RELEASE_MINOR_VERSION_C    != UART_DRV_AR_RELEASE_MINOR_VERSION_H) || \
     (UART_DRV_AR_RELEASE_REVISION_VERSION_C != UART_DRV_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart_Drv.c and CDD_Uart_Drv.h are different."
#endif
 
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS)
/* Check if current file and Dem.h are the same AUTOSAR version. */
#if ((UART_DRV_AR_RELEASE_MAJOR_VERSION_C    != DEM_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_DRV_AR_RELEASE_MINOR_VERSION_C    != DEM_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart_Drv.c and Dem.h are different."
#endif
#endif /* STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS */
 
/* Check if current file and SchM_Uart.h are the same Software version */
#if ((UART_DRV_AR_RELEASE_MAJOR_VERSION_C != SCHM_UART_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_DRV_AR_RELEASE_MINOR_VERSION_C != SCHM_UART_AR_RELEASE_MINOR_VERSION_H))
#error "Software Version Numbers of CDD_Uart_Drv.c and SchM_Uart.h are different"
#endif
 
/* Check if current file and Os.h are the same AUTOSAR version. */
#if ((UART_DRV_AR_RELEASE_MAJOR_VERSION_C    != OS_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_DRV_AR_RELEASE_MINOR_VERSION_C    != OS_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart_Drv.c and Os.h are different."
#endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
 
/**
 * @brief Typedef Uart_DrvRegType as SCI_Type to support specific UART feature.
 */
typedef SCI_Type      Uart_DrvRegType;
#define UART0_BASE                               SCI0_BASE
#define UART1_BASE                               SCI1_BASE
#define UART2_BASE                               SCI2_BASE
#define UART3_BASE                               SCI3_BASE
#define UART_MAX_CH                              (4U)
 
/**
 * @brief This macro used to convert micro seconds into tick duration.
 */
#define UART_DRV_TIMEOUT_DURATION_TICK(Val)      (uint32)(Val * (Div_DrvGetQuotient(UART_OS_TICK_PER_SECONDS, 1000000)))
 
/**
 * @brief This macro used to configuration parity of the UART channel.
 */
#define UART_PARITY_CONFIG(ParityType) \
      (((ParityType) == UART_PARITY_DISABLED) ? (UART_SCRMN_PTC_DISABLED) \
       : ((ParityType) == UART_PARITY_ZERO ? UART_SCRMN_PTC_ZERO \
       : (((ParityType) == UART_PARITY_EVEN) ? UART_SCRMN_PTC_EVEN : UART_SCRMN_PTC_ODD)))
/**
 * @brief This macro used to configuration stop bit length of the UART channel.
 */
#define UART_STOPBIT_CONFIG(StopbitType) (((StopbitType) == UART_ONE_STOP_BIT) ? UART_SCRMN_SLC_ONE_BIT : UART_SCRMN_SLC_TWO_BIT)
 
/**
 * @brief This macro used to configuration data length of the UART channel.
 */
#define UART_DATALENGTH_CONFIG(DataLengthType) \
      ((DataLengthType) == UART_7_BITS_DATA_LENGTH ? UART_SCRMN_DLS_7_BIT \
       : (((DataLengthType) == UART_8_BITS_DATA_LENGTH) ? UART_SCRMN_DLS_8_BIT \
       : (((DataLengthType) == UART_9_BITS_DATA_LENGTH) ? UART_SCRMN_DLS_9_BIT : UART_SCRMN_DLS_16_BIT)))
 
/**
 * @brief This macro used to modify data for transmit.
 */
#define UART_DATALENGTH_MASK(DataLengthType) \
      ((DataLengthType) == UART_7_BITS_DATA_LENGTH ? UART_7_BIT_DATA_MSK \
       : ((DataLengthType) == UART_8_BITS_DATA_LENGTH ? UART_8_BIT_DATA_MSK \
       : (((DataLengthType) == UART_9_BITS_DATA_LENGTH) ? UART_9_BIT_DATA_MSK : UART_16_BIT_DATA_MSK)))
 
#if (STD_ON == UART_GET_BAUDRATE_API)
/**
 * @brief This macro is used to calculate powers of 2.
 */
#define UART_POW_2(n)                        ((uint32)1U << (uint32)(n))
 
/**
 * @brief Macro used to read SPSm register.
 */
#define UART_SPS_CKM0_MSK                    ((uint16)0x000FU)
#endif
 
/**
 * @brief Macro used to get/put data to SDR register.
 */
#define UART_7_BIT_DATA_MSK                  ((uint16)0x007FU)
#define UART_8_BIT_DATA_MSK                  ((uint16)0x00FFU)
#define UART_9_BIT_DATA_MSK                  ((uint16)0x01FFU)
#define UART_16_BIT_DATA_MSK                 ((uint16)0xFFFFU)
 
/**
 * @brief Macro used to check the UART channel is on run/stop state.
 */
#define UART_SE_TRANSMIT_CHANNEL_MSK         ((uint16)0x0001U)
#define UART_SE_RECEIVE_CHANNEL_MSK          ((uint16)0x0002U)
 
#define UART_MOD_SPS_REG_MSK                 ((uint16)0xFFFFU)
#define UART_MOD_SDR_CLOCK_PRESCALE_MSK      ((uint16)0xFE00U)
#define UART_SDR_CLOCK_PRESCALE_POS          ((uint16)0x09U)
 
#if (STD_ON == UART_DEINIT_API)
/**
 * @brief Macro used to clear SDR register.
 */
#define UART_CLEAR_SDR_REG                   ((uint16)0x0000U)
 
/**
 * @brief Macro used to clear SPS register.
 */
#define UART_CLEAR_SPS_REG                   ((uint16)0x0000U)
 
/**
 * @brief Macro used to clear SMR register.
 */
#define UART_CLEAR_SMR_REG                   ((uint16)0x0020U)
 
/**
 * @brief Macro used to clear SCR register.
 */
#define UART_CLEAR_SCR_REG                   ((uint16)0x0087U)
 
/**
 * @brief Macro used to clear SIR register.
 */
#define UART_CLEAR_SIR_REG                   ((uint16)0x0000U)
 
/**
 * @brief Macro used to clear SOE register.
 */
#define UART_CLEAR_SOE_REG                   ((uint16)0x0000U)
 
/**
 * @brief Macro used to clear SO register.
 */
#define UART_CLEAR_SO_REG                    ((uint16)0x0F0FU)
 
/**
 * @brief Macro used to clear SOL register.
 */
#define UART_CLEAR_SOL_REG                   ((uint16)0x0000U)
#endif /* (STD_ON == UART_DEINIT_API) */
 
/**
 * @brief Macros for manipulating 16-bit UART registers
 */
#define UART_RD_REG_U16(Reg)                 (Reg)
#define UART_WR_REG_U16(Reg, Val)            ((Reg) = ((uint16)(Val)))
#define UART_MOD_REG_U16(Reg, Mask, Val)     ((Reg) = ((Reg) & ~((uint16)(Mask))) | (((uint16)(Val)) & ((uint16)(Mask))))
#define UART_SET_BIT_U16(Reg, Bit)           ((Reg) |= ((uint16)1U << ((uint16)(Bit))))
#define UART_CLR_BIT_U16(Reg, Bit)           ((Reg) &= ~((uint16)1U << ((uint16)(Bit))))
 
/**
 * @brief Macro used to start/stop corresponding UART channel.
 */
#define UART_TRANSMIT_CHANNEL_ST_SS_POS      ((uint16)0x0000U)
#define UART_RECEIVE_CHANNEL_ST_SS_POS       ((uint16)0x0001U)
#define UART_SOE_ENABLE_TRANSMIT_CHANNEL_POS ((uint16)0x0000U)
 
/**
 * @brief Macro used to clear flag of the SSRm register.
 */
#define UART_FLAG_BFF                        ((uint16)0x0020U)
#define UART_FLAG_FEF                        ((uint16)0x0004U)
#define UART_FLAG_PEF                        ((uint16)0x0002U)
#define UART_FLAG_OVF                        ((uint16)0x0001U)
#define UART_ERROR_FLAG                      (UART_FLAG_FEF | UART_FLAG_PEF | UART_FLAG_OVF)
 
#if (STD_ON == UART_DEINIT_API)
/**
 * @brief Macro used to clear busy flag of the SSRm register.
 */
#define UART_FLAG_TSF                        ((uint16)0x0040U)
#define UART_FLAG_BUSY                       (UART_FLAG_TSF | UART_FLAG_BFF)
#endif
/**
 * @brief Macro used to select clock of the UART channel.
 */
#define UART_SMRMN_CKS_POS                   ((uint16)15U)
 
/**
 * @brief Macro used to select transmission clock.
 */
#define UART_SMRMN_CCS_POS                   ((uint16)14U)
 
/**
 * @brief Macro used to select trigger source of UART channel.
 */
#define UART_SMRMN_STS_POS                   ((uint16)8U)
 
/**
 * @brief Macro used to configure the level inversion control for UART reception.
 */
#define UART_SMRMN_SIS_POS                   ((uint16)6U)
 
/**
 * @brief Macro for default value of SMRmn register.
 */
#define UART_SMRMN_DEFAULT_POS               ((uint16)5U)
 
/**
 * @brief Macro used to select interrupt type of UART channel.
 */
#define UART_SMRMN_MD0_POS                   ((uint16)0U)
 
/**
 * @brief Macro used to select mode of SCI module.
 */
#define UART_SMRMN_MD_MSK                    ((uint16)0x0006U)
#define UART_SMRMN_MD_UART                   ((uint16)0x0002U)
 
/**
 * @brief Macro used to configure transfer mode of the UART channel.
 */
#define UART_SCRMN_MODE_MSK                  ((uint16)0xC000)
#define UART_SCRMN_MODE_TX                   ((uint16)0x8000)
#define UART_SCRMN_MODE_RX                   ((uint16)0x4000)
 
/**
 * @brief Macro used to configure data and clock phase of SCI module.
 */
#define UART_SCRMN_TIMING_MSK                ((uint16)0x3000)
#define UART_SCRMN_TIMING_DISABLE            ((uint16)0x0000)
 
/**
 * @brief Macro used to configure mask control of error interrupt signals.
 */
#define UART_SCRMN_EOC_POS                   ((uint16)10U)
 
/**
 * @brief Macro used to configure parity bit.
 */
#define UART_SCRMN_PTC_MSK                   ((uint16)0x0300)
#define UART_SCRMN_PTC_DISABLED              ((uint16)0x0000)
#define UART_SCRMN_PTC_ZERO                  ((uint16)0x0100)
#define UART_SCRMN_PTC_EVEN                  ((uint16)0x0200)
#define UART_SCRMN_PTC_ODD                   ((uint16)0x0300)
 
/**
 * @brief Macro used to configure for the bit order (LSB or MSB) that will be transfer first in the UART frame.
 */
#define UART_SCRMN_DIR_POS                   ((uint16)7U)
/**
 * @brief Macro used to configure stop bit length for UART channel.
 */
#define UART_SCRMN_SLC_MSK                   ((uint16)0x0030)
#define UART_SCRMN_SLC_ONE_BIT               ((uint16)0x0010)
#define UART_SCRMN_SLC_TWO_BIT               ((uint16)0x0020)
 
/**
 * @brief Macro used to configure data length for UART channel.
 */
#define UART_SCRMN_DLS_MSK                   ((uint16)0x000F)
#define UART_SCRMN_DLS_7_BIT                 ((uint16)0x0006)
#define UART_SCRMN_DLS_8_BIT                 ((uint16)0x0007)
#define UART_SCRMN_DLS_9_BIT                 ((uint16)0x0008)
#define UART_SCRMN_DLS_16_BIT                ((uint16)0x000F)
 
/**
 * @brief Macro used to enable or disable inversion of the transmit UART channel.
 */
#define UART_SOL_SOL_POS                     ((uint16)0x0000U)
 
/**
 * @brief Macro to extract the high 8 bits from a 16-bit value.
 */
#define UART_U16_HIGH_MSK                    ((uint16)0xFF00U)
#define UART_U16_HIGH_POS                    ((uint16)0x0008U)
 
/**
 * @brief Macro to extract the low 8 bits from a 16-bit value.
 */
#define UART_U16_LOW_MSK                     ((uint16)0x00FFU)
#define UART_U16_LOW_POS                     ((uint16)0x0000U)
 
/** @} end of group Private_MacroDefinition */
 
/** @defgroup Private_TypeDefinition
*  @{
*/
 
 
/* @} end of group Private_TypeDefinition */
 
/** @defgroup Global_VariableDefinition
 *  @{
 */
 
/** @} end of group Global_VariableDefinition */
 
/** @defgroup Private_VariableDefinition
 *  @{
 */
#define UART_START_SEC_CONST_PTR
#include "Uart_MemMap.h"
/**
 * @brief   Local pointer to store register base address of the UART module.
 */
static CONSTP2VAR(Uart_DrvRegType, UART_VAR_INIT, UART_REGSPACE) Uart_l_DrvBaseAddr_aa[UART_MAX_CH] = {(Uart_DrvRegType *)UART0_BASE,
                                                                                                      (Uart_DrvRegType *)UART1_BASE,
                                                                                                      (Uart_DrvRegType *)UART2_BASE,
                                                                                                      (Uart_DrvRegType *)UART3_BASE};
#define UART_STOP_SEC_CONST_PTR
#include "Uart_MemMap.h"
 
#define UART_START_SEC_VAR_CLEARED_PTR
#include "Uart_MemMap.h"
/**
 * @brief   Local pointer to store channel configuration structure.
 */
static P2CONST(Uart_ChannelConfigType, UART_VAR_CLEAR, UART_APPL_CONST) Uart_l_ChCfg_aa[UART_CH_MAX_CONFIG];
#define UART_STOP_SEC_VAR_CLEARED_PTR
#include "Uart_MemMap.h"
 
#define UART_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Uart_MemMap.h"
/**
 * @brief   Store runtime status of the UART driver.
 */
static VAR(Uart_DrvHwStateType, UART_VAR_CLEAR) Uart_l_StateStructure_aa[UART_CH_MAX_CONFIG];
#define UART_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Uart_MemMap.h"
 
/** @} end of group Private_VariableDefinition */
 
/** @defgroup Private_FunctionDeclaration
 *  @{
 */
#define UART_START_SEC_CODE_SLOW
#include "Uart_MemMap.h"
 
static FUNC(Uart_DrvStatusType, UART_CODE_SLOW) Uart_HwInit(P2CONST(Uart_ChannelConfigType, AUTOMATIC, UART_APPL_DATA) p_ChannelConfig_ptr);
 
static FUNC(void, UART_CODE_SLOW) Uart_HwTransmitterInit(P2CONST(Uart_ChannelConfigType, AUTOMATIC, UART_APPL_DATA) p_ChannelConfig_ptr,
                                                        P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) p_BaseAddress_ptr);
 
static FUNC(void, UART_CODE_SLOW) Uart_HwReceiverInit(P2CONST(Uart_ChannelConfigType, AUTOMATIC, UART_APPL_DATA) p_ChannelConfig_ptr,
                                                      P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) p_BaseAddress_ptr);
 
#if (STD_ON == UART_DEINIT_API)
static FUNC(void, UART_CODE_SLOW) Uart_HwDeInit(CONST(uint8, AUTOMATIC) p_Channel_u8);
#endif /* (STD_ON == UART_DEINIT_API) */
 
#if (STD_ON == UART_GET_BAUDRATE_API)
static FUNC(void, UART_CODE_SLOW) Uart_HwGetBaudrate(CONST(uint8, AUTOMATIC) p_Channel_u8,
                                                     P2VAR(uint32, AUTOMATIC, UART_APPL_DATA) p_Baudrate_ptr,
                                                     CONST(uint32, AUTOMATIC) p_ClockFrequency_u32);
#endif /* (STD_ON == UART_GET_BAUDRATE_API) */
 
static FUNC(Uart_DrvStatusType, UART_CODE_SLOW) Uart_HwSetBaudrate(CONST(uint8, AUTOMATIC) p_Channel_u8,
                                                                    P2CONST(Uart_ChannelConfigType, AUTOMATIC, UART_APPL_DATA) p_ChannelConfig_ptr,
                                                                    CONST(Uart_BaudrateType, AUTOMATIC) p_Baudrate_en);
 
static FUNC(void, UART_CODE_SLOW) Uart_HwSyncSend(CONST(uint8, AUTOMATIC) p_Channel_u8);
 
static FUNC(void, UART_CODE_SLOW) Uart_HwSyncReceive(CONST(uint8, AUTOMATIC) p_Channel_u8);
 
#if ((UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON))
static FUNC(void, UART_CODE_SLOW) Uart_HwCompleteSendData(CONST(uint8, AUTOMATIC) p_Channel_u8);
#endif /* ((UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON)) */
 
static FUNC(void, UART_CODE_SLOW) Uart_HwCompleteReceiveData(CONST(uint8, AUTOMATIC) p_Channel_u8);
 
#if ((UART_SCI0_ISR_RX_USED == STD_ON) || (UART_SCI1_ISR_RX_USED == STD_ON) || (UART_SCI2_ISR_RX_USED == STD_ON) || (UART_SCI3_ISR_RX_USED == STD_ON) || \
    (UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON))
static FUNC(void, UART_CODE_SLOW) Uart_HwCallNotification(CONST(uint8, AUTOMATIC) p_Channel_u8, CONST(Uart_DataDirectionType, AUTOMATIC) p_Direction_en);
#endif /* ((UART_SCI0_ISR_RX_USED == STD_ON) || (UART_SCI1_ISR_RX_USED == STD_ON) || (UART_SCI2_ISR_RX_USED == STD_ON) || (UART_SCI3_ISR_RX_USED == STD_ON) || \
    (UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON)) */
 
static FUNC(void, UART_CODE_SLOW) Uart_HwWriteData(CONST(uint8, AUTOMATIC) p_Channel_u8);
 
static FUNC(void, UART_CODE_SLOW) Uart_HwReadData(CONST(uint8, AUTOMATIC) p_Channel_u8);
 
static FUNC(void, UART_CODE_SLOW) Uart_HwFuncCmd(CONST(uint8, AUTOMATIC) p_Channel_u8,
                                                CONST(Uart_DataDirectionType, AUTOMATIC) p_Direction_en,
                                                CONST(boolean, AUTOMATIC) p_Enable_bool);
 
static FUNC(void, UART_CODE_SLOW) Uart_HwClearStatus(CONST(uint8, AUTOMATIC) p_Channel_u8, CONST(uint16, AUTOMATIC) p_Flag_u16);
 
static FUNC(Uart_DrvStatusType, UART_CODE_SLOW) Uart_HwWaitStatus(CONST(uint8, AUTOMATIC) p_Channel_u8,
                                                                   CONST(Uart_DataDirectionType, AUTOMATIC) p_Direction_en,
                                                                   VAR(uint16, AUTOMATIC) p_Flag_u16,
                                                                   VAR(boolean, AUTOMATIC) p_ExpectedVal_bool);
 
static FUNC(Uart_StatusType, UART_CODE_SLOW) Uart_DrvConvertStatus(CONST(Uart_DrvStatusType, AUTOMATIC) p_DrvStatus_en);
 
static FUNC(void, UART_CODE_SLOW) Uart_HwErrorHandler(VAR(uint8, AUTOMATIC) p_Channel_u8, VAR(uint16, AUTOMATIC) p_SSRRegVal_u16);
#define UART_STOP_SEC_CODE_SLOW
#include "Uart_MemMap.h"
/** @} end of group Private_FunctionDeclaration */
 
/** @defgroup Private_FunctionDefinition
 *  @{
 */
#define UART_START_SEC_CODE_SLOW
#include "Uart_MemMap.h"
/**
 *
 * @brief       This function accesses the hardware to configure the registers for initializing the UART channel.
 *
 * @param[in]   p_ChannelConfig_ptr: Pointer to channel configuration.
 *
 * @return      Uart_DrvStatusType.
 *              UART_STATUS_SUCCESS: The UART channel was initialized successfully.
 *              UART_STATUS_ERROR: The UART channel was initialized unsuccessfully.
 *
 * @Design      SDD_UART_014, SDD_UART_034.
 */
static FUNC(Uart_DrvStatusType, UART_CODE_SLOW) Uart_HwInit(P2CONST(Uart_ChannelConfigType, AUTOMATIC, UART_APPL_DATA) p_ChannelConfig_ptr) {
  /* Variable to store the return value of the function. */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
  /* Pointer pointing directly to the register uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
 
  /* Init return value. */
  f_DrvStatus_en = UART_STATUS_SUCCESS;
  /* Check if pointer configuration is NULL_PTR. */
  if (NULL_PTR != p_ChannelConfig_ptr) {
    /* Get the pointer to the register uart with the corresponding UART Driver */
    f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[p_ChannelConfig_ptr->HwChannel_en];
 
    /* Configuration for the UART channel used for transmission. */
    if (UART_TRANSMIT_MODE == p_ChannelConfig_ptr->HwConfig_ptr->TransferMode_en) {
      /* Configuration for the UART transmitter. */
      Uart_HwTransmitterInit(p_ChannelConfig_ptr, f_BaseAddress_ptr);
    } else if (UART_RECEIVE_MODE == p_ChannelConfig_ptr->HwConfig_ptr->TransferMode_en) {
      /* Configuration for the UART receiver. */
      Uart_HwReceiverInit(p_ChannelConfig_ptr, f_BaseAddress_ptr);
    } else {
      /* Configuration for the UART transmitter. */
      Uart_HwTransmitterInit(p_ChannelConfig_ptr, f_BaseAddress_ptr);
      /* Configuration for the UART receiver. */
      Uart_HwReceiverInit(p_ChannelConfig_ptr, f_BaseAddress_ptr);
    }
 
  } else {
    /* Set the UART driver status to UART_STATUS_ERROR */
    f_DrvStatus_en = UART_STATUS_ERROR;
  }
 
  /* Return status of this function. */
  return f_DrvStatus_en;
}
 
/**
 * @brief       This function will access the registers to configure the UART transmitter.
 *
 * @param[in]   p_ChannelConfig_ptr: Pointer to channel configuration.
 * @param[in]   p_BaseAddress_ptr: Pointer to UART module base address.
 *
 * @return      None.
 *
 * @Design      SDD_UART_035.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwTransmitterInit(P2CONST(Uart_ChannelConfigType, AUTOMATIC, UART_APPL_DATA) p_ChannelConfig_ptr,
                                                        P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) p_BaseAddress_ptr) {
  /* Set default bit of SMR register. */
  UART_SET_BIT_U16(p_BaseAddress_ptr->SMRm0, UART_SMRMN_DEFAULT_POS);
  /* Configure CKm0 clock is source MCLK of UART transmitter. */
  UART_CLR_BIT_U16(p_BaseAddress_ptr->SMRm0, UART_SMRMN_CKS_POS);
  /* Configure clock mode for UART transmitter. */
  UART_CLR_BIT_U16(p_BaseAddress_ptr->SMRm0, UART_SMRMN_CCS_POS);
  /* Configure UART mode to used SCI module for UART feature. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SMRm0, UART_SMRMN_MD_MSK, UART_SMRMN_MD_UART);
  /* Configure interrupt type for UART transmitter. */
  UART_CLR_BIT_U16(p_BaseAddress_ptr->SMRm0, UART_SMRMN_MD0_POS);
  /* Configure the UART channel for transmit mode. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm0, UART_SCRMN_MODE_MSK, UART_SCRMN_MODE_TX);
  /* Configure the data and clock phase of UART channel  */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm0, UART_SCRMN_TIMING_MSK, UART_SCRMN_TIMING_DISABLE);
  /* Disable the generation of error interrupt INTSREx. */
  UART_CLR_BIT_U16(p_BaseAddress_ptr->SCRm0, UART_SCRMN_EOC_POS);
 
  /* Configuration for the bit order (LSB or MSB) that will be transmitted first in the UART frame. */
  if (UART_LSB_FIRST_MODE == p_ChannelConfig_ptr->HwConfig_ptr->SignificantSelect_en) {
    /* Configure to send LSB first. */
    UART_SET_BIT_U16(p_BaseAddress_ptr->SCRm0, UART_SCRMN_DIR_POS);
  } else {
    /* Configure to send MSB first. */
    UART_CLR_BIT_U16(p_BaseAddress_ptr->SCRm0, UART_SCRMN_DIR_POS);
  }
 
  /* Configuration parity bit of UART transmitter. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm0, UART_SCRMN_PTC_MSK, UART_PARITY_CONFIG(p_ChannelConfig_ptr->HwConfig_ptr->Parity_en));
  /* Configuration stop bit of UART transmitter. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm0, UART_SCRMN_SLC_MSK, UART_STOPBIT_CONFIG(p_ChannelConfig_ptr->HwConfig_ptr->StopBit_en));
  /* Configuration data length for UART transmitter. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm0, UART_SCRMN_DLS_MSK, UART_DATALENGTH_CONFIG(p_ChannelConfig_ptr->HwConfig_ptr->DataLength_en));
}
 
/**
 * @brief       This function will access the registers to configure the UART receiver.
 *
 * @param[in]   p_ChannelConfig_ptr: Pointer to channel configuration.
 * @param[in]   p_BaseAddress_ptr: Pointer to UART module base address.
 *
 * @return      None.
 *
 * @Design      SDD_UART_036.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwReceiverInit(P2CONST(Uart_ChannelConfigType, AUTOMATIC, UART_APPL_DATA) p_ChannelConfig_ptr,
                                                      P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) p_BaseAddress_ptr) {
  /* Set default bit of SMR register. */
  UART_SET_BIT_U16(p_BaseAddress_ptr->SMRm1, UART_SMRMN_DEFAULT_POS);
  /* Configure CKm0 clock is source MCLK of UART receiver. */
  UART_CLR_BIT_U16(p_BaseAddress_ptr->SMRm1, UART_SMRMN_CKS_POS);
  /* Configure clock mode for UART receiver. */
  UART_CLR_BIT_U16(p_BaseAddress_ptr->SMRm1, UART_SMRMN_CCS_POS);
  /* Configure UART mode to used SCI module for UART feature. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SMRm1, UART_SMRMN_MD_MSK, UART_SMRMN_MD_UART);
  /* Configure interrupt type for UART receiver. */
  UART_CLR_BIT_U16(p_BaseAddress_ptr->SMRm1, UART_SMRMN_MD0_POS);
  /* Configure trigger source for UART receiver. */
  UART_SET_BIT_U16(p_BaseAddress_ptr->SMRm1, UART_SMRMN_STS_POS);
 
  /* Configure the data will be invert or not. */
  if (UART_TRUE == p_ChannelConfig_ptr->HwConfig_ptr->InvertOutput_bool) {
    /* Receive data will be invert */
    UART_SET_BIT_U16(p_BaseAddress_ptr->SMRm1, UART_SMRMN_SIS_POS);
  } else {
    /* Receive data will not be invert */
    UART_CLR_BIT_U16(p_BaseAddress_ptr->SMRm1, UART_SMRMN_SIS_POS);
  }
 
  /* Configure the UART channel for receive mode. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm1, UART_SCRMN_MODE_MSK, UART_SCRMN_MODE_RX);
  /* Configure the data and clock phase of UART channel  */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm1, UART_SCRMN_TIMING_MSK, UART_SCRMN_TIMING_DISABLE);
  /* Disable the generation of error interrupt INTSREx. */
  UART_CLR_BIT_U16(p_BaseAddress_ptr->SCRm1, UART_SCRMN_EOC_POS);
 
  /* Configuration for the bit order (LSB or MSB) that will be receive first in the UART frame. */
  if (UART_LSB_FIRST_MODE == p_ChannelConfig_ptr->HwConfig_ptr->SignificantSelect_en) {
    /* Configure to send LSB first. */
    UART_SET_BIT_U16(p_BaseAddress_ptr->SCRm1, UART_SCRMN_DIR_POS);
  } else {
    /* Configure to send MSB first. */
    UART_CLR_BIT_U16(p_BaseAddress_ptr->SCRm1, UART_SCRMN_DIR_POS);
  }
 
  /* Configuration parity bit of UART receiver. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm1, UART_SCRMN_PTC_MSK, UART_PARITY_CONFIG(p_ChannelConfig_ptr->HwConfig_ptr->Parity_en));
  /* Configuration stop bit of UART receiver. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm1, UART_SCRMN_SLC_MSK, UART_STOPBIT_CONFIG(p_ChannelConfig_ptr->HwConfig_ptr->StopBit_en));
  /* Configuration data length for UART receiver. */
  UART_MOD_REG_U16(p_BaseAddress_ptr->SCRm1, UART_SCRMN_DLS_MSK, UART_DATALENGTH_CONFIG(p_ChannelConfig_ptr->HwConfig_ptr->DataLength_en));
}
#if (STD_ON == UART_DEINIT_API)
/**
 * @brief       This function accesses the hardware to configure the registers for de-initializing the UART channel.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel to be de-initialized.
 *
 * @return      None.
 *
 * @Design      SDD_UART_014, SDD_UART_015, SDD_UART_037.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwDeInit(CONST(uint8, AUTOMATIC) p_Channel_u8) {
  /* This variable used to store base address of the corresponding UART channel. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
 
  /* Get base address of UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
 
  /* Clear SPS register to default value. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SPS, UART_CLEAR_SPS_REG);
  /* Clear SMR register to default value. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SMRm0, UART_CLEAR_SMR_REG);
  UART_WR_REG_U16(f_BaseAddress_ptr->SMRm1, UART_CLEAR_SMR_REG);
  /* Clear SCR register to default value. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SCRm0, UART_CLEAR_SCR_REG);
  UART_WR_REG_U16(f_BaseAddress_ptr->SCRm1, UART_CLEAR_SCR_REG);
  /* Clear SDR register to default value. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SDRm0, UART_CLEAR_SDR_REG);
  UART_WR_REG_U16(f_BaseAddress_ptr->SDRm1, UART_CLEAR_SDR_REG);
  /* Clear SIR register to default value. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SIRm0, UART_CLEAR_SIR_REG);
  UART_WR_REG_U16(f_BaseAddress_ptr->SIRm1, UART_CLEAR_SIR_REG);
  /* Clear SOE register to default value. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SOE, UART_CLEAR_SOE_REG);
  /* Clear SO register to default value. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SO, UART_CLEAR_SO_REG);
  /* Clear SOL register to default value. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SOL, UART_CLEAR_SOL_REG);
}
#endif /* (STD_ON == UART_DEINIT_API) */
 
 
#if (STD_ON == UART_GET_BAUDRATE_API)
/**
 * @brief       This function accesses the hardware to get the value of the register, then calculates the current baudrate of the UART channel.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel to get the baudrate from.
 * @param[out]  p_Baudrate_ptr: A pointer where the current baud rate will be written.
 * @param[in]   p_ClockFrequency_u32: Specifies the clock frequency of the UART channel.
 *
 * @return      None.
 *
 * @Design      SDD_UART_014, SDD_UART_015, SDD_UART_016, SDD_UART_038.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwGetBaudrate(CONST(uint8, AUTOMATIC) p_Channel_u8,
                                                     P2VAR(uint32, AUTOMATIC, UART_APPL_DATA) p_Baudrate_ptr,
                                                     CONST(uint32, AUTOMATIC) p_ClockFrequency_u32) {
  /* This variable used to store value of */
  VAR(uint16, AUTOMATIC) f_SPSRegVal_u16;
  /* This variable used to store base address of the corresponding UART channel. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* This variable used to the quotient of the division. */
  VAR(uint32, AUTOMATIC) f_Quotient_u32;
 
  /* Get base address for UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
  /* Get SPS register value. */
  f_SPSRegVal_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SPS & UART_SPS_CKM0_MSK);
  /* Calculate baudrate. */
  f_Quotient_u32 = Div_DrvGetQuotient(p_ClockFrequency_u32, UART_POW_2(f_SPSRegVal_u16));
  *p_Baudrate_ptr = Div_DrvGetQuotient(f_Quotient_u32, (((uint32)Uart_l_StateStructure_aa[p_Channel_u8].SDRPrescaleVal_u8 + UART_U32_DAT_1) * UART_U32_DAT_2));
}
#endif /* (STD_ON == UART_GET_BAUDRATE_API) */
 
/**
 * @brief       This function accesses the hardware to configure the register for setting the baud rate of the UART channel.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel for which the baudrate will be set.
 * @param[in]   p_Baudrate_en: Specifies the baudrate will be set for UART channel.
 * @param[in]   p_ChannelConfig_ptr: Pointer to channel configuration.
 *
 * @return      Uart_DrvStatusType.
 *              UART_STATUS_SUCCESS: The baud rate was set for the UART channel successfully.
 *              UART_STATUS_ERROR: Failed to set the baud rate for the UART channel.
 *
 * @Design      SDD_UART_014, SDD_UART_016, SDD_UART_039.
 */
static FUNC(Uart_DrvStatusType, UART_CODE_SLOW) Uart_HwSetBaudrate(CONST(uint8, AUTOMATIC) p_Channel_u8,
                                                                    P2CONST(Uart_ChannelConfigType, AUTOMATIC, UART_APPL_DATA) p_ChannelConfig_ptr,
                                                                    CONST(Uart_BaudrateType, AUTOMATIC) p_Baudrate_en) {
/* Variable to store the return value of the function. */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
  /* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* This variable used to store SDR value to write into the SDR register. */
  VAR(uint8, AUTOMATIC) f_SDRVal_u8;
  /* This variable used to store SPS value to write into the SPS register. */
  VAR(uint8, AUTOMATIC) f_SPSVal_u8;
  /* Variable to store the current Tx enable/disable */
  VAR(uint16, AUTOMATIC) f_TxEnValue_u16;
  /* Variable to store the current Rx enable/disable */
  VAR(uint16, AUTOMATIC) f_RxEnValue_u16;
 
  /* Init for return value. */
  f_DrvStatus_en = UART_STATUS_SUCCESS;
  /* Get base address of UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[p_ChannelConfig_ptr->HwChannel_en];
  /* Get SDR value for corresponding baudrate. */
  f_SDRVal_u8 = p_ChannelConfig_ptr->HwConfig_ptr->ClockPrescale_ptr[p_Baudrate_en].SDRPrescaleVal_u8;
  /* Get SPS value for corresponding baudrate. */
  f_SPSVal_u8 = p_ChannelConfig_ptr->HwConfig_ptr->ClockPrescale_ptr[p_Baudrate_en].SPSPrescaleVal_u8;
  /* Get current Rx status */
  f_RxEnValue_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SE & UART_SE_RECEIVE_CHANNEL_MSK);
  /* Get current Tx status */
  f_TxEnValue_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SE & UART_SE_TRANSMIT_CHANNEL_MSK);
 
  if (UART_U32_DAT_0 != f_TxEnValue_u16) {
    /* Disable transmitter if current status is disabled */
    Uart_HwFuncCmd(p_Channel_u8, UART_SEND, UART_FALSE);
  } else {
    /* Do nothing */
  }
  if (UART_U32_DAT_0 != f_RxEnValue_u16) {
    /* Disable receiver if current status is disabled */
    Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, UART_FALSE);
  } else {
    /* Do nothing */
  }
  /* Check the input baudrate to set is valid or not. */
  if ((UART_U8_DAT_0 != f_SDRVal_u8)) {
    /* Set clock prescale to get FMCK for UART channel. */
    UART_MOD_REG_U16(f_BaseAddress_ptr->SPS, UART_MOD_SPS_REG_MSK, f_SPSVal_u8);
 
    if (UART_FULLDUPLEX_MODE == p_ChannelConfig_ptr->HwConfig_ptr->TransferMode_en) {
      /* Set clock prescale to SDR register. */
      UART_MOD_REG_U16(f_BaseAddress_ptr->SDRm0, UART_MOD_SDR_CLOCK_PRESCALE_MSK, (uint16)f_SDRVal_u8 << UART_SDR_CLOCK_PRESCALE_POS);
      UART_MOD_REG_U16(f_BaseAddress_ptr->SDRm1, UART_MOD_SDR_CLOCK_PRESCALE_MSK, (uint16)f_SDRVal_u8 << UART_SDR_CLOCK_PRESCALE_POS);
    } else if (UART_RECEIVE_MODE == p_ChannelConfig_ptr->HwConfig_ptr->TransferMode_en) {
      /* Set clock prescale to SDR register. */
      UART_MOD_REG_U16(f_BaseAddress_ptr->SDRm1, UART_MOD_SDR_CLOCK_PRESCALE_MSK, (uint16)f_SDRVal_u8 << UART_SDR_CLOCK_PRESCALE_POS);
    } else {
      /* Set clock prescale to SDR register. */
      UART_MOD_REG_U16(f_BaseAddress_ptr->SDRm0, UART_MOD_SDR_CLOCK_PRESCALE_MSK, (uint16)f_SDRVal_u8 << UART_SDR_CLOCK_PRESCALE_POS);
    }
 
    /* Store SDR value for current baudrate */
    Uart_l_StateStructure_aa[p_Channel_u8].SDRPrescaleVal_u8 = f_SDRVal_u8;
  } else {
    /* Set the UART driver status to UART_STATUS_ERROR */
    f_DrvStatus_en = UART_STATUS_ERROR;
  }
 
  /* Return status of this function. */
  return f_DrvStatus_en;
}
 
/**
 * @brief       This function will access the hardware to configure the register for synchronously send data over the specified UART channel.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel to be Send data.
 *
 * @return      None.
 *
 * @Design      SDD_UART_015, SDD_UART_016, SDD_UART_040.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwSyncSend(CONST(uint8, AUTOMATIC) p_Channel_u8) {
  /* This variable store the return value of this function. */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
  /* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  VAR(uint16, AUTOMATIC) f_SSRRegVal_u16;
  /* This variable stores the time value at the start. */
  VAR(uint32, AUTOMATIC) f_StartValue_u32;
  /* This variable stores elapsed time. */
  VAR(uint32, AUTOMATIC) f_ElapsedTime_u32;
  /* This variable stores timeout value. */
  VAR(uint32, AUTOMATIC) f_Timeout_u32;
  /* This variable stores the value to compare when a timeout occurs. */
  VAR(uint32, AUTOMATIC) f_TargetTimeout_u32;
 
  /* Get base address of UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
  /*Init value. */
  f_DrvStatus_en = UART_STATUS_SUCCESS;
  f_ElapsedTime_u32 = UART_U32_DAT_0;
  f_StartValue_u32 = UART_U32_DAT_0;
  f_Timeout_u32 = UART_U32_DAT_0;
  f_TargetTimeout_u32 = UART_DRV_TIMEOUT_DURATION_TICK(UART_TIMEOUT_DURATION_US);
 
  /* Write data to SDR register. */
  Uart_HwWriteData(p_Channel_u8);
 
  /* Get current counter. */
  (void)GetCounterValue(UART_OS_COUNTER_ID, &f_StartValue_u32);
 
  /* Wait until the data is shifted to the shift register or timeout occurs. */
  do {
    /* Check if this channel is in full-duplex mode. */
    if (UART_FULLDUPLEX_MODE == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->TransferMode_en) {
      /* Check whether the receiver has incoming data. */
      f_SSRRegVal_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SSRm1 & UART_FLAG_BFF);
 
      if (UART_U8_DAT_0 != f_SSRRegVal_u16) {
        /* Start receive data. */
        Uart_HwSyncReceive(p_Channel_u8);
 
      } else {
        /* Do nothing. */
      }
    }
 
    f_SSRRegVal_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SSRm0 & UART_FLAG_BFF);
 
    /* Get elapsed time. */
    (void)GetElapsedValue(UART_OS_COUNTER_ID, &f_StartValue_u32, &f_ElapsedTime_u32);
    f_Timeout_u32 += f_ElapsedTime_u32;
 
    /* Check timeout. */
    if (f_Timeout_u32 >= f_TargetTimeout_u32) {
      f_DrvStatus_en = UART_STATUS_TIMEOUT;
 
    } else {
      /* Do nothing */
    }
 
  } while ((UART_STATUS_TIMEOUT != f_DrvStatus_en) && (UART_FLAG_BFF == f_SSRRegVal_u16));
 
  /* Check the status of the wait BFF flag. */
  if (UART_STATUS_SUCCESS == f_DrvStatus_en) {
 
    /* Check if this is the last frame to send. */
    if ((UART_U32_DAT_0 == Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32)) {
      /* Set status of transmitter to success. */
      Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_SUCCESS;
    } else {
      /* Do nothing */
    }
 
  } else {
    /* Set status of transmitter to timeout. */
    Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_TIMEOUT;
  }
 
  /* Check if this channel is in full-duplex mode. */
  if (UART_FULLDUPLEX_MODE == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->TransferMode_en) {
    /* Check if this is the last frame to send. */
    if ((UART_U32_DAT_0 == Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32)) {
      /* Set status of transmitter to success. */
      Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_IDLE;
 
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
}
 
/**
 * @brief       This function will access the hardware to configure the register for synchronously receive data over the specified UART channel.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel to be receive data.
 *
 * @return      None.
 *
 * @Design      SDD_UART_016, SDD_UART_041, SDD_UART_053.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwSyncReceive(CONST(uint8, AUTOMATIC) p_Channel_u8) {
  /* This variable used to store SSR register value. */
  VAR(uint16, AUTOMATIC) f_SSRValue_u16;
/* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* This variable used to store dummy data when error occurs. */
  VAR(uint16, AUTOMATIC) f_DummyData_u16;
 
  /* Get base address of UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
  /* Get error flag of SSR register. */
  f_SSRValue_u16 = (f_BaseAddress_ptr->SSRm1 & UART_ERROR_FLAG);
 
 
  /* Check if any error occurs. */
  if (UART_U16_DAT_0 != f_SSRValue_u16) {
    /* Dummy read to clear error data. */
    f_DummyData_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SDRm1);
    (void)f_DummyData_u16;
    /* Error handle. */
    Uart_HwErrorHandler(p_Channel_u8, f_SSRValue_u16);
 
  } else {
    /* Do nothing */
  }
 
  if (UART_TRUE == Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool) {
    /* Read data from register. */
    Uart_HwReadData(p_Channel_u8);
 
    /* Check if this is the last frame to receive. */
    if (UART_U32_DAT_0 == Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32) {
      /* Change receive status to success. */
      Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_SUCCESS;
    } else {
      /* Do nothing */
    }
  }
}
 
#if ((UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON))
/**
 * @brief     Complete a transmission by finishing the process of transmitting data.
 *
 * @param[in] p_Channel_u8: Numeric identifier of the UART channel.
 *
 * @return    None.
 *
 * @Design    SDD_UART_016, SDD_UART_043.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwCompleteSendData(CONST(uint8, AUTOMATIC) p_Channel_u8) {
  /* Variable to store the status code of the function */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
 
  /* Prevent abort during transmission. */
  if (UART_STATUS_ABORTED != Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en) {
    /* Wait for the BFF flag to be reset or until a timeout occurs. */
    f_DrvStatus_en = Uart_HwWaitStatus(p_Channel_u8, UART_SEND, UART_FLAG_BFF, UART_FALSE);
 
    /* Check if timeout occurs. */
    if (UART_STATUS_TIMEOUT == f_DrvStatus_en) {
      /* Change status of transmitter to timeout. */
      Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_TIMEOUT;
    } else {
      /* Do nothing */
    }
 
  } else {
    /* Do nothing */
  }
 
  /* Update the information of the module driver state */
  Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool = UART_FALSE;
 
  if (UART_STATUS_BUSY == Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en) {
    /* Change status of transmitter to success. */
    Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_SUCCESS;
  } else {
    /* Do nothing */
  }
}
 
#endif /* ((UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON)) */
 
/**
 * @brief     Complete a reception by finishing the process of receiving data.
 *
 * @param[in] p_Channel_u8: Numeric identifier of the UART channel.
 *
 * @return    None.
 *
 * @Design    SDD_UART_016, SDD_UART_044.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwCompleteReceiveData(CONST(uint8, AUTOMATIC) p_Channel_u8) {
  /* Variable to store the status code of the function */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
 
  /* Update the information of the module driver state */
  Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool = UART_FALSE;
 
  /* Prevent abort during reception */
  if (UART_STATUS_ABORTED != Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en) {
    /* Wait for the BFF flag to be reset or until a timeout occurs. */
    f_DrvStatus_en = Uart_HwWaitStatus(p_Channel_u8, UART_RECEIVE, UART_FLAG_BFF, UART_FALSE);
 
    if (UART_STATUS_TIMEOUT == f_DrvStatus_en) {
      /* Change status of receiver to timeout. */
      Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_TIMEOUT;
    } else {
      /* Do nothing */
    }
 
  } else {
    /* Do nothing */
  }
 
  /* Disable receiver */
  Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, UART_FALSE);
 
  if (UART_STATUS_BUSY == Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en) {
    /* Change status of receiver to success. */
    Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_SUCCESS;
  } else {
    /* Do nothing */
  }
}
 
#if ((UART_SCI0_ISR_RX_USED == STD_ON) || (UART_SCI1_ISR_RX_USED == STD_ON) || (UART_SCI2_ISR_RX_USED == STD_ON) || (UART_SCI3_ISR_RX_USED == STD_ON) || \
    (UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON))
/**
 * @brief       This function will call the callback function to notify the user.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel.
 * @param[in]   p_Direction_en: Specifies the type of callback function used for the UART channel.
 *
 * @return      None.
 *
 * @Design      SDD_UART_015, SDD_UART_045.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwCallNotification(CONST(uint8, AUTOMATIC) p_Channel_u8, CONST(Uart_DataDirectionType, AUTOMATIC) p_Direction_en) {
  /* Check the input parameter p_Direction_en to call corresponding call back function. */
  if ((UART_SEND == p_Direction_en) && (NULL_PTR != Uart_l_ChCfg_aa[p_Channel_u8]->TxNotification_ptr)) {
    /* Invoke callback function for transmitter. */
    Uart_l_ChCfg_aa[p_Channel_u8]->TxNotification_ptr();
 
  } else if ((UART_RECEIVE == p_Direction_en) && (NULL_PTR != Uart_l_ChCfg_aa[p_Channel_u8]->RxNotification_ptr)) {
    /* Invoke callback function for receiver. */
    Uart_l_ChCfg_aa[p_Channel_u8]->RxNotification_ptr();
 
  } else {
    /* Do nothing */
  }
}
#endif /* ((UART_SCI0_ISR_RX_USED == STD_ON) || (UART_SCI1_ISR_RX_USED == STD_ON) || (UART_SCI2_ISR_RX_USED == STD_ON) || (UART_SCI3_ISR_RX_USED == STD_ON) || \
    (UART_SCI0_ISR_TX_USED == STD_ON) || (UART_SCI1_ISR_TX_USED == STD_ON) || (UART_SCI2_ISR_TX_USED == STD_ON) || (UART_SCI3_ISR_TX_USED == STD_ON)) */
 
/**
 * @brief       This function accesses the hardware to configure the registers for transmit data.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel to be write data to register.
 *
 * @return      None.
 *
 * @Design      SDD_UART_014, SDD_UART_015, SDD_UART_016, SDD_UART_046.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwWriteData(CONST(uint8, AUTOMATIC) p_Channel_u8) {
  /* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* This variable is used to store the data that will be transmitted. */
  VAR(uint16, AUTOMATIC) f_SendData_u16;
 
  /* Get base address for UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
 
  if (UART_FALSE != Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool) {
    /* Check data length of the UART transmitter. */
    if ((UART_7_BITS_DATA_LENGTH == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->DataLength_en) ||
        (UART_8_BITS_DATA_LENGTH == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->DataLength_en)) {
      /* Get the data that will be transmitted. */
      f_SendData_u16 = (uint16)Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr[UART_U8_DAT_0];
 
    } else { /* Data length is 9 bit or 16 bit. */
      /* Get the data that will be transmitted. */
      if (UART_U32_DAT_1 < Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32) {
        f_SendData_u16 = (((uint16)Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr[UART_U8_DAT_0] << UART_U16_LOW_POS) & UART_U16_LOW_MSK) |
                        (((uint16)Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr[UART_U8_DAT_1] << UART_U16_HIGH_POS) & UART_U16_HIGH_MSK);
        /* Increment the transmit buffer address by one byte. */
        Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr++;
        /* Decrease the transmit size by one unit. */
        Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32--;
      } else {
        f_SendData_u16 = (uint16)Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr[UART_U8_DAT_0];
      }
    }
 
    /* Increment the transmit buffer address by one byte. */
    Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr++;
    /* Decrease the transmit size by one unit. */
    Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32--;
    /* Write data to SDR register. */
    UART_WR_REG_U16(f_BaseAddress_ptr->SDRm0, f_SendData_u16 & UART_DATALENGTH_MASK(Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->DataLength_en));
  } else {
    /* Do nothing. */
  }
}
 
/**
 * @brief       This function used to read data from the SDRm1 register of the corresponding UART channel.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel to be read data from SDR register.
 *
 * @return      None.
 *
 * @Design      SDD_UART_014, SDD_UART_015, SDD_UART_016, SDD_UART_047.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwReadData(CONST(uint8, AUTOMATIC) p_Channel_u8) {
  /* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* This variable is used to store receive data. */
  VAR(uint16, AUTOMATIC) f_ReceiveData_u16;
 
  /* Get base address for UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
  /* Get received data. */
  f_ReceiveData_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SDRm1);
 
  if ((UART_7_BITS_DATA_LENGTH == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->DataLength_en) ||
    (UART_8_BITS_DATA_LENGTH == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->DataLength_en)) {
    /* Set received data into Rx buffer. */
    *(Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr) = (uint8)((f_ReceiveData_u16 & UART_U16_LOW_MSK) >> UART_U16_LOW_POS);
    /* Point to next index of Rx buffer */
    Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr++;
    /* Decreased the remain size of Rx Buffer */
    Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32--;
  } else { /* Data length is 9 bit or 16 bit. */
    if (UART_U32_DAT_1 < Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32) {
      /* Set received data into Rx buffer. */
      *(Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr) = (uint8)((f_ReceiveData_u16 & UART_U16_LOW_MSK) >> UART_U16_LOW_POS);
      /* Point to next index of Rx buffer */
      Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr++;
      /* Set received data into Rx buffer. */
      *(Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr) = (uint8)((f_ReceiveData_u16 & UART_U16_HIGH_MSK) >> UART_U16_HIGH_POS);
      /* Point to next index of Rx buffer */
      Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr++;
      /* Decreased the remain size of Rx Buffer */
      Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32 -= UART_U32_DAT_2;
 
    } else {
      /* Set received data into Rx buffer. */
      *(Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr) = (uint8)f_ReceiveData_u16;
      /* Point to next index of Rx buffer */
      Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr++;
      /* Decreased the remain size of Rx Buffer */
      Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32--;
    }
  }
 
}
 
 
 
/**
 * @brief       This function is used to enable or disable the transmit or receive function of the corresponding UART channel.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel to be enabled or disabled.
 * @param[in]   p_Direction_en: The type of UART channel to be enabled or disabled.
 * @param[in]   p_Enable_bool: Specifies whether the UART channel is enabled or disabled.
 *
 * @return      None.
 *
 * @Design      SDD_UART_014, SDD_UART_015, SDD_UART_048.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwFuncCmd(CONST(uint8, AUTOMATIC) p_Channel_u8,
                                                CONST(Uart_DataDirectionType, AUTOMATIC) p_Direction_en,
                                                CONST(boolean, AUTOMATIC) p_Enable_bool) {
  /* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
 
   /* Get base address for UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
 
  /*Check the input parameter p_Enable_bool value. */
  if (UART_TRUE == p_Enable_bool) {
    /* Check the input parameter p_Direction_en to determine which function (transmit or receive) to configure accordingly. */
    if (UART_SEND == p_Direction_en) {
      /* Configuration inversion of UART transmitter. */
      if (UART_TRUE == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->InvertOutput_bool) {
        /* Enable inversion of transmitted data in UART communication. */
        UART_SET_BIT_U16(f_BaseAddress_ptr->SOL, UART_SOL_SOL_POS);
      } else {
        /* Disable inversion of transmitted data in UART communication. */
        UART_CLR_BIT_U16(f_BaseAddress_ptr->SOL, UART_SOL_SOL_POS);
      }
 
      /* Enable transmit of corresponding UART channel. */
      UART_SET_BIT_U16(f_BaseAddress_ptr->SOE, UART_SOE_ENABLE_TRANSMIT_CHANNEL_POS);
      UART_SET_BIT_U16(f_BaseAddress_ptr->SS, UART_TRANSMIT_CHANNEL_ST_SS_POS);
 
    } else {
      /* Enable receive of corresponding UART channel. */
      UART_SET_BIT_U16(f_BaseAddress_ptr->SS, UART_RECEIVE_CHANNEL_ST_SS_POS);
 
    }
  } else {
    /* Check the input parameter p_Direction_en to determine which function (transmit or receive) to configure accordingly. */
    if (UART_SEND == p_Direction_en) {
      /* Disable transmit of corresponding UART channel. */
      UART_SET_BIT_U16(f_BaseAddress_ptr->ST, UART_TRANSMIT_CHANNEL_ST_SS_POS);
      UART_CLR_BIT_U16(f_BaseAddress_ptr->SOE, UART_SOE_ENABLE_TRANSMIT_CHANNEL_POS);
 
    } else {
      /* Disable receive of corresponding UART channel. */
      UART_SET_BIT_U16(f_BaseAddress_ptr->ST, UART_RECEIVE_CHANNEL_ST_SS_POS);
 
    }
  }
}
 
/**
 * @brief       This function used to clear error flag provided by p_Flag_u16 parameter for corresponding channel with p_Channel_u8 parameter.
 *
 * @param[in]   p_Channel_u8: Specifies the UART channel to be clear flag.
 * @param[in]   p_Flag_u16: Specifies the flag will be cleared in the corresponding UART channel.
 *
 * @return      None.
 *
 * @Design      SDD_UART_014, SDD_UART_015, SDD_UART_049.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwClearStatus(CONST(uint8, AUTOMATIC) p_Channel_u8, CONST(uint16, AUTOMATIC) p_Flag_u16) {
  /* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
 
  /* Get base address for UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
  /* Clear the flag. */
  UART_WR_REG_U16(f_BaseAddress_ptr->SIRm1, p_Flag_u16);
}
 
/**
 * @brief This function is used to wait for the corresponding flag to match the expected value.
 *
 * @param[in] p_Channel_u8: Specifies the UART channel to get the flag status.
 * @param[in] p_Direction_en: Specifies whether the type to be checked is the transmitter or receiver of the UART channel
 * @param[in] p_Flag_u16: The flag will be check.
 * @param[in] p_ExpectedVal_bool: Expected value of the flag.
 *
 * @return    Uart_DrvStatusType.
 *            UART_STATUS_SUCCESS: The input flag matches the expected value.
 *            UART_STATUS_TIMEOUT: Timeout occurs.
 *            UART_STATUS_ERROR: Error occurs when waiting for the expected flag to be set.
 *
 * @Design    SDD_UART_014, SDD_UART_015, SDD_UART_050.
 */
static FUNC(Uart_DrvStatusType, UART_CODE_SLOW) Uart_HwWaitStatus(CONST(uint8, AUTOMATIC) p_Channel_u8,
                                                                   CONST(Uart_DataDirectionType, AUTOMATIC) p_Direction_en,
                                                                   VAR(uint16, AUTOMATIC) p_Flag_u16,
                                                                   VAR(boolean, AUTOMATIC) p_ExpectedVal_bool) {
  /* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* This variable stores the corresponding flag value. */
  VAR(uint16, AUTOMATIC) f_FlagValue_u16;
  /* This variable stores the time value at the start. */
  VAR(uint32, AUTOMATIC) f_StartValue_u32;
  /* This variable stores elapsed time. */
  VAR(uint32, AUTOMATIC) f_ElapsedTime_u32;
  /* This variable stores timeout value. */
  VAR(uint32, AUTOMATIC) f_Timeout_u32;
  /* This variable stores return value of this function. */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
  /* This variable stores the value to compare when a timeout occurs. */
  VAR(uint32, AUTOMATIC) f_TargetTimeout_u32;
 
  /* Get base address for UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
  /*Init value. */
  f_ElapsedTime_u32 = UART_U32_DAT_0;
  f_StartValue_u32 = UART_U32_DAT_0;
  f_Timeout_u32 = UART_U32_DAT_0;
  f_TargetTimeout_u32 = UART_DRV_TIMEOUT_DURATION_TICK(UART_TIMEOUT_DURATION_US);
  /* Init return value. */
  f_DrvStatus_en = UART_STATUS_SUCCESS;
  /* Get current counter. */
  (void)GetCounterValue(UART_OS_COUNTER_ID, &f_StartValue_u32);
 
  do {
    /* Check flag. */
    if (UART_SEND == p_Direction_en) {
      /* Get flag value. */
      f_FlagValue_u16 = ((f_BaseAddress_ptr->SSRm0) & p_Flag_u16);
    } else {
      /* Get flag value. */
      f_FlagValue_u16 = ((f_BaseAddress_ptr->SSRm1) & p_Flag_u16);
    }
 
    (void)GetElapsedValue(UART_OS_COUNTER_ID, &f_StartValue_u32, &f_ElapsedTime_u32);
    /* Get elapsed time. */
    f_Timeout_u32 += f_ElapsedTime_u32;
 
    /* Check timeout. */
    if (f_Timeout_u32 >= f_TargetTimeout_u32) {
      f_DrvStatus_en = UART_STATUS_TIMEOUT;
    } else {
      /* Do nothing */
    }
 
  } while ((UART_STATUS_TIMEOUT != f_DrvStatus_en) &&
           (((UART_TRUE == p_ExpectedVal_bool) && (p_Flag_u16 != f_FlagValue_u16)) ||
            ((UART_FALSE == p_ExpectedVal_bool) && (p_Flag_u16 == f_FlagValue_u16))));
 
  /* Return status of this function. */
  return f_DrvStatus_en;
}
 
/**
 * @brief       This function used to convert from driver status to channel status.
 *
 * @param[in]   p_DrvStatus_en: Status to convert.
 *
 * @return      Uart_StatusType.
 *              UART_CH_IDLE: The UART channel is in idle state.
 *              UART_CH_BUSY: The UART channel is in busy state.
 *              UART_CH_ERROR: The UART channel encountered errors during receiving data.
 *              UART_CH_COMPLETE: The UART channel finished transaction without errors.
 *              UART_CH_ABORTED: The UART operation is aborted.
 *              UART_CH_TIMEOUT: Timeout occurs.
 *
 * @Design      SDD_UART_031.
 */
static FUNC(Uart_StatusType, UART_CODE_SLOW) Uart_DrvConvertStatus(CONST(Uart_DrvStatusType, AUTOMATIC) p_DrvStatus_en) {
  /* This variable used to store return value of this function. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
 
  /* Switch statement to map driver status code to UART status code */
  switch (p_DrvStatus_en) {
    /* Map driver idle status to UART channel idle status */
    case UART_STATUS_IDLE:
      f_ChStatus_en = UART_CH_IDLE;
      break;
    /* Map driver busy status to UART channel busy status */
    case UART_STATUS_BUSY:
      f_ChStatus_en = UART_CH_BUSY;
      break;
    /* Map driver error status to UART channel error status */
    case UART_STATUS_ERROR:
      f_ChStatus_en = UART_CH_ERROR;
      break;
    /* Map driver receive timeout status to UART timeout status */
    case UART_STATUS_TIMEOUT:
      f_ChStatus_en = UART_CH_TIMEOUT;
      break;
    /* Map driver receive overflow status to UART channel error status */
    case UART_STATUS_RX_OVERFLOW:
      f_ChStatus_en = UART_CH_ERROR;
      break;
    /* Map driver receive framing error status to UART channel error status */
    case UART_STATUS_RX_FRAMING_ERROR:
      f_ChStatus_en = UART_CH_ERROR;
      break;
    /* Map driver receive verifying error status to UART channel error status */
    case UART_STATUS_RX_PARITY_ERROR:
      f_ChStatus_en = UART_CH_ERROR;
      break;
    /* Map driver multiple error status to UART channel error status */
    case UART_STATUS_MULTIPLE_ERROR:
      f_ChStatus_en = UART_CH_ERROR;
      break;
    /* Map driver success status to UART channel complete status */
    case UART_STATUS_SUCCESS:
      f_ChStatus_en = UART_CH_COMPLETE;
      break;
    /* Map driver aborted status to UART channel aborted status */
    case UART_STATUS_ABORTED:
      f_ChStatus_en = UART_CH_ABORTED;
      break;
    /* Default case, map unknown status to UART channel error status */
    default:
      f_ChStatus_en = UART_CH_ERROR;
      break;
  }
 
  /* Return the converted status value. */
  return f_ChStatus_en;
}
 
/**
 * @brief     This function used to handle error of the UART channel.
 *
 * @param[in] p_Channel_u8: Specifies the UART channel need to be handle error.
 * @param[in] p_SSRRegVal_u16: The SSR register value of the corresponding UART channel.
 *
 * @return    None.
 *
 * @Design    SDD_UART_016, SDD_UART_051, SDD_UART_053.
 */
static FUNC(void, UART_CODE_SLOW) Uart_HwErrorHandler(VAR(uint8, AUTOMATIC) p_Channel_u8, VAR(uint16, AUTOMATIC) p_SSRRegVal_u16) {
  /* This variable used to store error status. */
  VAR(boolean, AUTOMATIC) f_IsError_bool;
#if (STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS)
  /* This variable used to store overflow error status. */
  VAR(boolean, AUTOMATIC) f_OvfError_bool;
  /* This variable used to store frame error status. */
  VAR(boolean, AUTOMATIC) f_FrameError_bool;
  /* This variable used to store parity error status. */
  VAR(boolean, AUTOMATIC) f_ParityError_bool;
#endif
 
  /* Init error status. */
  f_IsError_bool  = UART_FALSE;
#if (STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS)
  f_OvfError_bool = UART_FALSE;
  f_FrameError_bool = UART_FALSE;
  f_ParityError_bool = UART_FALSE;
#endif
  /* Handle receive overrun interrupt */
  if (UART_U16_DAT_0 != (p_SSRRegVal_u16 & UART_FLAG_OVF)) {
    /* Update the error status */
    f_IsError_bool = UART_TRUE;
    /* Change the status of the UART channel to overflow error. */
    Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_RX_OVERFLOW;
#if (STD_ON == UART_ENABLE_OVERFLOW_ERROR_DETECT)
    /* Update overflow error status. */
    f_OvfError_bool = UART_TRUE;
#endif
  } else {
    /* Do nothing */
  }
 
  /* Handle receive parity error interrupt */
  if (UART_U16_DAT_0 != (p_SSRRegVal_u16 & UART_FLAG_PEF)) {
 
    /* Check if another error occurs. */
    if (UART_TRUE == f_IsError_bool) {
      /* Change the status of the UART channel to multiple error. */
      Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_MULTIPLE_ERROR;
 
    } else {
      /* Update the error status */
      f_IsError_bool = UART_TRUE;
      /* Change the status of the UART channel to parity error. */
      Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_RX_PARITY_ERROR;
    }
 
#if (STD_ON == UART_ENABLE_PARITY_ERROR_DETECT)
    /* Update parity error status. */
    f_ParityError_bool = UART_TRUE;
#endif
  } else {
    /* Do nothing */
  }
 
  /* Handle receive frame error interrupt */
  if (UART_U16_DAT_0 != (p_SSRRegVal_u16 & UART_FLAG_FEF)) {
 
    /* Check if another error occurs. */
    if (UART_TRUE == f_IsError_bool) {
      /* Change the status of the UART channel to multiple error. */
      Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_MULTIPLE_ERROR;
 
    } else {
      /* Update the error status */
      f_IsError_bool = UART_TRUE;
       /* Change the status of the UART channel to frame error. */
      Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_RX_FRAMING_ERROR;
    }
 
#if (STD_ON == UART_ENABLE_FRAME_ERROR_DETECT)
    /* Update frame error status. */
    f_FrameError_bool = UART_TRUE;
#endif
  } else {
    /* Do nothing */
  }
 
  if (UART_TRUE == f_IsError_bool) {
    /* Invoke error notification function. */
    Uart_l_ChCfg_aa[p_Channel_u8]->ErrNotification_ptr();
 
    /* Finishing the process of receiving data. */
    Uart_HwCompleteReceiveData(p_Channel_u8);
    /* Clear the flag */
    Uart_HwClearStatus(p_Channel_u8, UART_ERROR_FLAG);
  } else {
    /* Do nothing. */
  }
 
#if (STD_OFF == UART_DISABLE_DEM_REPORT_ERROR_STATUS)
  if ((UART_TRUE == f_FrameError_bool) || (UART_TRUE == f_OvfError_bool) || (UART_TRUE == f_ParityError_bool)) {
    (void)Dem_SetEventStatus(UART_E_TRANSMISSION_ERROR, DEM_EVENT_STATUS_FAILED);
  } else {
    /* Do nothing */
  }
#endif
}
 
/** @} end of group Private_FunctionDefinition */
 
/** @defgroup Public_FunctionDefinition
 *  @{
 */
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
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_DrvInit(P2CONST(Uart_ConfigType, AUTOMATIC, UART_APPL_DATA) p_Config_ptr) {
  /* Variable to store the status code of the function. */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
  /* Variable to store return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
  /* Temp variable used to loop through UART configuration sets. */
  VAR(uint8, AUTOMATIC) f_Index_u8;
 
  /* Init return value */
  f_RetVal_u8 = E_OK;
 
  /* Configured for each channel. */
  for (f_Index_u8 = UART_U8_DAT_0; f_Index_u8 < UART_CH_MAX_CONFIG; f_Index_u8++) {
    /* Call the Uart_HwInit API to configure the registers. */
    f_DrvStatus_en = Uart_HwInit(&p_Config_ptr->ChannelConfig_ptr[f_Index_u8]);
    /* Check if it is configured successfully or not. */
    if (UART_STATUS_SUCCESS == f_DrvStatus_en) {
      /* Store configuration structure of the Uart channel. */
      Uart_l_ChCfg_aa[f_Index_u8] = (&p_Config_ptr->ChannelConfig_ptr[f_Index_u8]);
      /* Set the baudrate for the corresponding UART channel. */
      f_DrvStatus_en = Uart_HwSetBaudrate(f_Index_u8, &p_Config_ptr->ChannelConfig_ptr[f_Index_u8], p_Config_ptr->ChannelConfig_ptr[f_Index_u8].Baudrate_en);
 
      if (UART_STATUS_SUCCESS == f_DrvStatus_en) {
        /* Init structure stored the status of this channel. */
        Uart_l_StateStructure_aa[f_Index_u8].RxBuffer_ptr      = NULL_PTR;
        Uart_l_StateStructure_aa[f_Index_u8].TxBuffer_ptr      = NULL_PTR;
        Uart_l_StateStructure_aa[f_Index_u8].TxSize_u32        = UART_U32_DAT_0;
        Uart_l_StateStructure_aa[f_Index_u8].RxSize_u32        = UART_U32_DAT_0;
        Uart_l_StateStructure_aa[f_Index_u8].TxBusy_bool       = UART_FALSE;
        Uart_l_StateStructure_aa[f_Index_u8].RxBusy_bool       = UART_FALSE;
        Uart_l_StateStructure_aa[f_Index_u8].ReceiveStatus_en  = UART_STATUS_IDLE;
        Uart_l_StateStructure_aa[f_Index_u8].SendStatus_en     = UART_STATUS_IDLE;
 
      } else {
        /* Change the return result to E_NOT_OK. */
        f_RetVal_u8 = E_NOT_OK;
      }
 
    } else {
      /* Change the return result to E_NOT_OK. */
      f_RetVal_u8 = E_NOT_OK;
    }
 
    /* Break if fail in any step*/
    if (E_NOT_OK == f_RetVal_u8) {
      /* Clear our saved pointer to the state structure */
      Uart_l_ChCfg_aa[f_Index_u8] = NULL_PTR;
      break;
 
    } else {
      /* Do nothing */
    }
 
  }
 
  /* Return the result of this function. */
  return f_RetVal_u8;
}
 
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
#if (STD_ON == UART_DEINIT_API)
FUNC(void, UART_CODE_SLOW) Uart_DrvDeInit(CONST(uint8, AUTOMATIC) p_Channel_u8) {
  /* This variable is used to store the return value of the Uart_HwWaitStatus API. */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvRetVal_en;
 
  if (Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool == UART_TRUE) {
    /* Disable transmit of the corresponding UART channel. */
    Uart_HwFuncCmd(p_Channel_u8, UART_SEND, UART_FALSE);
    /* Wait for the BUSY flag to be reset or until a timeout occurs. */
    f_DrvRetVal_en = Uart_HwWaitStatus(p_Channel_u8, UART_SEND, UART_FLAG_BUSY, UART_FALSE);
 
  } else if (Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool == UART_TRUE) {
    /* Disable receive of the corresponding UART channel. */
    Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, UART_FALSE);
    /* Wait for the BUSY flag to be reset or until a timeout occurs. */
    f_DrvRetVal_en = Uart_HwWaitStatus(p_Channel_u8, UART_RECEIVE, UART_FLAG_BUSY, UART_FALSE);
 
  } else {
    /* If the Transmit and Receive operations of this channel are not busy, change the status to UART_STATUS_SUCCESS. */
    f_DrvRetVal_en = UART_STATUS_SUCCESS;
  }
 
  if (UART_STATUS_SUCCESS == f_DrvRetVal_en) {
    /* Call Uart_HwDeInit() to reset all registers to default value. */
    Uart_HwDeInit(p_Channel_u8);
 
    /* Clear our saved pointer to the state structure */
    Uart_l_ChCfg_aa[p_Channel_u8] = NULL_PTR;
 
    /* Clear structure stored the status of this channel. */
    Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr      = NULL_PTR;
    Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr      = NULL_PTR;
    Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32        = UART_U32_DAT_0;
    Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32        = UART_U32_DAT_0;
    Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool       = UART_FALSE;
    Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool       = UART_FALSE;
    Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en  = UART_STATUS_IDLE;
    Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en     = UART_STATUS_IDLE;
    Uart_l_StateStructure_aa[p_Channel_u8].SDRPrescaleVal_u8 = UART_U8_DAT_0;
 
  } else {
    /* Do nothing */
  }
}
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
                                                        P2CONST(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr) {
  /* This variable used to store this function status. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
  /* Set this function status to busy. */
  f_ChStatus_en = UART_CH_BUSY;
 
  SchM_Enter_Uart_UART_EXCLUSIVE_AREA_02();
  /* Check if the UART transmitter is busy */
  if (UART_FALSE == Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool) {
    /* Set the busy sending status of the UART to true */
    Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool = UART_TRUE;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_02();
    /* Set the UART send buffer pointer */
    Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr = p_DataBuffer_ptr;
    /* Set the UART send buffer size */
    Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32 = p_BufferSize_u32;
    /* Set the UART transmitter status to busy */
    Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_BUSY;
    /* Enable transmitter. */
    Uart_HwFuncCmd(p_Channel_u8, UART_SEND, UART_TRUE);
    /* Start writing data to the transmit register of the UART channel. */
    Uart_HwWriteData(p_Channel_u8);
 
    /* Change the function status to complete. */
    f_ChStatus_en = UART_CH_COMPLETE;
 
  } else {
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_02();
  }
 
  /* Return function status. */
  return f_ChStatus_en;
}
 
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
                                                       VAR(uint32, AUTOMATIC) p_Timeout_u32) {
  /* This variable is pointer pointing directly to the register Uart with the corresponding UART Driver. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* Return value of this function. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
  /* This variable used to store transmitter is ready to transmit data or not. */
  VAR(boolean, AUTOMATIC) f_TxReady_bool;
  /* Variable to store the current Tx enable/disable */
  VAR(uint16, AUTOMATIC) f_TxEnValue_u16;
  /* Variable to store the current Rx enable/disable */
  VAR(uint16, AUTOMATIC) f_RxEnValue_u16;
  /* This variable stores the time value at the start. */
  VAR(uint32, AUTOMATIC) f_StartValue_u32;
  /* This variable stores elapsed time. */
  VAR(uint32, AUTOMATIC) f_ElapsedTime_u32;
  /* This variable stores timeout value. */
  VAR(uint32, AUTOMATIC) f_Timeout_u32;
  /* This variable calculate input timeout value. */
  VAR(uint32, AUTOMATIC) f_InputTimeout_u32;
 
  /* Get base address of UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
  /* Init value. */
  f_TxReady_bool = UART_FALSE;
  f_InputTimeout_u32 = UART_DRV_TIMEOUT_DURATION_TICK(p_Timeout_u32);
  f_ElapsedTime_u32 = UART_U32_DAT_0;
  f_StartValue_u32 = UART_U32_DAT_0;
  f_Timeout_u32 = UART_U32_DAT_0;
 
  SchM_Enter_Uart_UART_EXCLUSIVE_AREA_01();
  if ((UART_FULLDUPLEX_MODE == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->TransferMode_en) &&
      (UART_TRUE != Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool)) {
    /* Set the busy receiving status of the UART to true */
    Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool = UART_TRUE;
    /* Set the UART received buffer pointer */
    Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr = p_SyncSendInfo_ptr->RxDataBuffer_ptr;
    /* Set the UART received buffer size */
    Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32 = (*p_SyncSendInfo_ptr->RxBufferSize_ptr);
    /* Set the UART received status to busy */
    Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_BUSY;
    /* Get current Rx status */
    f_RxEnValue_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SE & UART_SE_RECEIVE_CHANNEL_MSK);
 
    if (UART_U32_DAT_0 == f_RxEnValue_u16) {
      /* Enable receiver if current status is disabled */
      Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, UART_TRUE);
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (UART_TRUE != Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool) {
    /* Set the busy sending status of the UART to true */
    Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool = UART_TRUE;
    /* Set uart ready to send flag */
    f_TxReady_bool = UART_TRUE;
    /* Set the UART send status to busy */
    Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_BUSY;
  } else {
    Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_BUSY;
  }
  SchM_Exit_Uart_UART_EXCLUSIVE_AREA_01();
 
  if(UART_TRUE == f_TxReady_bool) {
    /* Set the UART send buffer pointer */
    Uart_l_StateStructure_aa[p_Channel_u8].TxBuffer_ptr = p_SyncSendInfo_ptr->TxDataBuffer_ptr;
    /* Set the UART send buffer size */
    Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32 = p_SyncSendInfo_ptr->TxBufferSize_u32;
    /* Get current Tx status */
    f_TxEnValue_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SE & UART_SE_TRANSMIT_CHANNEL_MSK);
 
    if (UART_U32_DAT_0 == f_TxEnValue_u16) {
      /* Enable transmitter if current status is disabled */
      Uart_HwFuncCmd(p_Channel_u8, UART_SEND, UART_TRUE);
    } else {
      /* Do nothing */
    }
 
    /* Get current counter. */
    (void)GetCounterValue(UART_OS_COUNTER_ID, &f_StartValue_u32);
 
    do {
      /* Start synchronous transmit data. */
      Uart_HwSyncSend(p_Channel_u8);
 
      /* Get elapsed time. */
      (void)GetElapsedValue(UART_OS_COUNTER_ID, &f_StartValue_u32, &f_ElapsedTime_u32);
      f_Timeout_u32 += f_ElapsedTime_u32;
 
      /* Check if timeout occurs. */
      if (f_InputTimeout_u32 <= f_Timeout_u32) {
        Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_TIMEOUT;
      } else {
        /* Do nothing */
      }
 
    } while ((UART_STATUS_TIMEOUT != Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en) && \
              (UART_U32_DAT_0 < Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32));
 
    if ((UART_STATUS_TIMEOUT == Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en)) {
      /* Callback error notification function. */
      Uart_l_ChCfg_aa[p_Channel_u8]->ErrNotification_ptr();
    } else {
      /* Do nothing. */
    }
    /* Update the information of the module driver state */
    Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool = UART_FALSE;
 
    if (UART_FULLDUPLEX_MODE == Uart_l_ChCfg_aa[p_Channel_u8]->HwConfig_ptr->TransferMode_en) {
      /* Disable the UART receiver */
      Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, UART_FALSE);
      /* Update the information of the module driver state */
      Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool = UART_FALSE;
    } else {
      /* Do nothing */
    }
 
  } else {
    /* Do nothing. */
  }
 
  /* Convert status. */
  f_ChStatus_en = Uart_DrvConvertStatus(Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en);
 
  /* Return the status of this function. */
  return f_ChStatus_en;
}
 
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
                                                           P2VAR(uint8, AUTOMATIC, UART_APPL_DATA) p_DataBuffer_ptr) {
  /* This variable used to store this function status. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
 
  /* Init function status. */
  f_ChStatus_en = UART_CH_BUSY;
 
  SchM_Enter_Uart_UART_EXCLUSIVE_AREA_04();
  /* Check if the receiver is performing receive data. */
  if (UART_FALSE == Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool) {
    /* Set the busy receive status of the UART to true */
    Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool = UART_TRUE;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
    /* Set the UART receive buffer pointer */
    Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr = p_DataBuffer_ptr;
    /* Set the UART receive buffer size */
    Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32 = p_BufferSize_u32;
    /* Set the UART receiver status to busy */
    Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_BUSY;
 
    /* Start receive data of the UART channel. */
    Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, UART_TRUE);
    /* Change the channel status to UART_CH_COMPLETE */
    f_ChStatus_en = UART_CH_COMPLETE;
 
  } else {
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
  }
 
  /* Return function status */
  return f_ChStatus_en;
}
 
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
                                                          VAR(uint32, AUTOMATIC) p_Timeout_u32) {
  /* This variable used to store this function status. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
  /* This variable used to store the current Rx enable/disable */
  VAR(uint16, AUTOMATIC) f_RxEnValue_u16;
  /* This variable used to store base address of the corresponding UART channel. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* Variable to store the status code of the function */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
  /* This variable stores the time value at the start. */
  VAR(uint32, AUTOMATIC) f_StartValue_u32;
  /* This variable stores elapsed time. */
  VAR(uint32, AUTOMATIC) f_ElapsedTime_u32;
  /* This variable stores timeout value. */
  VAR(uint32, AUTOMATIC) f_Timeout_u32;
  /* This variable calculate input timeout value. */
  VAR(uint32, AUTOMATIC) f_InputTimeout_u32;
  /* This variable used to store receiver is ready to receive data or not. */
  VAR(boolean, AUTOMATIC) f_RxReady_bool;
 
  /* Get base address of UART channel. */
  f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[p_Channel_u8]->HwChannel_en];
  /* Init value. */
  f_RxReady_bool = UART_FALSE;
  f_InputTimeout_u32 = UART_DRV_TIMEOUT_DURATION_TICK(p_Timeout_u32);
  f_ElapsedTime_u32 = UART_U32_DAT_0;
  f_StartValue_u32 = UART_U32_DAT_0;
  f_Timeout_u32 = UART_U32_DAT_0;
 
  SchM_Enter_Uart_UART_EXCLUSIVE_AREA_03();
  /* Check if receiver is in busy state or not. */
  if (UART_TRUE != Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool) {
    Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool      = UART_TRUE;
    Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_BUSY;
    f_RxReady_bool = UART_TRUE;
  } else {
    Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_BUSY;
  }
  SchM_Exit_Uart_UART_EXCLUSIVE_AREA_03();
 
  if (UART_TRUE == f_RxReady_bool) {
    Uart_l_StateStructure_aa[p_Channel_u8].RxBuffer_ptr     = p_DataBuffer_ptr;
    Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32       = p_BufferSize_u32;
    /* Check UART receiver operation. */
    f_RxEnValue_u16 = UART_RD_REG_U16(f_BaseAddress_ptr->SE & UART_SE_RECEIVE_CHANNEL_MSK);
 
    /* Enable receiver if current status is disabled */
    if (UART_U32_DAT_0 == f_RxEnValue_u16) {
      Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, UART_TRUE);
    } else {
      /* Do nothing */
    }
    /* Get current counter. */
    (void)GetCounterValue(UART_OS_COUNTER_ID, &f_StartValue_u32);
 
    do {
      /* Wait for the BFF flag to be reset or until a timeout occurs. */
      f_DrvStatus_en = Uart_HwWaitStatus(p_Channel_u8, UART_RECEIVE, UART_FLAG_BFF, UART_TRUE);
 
      if (UART_STATUS_SUCCESS == f_DrvStatus_en) {
        /* If BFF flag is set start receive data. */
        Uart_HwSyncReceive(p_Channel_u8);
      } else {
        /* Do nothing. */
      }
 
      /* Get elapsed time. */
      (void)GetElapsedValue(UART_OS_COUNTER_ID, &f_StartValue_u32, &f_ElapsedTime_u32);
      f_Timeout_u32 += f_ElapsedTime_u32;
 
      if (f_InputTimeout_u32 <= f_Timeout_u32) {
        /* Change status of receiver to timeout. */
        Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_TIMEOUT;
 
      } else {
        /* Do nothing */
      }
 
    } while ((UART_U32_DAT_0 < Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32) && \
             (UART_STATUS_TIMEOUT != Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en) && \
             (UART_FALSE != Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool));
 
    if (Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en == UART_STATUS_TIMEOUT) {
      /* Callback error notification function. */
      Uart_l_ChCfg_aa[p_Channel_u8]->ErrNotification_ptr();
    } else {
      /* Do nothing. */
    }
 
    if (UART_TRUE == Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool) {
      /* Update the information of the module driver state */
      Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool = UART_FALSE;
      /* Disable the UART receiver */
      Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, FALSE);
    } else {
      /* Do nothing */
    }
 
  } else {
    /* Do nothing. */
  }
 
  /* Convert status. */
  f_ChStatus_en = Uart_DrvConvertStatus(Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en);
 
  /* Return the status of this function. */
  return f_ChStatus_en;
}
 
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
 *
 */
FUNC(void, UART_CODE_SLOW) Uart_DrvGetBaudrate(VAR(uint8, AUTOMATIC) p_Channel_u8,
                                              P2VAR(uint32, AUTOMATIC, UART_APPL_DATA) p_Baudrate_ptr,
                                              VAR(uint32, AUTOMATIC) p_ClockFrequency_u32) {
  /* Access hardware to get value from register and calculate current baudrate of the UART channel. */
  Uart_HwGetBaudrate(p_Channel_u8, p_Baudrate_ptr, p_ClockFrequency_u32);
}
#endif /* (STD_ON == UART_GET_BAUDRATE_API) */
 
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
FUNC(Std_ReturnType, UART_CODE_SLOW) Uart_DrvSetBaudrate(VAR(uint8, AUTOMATIC) p_Channel_u8, VAR(Uart_BaudrateType, AUTOMATIC) p_Baudrate_en) {
  /* Variable to store the driver status of the function. */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
  /* Variable to store return value of this function. */
  VAR(Std_ReturnType, AUTOMATIC) f_RetVal_u8;
 
  /* Init value. */
  f_RetVal_u8 = E_NOT_OK;
 
  SchM_Enter_Uart_UART_EXCLUSIVE_AREA_05();
 
  /* Access hardware to set baudrate for UART channel. */
  f_DrvStatus_en = Uart_HwSetBaudrate(p_Channel_u8, Uart_l_ChCfg_aa[p_Channel_u8], p_Baudrate_en);
 
  SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05();
 
  /* Check if setting the baudrate is successful. */
  if (UART_STATUS_SUCCESS == f_DrvStatus_en) {
    /* Change return value to E_OK. */
    f_RetVal_u8 = E_OK;
 
  } else {
    /* Do nothing */
  }
 
  /* Return status of this function. */
  return f_RetVal_u8;
}
 
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
FUNC(void, UART_CODE_SLOW) Uart_DrvAbort(VAR(uint8, AUTOMATIC) p_Channel_u8, VAR(Uart_DataDirectionType, AUTOMATIC) p_Direction_en) {
  SchM_Enter_Uart_UART_EXCLUSIVE_AREA_06();
  /* Check if the data direction is send and the sending status is busy*/
  if ((UART_SEND == p_Direction_en) && (UART_TRUE == Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool)) {
    /* Set the status to aborted */
    Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en = UART_STATUS_ABORTED;
    /* Update the information of the module driver state */
    Uart_l_StateStructure_aa[p_Channel_u8].TxBusy_bool = UART_FALSE;
 
  } else if ((UART_RECEIVE == p_Direction_en) && (UART_TRUE == Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool)) {
    /* Set the status to aborted */
    Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en = UART_STATUS_ABORTED;
    /* Disable receiver */
    Uart_HwFuncCmd(p_Channel_u8, UART_RECEIVE, UART_FALSE);
    /* Update the information of the module driver state */
    Uart_l_StateStructure_aa[p_Channel_u8].RxBusy_bool = UART_FALSE;
 
  } else {
    /* Do nothing. */
  }
  SchM_Exit_Uart_UART_EXCLUSIVE_AREA_06();
}
 
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
                                                        VAR(Uart_DataDirectionType, AUTOMATIC) p_Direction_en) {
  /* This variable used to store UART channel status. */
  VAR(Uart_StatusType, AUTOMATIC) f_ChStatus_en;
  /* This variable used to store UART channel driver status of this layer. */
  VAR(Uart_DrvStatusType, AUTOMATIC) f_DrvStatus_en;
 
  /* Init UART channel driver status. */
  f_DrvStatus_en = UART_STATUS_ERROR;
  /* Check if the data direction is send. */
  if (UART_SEND == p_Direction_en) {
    /* Get the send status of the UART channel */
    f_DrvStatus_en = Uart_l_StateStructure_aa[p_Channel_u8].SendStatus_en;
 
    if (NULL_PTR != p_BytesTransaction_ptr) {
      /* Set the number of bytes remaining for transmission */
      *p_BytesTransaction_ptr = Uart_l_StateStructure_aa[p_Channel_u8].TxSize_u32;
    } else {
      /* Do nothing */
    }
 
  } else if (UART_RECEIVE == p_Direction_en) {
    /* Get the send status of the UART channel */
    f_DrvStatus_en = Uart_l_StateStructure_aa[p_Channel_u8].ReceiveStatus_en;
 
    if (NULL_PTR != p_BytesTransaction_ptr) {
      /* Set the number of bytes remaining for reception */
      *p_BytesTransaction_ptr = Uart_l_StateStructure_aa[p_Channel_u8].RxSize_u32;
    } else {
      /* Do nothing */
    }
 
  } else {
    /* Do nothing */
  }
 
  /* Convert status. */
  f_ChStatus_en = Uart_DrvConvertStatus(f_DrvStatus_en);
 
  /* Return UART channel status. */
  return f_ChStatus_en;
}
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
FUNC(void, UART_CODE_FAST) Uart_DrvTxIrqHandler(VAR(uint8, AUTOMATIC) p_HwChannel_u8) {
  /* Temp variable used to loop through UART configuration sets. */
  VAR(uint8, AUTOMATIC) f_Index_u8;
  /* This variable used to store channel index. */
  VAR(uint8, AUTOMATIC) f_Channel_u8;
 
  /* Loop all configuration sets to get channel index. */
  for (f_Index_u8 = UART_U8_DAT_0; f_Index_u8 < UART_CH_MAX_CONFIG; f_Index_u8++) {
 
    if (p_HwChannel_u8 == (uint8)Uart_l_ChCfg_aa[f_Index_u8]->HwChannel_en) {
      f_Channel_u8 = f_Index_u8;
      break;
    }  else {
      /* Do nothing */
    }
 
  }
 
  /* If not found the Channel */
  if (UART_CH_MAX_CONFIG == f_Index_u8) {
    /* Do nothing */
  } else {
 
    /* Check if this is not the last frame to transmit. */
    if (UART_U32_DAT_0 < Uart_l_StateStructure_aa[f_Channel_u8].TxSize_u32) {
      /* Transmit the data */
      Uart_HwWriteData(f_Channel_u8);
    } else {
      /* If this is the last frame, finishing the process of transmitting data. */
      Uart_HwCompleteSendData(f_Channel_u8);
      /* Invoke callback */
      Uart_HwCallNotification(f_Channel_u8, UART_SEND);
    }
  }
}
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
FUNC(void, UART_CODE_FAST) Uart_DrvRxIrqHandler(VAR(uint8, AUTOMATIC) p_HwChannel_u8) {
  /* This variable used to store SSR register value. */
  VAR(uint16, AUTOMATIC) f_SSRValue_u16;
  /* Temp variable used to loop through UART configuration sets. */
  VAR(uint8, AUTOMATIC) f_Index_u8;
  /* This variable used to store channel index. */
  VAR(uint8, AUTOMATIC) f_Channel_u8;
  /* This variable used to store base address of the corresponding UART channel. */
  P2VAR(Uart_DrvRegType, AUTOMATIC, UART_APPL_DATA) f_BaseAddress_ptr;
  /* This variable used to store dummy data when error occurs. */
  VAR(uint16, AUTOMATIC) f_DummyData_u16;
 
  /* Loop all configuration sets to get channel index. */
  for (f_Index_u8 = UART_U8_DAT_0; f_Index_u8 < UART_CH_MAX_CONFIG; f_Index_u8++) {
    if (p_HwChannel_u8 == (uint8)Uart_l_ChCfg_aa[f_Index_u8]->HwChannel_en) {
      f_Channel_u8 = f_Index_u8;
      break;
    }  else {
      /* Do nothing */
    }
  }
 
  /* If not found the Channel */
  if (UART_CH_MAX_CONFIG == f_Index_u8) {
    /* Do nothing */
  } else {
    /* Get base address of UART channel. */
    f_BaseAddress_ptr = Uart_l_DrvBaseAddr_aa[Uart_l_ChCfg_aa[f_Channel_u8]->HwChannel_en];
 
    /* Get error flag of SSR register. */
    f_SSRValue_u16 = (f_BaseAddress_ptr->SSRm1 & UART_ERROR_FLAG);
 
    /* Check if any error occurs. */
    if (UART_U16_DAT_0 != f_SSRValue_u16) {
      /* Dummy read to clear error data. */
      f_DummyData_u16 = f_BaseAddress_ptr->SDRm1;
      (void)f_DummyData_u16;
      /* Error handler. */
      Uart_HwErrorHandler(f_Channel_u8, f_SSRValue_u16);
 
    } else {
      Uart_HwReadData(f_Channel_u8);
 
      /* Finish reception if this was the last byte received */
      if(UART_U32_DAT_0 == Uart_l_StateStructure_aa[f_Channel_u8].RxSize_u32) {
        /* Finishing the process of receiving data. */
        Uart_HwCompleteReceiveData(f_Channel_u8);
        /* Invoke callback */
        Uart_HwCallNotification(f_Channel_u8, UART_RECEIVE);
 
      } else {
        /* Do nothing */
      }
    }
  }
}
#endif /* ((UART_SCI0_ISR_RX_USED == STD_ON) || (UART_SCI1_ISR_RX_USED == STD_ON) || (UART_SCI2_ISR_RX_USED == STD_ON) || (UART_SCI3_ISR_RX_USED == STD_ON)) */
 
#define UART_STOP_SEC_CODE_FAST
#include "Uart_MemMap.h"
 
/** @} end of group Public_FunctionDefinition */
#ifdef __cplusplus
}
#endif
/** @} end of group Uart */
 