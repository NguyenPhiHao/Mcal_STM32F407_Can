/**************************************************************************************************************************************************************/
/**
 * @file      : CDD_Uart_Irq.c
 * @brief     : CDD_Uart_Irq source file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
/** @addtogroup Uart
 *  @brief Autosar R23-11 CDD_Uart_Irq source code
 *  @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "CDD_Uart_Drv.h"
#include "Mcal.h"
 
 
/** @defgroup Private_MacroDefinition
 *  @{
 */
#define UART_IRQ_VENDOR_ID_C                   0x0000U
#define UART_IRQ_SW_MAJOR_VERSION_C            0x01U
#define UART_IRQ_SW_MINOR_VERSION_C            0x00U
#define UART_IRQ_SW_PATCH_VERSION_C            0x00U
#define UART_IRQ_AR_RELEASE_MAJOR_VERSION_C    0x04U
#define UART_IRQ_AR_RELEASE_MINOR_VERSION_C    0x09U
#define UART_IRQ_AR_RELEASE_REVISION_VERSION_C 0x00U
 
/* Check if current file and CDD_Uart_Drv.h are the same Vendor Id */
#if (UART_IRQ_VENDOR_ID_C != UART_DRV_VENDOR_ID_H)
#error "Vendor Id of CDD_Uart_Irq.c and CDD_Uart_Drv.h are different"
#endif
 
/* Check if current file and CDD_Uart_Drv.h are the same Software version. */
#if ((UART_IRQ_SW_MAJOR_VERSION_C != UART_DRV_SW_MAJOR_VERSION_H) || \
     (UART_IRQ_SW_MINOR_VERSION_C != UART_DRV_SW_MINOR_VERSION_H) || \
     (UART_IRQ_SW_PATCH_VERSION_C != UART_DRV_SW_PATCH_VERSION_H))
#error "Software Version Numbers of CDD_Uart_Irq.c and CDD_Uart_Drv.h are different."
#endif
 
