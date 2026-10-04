/*-------------------------------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Can.c                                                                             |
| Description:|                                                                                   |
|             | Microcontrollers: STM32F407                                                       |
|             | Compiler        : GCC IAR GHS TASKING                                             |
|             | Technical Ref   : AUTOSAR_SWS_CANDriver.pdf (4.4.0)                              |
|--------------------------------------------------------------------------------------------------------------------------|
| COPYRIGHT                                                                                       |
|--------------------------------------------------------------------------------------------------------------------------|
|                                                                                                                          |
|                                                                                                                          |
|                                                                                                                          |
|--------------------------------------------------------------------------------------------------------------------------|
| FILE DESCRIPTION                                                                                |
|--------------------------------------------------------------------------------------------------------------------------|
| File        | Can.c                                                                             |
| Module      | CAN                                                                               |
| Version     | 1.00.00                                                                           |
| Contents    | CAN Module source                                                                 |
|             | The CAN is a basic software module at the service layer of the standardized basic |
|             | software architecture of AUTOSAR.                                                 |
|--------------------------------------------------------------------------------------------------------------------------|
| AUTHOR IDENTITY                                                                                 |
|--------------------------------------------------------------------------------------------------------------------------|
| Author      | HaoNP                                                                             |
| Company     | H-Car Autosar Technology Inc.                                                     |
| Note        | --                                                                                |
|--------------------------------------------------------------------------------------------------------------------------|
| REVISION CONTROL HISTORY                                                                        |
|--------------------------------------------------------------------------------------------------------------------------|
| V1.00.00 | 01/01/2025 | HaoNP    | [CAN-ID-001] Initial Version.                                |
|                                  |                                                              |
|-------------------------------------------------------------------------------------------------------------------------*/

 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "Can.h"
 
#include "CanIf.h"
#include "Can_Drv.h"

#if (STD_ON == CAN_LPDU_RECEIVE_CALLOUT_SUPPORT)
#include "Can_Externals.h"
#endif /* STD_ON == CAN_LPDU_RECEIVE_CALLOUT_SUPPORT */

#include "Dem.h"
#include "Det.h"
#include "EcuM.h"
#include "Os.h"
#include "SchM_Can.h"
 
/*-------------------------------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|-------------------------------------------------------------------------------------------------------------------------*/
/* Common published information */
#define CAN_VENDOR_ID_C                         (0x0FU)
#define CAN_MODULE_ID_C                         (0x7CU)

/* AUTOSAR release version: 4.4.0 */
#define CAN_AR_RELEASE_MAJOR_VERSION_C          (0x04U)
#define CAN_AR_RELEASE_MINOR_VERSION_C          (0x04U)
#define CAN_AR_RELEASE_REVISION_VERSION_C       (0x00U)

/* Software version: 1.0.0 */
#define CAN_SW_MAJOR_VERSION_C                  (0x01U)
#define CAN_SW_MINOR_VERSION_C                  (0x00U)
#define CAN_SW_PATCH_VERSION_C                  (0x00U)

/*-------------------------------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|-------------------------------------------------------------------------------------------------------------------------*/
/* Check if current file and Can.h are the same Vendor Id */
#if (CAN_VENDOR_ID_C != CAN_VENDOR_ID_H)
#error "Vendor Id of Can.c and Can.h are different"
#endif
 
/* Check if current file and Can.h are the same Vendor Id */
#if (CAN_VENDOR_ID_C != CAN_VENDOR_ID_H)
#error "Vendor Id of Can.c and Can.h are different"
#endif
 
/* Check if current file and Can.h are the same Software version */
#if ((CAN_SW_MAJOR_VERSION_C != CAN_SW_MAJOR_VERSION_H) || \
     (CAN_SW_MINOR_VERSION_C != CAN_SW_MINOR_VERSION_H) || \
     (CAN_SW_PATCH_VERSION_C != CAN_SW_PATCH_VERSION_H))
#error "Software Version Numbers of Can.c and Can.h are different"
#endif
 
/* Check if current file and Can.h are the same Software version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C != CAN_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_C != CAN_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_AR_RELEASE_REVISION_VERSION_C != CAN_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of Can.c and Can.h are different"
#endif
 
/* Check if current file and Can_Drv.h are the same Software version */
#if ((CAN_SW_MAJOR_VERSION_C != CAN_DRV_SW_MAJOR_VERSION_H) || \
     (CAN_SW_MINOR_VERSION_C != CAN_DRV_SW_MINOR_VERSION_H) || \
     (CAN_SW_PATCH_VERSION_C != CAN_DRV_SW_PATCH_VERSION_H))
#error "Software Version Numbers of Can.c and Can_Drv.h are different"
#endif
 
/* Check if current file and Can_Drv.h are the same Software version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C != CAN_DRV_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_C != CAN_DRV_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_AR_RELEASE_REVISION_VERSION_C != CAN_DRV_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of Can.c and Can_Drv.h are different"
#endif
 
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and CanIf.h are the same Software version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C != CANIF_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_C != CANIF_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of Can.c and CanIf.h are different"
#endif
 
/* Check if current file and Dem.h are the same Software version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of Can.c and Dem.h are different"
#endif
 
/* Check if current file and Det.h are the same Software version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of Can.c and Det.h are different"
#endif
 
/* Check if current file and EcuM.h are the same Software version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C != ECUM_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_C != ECUM_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of Can.c and EcuM.h are different"
#endif
 
/* Check if current file and Os.h are the same Software version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C != OS_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_C != OS_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of Can.c and Os.h are different"
#endif
 
/* Check if current file and SchM_Can.h are the same Software version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_C != SCHM_CAN_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_C != SCHM_CAN_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of Can.c and SchM_Can.h are different"
#endif
#endif
 
/**
 * @brief Can without error value.
 */
#define CAN_E_NONE ((uint8)0x00U)
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
/**
 * @brief Validation for Can Initialize.
 */
#define CAN_INITIALIZE_VALID()                            ((CAN_READY != Can_l_GlobalState_en) ? CAN_E_UNINIT : CAN_E_NONE)
#define CAN_STATE_READY_VALID()                           ((CAN_READY != Can_l_GlobalState_en) ? CAN_E_TRANSITION : CAN_E_NONE)
#define CAN_STATE_STARTED_VALID(CtrlId)                   ((CAN_CS_STARTED == Can_l_CtrlState_aa[(CtrlId)]) ? CAN_E_TRANSITION : CAN_E_NONE)
#define CAN_CONTROLLER_ID_VALID(CtrlId)                   ((Can_l_Config_ptr->CtrlNum_u32 <= (CtrlId)) ? CAN_E_PARAM_CONTROLLER : CAN_E_NONE)
#define CAN_WRITE_PDU_PARAM_VALID(CtrlCfg, HwObj, PduInf) (Can_ValidatePdu(CtrlCfg, HwObj, PduInf))
 
#if (STD_ON == CAN_SET_BAUDRATE_API)
#define CAN_BAUDRATE_CONFIG_ID_VALID(CtrlId, BaudrateId) \
  ((Can_l_Config_ptr->CtrlCfg_ptr[(CtrlId)].BaudrateNum_u8 <= (BaudrateId)) ? CAN_E_PARAM_BAUDRATE : CAN_E_NONE)
#endif /* STD_ON == CAN_SET_BAUDRATE_API */
 
#define CAN_HTH_PARAM_VALID(Hth) \
  (((CAN_U8_DAT_0 == (Can_l_Config_ptr->HthHwObjNum_u32)) || \
    (Can_l_Config_ptr->Hth1stId_u8 > (Hth)) || \
    ((Can_l_Config_ptr->HthHwObjNum_u32 + Can_l_Config_ptr->Hth1stId_u8) <= (Hth))) ? CAN_E_PARAM_HANDLE : CAN_E_NONE)
 
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
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
#define CAN_START_SEC_VAR_CLEARED_PTR
#include "Can_MemMap.h"
/**
 * @brief Pointers to Can high level configuration structure - the pointer is valid only when the driver is in initialized state for a given partition.
 */
static P2CONST(Can_ConfigType, CAN_VAR_CLEAR, CAN_VAR_CLEAR) Can_l_Config_ptr;
#define CAN_STOP_SEC_VAR_CLEARED_PTR
 
 
#include "Can_MemMap.h"
 
#define CAN_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Can_MemMap.h"
/**
 * @brief Store controllers mode.
 */
static VAR(Can_ControllerStateType, CAN_VAR_CLEAR) Can_l_CtrlState_aa[CAN_CONTROLLER_CFG_NUM];
#define CAN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Can_MemMap.h"
 
#define CAN_START_SEC_VAR_CLEARED_8
#include "Can_MemMap.h"
/**
 * @brief Store the interrupt level.
 */
static VAR(uint8, CAN_VAR_CLEAR) Can_l_DisableIrqCnt_aa[CAN_CONTROLLER_CFG_NUM];
#define CAN_STOP_SEC_VAR_CLEARED_8
#include "Can_MemMap.h"
 
#define CAN_START_SEC_VAR_INIT_UNSPECIFIED
#include "Can_MemMap.h"
/**
 * @brief CAN driver status(uninit or ready).
 */
