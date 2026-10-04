/**************************************************************************************************************************************************************/
/**
 * @file      : Can_Drv.h
 * @brief     : Can_Drv header file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
#ifndef CAN_DRV_H
#define CAN_DRV_H
 
/**
 * @addtogroup Can
 * @brief Autosar R23-11 Can_Drv header
 * @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "Can_Types.h"
 
/** @defgroup Public_MacroDefinition
 *  @{
 */
#define CAN_DRV_VENDOR_ID_H                   0x0000U
#define CAN_DRV_MODULE_ID_H                   0x0050U
#define CAN_DRV_SW_MAJOR_VERSION_H            0x01U
#define CAN_DRV_SW_MINOR_VERSION_H            0x00U
#define CAN_DRV_SW_PATCH_VERSION_H            0x00U
#define CAN_DRV_AR_RELEASE_MAJOR_VERSION_H    0x04U
#define CAN_DRV_AR_RELEASE_MINOR_VERSION_H    0x09U
#define CAN_DRV_AR_RELEASE_REVISION_VERSION_H 0x00U
 
/* Check if current file Can_Drv.h and header file Can_Types.h are of the same vendor */
#if (CAN_DRV_VENDOR_ID_H != CAN_TYPES_VENDOR_ID_H)
#error "Can_Drv.h and Can_Types.h have different vendor ids"
#endif
 
/* Check if current file and Can_Types.h are the same Module Id. */
#if (CAN_DRV_MODULE_ID_H != CAN_TYPES_MODULE_ID_H)
#error "Module ID Numbers of Can_Drv.h and Can_Types.h are different."
#endif
 
/* Check if current file Can_Drv.h and header file Can_Types.h are of the same Software version */
#if ((CAN_DRV_SW_MAJOR_VERSION_H != CAN_TYPES_SW_MAJOR_VERSION_H) || \
     (CAN_DRV_SW_MINOR_VERSION_H != CAN_TYPES_SW_MINOR_VERSION_H) || \
     (CAN_DRV_SW_PATCH_VERSION_H != CAN_TYPES_SW_PATCH_VERSION_H))
#error "Software Version Numbers of Can_Drv.h and Can_Types.h"
#endif
 
/* Check if current file Can_Drv.h and header file Can_Types.h are of the same Autosar version */
#if ((CAN_DRV_AR_RELEASE_MAJOR_VERSION_H    != CAN_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_DRV_AR_RELEASE_MINOR_VERSION_H    != CAN_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_DRV_AR_RELEASE_REVISION_VERSION_H != CAN_TYPES_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of Can_Drv.h and Can_Types.h"
#endif
 
#if (STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT)
 
/**
 * @brief Define the depth of multiple transmit
 */
#define CAN_STB_FIFO_DEPTH ((uint8)0x03U)
 
#endif /* STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT */
 
/** @} end of Public_MacroDefinition */
 
/** @defgroup Public_TypeDefinition
 *  @{
 */
 
/** @} end of group Public_TypeDefinition */
 
/** @defgroup Global_VariableDeclaration
 *  @{
 */
 
/** @} end of group Global_VariableDeclaration */
 
/** @defgroup Public_FunctionDeclaration
 *  @{
 */
#define CAN_START_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
/**
 * @brief        This function initializes the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Channel initialized success.
 * @retval       E_NOT_OK: Channel initialized failed.
 *
 * @Design       SDD_CAN_068, SDD_CAN_028, SDD_CAN_029
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvInit(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
 
/**
 * @brief        This function changes the setting of the CAN bit timing.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[in]    p_BaudrateCfg_ptr: Pointer to the controller baudrate configuration set.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Channel Change Baudrate success.
 * @retval       E_NOT_OK: Channel Change Baudrate failed.
 *
 * @Design       SDD_CAN_069
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvChangeBaudrate(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                          P2CONST(Can_BaudrateCfgType, AUTOMATIC, CAN_APPL_DATA) p_BaudrateCfg_ptr);
 
/**
 * @brief        This function disables the interrupt for the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_070, SDD_CAN_028, SDD_CAN_035
 */