/* Check if current file and CDD_Uart_Drv.h are the same AUTOSAR version. */
#if ((UART_IRQ_AR_RELEASE_MAJOR_VERSION_C    != UART_DRV_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_IRQ_AR_RELEASE_MINOR_VERSION_C    != UART_DRV_AR_RELEASE_MINOR_VERSION_H) || \
     (UART_IRQ_AR_RELEASE_REVISION_VERSION_C != UART_DRV_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart_Irq.c and CDD_Uart_Drv.h are different."
#endif
 
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Mcal.h are the same AUTOSAR version. */
#if ((UART_IRQ_AR_RELEASE_MAJOR_VERSION_C    != MCAL_AR_RELEASE_MAJOR_VERSION_H) || \
     (UART_IRQ_AR_RELEASE_MINOR_VERSION_C    != MCAL_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of CDD_Uart_Irq.c and Mcal.h are different."
#endif
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
 
/** @} end of group Private_VariableDefinition */
 
/** @defgroup Private_FunctionDeclaration
 *  @{
 */
 
/** @} end of group Private_FunctionDeclaration */
 
/** @defgroup Private_FunctionDefinition
 *  @{
 */
/** @} end of group Private_FunctionDefinition */
 
/** @defgroup Public_FunctionDeclaration
 *  @{
 */
#define UART_START_SEC_CODE_FAST
#include "Uart_MemMap.h"
 
#if (STD_ON == UART_SCI0_ISR_USED)
#if (STD_ON == UART_SCI0_ISR_TX_USED)
ISR(Uart_Channel0TxIsr);
#endif /* (STD_ON == UART_SCI0_ISR_TX_USED) */
 
#if (STD_ON == UART_SCI0_ISR_RX_USED)
ISR(Uart_Channel0RxIsr);
#endif /* (STD_ON == UART_SCI0_ISR_RX_USED) */
#endif /* (STD_ON == UART_SCI0_ISR_USED) */
 
#if (STD_ON == UART_SCI1_ISR_USED)
#if (STD_ON == UART_SCI1_ISR_TX_USED)
ISR(Uart_Channel1TxIsr);
#endif /* (STD_ON == UART_SCI1_ISR_TX_USED) */
 
#if (STD_ON == UART_SCI1_ISR_RX_USED)
ISR(Uart_Channel1RxIsr);
#endif /* (STD_ON == UART_SCI1_ISR_RX_USED) */
#endif /* (STD_ON == UART_SCI1_ISR_USED) */
 
#if (STD_ON == UART_SCI2_ISR_USED)
#if (STD_ON == UART_SCI2_ISR_TX_USED)
ISR(Uart_Channel2TxIsr);
#endif /* (STD_ON == UART_SCI2_ISR_TX_USED) */
 
#if (STD_ON == UART_SCI2_ISR_RX_USED)
ISR(Uart_Channel2RxIsr);
#endif /* (STD_ON == UART_SCI2_ISR_RX_USED) */
#endif /* (STD_ON == UART_SCI2_ISR_USED) */
 
#if (STD_ON == UART_SCI3_ISR_USED)
#if (STD_ON == UART_SCI3_ISR_TX_USED)
ISR(Uart_Channel3TxIsr);
#endif /* (STD_ON == UART_SCI3_ISR_TX_USED) */
 
#if (STD_ON == UART_SCI3_ISR_RX_USED)
ISR(Uart_Channel3RxIsr);
#endif /* (STD_ON == UART_SCI3_ISR_RX_USED) */
#endif /* (STD_ON == UART_SCI3_ISR_USED) */
 
#define UART_STOP_SEC_CODE_FAST
#include "Uart_MemMap.h"
/** @} end of group Public_FunctionDeclaration */
 
/** @defgroup Public_FunctionDefinition
 *  @{
 */
#define UART_START_SEC_CODE_FAST
#include "Uart_MemMap.h"
 
#if (STD_ON == UART_SCI0_ISR_USED)
 
#if (STD_ON == UART_SCI0_ISR_TX_USED)
/**
 * @brief     This function used for process the transmission UART ISR for SCI0.
 *
 * @param[in] void.
 *
 * @return    void.
 */
 
ISR(Uart_Channel0TxIsr)
{
  Uart_DrvTxIrqHandler(UART_U8_DAT_0);
  EXIT_INTERRUPT();
}
 
#endif /* (STD_ON == UART_SCI0_ISR_TX_USED) */
 
#if (STD_ON == UART_SCI0_ISR_RX_USED)
/**
 * @brief     This function used for process the reception UART ISR for SCI0.
 *
 * @param[in] void.
 *
 * @return    void.
 */
ISR(Uart_Channel0RxIsr)
{
  Uart_DrvRxIrqHandler(UART_U8_DAT_0);
  EXIT_INTERRUPT();
}
#endif /* (STD_ON == UART_SCI0_ISR_TX_USED) */
#endif /* (STD_ON == UART_SCI0_ISR_USED) */
 
#if (STD_ON == UART_SCI1_ISR_USED)
#if (STD_ON == UART_SCI1_ISR_TX_USED)
/**
 * @brief     This function used for process the transmission UART ISR for SCI1.
 *
 * @param[in] void.
 *
 * @return    void.
 */
ISR(Uart_Channel1TxIsr)
{
  Uart_DrvTxIrqHandler(UART_U8_DAT_1);
  EXIT_INTERRUPT();
}
 
#endif /* (STD_ON == UART_SCI1_ISR_TX_USED) */
 
#if (STD_ON == UART_SCI1_ISR_RX_USED)
/**
 * @brief     This function used for process the reception UART ISR for SCI1.
 *
 * @param[in] void.
 *
 * @return    void.
 */
ISR(Uart_Channel1RxIsr)
{
  Uart_DrvRxIrqHandler(UART_U8_DAT_1);
  EXIT_INTERRUPT();
}
#endif /* (STD_ON == UART_SCI1_ISR_TX_USED) */
#endif /* (STD_ON == UART_SCI1_ISR_USED) */
 
#if (STD_ON == UART_SCI2_ISR_USED)
#if (STD_ON == UART_SCI2_ISR_TX_USED)
/**
 * @brief     This function used for process the transmission UART ISR for SCI2.
 *
 * @param[in] void.
 *
 * @return    void.
 */
ISR(Uart_Channel2TxIsr)
{
  Uart_DrvTxIrqHandler(UART_U8_DAT_2);
  EXIT_INTERRUPT();
}
#endif /* (STD_ON == UART_SCI2_ISR_TX_USED) */
 
#if (STD_ON == UART_SCI2_ISR_RX_USED)
/**
 * @brief     This function used for process the reception UART ISR for SCI2.
 *
 * @param[in] void.
 *
 * @return    void.
 */
ISR(Uart_Channel2RxIsr)
{
  Uart_DrvRxIrqHandler(UART_U8_DAT_2);
  EXIT_INTERRUPT();
}
#endif /* (STD_ON == UART_SCI2_ISR_TX_USED) */
#endif /* (STD_ON == UART_SCI2_ISR_USED) */
 
#if (STD_ON == UART_SCI3_ISR_USED)
#if (STD_ON == UART_SCI3_ISR_TX_USED)
/**
 * @brief     This function used for process the transmission UART ISR for SCI3.
 *
 * @param[in] void.
 *
 * @return    void.
 */
ISR(Uart_Channel3TxIsr)
{
  Uart_DrvTxIrqHandler(UART_U8_DAT_3);
  EXIT_INTERRUPT();
}
#endif /* (STD_ON == UART_SCI3_ISR_TX_USED) */
 
#if (STD_ON == UART_SCI3_ISR_RX_USED)
/**
 * @brief     This function used for process the reception UART ISR for SCI3.
 *
 * @param[in] void.
 *
 * @return    void.
 */
ISR(Uart_Channel3RxIsr)
{
  Uart_DrvRxIrqHandler(UART_U8_DAT_3);
  EXIT_INTERRUPT();
}
#endif /* (STD_ON == UART_SCI3_ISR_TX_USED) */
#endif /* (STD_ON == UART_SCI3_ISR_USED) */
 
#define UART_STOP_SEC_CODE_FAST
#include "Uart_MemMap.h"
/** @} end of group Public_FunctionDefinition */
 
#ifdef __cplusplus
}
#endif
 
/** @} end of group Uart */
 