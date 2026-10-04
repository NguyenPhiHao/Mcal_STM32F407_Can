/**************************************************************************************************************************************************************/
/**
 * @file      : Can_Types.h
 * @brief     : Can_Types header file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
#ifndef CAN_TYPES_H
#define CAN_TYPES_H
 
/**
 * @addtogroup Can_Types
 * @brief Autosar R23-11 Can_Types header
 * @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif

#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"

/*-------------------------------------------------------------------------------------------------------------------------|
| SOURCE FILE VERSION                                                                             |
|-------------------------------------------------------------------------------------------------------------------------*/
/* Common published information */
#define CAN_TYPES_VENDOR_ID_H                    (0x00U)
#define CAN_TYPES_MODULE_ID_H                    (0x50U)

/* Software version: 1.0.0 */
#define CAN_TYPES_SW_MAJOR_VERSION_H             (0x01U)
#define CAN_TYPES_SW_MINOR_VERSION_H             (0x00U)
#define CAN_TYPES_SW_PATCH_VERSION_H             (0x00U)

/* AUTOSAR release version: 4.4.0 */
#define CAN_TYPES_AR_RELEASE_MAJOR_VERSION_H     (0x04U)
#define CAN_TYPES_AR_RELEASE_MINOR_VERSION_H     (0x04U)
#define CAN_TYPES_AR_RELEASE_REVISION_VERSION_H  (0x00U)

/*-------------------------------------------------------------------------------------------------------------------------|
| FILE VERSION CHECK                                                                              |
|-------------------------------------------------------------------------------------------------------------------------*/
/* Check if current file and Can_Cfg.h are of the same vendor */
#if (CAN_TYPES_VENDOR_ID_H != CAN_CFG_VENDOR_ID_H)
#error "Can_Types.h and Can_Cfg.h have different vendor ids"
#endif
 
/* Check if current file and Can_Cfg.h are the same Module Id. */
#if (CAN_TYPES_MODULE_ID_H != CAN_CFG_MODULE_ID_H)
#error "Module ID Numbers of Can_Types.h and Can_Cfg.h are different."
#endif
 
/* Check if current file and Can_Cfg.h are of the same Software version */
#if ((CAN_TYPES_SW_MAJOR_VERSION_H != CAN_CFG_SW_MAJOR_VERSION_H) || \
     (CAN_TYPES_SW_MINOR_VERSION_H != CAN_CFG_SW_MINOR_VERSION_H) || \
     (CAN_TYPES_SW_PATCH_VERSION_H != CAN_CFG_SW_PATCH_VERSION_H))
#error "Software Version Numbers of Can_Types.h and Can_Cfg.h"
#endif
 
/* Check if current file and Can_Cfg.h are of the same Autosar version */
#if ((CAN_TYPES_AR_RELEASE_MAJOR_VERSION_H    != CAN_CFG_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_TYPES_AR_RELEASE_MINOR_VERSION_H    != CAN_CFG_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_TYPES_AR_RELEASE_REVISION_VERSION_H != CAN_CFG_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of Can_Types.h and Can_Cfg.h"
#endif
 
/* Check if current file and Can_Cfg.h are the same Module Id. */
#if (CAN_TYPES_MODULE_ID_H != CAN_GENERALTYPES_MODULE_ID_H)
#error "Module ID Numbers of Can_Types.h and Can_GeneralTypes.h are different."
#endif
 
/* Check if current file and Can_GeneralTypes.h are of the same vendor */
#if (CAN_TYPES_VENDOR_ID_H != CAN_GENERALTYPES_VENDOR_ID_H)
#error "Can_Types.h and Can_GeneralTypes.h have different vendor ids"
#endif
 
/* Check if current file and Can_GeneralTypes.h are the same Module Id. */
#if (CAN_TYPES_MODULE_ID_H != CAN_GENERALTYPES_MODULE_ID_H)
#error "Module ID Numbers of Can_Types.h and Can_GeneralTypes.h are different."
#endif
 
/* Check if current file and Can_GeneralTypes.h are of the same Software version */
#if ((CAN_TYPES_SW_MAJOR_VERSION_H != CAN_GENERALTYPES_SW_MAJOR_VERSION_H) || \
     (CAN_TYPES_SW_MINOR_VERSION_H != CAN_GENERALTYPES_SW_MINOR_VERSION_H) || \
     (CAN_TYPES_SW_PATCH_VERSION_H != CAN_GENERALTYPES_SW_PATCH_VERSION_H))