FUNC(void, CAN_CODE_SLOW) Can_DrvDisControllerInt(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
 
/**
 * @brief        This function enables the interrupt for the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_071, SDD_CAN_028, SDD_CAN_035
 */
FUNC(void, CAN_CODE_SLOW) Can_DrvEnaControllerInt(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
 
#if (STD_ON == CAN_WAKEUP_SUPPORT)
/**
 * @brief        This function checks if a wakeup event was successfully detected by the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Wakeup source found from CAN controller.
 * @retval       E_NOT_OK: No wakeup source found.
 *
 * @Design       SDD_CAN_072
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvCheckWakeup(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
#endif /* STD_ON == CAN_WAKEUP_SUPPORT */
 
/**
 * @brief        This function gets the error state of the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[out]   p_ErrorState_ptr: Pointer to get the controller Error state.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Get Error state success.
 * @retval       E_NOT_OK: Get Error state failed.
 *
 * @Design       SDD_CAN_073, SDD_CAN_028
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvGetControllerErrorState(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                                   P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) p_ErrorState_ptr);
 
/**
 * @brief        This function gets the Rx error counter of the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[out]   p_RxErrCnt_ptr: Pointer to get the Rx Error counter.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Get Rx Error counter success.
 * @retval       E_NOT_OK: Get Rx Error counter failed.
 *
 * @Design       SDD_CAN_074, SDD_CAN_028
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvGetRxErrCnt(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                       P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) p_RxErrCnt_ptr);
 
/**
 * @brief        This function gets the Tx error counter of the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[out]   p_TxErrCnt_ptr: Pointer to get the Tx Error counter.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Get Tx Error counter success.
 * @retval       E_NOT_OK: Get Tx Error counter failed.
 *
 * @Design       SDD_CAN_075, SDD_CAN_028
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvGetTxErrCnt(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                       P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) p_TxErrCnt_ptr);
 
/**
 * @brief        This function stops the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Stop the CAN controller success.
 * @retval       E_NOT_OK: Stop the CAN controller failed.
 *
 * @Design       SDD_CAN_076, SDD_CAN_028
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvStopController(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
 
/**
 * @brief        This function starts the CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[in]    p_DisableIrqCnt_u8: Counter for the number of interrupt‑disable requests.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Start the CAN controller success.
 * @retval       E_NOT_OK: Start the CAN controller failed.
 *
 * @Design       SDD_CAN_077, SDD_CAN_028
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvStartController(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                           CONST(uint8, AUTOMATIC) p_DisableIrqCnt_u8);
 
/**
 * @brief        This function processes transmitting the message to the CAN bus.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[in]    p_HthHwObject_ptr: Pointer to hardware transmit object.
 * @param[in]    p_PduInfo_ptr: Pointer to the information of Loopback test.
 * @param[in]    p_HthIdx_u8: Transmit buffer's HTH index.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: CAN controller transmit success.
 * @retval       E_NOT_OK: CAN controller is Busy, trasnmirt failed.
 *
 * @Design       SDD_CAN_078
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvTransmit(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                    P2CONST(Can_HthHwObjCfgType, AUTOMATIC, CAN_APPL_DATA) p_HthHwObject_ptr,
                                                    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr,
                                                    CONST(uint8, AUTOMATIC) p_HthIdx_u8);
 
/**
 * @brief        This function processes the polling of Tx confirmation.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[in]    p_PduId_ptr: Identifier of a PDU.
 *
 * @return       uint8.
 * @retval       [0-255]: Number of Tx confirmation message.
 *
 * @Design       SDD_CAN_079, SDD_CAN_028, SDD_CAN_030, SDD_CAN_031, SDD_CAN_032, SDD_CAN_033, SDD_CAN_034, SDD_CAN_039, SDD_CAN_040, SDD_CAN_042
 */
FUNC(uint8, CAN_CODE_SLOW) Can_DrvProcessTxMsg(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                               P2VAR(PduIdType, AUTOMATIC, CAN_APPL_DATA) p_PduId_ptr);
 
/**
 * @brief        This function processes the polling of Rx indication.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       boolean.
 * @retval       TRUE: The Rx buffer is overflow.
 * @retval       FALSE: The Rx buffer is not overflow.
 *
 * @Design       SDD_CAN_080, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_FAST) Can_DrvRxOverFlow(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
 
/**
 * @brief        This function checks if the Rx buffer is empty or not.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       boolean.
 * @retval       TRUE: The Rx buffer is empty.
 * @retval       FALSE: The Rx buffer is not empty.
 *
 * @Design       SDD_CAN_081, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_SLOW) Can_DrvRxMsgIsEmpty(CONST(uint8, TYPEDEF) p_CtrlOffset_u8);
 
/**
 * @brief        This function gets the information of the Rx buffer.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[out]   p_Mailbox_ptr: Pointer to get Can frame information.
 * @param[out]   p_PduInfo_ptr: Pointer to get Data of Rx Buffer.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_082, SDD_CAN_028, SDD_CAN_028, SDD_CAN_036, SDD_CAN_041
 */
FUNC(void, CAN_CODE_SLOW) Can_DrvGetRxInfo(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) p_CtrlCfg_ptr,
                                           P2VAR(Can_HwType, AUTOMATIC, CAN_APPL_DATA) p_Mailbox_ptr,
                                           P2VAR(PduInfoType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr);
 
/**
 * @brief        This function processes the CAN controller in BusOff state.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_083
 */
FUNC(void, CAN_CODE_SLOW) Can_DrvProcessBusOff(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
 
/**
 * @brief        This function checks if the CAN controller is in the BusOff state or not.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       boolean.
 * @retval       TRUE: The CAN controller is in state Bussoff
 * @retval       FALSE: The CAN controller is not in state Bussoff
 *
 * @Design       SDD_CAN_084, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_SLOW) Can_DrvBusOff(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) p_CtrlCfg_ptr);
 
/**
 * @brief        This function checks if the CAN controller is started or not.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       boolean.
 * @retval       TRUE: The CAN controller is in state start.
 * @retval       FALSE: The CAN controller is in state stop.
 *
 * @Design       SDD_CAN_085, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_SLOW) Can_ControllerStarted(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
 
#if (STD_ON == CAN_GLOBAL_TIME_SUPPORT)
/**
 * @brief        This function gets the current time of the CAN controller.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 * @param[in]    p_CtrlId_u8: Controller Controller Id.
 * @param[out]   p_TimeStamp_ptr: Pointer to the variable store current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Get current time success.
 * @retval       E_NOT_OK: Get current time failed.
 *
 * @Design       SDD_CAN_086, SDD_CAN_028
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvGetCurrentTime(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8,
                                                          CONST(uint8, AUTOMATIC) p_CtrlId_u8,
                                                          P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) p_TimeStamp_ptr);
 
/**
 * @brief        Processes the controller’s time information to maintain accurate timestamp or global time synchronization.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_xxx, SDD_CAN_xxx
 */
FUNC(void, CAN_CODE_SLOW) Can_DrvProcessCurrentTime(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
#endif /* STD_ON == CAN_GLOBAL_TIME_SUPPORT */
 
/**
 * @brief        This function enables recording of the timestamp for Tx messages.
 *
 * @param[in]    p_HthIdx_u8: Transmit buffer's HTH index.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_087, SDD_CAN_038
 */
FUNC(void, CAN_CODE_SLOW) Can_DrvEnableEgressTimeStamp(CONST(uint8, AUTOMATIC) p_HthIdx_u8);
 
/**
 * @brief        This function gets the transmit timestamp of the target HTH.
 *
 * @param[in]    p_TxPduId_u16: L-PDU handle of CAN L-PDU for which the time stamp shall be returned.
 * @param[in]    p_HthIdx_u8: Transmit buffer's HTH index.
 * @param[out]   p_TimeStamp_ptr: Pointer to the variable store current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Get Egress TimeStamp success.
 * @retval       E_NOT_OK: Get Egress TimeStamp failed.
 *
 * @Design       SDD_CAN_040, SDD_CAN_042, SDD_CAN_088
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvGetEgressTimeStamp(VAR(PduIdType, AUTOMATIC) p_TxPduId_u16,
                                                              CONST(uint8, AUTOMATIC) p_HthIdx_u8,
                                                              P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) p_TimeStamp_ptr);
 
/**
 * @brief        This function gets the receive timestamp of the target HTH.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 * @param[in]    p_HrhIdx_u8: Receive buffer's HRH index.
 * @param[out]   p_TimeStamp_ptr: Pointer to the variable store current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Get Ingress TimeStamp success.
 * @retval       E_NOT_OK: Get Ingress TimeStamp failed.
 *
 * @Design       SDD_CAN_089, SDD_CAN_041
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_DrvGetIngressTimeStamp(CONST(uint8, AUTOMATIC) p_CtrlId_u8,
                                                               CONST(uint8, AUTOMATIC) p_HrhIdx_u8,
                                                               P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) p_TimeStamp_ptr);
 
/**
 * @brief        This function performs a CAN controller loopback test to confirm the controller's ability to transmit and receive data correctly.
 *
 * @param[in]    p_CtrlCfg_ptr: Controller offset value.
 * @param[in]    p_PduInfo_ptr: Pointer to the information needed for Loopback test.
 * @param[in]    p_Mode_en: Loopback mode test type.
 * @param[in]    p_TimeoutMs_u32: Timeout value for Loopback test.
 *
 * @return       Can_LoopBackTestResultType.
 * @retval       CAN_LOOPBACK_PASS: Loopback test is pass.
 * @retval       CAN_LOOPBACK_TIMEOUT: Loopback test has timout error.
 * @retval       CAN_LOOPBACK_DATA_MISMATCH: Loopback test has data mismatch error.
 *
 * @Design       SDD_CAN_090, SDD_CAN_028
 */
FUNC(Can_LoopBackTestResultType, CAN_CODE_SLOW) Can_DrvLoopBackTest(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                                    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr,
                                                                    CONST(Can_LoopBackModeType, AUTOMATIC) p_Mode_en,
                                                                    CONST(uint32, AUTOMATIC) p_TimeoutMs_u32);
 
#define CAN_STOP_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
/**
 * @brief        This function get the controller's transmit interrupt flag.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       boolean.
 * @retval       TRUE: The CAN controller transmit interrupt flag is set
 * @retval       FALSE: The CAN controller transmit interrupt flag is not set
 *
 * @Design       SDD_CAN_107, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_FAST) Can_DrvIsTxIrqFlag(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
 
/**
 * @brief        This function clear interrupt flag for Controller transmission flag.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_091, SDD_CAN_028
 */
FUNC(void, CAN_CODE_FAST) Can_DrvClrTxIrqFlag(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_RX_INTERRUPT_PROCESSING)
/**
 * @brief        This function get the controller's reception interrupt flag.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       boolean.
 * @retval       TRUE: The CAN controller receive interrupt flag is set
 * @retval       FALSE: The CAN controller receive interrupt flag is not set
 *
 * @Design       SDD_CAN_108, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_FAST) Can_DrvIsRxIrqFlag(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
 
/**
 * @brief        This function clear interrupt flag for Controller reception flag.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_092, SDD_CAN_028
 */
FUNC(void, CAN_CODE_FAST) Can_DrvClrRxIrqFlag(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* STD_ON == CAN_RX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING)
/**
 * @brief        This function clear interrupt flag for Controller Busoff error flag.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_093, SDD_CAN_028
 */
FUNC(void, CAN_CODE_FAST) Can_DrvClrBusoffIrqFlag(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
/**
 * @brief        This function clear interrupt flag for Controller error flag.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_094, SDD_CAN_028
 */
FUNC(void, CAN_CODE_FAST) Can_DrvClrErrIrqFlag(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION) */
 
#if (STD_ON == CAN_SECURITY_EVENT_REPORTING)
/**
 * @brief        This function get the Passive error and Tx/Rx error counter of Controller.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 * @param[out]   p_RxErrCnt_ptr: Pointer to get Rx error counter.
 * @param[out]   p_TxErrCnt_ptr: Pointer to get Tx error counter.
 *
 * @return       boolean.
 * @retval       TRUE: The CAN controller has encountered Passive error
 * @retval       FALSE: The CAN controller has not encountered Passive error
 *
 * @Design       SDD_CAN_095, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_FAST) Can_DrvIsPassiveErr(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8,
                                                 P2VAR(uint16, AUTOMATIC, CAN_APPL_DATA) p_RxErrCnt_ptr,
                                                 P2VAR(uint16, AUTOMATIC, CAN_APPL_DATA) p_TxErrCnt_ptr);
 
/**
 * @brief        This function get the Arbitration Lost error of Controller.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       boolean.
 * @retval       TRUE: The CAN controller has encountered an Arbitration Lost error
 * @retval       FALSE: The CAN controller has not encountered an Arbitration Lost error
 *
 * @Design       SDD_CAN_096, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_FAST) Can_DrvIsArbitrationLost(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
 
/**
 * @brief        This function get the Overload error of Controller.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       boolean.
 * @retval       TRUE: The CAN controller has encountered an Overload error
 * @retval       FALSE: The CAN controller has not encountered an Overload error
 *
 * @Design       SDD_CAN_097, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_FAST) Can_DrvIsOverloadErr(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* STD_ON == CAN_SECURITY_EVENT_REPORTING */
 
#if (STD_ON == CAN_ECC_DETECTION)
/**
 * @brief        This function check the Ecc detection error of Controller.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 * @param[out]   p_MemError_ptr: Pointer to get the value of Mem Error status.
 *
 * @return       boolean.
 * @retval       TRUE: The CAN controller has encountered an ECC error
 * @retval       FALSE: The CAN controller has not encountered an ECC error
 *
 * @Design       SDD_CAN_098, SDD_CAN_028
 */
FUNC(boolean, CAN_CODE_FAST) Can_DrvIsEccErr(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8, P2VAR(boolean, AUTOMATIC, CAN_APPL_DATA) p_MemError_ptr);
#endif /* STD_ON == CAN_ECC_DETECTION */
 
#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"
 
/** @} end of group Public_FunctionDeclaration */
 
#ifdef __cplusplus
}
#endif
 
/** @} end of group Can */
 
#endif /* CAN_DRV_H */
 