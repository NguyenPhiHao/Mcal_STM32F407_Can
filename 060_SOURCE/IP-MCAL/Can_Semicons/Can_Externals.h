/**************************************************************************************************************************************************************/
/**
 * @file      : Can_Externals.h
 * @brief     : Can_Externals header file
 *              - Platform: BAT32A259
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
#ifndef CAN_EXTERNALS_H
#define CAN_EXTERNALS_H
 
/** @addtogroup Can_Externals
 *  @brief Autosar R23-11 Can_Externals header
 *  @{
 */
 
#include "Can.h"
 
#ifdef __cplusplus
extern "C" {
#endif
 
/** @defgroup Public_MacroDefinition
 *  @{
 */
#define CAN_EXTERNALS_VENDOR_ID_H                   0x0000U
#define CAN_EXTERNALS_MODULE_ID_H                   0x0050U
#define CAN_EXTERNALS_SW_MAJOR_VERSION_H            0x01U
#define CAN_EXTERNALS_SW_MINOR_VERSION_H            0x00U
#define CAN_EXTERNALS_SW_PATCH_VERSION_H            0x00U
#define CAN_EXTERNALS_AR_RELEASE_MAJOR_VERSION_H    0x04U
#define CAN_EXTERNALS_AR_RELEASE_MINOR_VERSION_H    0x09U
#define CAN_EXTERNALS_AR_RELEASE_REVISION_VERSION_H 0x00U
 
/* Check if current file and Can.h are of the same vendor */
#if (CAN_EXTERNALS_VENDOR_ID_H != CAN_VENDOR_ID_H)
#error "Can_Externals.h and Can.h have different vendor ids"
#endif
 
/* Check if current file and Can.h are the same Module Id. */
#if (CAN_EXTERNALS_MODULE_ID_H != CAN_MODULE_ID_H)
#error "Module ID Numbers of Can_Externals.h and Can.h are different."
#endif
 
/* Check if current file and Can.h are of the same Software version */
#if ((CAN_EXTERNALS_SW_MAJOR_VERSION_H != CAN_SW_MAJOR_VERSION_H) || \
     (CAN_EXTERNALS_SW_MINOR_VERSION_H != CAN_SW_MINOR_VERSION_H) || \
     (CAN_EXTERNALS_SW_PATCH_VERSION_H != CAN_SW_PATCH_VERSION_H))
#error "Software Version Numbers of Can_Externals.h and Can.h"
#endif
 
/* Check if current file and Can.h are of the same Autosar version */
#if ((CAN_EXTERNALS_AR_RELEASE_MAJOR_VERSION_H    != CAN_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_EXTERNALS_AR_RELEASE_MINOR_VERSION_H    != CAN_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_EXTERNALS_AR_RELEASE_REVISION_VERSION_H != CAN_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of Can_Externals.h and Can.h"
#endif
 
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
#if (STD_ON == CAN_LPDU_RECEIVE_CALLOUT_SUPPORT)
#define CAN_START_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
LPDU_CALLOUT_FUNCTION_CALLED_EXTERN
 
#define CAN_STOP_SEC_CODE_SLOW
#include "Can_MemMap.h"
#endif /* STD_ON == CAN_LPDU_RECEIVE_CALLOUT_SUPPORT */
/** @} end of group Public_FunctionDeclaration */
 
#ifdef __cplusplus
}
#endif
 
/** @} end of group Can_Externals */
 
#endif /* CAN_EXTERNALS_H */
 