#error "Software Version Numbers of Can_Types.h and Can_GeneralTypes.h"
#endif
 
/* Check if current file and Can_GeneralTypes.h are of the same Autosar version */
#if ((CAN_TYPES_AR_RELEASE_MAJOR_VERSION_H    != CAN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_TYPES_AR_RELEASE_MINOR_VERSION_H    != CAN_GENERALTYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_TYPES_AR_RELEASE_REVISION_VERSION_H != CAN_GENERALTYPES_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of Can_Types.h and Can_GeneralTypes.h"
#endif
 
/**
 * @brief Define boolean macros castype.
 */
#define CAN_TRUE                         ((boolean)TRUE)
#define CAN_FALSE                        ((boolean)FALSE)
 
/**
 * @brief Define boolean macros castype.
 */
#define CAN_E_OK                         ((Std_ReturnType)E_OK)
#define CAN_E_NOT_OK                     ((Std_ReturnType)E_NOT_OK)
 
/**
 * @brief Define number macros uint8.
 */
#define CAN_U8_DAT_0                     ((uint8)0x00U) /*!< Num 0 cast type uint8  */
#define CAN_U8_DAT_1                     ((uint8)0x01U) /*!< Num 1 cast type uint8  */
#define CAN_U8_DAT_2                     ((uint8)0x02U) /*!< Num 2 cast type uint8  */
#define CAN_U8_DAT_3                     ((uint8)0x03U) /*!< Num 3 cast type uint8  */
#define CAN_U8_DAT_4                     ((uint8)0x04U) /*!< Num 4 cast type uint8  */
#define CAN_U8_DAT_5                     ((uint8)0x05U) /*!< Num 5 cast type uint8  */
#define CAN_U8_DAT_6                     ((uint8)0x06U) /*!< Num 6 cast type uint8  */
#define CAN_U8_DAT_7                     ((uint8)0x07U) /*!< Num 7 cast type uint8  */
#define CAN_U8_DAT_8                     ((uint8)0x08U) /*!< Num 8 cast type uint8  */
#define CAN_U8_DAT_9                     ((uint8)0x09U) /*!< Num 9 cast type uint8  */
#define CAN_U8_DAT_10                    ((uint8)0x0AU) /*!< Num 10 cast to uint8   */
#define CAN_U8_DAT_11                    ((uint8)0x0BU) /*!< Num 11 cast to uint8   */
#define CAN_U8_DAT_12                    ((uint8)0x0CU) /*!< Num 12 cast to uint8   */
#define CAN_U8_DAT_13                    ((uint8)0x0DU) /*!< Num 13 cast to uint8   */
#define CAN_U8_DAT_14                    ((uint8)0x0EU) /*!< Num 14 cast to uint8   */
#define CAN_U8_DAT_15                    ((uint8)0x0FU) /*!< Num 15 cast to uint8   */
#define CAN_U8_DAT_16                    ((uint8)0x10U) /*!< Num 16 cast to uint8   */
#define CAN_U8_DAT_20                    ((uint8)0x14U) /*!< Num 20 cast to uint8   */
#if (STD_ON == CAN_FD_SUPPORT)
#define CAN_U8_DAT_24                    ((uint8)0x18U) /*!< Num 24 cast to uint8   */
#endif
#define CAN_U8_DAT_32                    ((uint8)0x20U) /*!< Num 32 cast to uint8   */
#define CAN_U8_DAT_48                    ((uint8)0x30U) /*!< Num 48 cast to uint8   */
#define CAN_U8_DAT_64                    ((uint8)0x40U) /*!< Num 64 cast to uint8   */
#define CAN_U8_DAT_65                    ((uint8)0x41U) /*!< Num 65 cast to uint8   */
#define CAN_U8_DAT_MAX                   ((uint8)0xFFU) /*!< Max value of uint8     */
 
/**
 * @brief Define number macros uint16.
 */
#define CAN_U16_DAT_0                    ((uint16)0x0000U) /*!< Num 0 cast type uint16 */
#define CAN_U16_DAT_1                    ((uint16)0x0001U) /*!< Num 1 cast type uint16 */
 
/**
 * @brief Define number macros uint32.
 */