static VAR(Can_DriverStateType, CAN_VAR_CLEAR) Can_l_GlobalState_en = CAN_UNINIT;
#define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Can_MemMap.h"
 
/** @} end of group Private_VariableDefinition */
 
/** @defgroup Private_FunctionDeclaration
 *  @{
 */
#define CAN_START_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
static FUNC(void, CAN_CODE_SLOW) Can_InitControllers(void);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
static FUNC(uint8, CAN_CODE_SLOW) Can_ValidatePdu(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                  P2CONST(Can_HthHwObjCfgType, AUTOMATIC, CAN_APPL_DATA) p_HthHwObject_ptr,
                                                  P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr);
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
static FUNC(void, CAN_CODE_SLOW) Can_NotifyUpperLayer(CONST(uint8, AUTOMATIC) p_CtrlId_u8, CONST(Can_ControllerStateType, AUTOMATIC) p_Transition_en);
 
static FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_ProcessModeTransition(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                                     CONST(Can_ControllerStateType, AUTOMATIC) p_CurState_en,
                                                                     CONST(Can_ControllerStateType, AUTOMATIC) p_Transition_en);
 
static FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_ProcessTransmit(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                               P2CONST(Can_HthHwObjCfgType, AUTOMATIC, CAN_APPL_DATA) p_HthHwObject_ptr,
                                                               P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr);
 
#if ((STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_RX_POLLING_PROCESSING))
static FUNC(void, CAN_CODE_SLOW) Can_ProcessMsgRead(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) p_CtrlCfg_ptr);
#endif /* (STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_RX_POLLING_PROCESSING) */
 
#define CAN_STOP_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
static FUNC(void, CAN_CODE_FAST) Can_TxIrqProcess(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_RX_INTERRUPT_PROCESSING)
static FUNC(void, CAN_CODE_FAST) Can_RxIrqProcess(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
#endif /* STD_ON == CAN_RX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING)
static FUNC(void, CAN_CODE_FAST) Can_BusOffIrqProcess(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                      VAR(uint8, AUTOMATIC) p_ControllerId_u8);
#endif /* STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
static FUNC(void, CAN_CODE_FAST) Can_ErrorIrqProcess(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr);
#endif /* (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION) */
 
#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"
 
/** @} end of group Private_FunctionDeclaration */
#define CAN_START_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
/** @defgroup Private_FunctionDefinition
 *  @{
 */
/**
 * @brief        This fuction initializes for all controller and global variable.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_044, SDD_CAN_024, SDD_CAN_025, SDD_CAN_026, SDD_CAN_027, SDD_CAN_102
 */
static FUNC(void, CAN_CODE_SLOW) Can_InitControllers(void) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) f_CtrlCfg_ptr;
 
  /* Init return value */
  f_Ret_u8 = CAN_E_NOT_OK;
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  /* Init Error Id value */
  f_ErrorId_u8 = CAN_E_NONE;
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  /* Change the module state to CAN_READY */
  Can_l_GlobalState_en = CAN_READY;
 
  /* Loop through all configured channels */
  for (f_Idx_u8 = CAN_U8_DAT_0; (f_Idx_u8 < CAN_CONTROLLER_CFG_NUM) && (f_ErrorId_u8 == CAN_E_NONE); f_Idx_u8++) {
    if (CAN_CS_UNINIT == Can_l_CtrlState_aa[f_Idx_u8]) {
      /* Get controller configuration */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
 
      if ((NULL_PTR != f_CtrlCfg_ptr) && (CAN_TRUE == f_CtrlCfg_ptr->Active_bool)) {
        /* Reset interrupt level after re-init */
        Can_l_DisableIrqCnt_aa[f_Idx_u8] = CAN_U8_DAT_0;
 
        /* Initialize all CAN controllers according to their configuration */
        f_Ret_u8 = Can_DrvInit(f_CtrlCfg_ptr);
 
        /* Stop in case any can controller init failed */
        if (CAN_E_NOT_OK == f_Ret_u8) {
          /* Change the module state to CAN_UNINIT */
          Can_l_GlobalState_en = CAN_UNINIT;
 
          break;
        } else {
          /* Do nothing */
        }
 
        /* CAN controller state STOPPED */
        Can_l_CtrlState_aa[f_Idx_u8] = CAN_CS_STOPPED;
      } else {
        f_Ret_u8 = CAN_E_NOT_OK;
      }
    } else {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      f_ErrorId_u8 = CAN_E_TRANSITION;
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
    }
  }
 
  if (CAN_E_NOT_OK == f_Ret_u8) {
    for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
      /* Reset CAN controller status */
      Can_l_CtrlState_aa[f_Idx_u8] = CAN_CS_UNINIT;
    }
  } else {
    /* Do nothing */
  }
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_INIT_ID, f_ErrorId_u8);
 
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
  return;
}
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
/**
 * @brief        This function validate the valid of input PduInfo.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[in]    p_HthHwObject_ptr: Pointer to the HTH object configuration set.
 * @param[in]    p_PduInfo_ptr: Pointer to the information needed for validation.
 *
 * @return       uint8.
 * @retval       CAN_E_PARAM_DATA_LENGTH: API Service called with invalid length.
 * @retval       CAN_E_PARAM_POINTER: API Service called with invalid sdu.
 *
 * @Design       SDD_CAN_045
 */
static FUNC(uint8, CAN_CODE_SLOW) Can_ValidatePdu(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                  P2CONST(Can_HthHwObjCfgType, AUTOMATIC, CAN_APPL_DATA) p_HthHwObject_ptr,
                                                  P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr) {
  VAR(uint8, AUTOMATIC) f_Ret_u8;
 
  /** Check if:
   * - The length is more than 64 byte.
   * - The length is more than 8 byte and the CAN controller is not in CAN FD mode.
   * - The length is more than 8 byte and the CAN controller is in CAN FD mode, but the CAN FD flag in Can_PduType->id is not set.
   * - CanTriggerTransmitEnable = FALSE and The SDU pointer inside PduInfo is a null pointer
   */
  if ((NULL_PTR == p_PduInfo_ptr) || ((NULL_PTR == p_PduInfo_ptr->sdu) && (CAN_FALSE == p_HthHwObject_ptr->TriggerTxEn_bool))) {
    f_Ret_u8 = CAN_E_PARAM_POINTER;
  } else if (CAN_U8_DAT_64 < p_PduInfo_ptr->length) {
      f_Ret_u8 = CAN_E_PARAM_DATA_LENGTH;
 
#if (CAN_FD_SUPPORT == STD_ON)
  } else if (((CAN_U8_DAT_8 < p_PduInfo_ptr->length) && (CAN_FALSE == p_CtrlCfg_ptr->BaudrateCfg_ptr->FdEn_bool)) ||
             ((CAN_U8_DAT_8 < p_PduInfo_ptr->length) && (CAN_FD_FRAME != (CAN_FD_FRAME & p_PduInfo_ptr->id)))) {
    f_Ret_u8 = CAN_E_PARAM_DATA_LENGTH;
#else
  } else if (CAN_U8_DAT_8 < p_PduInfo_ptr->length) {
    f_Ret_u8 = CAN_E_PARAM_DATA_LENGTH;
#endif /* CAN_FD_SUPPORT == STD_ON */
 
  } else {
    f_Ret_u8 = CAN_E_NONE;
  }
 
  return f_Ret_u8;
}
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
/**
 * @brief        This function update controller state and notify to CanIf via CanIf_ControllerModeIndication.
 *
 * @param[in]    p_CtrlId_u8: Controller Id.
 * @param[in]    p_Transition_en: CAN controller state.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_046, SDD_CAN_025, SDD_CAN_099
 */
static FUNC(void, CAN_CODE_SLOW) Can_NotifyUpperLayer(CONST(uint8, AUTOMATIC) p_CtrlId_u8, CONST(Can_ControllerStateType, AUTOMATIC) p_Transition_en) {
  /* Update Controller state */
  Can_l_CtrlState_aa[p_CtrlId_u8] = p_Transition_en;
  /* Indicate to upper layer */
  CanIf_ControllerModeIndication(p_CtrlId_u8, p_Transition_en);
 
  return;
}
 
/**
 * @brief        This function process the transition mode of CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[in]    p_CurState_en: Current CAN controller state.
 * @param[in]    p_Transition_en: Transition CAN controller state.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Controller transition mode successful.
 * @retval       E_NOT_OK: Controller transition mode failed.
 *
 * @Design       SDD_CAN_047, SDD_CAN_102
 */
static FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_ProcessModeTransition(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                                     CONST(Can_ControllerStateType, AUTOMATIC) p_CurState_en,
                                                                     CONST(Can_ControllerStateType, AUTOMATIC) p_Transition_en) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
  f_Ret_u8 = CAN_E_OK;
 
  /* [SWS_Can_00017] */
  switch (p_Transition_en) {
    case CAN_CS_STOPPED:
 
      if (CAN_CS_STARTED == p_CurState_en) {
        /* Stop the CAN controller */
        if(E_OK == Can_DrvStopController(p_CtrlCfg_ptr)) {
          /* Notify to upper layer */
          Can_NotifyUpperLayer(p_CtrlCfg_ptr->CtrlId_u8, CAN_CS_STOPPED);
        } else {
          /* Do nothing */
        }
      } else if ((CAN_CS_STOPPED == p_CurState_en) || (CAN_CS_SLEEP == p_CurState_en)) {
        /* Notify to upper layer */
        Can_NotifyUpperLayer(p_CtrlCfg_ptr->CtrlId_u8, CAN_CS_STOPPED);
 
      } else {
        /* Do nothing */
      }
 
      break;
 
    case CAN_CS_STARTED:
 
      if (CAN_CS_STOPPED == p_CurState_en) {
        /* Start the CAN controller */
        if(E_OK == Can_DrvStartController(p_CtrlCfg_ptr, Can_l_DisableIrqCnt_aa[p_CtrlCfg_ptr->CtrlId_u8])) {
          /* Notify to upper layer */
          Can_NotifyUpperLayer(p_CtrlCfg_ptr->CtrlId_u8, CAN_CS_STARTED);
 
        } else {
          /* Do nothing */
        }
      } else {
        f_Ret_u8 = CAN_E_NOT_OK;
      }
      break;
 
    case CAN_CS_SLEEP:
 
      if (CAN_CS_STOPPED == p_CurState_en) {
        /* Notify to upper layer */
        Can_NotifyUpperLayer(p_CtrlCfg_ptr->CtrlId_u8, CAN_CS_SLEEP);
 
      } else {
        f_Ret_u8 = CAN_E_NOT_OK;
      }
 
      break;
 
    default:
 
      f_Ret_u8 = CAN_E_NOT_OK;
      break;
  }
 
  return f_Ret_u8;
}
 
/**
 * @brief        This function process the transmission for CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[in]    p_HthHwObject_ptr: Pointer to the HTH object configuration set.
 * @param[in]    p_PduInfo_ptr: Pointer to the information needed for transmission.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Message transmit success.
 * @retval       E_NOT_OK: CAN controller is busy.
 *
 * @Design       SDD_CAN_048, SDD_CAN_024, SDD_CAN_099
 */
static FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_ProcessTransmit(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                               P2CONST(Can_HthHwObjCfgType, AUTOMATIC, CAN_APPL_DATA) p_HthHwObject_ptr,
                                                               P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
  VAR(Can_PduType, AUTOMATIC) f_PduInfoTemp_st;
#if (STD_ON == CAN_TRIGGER_TRANSMIT_USED)
  VAR(PduInfoType, AUTOMATIC) f_CanIfPduInfo_st;
  VAR(uint8, AUTOMATIC) f_DataBuf_aa[CAN_U8_DAT_64];
#endif /* (STD_ON == CAN_TRIGGER_TRANSMIT_USED) */
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Get Pdu information */
  f_PduInfoTemp_st.id          = p_PduInfo_ptr->id;
  f_PduInfoTemp_st.length      = p_PduInfo_ptr->length;
  f_PduInfoTemp_st.sdu         = p_PduInfo_ptr->sdu;
  f_PduInfoTemp_st.swPduHandle = p_PduInfo_ptr->swPduHandle;
 
#if (STD_ON == CAN_TRIGGER_TRANSMIT_USED)
 
  if ((CAN_TRUE == p_HthHwObject_ptr->TriggerTxEn_bool) && (NULL_PTR == p_PduInfo_ptr->sdu)) {
    /* Set data buffer */
    f_CanIfPduInfo_st.SduDataPtr = f_DataBuf_aa;
 
    /* Copy upper layer data into the Can Hw buffer and update the length of the actual copied data */
 
    if (CAN_E_OK == CanIf_TriggerTransmit(p_PduInfo_ptr->swPduHandle, &f_CanIfPduInfo_st)) {
      f_PduInfoTemp_st.length = (uint8)f_CanIfPduInfo_st.SduLength;
      f_PduInfoTemp_st.sdu    = f_CanIfPduInfo_st.SduDataPtr;
 
      f_Ret_u8 = Can_DrvTransmit(p_CtrlCfg_ptr, p_HthHwObject_ptr, &f_PduInfoTemp_st, (p_HthHwObject_ptr->HwObjectId_u8 - Can_l_Config_ptr->Hth1stId_u8));
    } else {
      /* Do nothing */
    }
  } else {
#endif /* (STD_ON == CAN_TRIGGER_TRANSMIT_USED) */
 
    f_Ret_u8 = Can_DrvTransmit(p_CtrlCfg_ptr, p_HthHwObject_ptr, &f_PduInfoTemp_st, (p_HthHwObject_ptr->HwObjectId_u8 - Can_l_Config_ptr->Hth1stId_u8));
 
#if (STD_ON == CAN_TRIGGER_TRANSMIT_USED)
  }
#endif /* (STD_ON == CAN_TRIGGER_TRANSMIT_USED) */
 
  return f_Ret_u8;
}
 
#if ((STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_RX_POLLING_PROCESSING))
/**
 * @brief        This function process the receive message for CAN controller.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_049, SDD_CAN_099
 */
static FUNC(void, CAN_CODE_SLOW) Can_ProcessMsgRead(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) p_CtrlCfg_ptr) {
  VAR(boolean, AUTOMATIC) f_RxIsEmpty_bool;
  VAR(Can_HwType, AUTOMATIC) f_Mailbox_st;
  VAR(PduInfoType, AUTOMATIC) f_PduInfo_st;
  VAR(uint8, AUTOMATIC) f_RxData_aa[CAN_U8_DAT_64];
 
  /* Set data buffer */
  f_PduInfo_st.SduDataPtr   = f_RxData_aa;
  f_Mailbox_st.ControllerId = p_CtrlCfg_ptr->CtrlId_u8;
  f_Mailbox_st.Hoh          = p_CtrlCfg_ptr->HrhConfig_ptr[p_CtrlCfg_ptr->CtrlId_u8].HrhIdx_u8;
 
  f_RxIsEmpty_bool = Can_DrvRxMsgIsEmpty(p_CtrlCfg_ptr->CtrlOffset_u8);
 
  /* Check if Rx over flow error */
  if (CAN_TRUE == Can_DrvRxOverFlow(p_CtrlCfg_ptr)) {
    /* Report runtime error */
    (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_MAIN_FUNCTION_READ_ID, CAN_E_DATALOST);
  } else {
    /* Do nothing */
  }
 
  while (CAN_FALSE == f_RxIsEmpty_bool) {
    /* Get Rx infomation and only handle receive data frame, ignore remote frame */
    Can_DrvGetRxInfo(p_CtrlCfg_ptr, &f_Mailbox_st, &f_PduInfo_st);
 
#if (STD_ON == CAN_LPDU_RECEIVE_CALLOUT_SUPPORT)
    if (CAN_TRUE == LPDU_CALLOUT_FUNCTION_CALLED(f_Mailbox_st.Hoh, f_Mailbox_st.CanId, (uint8)f_PduInfo_st.SduLength, f_PduInfo_st.SduDataPtr)) {
#endif /* STD_ON == CAN_LPDU_RECEIVE_CALLOUT_SUPPORT */
 
      /* Indication information to CanIf */
      CanIf_RxIndication(&f_Mailbox_st, &f_PduInfo_st);
 
#if (STD_ON == CAN_LPDU_RECEIVE_CALLOUT_SUPPORT)
    } else {
      /* Do nothing */
    }
#endif /* STD_ON == CAN_LPDU_RECEIVE_CALLOUT_SUPPORT */
 
    /* Continuous to get Rx msg status */
    f_RxIsEmpty_bool = Can_DrvRxMsgIsEmpty(p_CtrlCfg_ptr->CtrlOffset_u8);
  }
  return;
}
#endif /* (STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_RX_POLLING_PROCESSING) */
 
#define CAN_STOP_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
/**
 * @brief        This function process Tx comfirmation message of CAN controller in interrupt.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_050
 */
static FUNC(void, CAN_CODE_FAST) Can_TxIrqProcess(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr) {
  VAR(uint8, AUTOMATIC) f_TxMsgCnt_u8;
#if (STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT)
  VAR(uint8, AUTOMATIC) f_Idx2_u8;
  VAR(PduIdType, AUTOMATIC) f_PduType_aa[(uint16)(CAN_STB_FIFO_DEPTH + CAN_U8_DAT_1)];
#else
  VAR(PduIdType, AUTOMATIC) f_PduType_u16;
#endif /* STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT */
 
#if (STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT)
 
  f_TxMsgCnt_u8 = Can_DrvProcessTxMsg(p_CtrlCfg_ptr, &f_PduType_aa[CAN_U8_DAT_0]);
 
  /* Notify the transmitted message */
  for (f_Idx2_u8 = CAN_U8_DAT_0; f_Idx2_u8 < f_TxMsgCnt_u8; f_Idx2_u8++) {
    CanIf_TxConfirmation(f_PduType_aa[f_Idx2_u8]);
  }
 
#else
  f_TxMsgCnt_u8 = Can_DrvProcessTxMsg(p_CtrlCfg_ptr, &f_PduType_u16);
    /* Notify the TxPdu transmitted message when Tx Primary buffer has been process. */
  if (CAN_U8_DAT_1 == f_TxMsgCnt_u8){
    CanIf_TxConfirmation(f_PduType_u16);
  } else {
    /* Do nothing */
  }
 
 
#endif /* STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT */
 
  /* Clear Tx interrupt flag */
  Can_DrvClrTxIrqFlag(p_CtrlCfg_ptr->CtrlOffset_u8);
 
  return;
}
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_RX_INTERRUPT_PROCESSING)
/**
 * @brief        This function process Rx indication message of CAN controller in interrupt.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_051
 */
