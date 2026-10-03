/**************************************************************************************************************************************************************/
/**
 * @file      : Can_Irq.c
 * @brief     : Can_Irq source file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
/**
 * @addtogroup Can
 * @brief Autosar R23-11 Can_Irq source code
 * @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "Can.h"
#include "Mcal.h"
 
/** @defgroup Private_MacroDefinition
 *  @{
 */
 
#define CAN_IRQ_VENDOR_ID_C                   0x0000U
#define CAN_IRQ_SW_MAJOR_VERSION_C            0x01U
#define CAN_IRQ_SW_MINOR_VERSION_C            0x00U
#define CAN_IRQ_SW_PATCH_VERSION_C            0x00U
#define CAN_IRQ_AR_RELEASE_MAJOR_VERSION_C    0x04U
#define CAN_IRQ_AR_RELEASE_MINOR_VERSION_C    0x09U
#define CAN_IRQ_AR_RELEASE_REVISION_VERSION_C 0x00U
 
/* Check if current file and Can.h are the same Vendor Id */
#if (CAN_IRQ_VENDOR_ID_C != CAN_VENDOR_ID_H)
#error "Vendor Id of Can_Irq.c and Can.h are different"
#endif
 
/* Check if current file and Can.h are the same Software version */
#if ((CAN_IRQ_SW_MAJOR_VERSION_C != CAN_SW_MAJOR_VERSION_H) || \
     (CAN_IRQ_SW_MINOR_VERSION_C != CAN_SW_MINOR_VERSION_H) || \
     (CAN_IRQ_SW_PATCH_VERSION_C != CAN_SW_PATCH_VERSION_H))
#error "Software Version Numbers of Can_Irq.c and Can.h are different"
#endif
 
/* Check if current file and Can.h are the same Software version */
#if ((CAN_IRQ_AR_RELEASE_MAJOR_VERSION_C != CAN_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_IRQ_AR_RELEASE_MINOR_VERSION_C != CAN_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_IRQ_AR_RELEASE_REVISION_VERSION_C != CAN_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of Can_Irq.c and Can.h are different"
#endif
 
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Mcal.h are the same Software version */
#if ((CAN_IRQ_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_IRQ_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of Can_Irq.c and Mcal.h are different"
#endif
#endif
 
/**
 * @brief Controller offset.
 */
#define CAN_CONTROLLER0_OFFSET                (0U)
#define CAN_CONTROLLER1_OFFSET                (1U)
 
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
#if ((STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || \
     (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
ISR(Can_Controller0TxIsr);
ISR(Can_Controller1TxIsr);
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_RX_INTERRUPT_PROCESSING)
ISR(Can_Controller0RxIsr);
ISR(Can_Controller1RxIsr);
#endif /* STD_ON == CAN_RX_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || (STD_ON == CAN_SECURITY_EVENT_REPORTING) || \
     (STD_ON == CAN_ECC_DETECTION))
ISR(Can_Controller0OrIsr);
ISR(Can_Controller1OrIsr);
#endif /*(STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || (STD_ON == CAN_SECURITY_EVENT_REPORTING) || \
     (STD_ON == CAN_ECC_DETECTION) */
 
#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"
#endif /* ((STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || \
          (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION)) */
/** @} end of group Public_FunctionDeclaration */
 
/** @defgroup Public_FunctionDefinition
 *  @{
 */
#if ((STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || \
     (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
/**
 * @brief        This function is the Interrupt handler of multiplex transmit (STB) in CAN controller 0.
 *
 * @param[in]    None.
 *
 * @return       None.
 */
ISR(Can_Controller0TxIsr) {
 
  Can_TxIsrHandler(CAN_CONTROLLER0_OFFSET);
 
  EXIT_INTERRUPT();
}
 
/**
 * @brief        This function is the Interrupt handler of multiplex transmit (STB) in CAN controller 1.
 *
 * @param[in]    None.
 *
 * @return       None.
 */
ISR(Can_Controller1TxIsr) {
 
  Can_TxIsrHandler(CAN_CONTROLLER1_OFFSET);
 
  EXIT_INTERRUPT();
}
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_RX_INTERRUPT_PROCESSING)
/**
 * @brief        This function is the Interrupt handler of receive in CAN controller 0.
 *
 * @param[in]    None.
 *
 * @return       None.
 */
ISR(Can_Controller0RxIsr) {
 
  Can_RxIsrHandler(CAN_CONTROLLER0_OFFSET);
 
  EXIT_INTERRUPT();
}
 
/**
 * @brief        This function is the Interrupt handler of receive in CAN controller 1.
 *
 * @param[in]    None.
 *
 * @return       None.
 */
ISR(Can_Controller1RxIsr) {
 
  Can_RxIsrHandler(CAN_CONTROLLER1_OFFSET);
 
  EXIT_INTERRUPT();
}
#endif /* STD_ON == CAN_RX_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || (STD_ON == CAN_SECURITY_EVENT_REPORTING) || \
     (STD_ON == CAN_ECC_DETECTION))
/**
 * @brief        Interrupt handler for single transmit PTB, BusOff events, and error conditions on CAN controller 0.
 *
 * @param[in]    None.
 *
 * @return       None.
 */
ISR(Can_Controller0OrIsr) {
#if (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING)
  /* Handle BusOff Event controller0 if occurs */
  Can_BusOffIsrHandler(CAN_CONTROLLER0_OFFSET);
#endif /* STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
  /* Handle Error condition controller0 if occurs */
  Can_ErrorIsrHandler(CAN_CONTROLLER0_OFFSET);
#endif /* (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION)*/
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
  /* Handle PTB transmit successful controller0 if occurs */
  Can_TxIsrHandler(CAN_CONTROLLER0_OFFSET);
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
  EXIT_INTERRUPT();
}
 
/**
 * @brief        Interrupt handler for single transmit PTB, BusOff events, and error conditions on CAN controller 1.
 *
 * @param[in]    None.
 *
 * @return       None.
 */
ISR(Can_Controller1OrIsr) {
#if (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING)
  /* Handle BusOff Event controller1 if occurs */
  Can_BusOffIsrHandler(CAN_CONTROLLER1_OFFSET);
#endif /* STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
  /* Handle Error condition controller1 if occurs */
  Can_ErrorIsrHandler(CAN_CONTROLLER1_OFFSET);
#endif /* (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION)*/
  /* Handle PTB transmit successful controller1 if occurs */
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
  Can_TxIsrHandler(CAN_CONTROLLER1_OFFSET);
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
 
  EXIT_INTERRUPT();
}
#endif /* (STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || (STD_ON == CAN_SECURITY_EVENT_REPORTING) || \
          (STD_ON == CAN_ECC_DETECTION) */
 
#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"
 
#endif /* ((STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || \
          (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION)) */
/** @} end of group Public_FunctionDefinition */
#ifdef __cplusplus
}
#endif
 
 
/** @} end of group Can */
 