#define CAN_U32_DAT_0                    ((uint32)0x00000000U) /*!< Num 0 cast type uint32  */
#define CAN_U32_DAT_1                    ((uint32)0x00000001U) /*!< Num 1 cast type uint32  */
#define CAN_U32_DAT_4                    ((uint32)0x00000004U) /*!< Num 4 cast type uint32  */
#if ((STD_ON == CAN_GLOBAL_TIME_SUPPORT) || (STD_ON == CAN_RX_FILTER_SUPPORT))
#define CAN_U32_DAT_MAX                  ((uint32)0xFFFFFFFFU) /*!< Max value of uint32     */
#endif
/**
 * @brief Define configuration value for Can controller mode setting.
 */
#define CAN_INTERNAL_LOOPBACK_MODE       ((uint8)0x01U)
#define CAN_EXTERNAL_LOOPBACK_MODE       ((uint8)0x02U)
#define CAN_SELF_ACK_ENABLE_FLAG         ((uint8)0x04U)
#define CAN_LISTEN_ONLY_MODE             ((uint8)0x08U)
#define CAN_NORMAL_OPERATION_MODE        ((uint8)0x00U)
#define CAN_FD_ISO_MODE                  ((uint8)0x10U)
#define CAN_MULTI_TRANSMIT_PRIORITY_MODE ((uint8)0x20U)
 
/**
 * @brief Define configuration value for supported Can frame.
 */
#define CAN_FD_FRAME                     ((uint32)0x40000000U)
#define CAN_EXT_ID                       ((uint32)0x80000000U)
 
/**
 * @brief Define configuration value for supported Can interrupt type.
 */
#define CAN_BUSOFF_INT_ENABLE            ((uint8)0x01U)
#define CAN_TX_INT_ENABLE                ((uint8)0x02U)
#define CAN_RX_INT_ENABLE                ((uint8)0x04U)
#define CAN_BUSOFF_INT_DISABLE           ((uint8)0x00U)
#define CAN_TX_INT_DISABLE               ((uint8)0x00U)
#define CAN_RX_INT_DISABLE               ((uint8)0x00U)
 
/** @} end of Public_MacroDefinition */
 
/** @defgroup Public_TypeDefinition
 *  @{
 */
 
/**
 * @brief Can module State Type.
 */
typedef enum Can_DriverStateType_t {
  CAN_UNINIT = 0U, /*!< Can module not initialized */
  CAN_READY  = 1U  /*!< Can module ready */
} Can_DriverStateType;
 
/**
 * @brief Can Loopback mode Type.
 */
typedef enum Can_LoopBackModeType_t {
  CAN_LBMI_MODE = 0U, /*!< Can loop-back internal mode */
  CAN_LBME_MODE = 1U  /*!< Can loop-back external mode */
} Can_LoopBackModeType;
 
/**
 * @brief Can Loopback test result Type.
 */
typedef enum Can_LoopBackTestResultType_t {
  CAN_LOOPBACK_PASS          = 0U, /*!< Loop-back test passed successfully */
  CAN_LOOPBACK_TIMEOUT       = 1U, /*!< Loop-back test failed due to timeout */
  CAN_LOOPBACK_DATA_MISMATCH = 2U  /*!< Loop-back test failed due to data mismatch */
} Can_LoopBackTestResultType;
 
/**
 * @brief CAN Hardware Object Type
 */
typedef struct Can_HthHwObjCfgType_t {
  CONST(uint8, TYPEDEF) CtrlId_u8;           /*!< CAN controller identifier */
  CONST(uint8, TYPEDEF) HwObjectId_u8;       /*!< CAN hardware object identifier */
  CONST(uint8, TYPEDEF) PaddingVal_u8;       /*!< CAN data padding value */
  CONST(boolean, TYPEDEF) TriggerTxEn_bool;  /*!< Enable trigger transmission */
  CONST(boolean, TYPEDEF) MultipleTxEn_bool; /*!< Enable multiple transmissions */
} Can_HthHwObjCfgType;
 
#if (CAN_RX_FILTER_SUPPORT == STD_ON)
/**
 * @brief Can_RxFilterCfgType
 */
typedef struct Can_RxFilterCfgType_t {
  CONST(uint32, TYPEDEF) FilterCode_u32; /*!< CanHwFilterCode with max 29 bits. */
  CONST(uint32, TYPEDEF) FilterMask_u32; /*!< CanHwFilterMask with max 29 bits. */
} Can_RxFilterCfgType;
#endif /* CAN_RX_FILTER_SUPPORT == STD_ON */
 
/**
 * @brief Can_HrhHwObjType
 */