static FUNC(void, CAN_CODE_FAST) Can_RxIrqProcess(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr) {
 
  /* Process for Rx message */
  Can_ProcessMsgRead(p_CtrlCfg_ptr);
 
  /* Clear Rx interrupt flag */
  Can_DrvClrRxIrqFlag(p_CtrlCfg_ptr->CtrlOffset_u8);
 
  return;
}
#endif /* STD_ON == CAN_RX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING)
/**
 * @brief        This function process the Bus off error of CAN controller in interrupt.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 * @param[in]    p_ControllerId_u8: Controller Id.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_052, SDD_CAN_099
 */
static FUNC(void, CAN_CODE_FAST) Can_BusOffIrqProcess(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr,
                                                      VAR(uint8, AUTOMATIC) p_ControllerId_u8) {
  /* Check if the Busoff error is raised */
  if (CAN_TRUE == Can_DrvBusOff(p_CtrlCfg_ptr)) {
    /* Driver process when Busoff */
    Can_DrvProcessBusOff(p_CtrlCfg_ptr);
 
    /* Update controller state */
    Can_NotifyUpperLayer(p_ControllerId_u8, CAN_CS_STOPPED);
 
    /* Call Busoff Callback function */
    CanIf_ControllerBusOff(p_ControllerId_u8);
 
    /* Clear Busoff interrupt flag */
    Can_DrvClrBusoffIrqFlag(p_CtrlCfg_ptr->CtrlOffset_u8);
 
  } else {
    /* Do nothing */
  }
 
#if (STD_OFF == CAN_SECURITY_EVENT_REPORTING)
  /* Clear the Bus-off interrupt flag. This flag is initially raised when the controller enters Error Passive mode, prior to entering Bus-off mode, in cases
   * where the driver does not enable the Security Event feature,  this flag must be cleared to allow proper entry into Bus-off mode. */
  Can_DrvClrBusoffIrqFlag();
#endif /* STD_OFF == CAN_SECURITY_EVENT_REPORTING */
 
  return;
}
#endif /* STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
/**
 * @brief        This function process the error of CAN controller in interrupt.
 *
 * @param[in]    p_CtrlCfg_ptr: Pointer to the controller configuration set.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_053, SDD_CAN_099, SDD_CAN_100
 */
static FUNC(void, CAN_CODE_FAST) Can_ErrorIrqProcess(P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_APPL_DATA) p_CtrlCfg_ptr) {
 
  VAR(boolean, AUTOMATIC) f_ErrSt_bool;
#if (STD_ON == CAN_ECC_DETECTION)
  VAR(uint8, AUTOMATIC) f_MemError_bool;
#endif /* STD_ON == CAN_ECC_DETECTION */
#if (STD_ON == CAN_SECURITY_EVENT_REPORTING)
  VAR(uint16, AUTOMATIC) f_RxErrCnt_u16;
  VAR(uint16, AUTOMATIC) f_TxErrCnt_u16;
 
  /* Get passive error status */
  f_ErrSt_bool = Can_DrvIsPassiveErr(p_CtrlCfg_ptr->CtrlOffset_u8, &f_RxErrCnt_u16, &f_TxErrCnt_u16);
  /* Check if a passive error is occurring */
  if(CAN_TRUE == f_ErrSt_bool) {
    CanIf_ControllerErrorStatePassive(p_CtrlCfg_ptr->CtrlId_u8 , f_RxErrCnt_u16, f_TxErrCnt_u16);
  } else {
    /* Do nothing */
  }
 
  /* Get Arbitration lost status */
  f_ErrSt_bool = Can_DrvIsArbitrationLost(p_CtrlCfg_ptr->CtrlOffset_u8);
  /* Check if a Arbitration lost is occurring */
  if(CAN_TRUE == f_ErrSt_bool) {
    CanIf_ErrorNotification(p_CtrlCfg_ptr->CtrlId_u8, CAN_ERROR_ARBITRATION_LOST);
  } else {
    /* Do nothing */
  }
 
  /* Get Overload error status */
  f_ErrSt_bool = Can_DrvIsOverloadErr(p_CtrlCfg_ptr->CtrlOffset_u8);
  /* Check if a Overload error is occurring */
  if(CAN_TRUE == f_ErrSt_bool) {
    CanIf_ErrorNotification(p_CtrlCfg_ptr->CtrlId_u8, CAN_ERROR_OVERLOAD);
  } else {
    /* Do nothing */
  }
 
#endif /* STD_ON == CAN_SECURITY_EVENT_REPORTING */
 
#if (STD_ON == CAN_ECC_DETECTION)
 
  /* Get Memory error status */
  f_ErrSt_bool = Can_DrvIsEccErr(p_CtrlCfg_ptr->CtrlOffset_u8, &f_MemError_bool);
  /* Check if a Memory error is occurring */
  if((CAN_TRUE == f_ErrSt_bool) && (CAN_TRUE == f_MemError_bool)) {
    /* Dual-bit error occurs or Single-bit error occurs and is unsuccessfully auto-corrected by the hardware */
    (void)Dem_SetEventStatus(CAN_E_ECC_PERMANENT_ERROR, DEM_EVENT_STATUS_FAILED);
  } else if(CAN_TRUE == f_ErrSt_bool) {
    /* Single-bit error occurs and is successfully auto-corrected by the hardware */
    (void)Dem_SetEventStatus(CAN_E_ECC_TRANSIENT_ERROR, DEM_EVENT_STATUS_FAILED);
  } else {
    /* Do nothing */
  }
 
#endif /* STD_ON == CAN_ECC_DETECTION */
 
 
  /* Clear Error interrupt flag */
  Can_DrvClrErrIrqFlag(p_CtrlCfg_ptr->CtrlOffset_u8);
 
  return;
}
#endif /* (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION) */
 
#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"
 
/** @} end of group Private_FunctionDefinition */
 
/** @defgroup Public_FunctionDefinition
 *  @{
 */
#define CAN_START_SEC_CODE_SLOW
#include "Can_MemMap.h"
/**
 * @brief        This function initializes the module.
 *
 * @details      Initializes the CAN module with the provided configuration parameters. This function sets up initial settings for the CAN controller,
 *               allocates necessary resources, and prepares the module for operation.
 *
 * @param[in]    Config: Pointer to driver configuration.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_001, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100, SDD_CAN_101, SDD_CAN_102
 */
FUNC(void, CAN_CODE_SLOW) Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Config) {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_InitState_u8;
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  /* Init error value */
  f_ErrorId_u8 = CAN_E_NONE;
  /* Check if the module is already initialized */
  f_InitState_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_UNINIT == f_InitState_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
    if (NULL_PTR == Config) {
#if (STD_ON == CAN_PRECOMPILE_SUPPORT)
      /* Use pre-compile configuration set structure */
      Can_l_Config_ptr = &Can_g_CanCfg_st;
      (void)Config;
 
#else /* CAN_PRECOMPILE_SUPPORT */
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    f_ErrorId_u8 = CAN_E_INIT_FAILED;
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
#endif /* STD_ON == CAN_PRECOMPILE_SUPPORT */
    } else {
#if (STD_ON == CAN_PRECOMPILE_SUPPORT)
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      f_ErrorId_u8 = CAN_E_INIT_FAILED;
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
#else  /* CAN_PRECOMPILE_SUPPORT */
    /* Use post-build configuration set structure */
    Can_l_Config_ptr = Config;
 
#endif /* STD_ON == CAN_PRECOMPILE_SUPPORT */
    }
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  } else {
    f_ErrorId_u8 = CAN_E_TRANSITION;
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
    Can_InitControllers();
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
 
  } else {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_INIT_ID, f_ErrorId_u8);
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return;
}
 
#if (STD_ON == CAN_VERSION_INFO_API)
/**
 * @brief        This function returns the version information of this module.
 *
 * @details      Returns the version information of the CAN module. Typically includes software version, vendor ID, and other relevant details about the
 *               implementation.
 *
 * @param[in]    versioninfo: Pointer to where to store the version information of this module.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_002, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo) {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  if (NULL_PTR != versioninfo) {
#endif
 
    versioninfo->moduleID         = CAN_MODULE_ID_H;
    versioninfo->vendorID         = (uint16)CAN_VENDOR_ID_H;
    versioninfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION_H;
    versioninfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION_H;
    versioninfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION_H;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  } else {
    /* Report to Det */
    (void)Det_ReportError(CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_GET_VERSION_INFO_ID, CAN_E_PARAM_POINTER);
  }
#endif
  return;
}
#endif /* STD_ON == CAN_VERSION_INFO_API */
 
/**
 * @brief        This function de-initializes the module.
 *
 * @details      De-initializes and releases the CAN module. This function resets the controller to its default state, frees allocated resources, and stops all
 *               CAN-related activities.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_003, SDD_CAN_025, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100, SDD_CAN_102
 */
FUNC(void, CAN_CODE_SLOW) Can_DeInit(void) {
  VAR(uint8, AUTOMATIC) f_Idx_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  /* Check if the driver is not in state CAN_READY */
  f_ErrorId_u8 = CAN_STATE_READY_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
    /* Loop through all configured channels */
    for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
 
      /* Check if the driver is not in state STARTED */
      f_ErrorId_u8 = CAN_STATE_STARTED_VALID(f_Idx_u8);
      if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        Can_l_CtrlState_aa[f_Idx_u8] = CAN_CS_UNINIT;
 
        (void)Can_DrvStopController(&(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]));
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        break;
      }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
    }
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_DEINIT_ID, f_ErrorId_u8);
  } else {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
    Can_l_GlobalState_en = CAN_UNINIT;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return;
}
 
#if (STD_ON == CAN_SET_BAUDRATE_API)
/**
 * @brief        This service shall set the baud rate configuration of the CAN controller. Depending on necessary baud rate modifications the controller might
 *
 * @details      Sets or changes the baud rate configuration of the CAN controller. Allows dynamic adjustment of the CAN network communication speed.
 *
 * @param[in]    Controller: CAN controller, whose baud rate shall be set.
 * @param[in]    BaudRateConfigID: References a baud rate configuration by ID (see CanController BaudRateConfigID).
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Service request accepted, setting of (new) baud rate started.
 * @retval       E_NOT_OK: Service request not accepted.
 *
 * @Design       SDD_CAN_004, SDD_CAN_024, SDD_CAN_025, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetBaudrate(VAR(uint8, AUTOMATIC) Controller, VAR(uint16, AUTOMATIC) BaudRateConfigID) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  f_Ret_u8 = CAN_E_NOT_OK;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter Controller is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(Controller);
    if (CAN_E_NONE == f_ErrorId_u8) {
      /* Check if the parameter BaudRateConfigID has an invalid value */
      f_ErrorId_u8 = CAN_BAUDRATE_CONFIG_ID_VALID(Controller, BaudRateConfigID);
      if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        /* The CAN controller must be in state STOPPED when this function is called */
        if (CAN_CS_STOPPED != Can_l_CtrlState_aa[Controller]) {
          f_Ret_u8 = CAN_E_NOT_OK;
        } else {
          SchM_Enter_Can_CAN_EXCLUSIVE_AREA_01();
 
          f_Ret_u8 = Can_DrvChangeBaudrate(&(Can_l_Config_ptr->CtrlCfg_ptr[Controller]),
                                           &(Can_l_Config_ptr->CtrlCfg_ptr[Controller].BaudrateCfg_ptr[BaudRateConfigID]));
 
          SchM_Exit_Can_CAN_EXCLUSIVE_AREA_01();
        }
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        /* Do nothing */
      }
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_SET_BAUDRATE_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_Ret_u8;
}
#endif /* STD_ON == CAN_SET_BAUDRATE_API */
 
/**
 * @brief        This function performs software triggered state transitions of the CAN controller State machine.
 *
 * @details      Performs software-triggered state transitions of the CAN controller, such as switching between Start, Stop, or Sleep modes.
 *
 * @param[in]    Controller: CAN controller for which the status shall be changed.
 * @param[in]    Transition: Transition value to request new CAN controller state.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Request accepted.
 * @retval       E_NOT_OK: Request not accepted, a development error occurred.
 *
 * @Design       SDD_CAN_005, SDD_CAN_024, SDD_CAN_025, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100, SDD_CAN_102
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetControllerMode(VAR(uint8, AUTOMATIC) Controller, VAR(Can_ControllerStateType, AUTOMATIC) Transition) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(Controller);
    if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
      f_Ret_u8 = Can_ProcessModeTransition(&(Can_l_Config_ptr->CtrlCfg_ptr[Controller]), Can_l_CtrlState_aa[Controller], Transition);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      if (CAN_E_OK != f_Ret_u8) {
        f_ErrorId_u8 = CAN_E_TRANSITION;
      } else {
        /* Do nothing */
      }
    } else {
      /* Do nothing */
    }
 
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_SET_CONTROLLER_MODE_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
  return f_Ret_u8;
}
 
/**
 * @brief        This function disables all interrupts for this CAN controller.
 *
 * @details      Disables all interrupts for the specified CAN controller. Used to protect critical operations from being interrupted.
 *
 * @param[in]    Controller: CAN controller for which interrupts shall be disabled.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_006, SDD_CAN_024, SDD_CAN_026, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_DisableControllerInterrupts(VAR(uint8, AUTOMATIC) Controller) {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(Controller);
    if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_02();
 
      if (Can_l_DisableIrqCnt_aa[Controller] == CAN_U8_DAT_MAX) {
        /* Do nothing */
      } else {
        Can_l_DisableIrqCnt_aa[Controller] += CAN_U8_DAT_1;
      }
 
      Can_DrvDisControllerInt(&(Can_l_Config_ptr->CtrlCfg_ptr[Controller]));
 
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_02();
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_DISABLE_CONTROLLER_INTERRUPTS_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return;
}
 
/**
 * @brief        This function enables all allowed interrupts.
 *
 * @details      Enables all allowed interrupts for the specified CAN controller, allowing the controller to respond to real-time events.
 *
 * @param[in]    Controller: CAN controller for which interrupts shall be disabled.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_007, SDD_CAN_024, SDD_CAN_026, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_EnableControllerInterrupts(VAR(uint8, AUTOMATIC) Controller) {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(Controller);
    if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_03();
 
      if (CAN_U8_DAT_0 < Can_l_DisableIrqCnt_aa[Controller]) {
        Can_l_DisableIrqCnt_aa[Controller] -= CAN_U8_DAT_1;
      } else {
        Can_DrvEnaControllerInt(&(Can_l_Config_ptr->CtrlCfg_ptr[Controller]));
      }
 
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_03();
 
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_ENABLE_CONTROLLER_INTERRUPTS_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return;
}
 
#if (STD_ON == CAN_WAKEUP_SUPPORT)
/**
 * @brief        This function checks if a wakeup has occurred for the given controller.
 *
 * @details      Checks if a wakeup event has occurred for the given CAN controller, typically to detect external triggers that bring the controller out of
 *               Sleep mode.
 *
 * @param[in]    Controller: CAN controller for which interrupts shall be disabled.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: API call has been accepted.
 * @retval       E_NOT_OK: API call has not been accepted.
 *
 * @Design       SDD_CAN_008, SDD_CAN_024, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckWakeup(VAR(uint8, AUTOMATIC) Controller) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(Controller);
    if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
      /* Check the wakeup flag of driver */
      f_Ret_u8 = Can_DrvCheckWakeup(&(Can_l_Config_ptr->CtrlCfg_ptr[Controller]));
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_CHECK_WAKEUP_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_Ret_u8;
}
#endif /* STD_ON == CAN_WAKEUP_SUPPORT */
 
/**
 * @brief        This service obtains the error state of the CAN controller.
 *
 * @details      Obtains the current error state of the CAN controller, including conditions like Bus-off, Error Passive, or Error Warning.
 *
 * @param[in]    ControllerId: Abstracted CanIf ControllerId which is assigned to a CAN controller, which is requested for ErrorState.
 * @param[out]   ErrorStatePtr: Pointer to a memory location, where the error state of the CAN controller will be stored.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Error state request has been accepted.
 * @retval       E_NOT_OK:  Error state request has not been accepted.
 *
 * @Design       SDD_CAN_009, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerErrorState(VAR(uint8, AUTOMATIC) ControllerId,
                                                                P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) ErrorStatePtr) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(ControllerId);
    if (CAN_E_NONE == f_ErrorId_u8) {
      /* Check if the parameter ErrorStatePtr is a null pointer */
      if (NULL_PTR != ErrorStatePtr) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        f_Ret_u8 = Can_DrvGetControllerErrorState(&(Can_l_Config_ptr->CtrlCfg_ptr[ControllerId]), ErrorStatePtr);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        f_ErrorId_u8 = CAN_E_PARAM_POINTER;
      }
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_GET_CONTROLLER_ERROR_STATE_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_Ret_u8;
}
 
/**
 * @brief        This service reports about the current status of the requested CAN controller.
 *
 * @details      Reports the current operating mode of the requested CAN controller, such as Active, Stopped, or Sleeping.
 *
 * @param[in]    Controller: CAN controller for which interrupts shall be disabled.
 * @param[out]   ControllerModePtr: Pointer to a memory location, where the current mode of the CAN controller will be stored.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Description.
 * @retval       E_NOT_OK: Description.
 *
 * @Design       SDD_CAN_010, SDD_CAN_024, SDD_CAN_025, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerMode(VAR(uint8, AUTOMATIC) Controller,
                                                          P2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_DATA) ControllerModePtr) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(Controller);
    if (CAN_E_NONE == f_ErrorId_u8) {
      /* Check if parameter ControllerModePtr is a null pointer */
      if (NULL_PTR != ControllerModePtr) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        *ControllerModePtr = Can_l_CtrlState_aa[Controller];
        f_Ret_u8           = CAN_E_OK;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        f_ErrorId_u8 = CAN_E_PARAM_POINTER;
      }
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_GET_CONTROLLER_MODE_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_Ret_u8;
}
 