typedef struct Can_HrhHwObjType_t {
  VAR(uint8, TYPEDEF) HrhIdx_u8; /*!< Hrh identifier */
#if (CAN_RX_FILTER_SUPPORT == STD_ON)
  VAR(uint8, TYPEDEF) HrhFilterNumber_u8;                            /*!< Number filter config set of Hrh */
  P2CONST(Can_RxFilterCfgType, TYPEDEF, AUTOMATIC) FilterConfig_ptr; /*!< Pointer to Hrh filter configure */
#endif                                                               /* CAN_RX_FILTER_SUPPORT == STD_ON */
} Can_HrhHwObjType;
 
/**
 * @brief  This structure used for setting Can baudrate.
 */
typedef struct Can_ControllerBaudrateCfgType_t {
  CONST(uint8, TYPEDEF) BaudrateId_u8; /*!< Can baudrate identifier */
  CONST(uint8, TYPEDEF) PreScaler_u8;  /*!< Clock pre-scaler division factor */
  CONST(uint8, TYPEDEF) Ntseg1_u8;     /*!< Phase segment 1 */
  CONST(uint8, TYPEDEF) Ntseg2_u8;     /*!< Phase segment 2 */
  CONST(uint8, TYPEDEF) Nsjw_u8;       /*!< Resync jump width */
#if (CAN_FD_SUPPORT == STD_ON)
  CONST(boolean, TYPEDEF) FdEn_bool;      /*!< Can Fd frame support bit */
  CONST(boolean, TYPEDEF) BitRateSw_bool; /*!< Enable bit Rate switch inside a CAN FD Format frame*/
  CONST(uint8, TYPEDEF) TdcOffset_u8;     /*!< Specifies the Transmitter Delay Compensation Offset in minimum time quanta */
  CONST(uint8, TYPEDEF) Dsjw_u8;          /*!< Resync jump width = AC_SJW + 1 */
  CONST(uint8, TYPEDEF) Dtseg1_u8;        /*!< Phase segment 1 = AC_SEG_1 + 2 */
  CONST(uint8, TYPEDEF) Dtseg2_u8;        /*!< Phase segment 2 = AC_SEG_2 + 1 */
#endif                                    /* CAN_FD_SUPPORT == STD_ON */
} Can_BaudrateCfgType;
 
/**
 * @brief CAN Controller Configure Type
 */
typedef struct Can_ControllerCfgType_t {
  CONST(uint8, TYPEDEF) CtrlId_u8;                                   /*!< Current Can Controller identifier */
  CONST(uint8, TYPEDEF) CtrlMode_u8;                                 /*!< Enable internal loopback, external loopback, listen only modes. */
  CONST(uint8, TYPEDEF) CtrlOffset_u8;                               /*!< Current Can Controller Offset */
  CONST(boolean, TYPEDEF) Active_bool;                               /*!< Can Controller active Status configure bit */
  CONST(uint8, TYPEDEF) IrqFlag_u8;                                  /*!< Can interrupt config flag */
  P2CONST(Can_HrhHwObjType, TYPEDEF, CAN_CONFIG_DATA) HrhConfig_ptr; /*!< Point to hrh structure. */
  CONST(uint16, TYPEDEF) BaudrateNum_u8;                             /*!< Number of Can baudrate */
  CONST(uint16, TYPEDEF) DefaultBaudrateIdx_u8;                      /*!< Can baudrate default index */
  P2CONST(Can_BaudrateCfgType, TYPEDEF, AUTOMATIC) BaudrateCfg_ptr;  /*!< Pointer to Can baudrate configure */
} Can_ControllerCfgType;
 
/**
 * @brief This is the type of the external data structure containing the overall initialization data for the CAN driver and SFR settings affecting all
 *        controllers. Furthermore it contains pointers to controller configuration structures. The contents of the initialization data structure are CAN
 *        hardware specific.
 */
typedef struct Can_ConfigType_t {
  CONST(uint8, TYPEDEF) Hth1stId_u8;                                /*!< First Hth Index of Can Tx */
  CONST(uint32, TYPEDEF) HthHwObjNum_u32;                           /*!< Number of Hardware object */
  P2CONST(Can_HthHwObjCfgType, TYPEDEF, AUTOMATIC) HthHwObjCfg_ptr; /*!< Can Hardware Object Config Pointer */
  CONST(uint32, TYPEDEF) CtrlNum_u32;                               /*!< Number of CAN controller  */
  P2CONST(Can_ControllerCfgType, TYPEDEF, AUTOMATIC) CtrlCfg_ptr;   /*!< Can Controller Config pointer */
} Can_ConfigType;
 
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
 
/** @} end of group Can_Types */
 
#endif /* CAN_TYPES_H */
 