/**
 * @brief        Returns the Rx error counter for a CAN controller. This value might not be available for all CAN controllers, in which case E_NOT_OK would
 *               be returned.
 *
 * @details      Returns the value of the receive (Rx) error counter for the CAN controller. Useful for diagnosing problems with data reception. Please note
 *               that the value of the counter might not be correct at the moment the API returns it, because the Rx counter is handled asynchronously in
 *               hardware. Applications should not trust this value for any assumption about the current bus state.
 *
 * @param[in]    ControllerId: CAN controller, whose current Rx error counter shall be acquired.
 * @param[out]   RxErrorCounterPtr: Pointer to a memory location, where the current Rx error counter of the CAN controller will be stored.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Rx error counter available.
 * @retval       E_NOT_OK: Wrong ControllerId, or Rx error counter not available.
 *
 * @Design       SDD_CAN_011, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerRxErrorCounter(VAR(uint8, AUTOMATIC) ControllerId,
                                                                    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) RxErrorCounterPtr) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(ControllerId);
    if (CAN_E_NONE == f_ErrorId_u8) {
      /* Check if parameter RxErrorCounterPtr is a null pointer */
      if (NULL_PTR != RxErrorCounterPtr) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        f_Ret_u8 = Can_DrvGetRxErrCnt(&(Can_l_Config_ptr->CtrlCfg_ptr[ControllerId]), RxErrorCounterPtr);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        f_ErrorId_u8 = CAN_E_PARAM_POINTER;
      }
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_GET_CONTROLLER_RX_ERROR_COUNTER, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_Ret_u8;
}
 
/**
 * @brief        Returns the Tx error counter for a CAN controller. This value might not be available for all CAN controllers, in which case E_NOT_OK would
 *               be returned.
 *
 * @details      Returns the value of the transmit (Tx) error counter for the CAN controller. Helps monitor and analyze transmission issues. Please note
 *               that the value of the counter might not be correct at the moment the API returns it, because the Tx counter is handled asynchronously in
 *               hardware. Applications should not trust this value for any assumption about the current bus state.
 *
 * @param[in]    ControllerId: CAN controller, whose current Rx error counter shall be acquired.
 * @param[out]   TxErrorCounterPtr: Pointer to a memory location, where the current Tx error counter of the CAN controller will be stored.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Tx error counter available.
 * @retval       E_NOT_OK: Wrong ControllerId, or Tx error counter not available.
 *
 * @Design       SDD_CAN_012, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerTxErrorCounter(VAR(uint8, AUTOMATIC) ControllerId,
                                                                    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) TxErrorCounterPtr) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(ControllerId);
    if (CAN_E_NONE == f_ErrorId_u8) {
      /* Check if parameter TxErrorCounterPtr is a null pointer */
      if (NULL_PTR != TxErrorCounterPtr) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        f_Ret_u8 = Can_DrvGetTxErrCnt(&(Can_l_Config_ptr->CtrlCfg_ptr[ControllerId]), TxErrorCounterPtr);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        f_ErrorId_u8 = CAN_E_PARAM_POINTER;
      }
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_GET_CONTROLLER_TX_ERROR_COUNTER, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_Ret_u8;
}
 
#if (STD_ON == CAN_GLOBAL_TIME_SUPPORT)
/**
 * @brief        Returns a time value out of the HW registers according to the capability of the HW.
 *
 * @details      Retrieves a time value from the hardware registers, often used for timestamping functions within CAN communication. Can_GetCurrentTime may
 *               be called within an exclusive area.
 *
 * @param[in]    ControllerId: Index of the addresses CAN controller.
 * @param[out]   timeStampPtr: Current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Successful.
 * @retval       E_NOT_OK: Failed.
 *
 * @Design       SDD_CAN_013, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetCurrentTime(VAR(uint8, AUTOMATIC) ControllerId, P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) timeStampPtr) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter is out of range */
    f_ErrorId_u8 = CAN_CONTROLLER_ID_VALID(ControllerId);
    if (CAN_E_NONE == f_ErrorId_u8) {
      /* Check if parameter timeStampPtr is a null pointer */
      if (NULL_PTR != timeStampPtr) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        f_Ret_u8 = Can_DrvGetCurrentTime(Can_l_Config_ptr->CtrlCfg_ptr[ControllerId].CtrlOffset_u8, ControllerId, timeStampPtr);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        f_ErrorId_u8 = CAN_E_PARAM_POINTER;
      }
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_GET_CURRENT_TIME, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_Ret_u8;
}
 
/**
 * @brief        Activates egress time stamping on a dedicated HTH.
 *
 * @details      Activates egress (transmit) timestamping on a dedicated HTH. Some HW does store once the egress time stamp marker and some HW needs it always
 *               before transmission. There will be no ""disable"" functionality, due to the fact, that the message type is always ""time stamped"" by network
 *               design.
 *
 * @param[in]    Hth: information which HW-transmit handle shall be used for enabling the time stamp.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_014, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_EnableEgressTimeStamp(VAR(Can_HwHandleType, AUTOMATIC) Hth) {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter Hth is not a configured Hardware Transmit Handle */
    f_ErrorId_u8 = CAN_HTH_PARAM_VALID(Hth);
    if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
      Can_DrvEnableEgressTimeStamp(Hth - Can_l_Config_ptr->Hth1stId_u8);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_ENABLE_EGRESS_TIMESTAMP, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return;
}
 
 
/**
 * @brief        Reads back the egress time stamp on a dedicated message object. It needs to be called within the TxConfirmation() function.
 *
 * @details      Reads back the egress timestamp from a dedicated message object, providing the time that a specific message was transmitted.
 *
 * @param[in]    TxPduId: L-PDU handle of CAN L-PDU for which the time stamp shall be returned.
 * @param[in]    Hth: HW-transmit handle for which the egress timestamp shall be retrieved.
 * @param[out]   timeStampPtr: Current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Success.
 * @retval       E_NOT_OK: Failed to read time stamp.
 *
 * @Design       SDD_CAN_015, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetEgressTimeStamp(VAR(PduIdType, AUTOMATIC) TxPduId,
                                                           VAR(Can_HwHandleType, AUTOMATIC) Hth,
                                                           P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) timeStampPtr) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
 
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  f_Ret_u8 = CAN_E_NOT_OK;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter Hth is not a configured Hardware Transmit Handle */
    f_ErrorId_u8 = CAN_HTH_PARAM_VALID(Hth);
    if (CAN_E_NONE == f_ErrorId_u8) {
      /* Check if parameter timeStampPtr is a null pointer */
      if (NULL_PTR != timeStampPtr) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        f_Ret_u8 = Can_DrvGetEgressTimeStamp(TxPduId, (Hth - Can_l_Config_ptr->Hth1stId_u8), timeStampPtr);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        f_ErrorId_u8 = CAN_E_PARAM_POINTER;
      }
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
 
  /* Check if the parameter TxPduId for being valid */
  if ((CAN_E_NOT_OK == f_Ret_u8) && (CAN_E_NONE == f_ErrorId_u8)) {
    f_ErrorId_u8 = CAN_E_PARAM_LPDU;
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_GET_EGRESS_TIMESTAMP, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
  return f_Ret_u8;
}
 
/**
 * @brief        Reads back the ingress time stamp on a dedicated message object. It needs to be called within the RxIndication() function.
 *
 * @details      Reads back the ingress (receive) timestamp from a dedicated message object, useful for analyzing message arrival times.
 *
 * @param[in]    Hrh: HW-receive handle for which the ingress timestamp shall be retrieved.
 * @param[out]   timeStampPtr: Current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Success.
 * @retval       E_NOT_OK: Failed to read time stamp.
 *
 * @Design       SDD_CAN_016, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetIngressTimeStamp(VAR(Can_HwHandleType, AUTOMATIC) Hrh,
                                                            P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) timeStampPtr) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  VAR(uint8, AUTOMATIC) f_CtrlId_u8;
  VAR(uint8, TYPEDEF) f_HrhIdx_u8;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  f_Ret_u8 = CAN_E_NOT_OK;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
    /* Loop thougth all Controller to find the target Controller Id */
    for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
      if (Hrh == Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8].HrhConfig_ptr->HrhIdx_u8) {
        /* Get controller Id */
        f_CtrlId_u8 = Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8].CtrlId_u8;
        /* Break if find the mapping id */
        break;
 
      } else {
        /* Do nothing */
      }
    }
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    /* If the f_Idx_u8 is out range meant to the parameter Hrh is not a configured Hardware Receive Handle */
    if (CAN_CONTROLLER_CFG_NUM > f_Idx_u8) {
      /* Check if parameter timeStampPtr is a null pointer */
      if (NULL_PTR != timeStampPtr) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        /* Get Hardware Object pointer */
        f_HrhIdx_u8 = Can_l_Config_ptr->CtrlCfg_ptr[f_CtrlId_u8].HrhConfig_ptr->HrhIdx_u8;
 
        f_Ret_u8 = Can_DrvGetIngressTimeStamp(f_CtrlId_u8, f_HrhIdx_u8, timeStampPtr);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      } else {
        f_ErrorId_u8 = CAN_E_PARAM_POINTER;
      }
    } else {
      f_ErrorId_u8 = CAN_E_PARAM_HANDLE;
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_GET_INGRESS_TIMESTAMP, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
  return f_Ret_u8;
}
 
#endif /* STD_ON == CAN_GLOBAL_TIME_SUPPORT */
 
/**
 * @brief        This function is called by CanIf to pass a CAN message to CanDrv for transmission.
 *
 * @details      Called by CanIf to pass a CAN message to CanDrv for transmission. Ensures the message is sent through the correct controller and handled
 *               appropriately.
 *
 * @param[in]    Hth: information which HW-transmit handle shall be used for transmit. Implicitly this is also the information about the controller to use
 *                    because the Hth numbers are unique inside one hardware unit.
 * @param[in]    PduInfo: Pointer to SDU user memory, Data Length and Identifier.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Write command has been accepted.
 * @retval       E_NOT_OK: development error occurred.
 * @retval       CAN_BUSY: No TX hardware buffer available or pre-emptive call of Can_Write that can't be implemented re-entrant (see Can_ReturnType)
 *
 * @Design       SDD_CAN_017, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_Write(VAR(Can_HwHandleType, AUTOMATIC) Hth, P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo) {
  VAR(Std_ReturnType, AUTOMATIC) f_Ret_u8;
  VAR(uint8, AUTOMATIC) f_CtrlId_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_Controller_ptr;
  P2CONST(Can_HthHwObjCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_HwObject_ptr;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
 
  f_Ret_u8 = CAN_E_NOT_OK;
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
    /* Check if the parameter Hth is not a configured Hardware Transmit Handle */
    f_ErrorId_u8 = CAN_HTH_PARAM_VALID(Hth);
    if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
      /* Get Controller Id */
      f_CtrlId_u8 = Can_l_Config_ptr->HthHwObjCfg_ptr[Hth - Can_l_Config_ptr->Hth1stId_u8].CtrlId_u8;
      /* Get Controller configuration pointer */
      f_Controller_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_CtrlId_u8]);
 
      f_HwObject_ptr = &(Can_l_Config_ptr->HthHwObjCfg_ptr[Hth - Can_l_Config_ptr->Hth1stId_u8]);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
      /* Check the valid of PduInfo parameter */
      f_ErrorId_u8 = CAN_WRITE_PDU_PARAM_VALID(f_Controller_ptr, f_HwObject_ptr, PduInfo);
 
      if (CAN_E_NONE == f_ErrorId_u8) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
        f_Ret_u8 = Can_ProcessTransmit(f_Controller_ptr, f_HwObject_ptr, PduInfo);
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
 
      } else {
        /* Do nothing */
      }
    } else {
      /* Do nothing */
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_WRITE_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
 
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_Ret_u8;
}
 
/**
 * @brief        This function performs the polling of TX confirmation when CAN_TX_PROCESSING is set to POLLING.
 *
 * @details      Performs polling for TX (transmit) confirmation events when CAN_TX_PROCESSING is configured for polling mode. This function checks for
 *               completed transmissions and reports them to higher layers.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_018, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Write(void) {
#if ((STD_ON == CAN_TX_POLLING_PROCESSING) || (STD_ON == CAN_GLOBAL_TIME_SUPPORT))
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_CtrlCfg_ptr;
#if (STD_ON == CAN_TX_POLLING_PROCESSING)
  VAR(uint8, AUTOMATIC) f_TxMsgCnt_u8;
#endif /* STD_ON == CAN_TX_POLLING_PROCESSING */
#if ((STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT) && (STD_ON == CAN_TX_POLLING_PROCESSING))
  VAR(uint8, AUTOMATIC) f_Idx2_u8;
  VAR(PduIdType, AUTOMATIC) f_PduId_aa[CAN_STB_FIFO_DEPTH];
#elif ((STD_OFF == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT) && (STD_ON == CAN_TX_POLLING_PROCESSING))
  VAR(PduIdType, AUTOMATIC) f_PduId_u16;
#endif /* (STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT) && (STD_ON == CAN_TX_POLLING_PROCESSING) */
 
  if (CAN_READY == Can_l_GlobalState_en) {
    for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
      /* Get controller config pointer */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
 
#if (STD_ON == CAN_GLOBAL_TIME_SUPPORT)
      if (CAN_TRUE == f_CtrlCfg_ptr->Active_bool) {
        /* Process current time stamp  in each cycle polling MainFunction Write */
        Can_DrvProcessCurrentTime(f_CtrlCfg_ptr);
      } else {
        /* Do nothing */
      }
#endif /* STD_ON == CAN_GLOBAL_TIME_SUPPORT */
 
#if (STD_ON == CAN_TX_POLLING_PROCESSING)
      /* Check if the process is polling */
      if (CAN_TX_INT_ENABLE != (CAN_TX_INT_ENABLE & f_CtrlCfg_ptr->CtrlMode_u8)) {
        /* Process for Tx message */
#if (STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT)
 
        f_TxMsgCnt_u8 = Can_DrvProcessTxMsg(f_CtrlCfg_ptr, &f_PduId_aa[CAN_U8_DAT_0]);
 
        /* Notify the transmitted message */
        for (f_Idx2_u8 = CAN_U8_DAT_0; f_Idx2_u8 < f_TxMsgCnt_u8; f_Idx2_u8++) {
          CanIf_TxConfirmation(f_PduId_aa[f_Idx2_u8]);
        }
 
#else
        f_TxMsgCnt_u8 = Can_DrvProcessTxMsg(f_CtrlCfg_ptr, &f_PduId_u16);
        /* Notify the TxPdu transmitted message when Tx Primary buffer has been process. */
        if (CAN_U8_DAT_1 == f_TxMsgCnt_u8){
          CanIf_TxConfirmation(f_PduId_u16);
        } else {
          /* Do nothing */
        }
 
 
#endif /* STD_ON == CAN_MULTIPLEXED_TRANSMISSION_SUPPORT */
      } else {
        /* Do nothing */
      }
#endif /* STD_ON == CAN_TX_POLLING_PROCESSING */
    }
 
  } else {
    /* Do nothing */
  }
  return;
#endif /* (STD_ON == CAN_TX_POLLING_PROCESSING) || (STD_ON == CAN_GLOBAL_TIME_SUPPORT) */
}
 
/**
 * @brief        This function performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
 *
 * @details      Performs polling for RX (receive) indication events when CAN_RX_PROCESSING is configured for polling. This function scans for received CAN
 *               messages and notifies higher layers.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_019, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Read(void) {
#if ((STD_ON == CAN_RX_POLLING_PROCESSING) || (STD_ON == CAN_GLOBAL_TIME_SUPPORT))
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_CtrlCfg_ptr;
 
  if (CAN_READY == Can_l_GlobalState_en) {
    for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
      /* Get controller config pointer */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
 
#if (STD_ON == CAN_GLOBAL_TIME_SUPPORT)
      if (CAN_TRUE == f_CtrlCfg_ptr->Active_bool) {
        /* Process current time stamp in each cycle polling MainFunction Read*/
        Can_DrvProcessCurrentTime(f_CtrlCfg_ptr);
      } else {
        /* Do nothing */
      }
#endif /* STD_ON == CAN_GLOBAL_TIME_SUPPORT */
 
#if (STD_ON == CAN_RX_POLLING_PROCESSING)
      /* Check if the process is polling */
      if (CAN_RX_INT_ENABLE != (CAN_RX_INT_ENABLE & f_CtrlCfg_ptr->IrqFlag_u8)) {
        /* Process for Rx message */
        Can_ProcessMsgRead(f_CtrlCfg_ptr);
 
      } else {
        /* Do nothing */
      }
#endif /* STD_ON == CAN_RX_POLLING_PROCESSING */
    }
 
  } else {
    /* Do nothing */
  }
#endif /* (STD_ON == CAN_RX_POLLING_PROCESSING) || (STD_ON == CAN_GLOBAL_TIME_SUPPORT) */
  return;
}
 
 
/**
 * @brief        This function performs the polling of bus-off events that are configured statically as 'to be polled'.
 *
 * @details      Performs polling for bus-off events that are statically configured to be polled. This function monitors the CAN controller for bus-off status
 *               and handles recovery or notification as required.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_020, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_BusOff(void) {
#if (STD_ON == CAN_BUSOFF_POLLING_PROCESSING)
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_CtrlCfg_ptr;
 
  if (CAN_READY == Can_l_GlobalState_en) {
    for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
      /* Get controller config pointer */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
 
      /* Check if the process is polling */
      if (CAN_BUSOFF_INT_ENABLE != (CAN_BUSOFF_INT_ENABLE & f_CtrlCfg_ptr->CtrlMode_u8)) {
        /* Check if the Busoff error is raised */
        if (CAN_TRUE == Can_DrvBusOff(f_CtrlCfg_ptr)) {
          /* Driver process when Busoff */
          Can_DrvProcessBusOff(f_CtrlCfg_ptr);
 
          /* Update controller state */
          Can_NotifyUpperLayer(f_Idx_u8, CAN_CS_STOPPED);
 
          /* Call Busoff Callback function */
          CanIf_ControllerBusOff(f_Idx_u8);
 
        } else {
          /* Do nothing */
        }
      } else {
        /* Do nothing */
      }
    }
 
  } else {
    /* Do nothing */
  }
  return;
#endif /* STD_ON == CAN_BUSOFF_POLLING_PROCESSING */
}
 
#if (STD_ON == CAN_WAKEUP_SUPPORT)
/**
 * @brief        This function performs the polling of wake-up events that are configured statically as 'to be polled'.
 *
 * @details      Performs polling for wake-up events that are statically configured to be polled. This function detects if the CAN controller has been woken up
 *               from sleep mode and reports the event.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_021
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Wakeup(void) {
 
#if (STD_ON == CAN_WAKEUP_POLLING_PROCESSING)
 
#endif /* STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING */
 
  return;
}
#endif /* STD_ON == CAN_WAKEUP_SUPPORT */
 
/**
 * @brief        This function performs the polling of CAN controller mode transitions.
 *
 * @details      Performs polling for CAN controller mode transitions. This function checks for changes in the controller's operating mode (such as Start,
 *               Stop, or Sleep) and notifies upper layers.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_022, SDD_CAN_024, SDD_CAN_025, SDD_CAN_027
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Mode(void) {
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  VAR(boolean, AUTOMATIC) f_RetVal_bool;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_CtrlCfg_ptr;
 
  if (CAN_READY == Can_l_GlobalState_en) {
    for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
      /* Get controller config pointer */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
 
      f_RetVal_bool = Can_ControllerStarted(f_CtrlCfg_ptr);
 
      switch (Can_l_CtrlState_aa[f_Idx_u8]) {
        case CAN_CS_STARTED:
          if (f_RetVal_bool == CAN_FALSE) {
            /* Update controller state */
            Can_NotifyUpperLayer(f_Idx_u8, CAN_CS_STOPPED);
 
          } else {
            /* Do nothing */
          }
          break;
 
        case CAN_CS_STOPPED:
          if (f_RetVal_bool == CAN_TRUE) {
            /* Update controller state */
            Can_NotifyUpperLayer(f_Idx_u8, CAN_CS_STARTED);
 
          } else {
            /* Do nothing */
          }
          break;
 
        default:
          /* Do nothing */
          break;
      }
    }
  } else {
    /* Do nothing */
  }
 
  return;
}
 
#if (STD_ON == CAN_LOOPBACK_TEST_API)
/**
 * @brief        This function performs a CAN controller Loopback test to verify proper operation.
 *
 * @details      Perform the loopback testing function for diagnostic and validation purposes.
 *
 * @param[in]    p_CtrlId_u8: Controller Id.
 * @param[in]    p_PduInfo_ptr: Pointer to SDU user memory, Data Length and Identifier.
 * @param[in]    p_Mode_en: Loopback mode test type.
 * @param[in]    p_TimeoutMs_u32: Timeout value for Loopback test.
 *
 * @return       Can_LoopBackTestResultType.
 * @retval       CAN_LOOPBACK_PASS: Loopback test is pass.
 * @retval       CAN_LOOPBACK_TIMEOUT: Loopback test has timeout error.
 * @retval       CAN_LOOPBACK_DATA_MISMATCH: Loopback test has data mismatch error.
 *
 * @Design       SDD_CAN_023, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Can_LoopBackTestResultType, CAN_CODE_SLOW) Can_LoopBackTest(CONST(uint8, AUTOMATIC) p_CtrlId_u8,
                                                                 P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr,
                                                                 CONST(Can_LoopBackModeType, AUTOMATIC) p_Mode_en,
                                                                 CONST(uint32, AUTOMATIC) p_TimeoutMs_u32) {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) f_ErrorId_u8;
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
  VAR(Can_LoopBackTestResultType, AUTOMATIC) f_TestResult_en;
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
  /* Init return value */
  f_TestResult_en = CAN_LOOPBACK_TIMEOUT;
 
  /* Check if the module is not yet initialized */
  f_ErrorId_u8 = CAN_INITIALIZE_VALID();
  if (CAN_E_NONE == f_ErrorId_u8) {
 
    if (NULL_PTR != p_PduInfo_ptr) {
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
      f_TestResult_en = Can_DrvLoopBackTest(&(Can_l_Config_ptr->CtrlCfg_ptr[p_CtrlId_u8]), p_PduInfo_ptr, p_Mode_en, p_TimeoutMs_u32);
 
      if (CAN_LOOPBACK_PASS != f_TestResult_en) {
        (void)Dem_SetEventStatus(CAN_E_LOOPBACK_TEST_FAILURE, DEM_EVENT_STATUS_FAILED);
      } else {
        /* Do nothing */
      }
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    } else {
      f_ErrorId_u8 = CAN_E_PARAM_POINTER;
    }
  } else {
    /* Do nothing */
  }
 
  if (CAN_E_NONE != f_ErrorId_u8) {
    /* Report to Det */
    (void)Det_ReportError((uint16)CAN_MODULE_ID_H, CAN_INSTANCE_IDX, CAN_LOOPBACKTEST_ID, f_ErrorId_u8);
  } else {
    /* Do nothing */
  }
#endif /* STD_ON == CAN_DEV_ERROR_DETECT */
 
  return f_TestResult_en;
}
#endif /* STD_ON == CAN_LOOPBACK_TEST_API */
 
#define CAN_STOP_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
#if ((STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || \
     (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
 
#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
/**
 * @brief        This function process the CAN controller transmit in interrupt.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_103, SDD_CAN_024
 */
FUNC(void, CAN_CODE_FAST) Can_TxIsrHandler(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8) {
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_CtrlCfg_ptr;
 
  for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
    if (p_CtrlOffset_u8 == Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8].CtrlOffset_u8) {
      /* Get controller config pointer */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
      /* Process the transmit interrupt for the specified controller configuration */
      if (CAN_TRUE == Can_DrvIsTxIrqFlag(f_Idx_u8)) {
        Can_TxIrqProcess(f_CtrlCfg_ptr);
      }
      else {
        /* Do nothing */
      }
 
    } else {
      /* Do nothing */
    }
  }
 
  return;
}
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_RX_INTERRUPT_PROCESSING)
/**
 * @brief        This function process the CAN controller receive in interrupt.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_104, SDD_CAN_024
 */
FUNC(void, CAN_CODE_FAST) Can_RxIsrHandler(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8) {
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_CtrlCfg_ptr;
 
  for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
    if (p_CtrlOffset_u8 == Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8].CtrlOffset_u8) {
      /* Get controller config pointer */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
      /* Process the receive interrupt for the specified controller configuration */
      if (CAN_TRUE == Can_DrvIsRxIrqFlag(f_Idx_u8)) {
        Can_RxIrqProcess(f_CtrlCfg_ptr);
      }
      else {
        /* Do nothing */
      }
    } else {
      /* Do nothing */
    }
  }
 
  return;
}
#endif /* STD_ON == CAN_RX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING)
/**
 * @brief        This function process the CAN controller busoff event in interrupt.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_105, SDD_CAN_024
 */
FUNC(void, CAN_CODE_FAST) Can_BusOffIsrHandler(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8) {
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_CtrlCfg_ptr;
 
  for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
    if (p_CtrlOffset_u8 == Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8].CtrlOffset_u8) {
      /* Get controller config pointer */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
      /* Process the busoff interrupt for the specified controller configuration */
      Can_BusOffIrqProcess(f_CtrlCfg_ptr, f_Idx_u8);
 
    } else {
      /* Do nothing */
    }
  }
 
  return;
}
#endif /* STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
/**
 * @brief        This function process the CAN controller error in interrupt.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_106, SDD_CAN_024
 */
FUNC(void, CAN_CODE_FAST) Can_ErrorIsrHandler(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8) {
  VAR(uint8, AUTOMATIC) f_Idx_u8;
  P2CONST(Can_ControllerCfgType, AUTOMATIC, CAN_CONFIG_DATA) f_CtrlCfg_ptr;
 
  for (f_Idx_u8 = CAN_U8_DAT_0; f_Idx_u8 < CAN_CONTROLLER_CFG_NUM; f_Idx_u8++) {
    if (p_CtrlOffset_u8 == Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8].CtrlOffset_u8) {
      /* Get controller config pointer */
      f_CtrlCfg_ptr = &(Can_l_Config_ptr->CtrlCfg_ptr[f_Idx_u8]);
      /* Process the Error interrupt for the specified controller configuration */
      Can_ErrorIrqProcess(f_CtrlCfg_ptr);
 
    } else {
      /* Do nothing */
    }
  }
 
  return;
}
#endif /* (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION) */
 
#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"
#endif /* ((STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || \
           (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION)) */
 
/** @} end of group Public_FunctionDefinition */
 
#ifdef __cplusplus
}
#endif
 
/** @} end of group Can */
 
 