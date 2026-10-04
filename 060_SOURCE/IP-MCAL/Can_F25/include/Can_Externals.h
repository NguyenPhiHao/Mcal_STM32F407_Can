/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Can_Externals.h                                              */
/* Version     : v1.00.00                                                     */
/* Contents    : CAN module header file                                       */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of CAN Driver                                                */
/* R22-11                                                                     */
/******************************************************************************/
#ifndef CAN_EXTERNAL_H
#define CAN_EXTERNAL_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/

#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_70_Types.h"
#include "Can_Cfg.h"
#include "Can_70_RL78F2X.h"
#include "Can_70_HW.h"
#include "QINeS_Lite.h"

/*----------------------------------------------------------------------------*/
/* file version information                                                   */
/*----------------------------------------------------------------------------*/
#define CAN_VENDOR_ID_EXTERNAL_H                    ( 70U )
#define CAN_MODULE_ID_EXTERNAL_H                    ( 80U )

#define CAN_AR_RELEASE_MAJOR_VERSION_EXTERNAL_H     ( 22U )
#define CAN_AR_RELEASE_MINOR_VERSION_EXTERNAL_H     ( 11U )
#define CAN_AR_RELEASE_REVISION_VERSION_EXTERNAL_H  (  0U )

#define CAN_SW_MAJOR_VERSION_EXTERNAL_H             (  1U )
#define CAN_SW_MINOR_VERSION_EXTERNAL_H             (  0U )
#define CAN_SW_PATCH_VERSION_EXTERNAL_H             (  0U )

/*----------------------------------------------------------------------------*/
/* file version checks                                                        */
/*----------------------------------------------------------------------------*/

/*---------------ComStack_Types.h--------------------------------------------------*/

/* Check if current file and ComStack_Types.h header file are of the same Autosar version */
#if (( CAN_AR_RELEASE_MAJOR_VERSION_EXTERNAL_H    != COMSTACKTYPE_AR_RELEASE_MAJOR_VERSION )  ||  \
     ( CAN_AR_RELEASE_MINOR_VERSION_EXTERNAL_H    != COMSTACKTYPE_AR_RELEASE_MINOR_VERSION )      \
    )
    #error "AUTOSAR Version Numbers of Can.h and ComStack_Types.h are different"
#endif      /* End of Autosar Version check */

/*---------------Can_70_Types.h--------------------------------------------------*/

/* Check if current file and Can_70_Types.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID_EXTERNAL_H    != CAN_70_VENDOR_ID_TYPES_H))
    #error "VENDOR ID for Can.h and Can_70_Types.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID_EXTERNAL_H    != CAN_70_MODULE_ID_TYPES_H))
    #error "MODULE ID of Can.h and Can_70_Types.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_70_Types.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_EXTERNAL_H    != CAN_70_SW_MAJOR_VERSION_TYPES_H)  ||  \
     (CAN_SW_MINOR_VERSION_EXTERNAL_H    != CAN_70_SW_MINOR_VERSION_TYPES_H)  ||  \
     (CAN_SW_PATCH_VERSION_EXTERNAL_H    != CAN_70_SW_PATCH_VERSION_TYPES_H)
    )
    #error "Software Version Numbers of Can.h and Can_70_Types.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_70_Types.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_EXTERNAL_H    != CAN_70_AR_RELEASE_MAJOR_VERSION_TYPES_H    )  ||  \
     (CAN_AR_RELEASE_MINOR_VERSION_EXTERNAL_H    != CAN_70_AR_RELEASE_MINOR_VERSION_TYPES_H    )  ||  \
     (CAN_AR_RELEASE_REVISION_VERSION_EXTERNAL_H != CAN_70_AR_RELEASE_REVISION_VERSION_TYPES_H )      \
    )
    #error "AUTOSAR Version Numbers of Can.h and Can_70_Types.h are different"
#endif      /* End of Autosar Version check */

/*---------------Can_Cfg.h--------------------------------------------------*/

/* Check if current file and Can_Cfg.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID_EXTERNAL_H    != CAN_70_VENDOR_ID_CFG_H))
    #error "VENDOR ID for Can.h and Can_Cfg.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID_EXTERNAL_H    != CAN_70_MODULE_ID_CFG_H))
    #error "MODULE ID for Can.h and Can_Cfg.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_Cfg.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_EXTERNAL_H    != CAN_70_SW_MAJOR_VERSION_CFG_H )  ||  \
     (CAN_SW_MINOR_VERSION_EXTERNAL_H    != CAN_70_SW_MINOR_VERSION_CFG_H )  ||  \
     (CAN_SW_PATCH_VERSION_EXTERNAL_H    != CAN_70_SW_PATCH_VERSION_CFG_H )      \
    )
    #error "Software Version Numbers of Can.h and Can_Cfg.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_Cfg.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_EXTERNAL_H    != CAN_70_AR_RELEASE_MAJOR_VERSION_CFG_H    )   ||  \
     (CAN_AR_RELEASE_MINOR_VERSION_EXTERNAL_H    != CAN_70_AR_RELEASE_MINOR_VERSION_CFG_H    )   ||  \
     (CAN_AR_RELEASE_REVISION_VERSION_EXTERNAL_H != CAN_70_AR_RELEASE_REVISION_VERSION_CFG_H )       \
    )
    #error "AUTOSAR Version Numbers of Can.h and Can_Cfg.h are different"
#endif      /* End of Autosar Version check */

/*---------------Can_70_RL78F2X.h--------------------------------------------------*/

/* Check if current file and Can_70_RL78F2X.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID_EXTERNAL_H    != CAN_70_VENDOR_ID_RL78F2X_H))
    #error "VENDOR ID for Can.h and Can_70_RL78F2X.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID_EXTERNAL_H    != CAN_70_MODULE_ID_RL78F2X_H))
    #error "MODULE ID for Can.h and Can_70_RL78F2X.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_70_RL78F2X.h header file are of the same Software version */
#if (( CAN_SW_MAJOR_VERSION_EXTERNAL_H    != CAN_70_SW_MAJOR_VERSION_RL78F2X_H )  ||  \
     ( CAN_SW_MINOR_VERSION_EXTERNAL_H    != CAN_70_SW_MINOR_VERSION_RL78F2X_H )  ||  \
     ( CAN_SW_PATCH_VERSION_EXTERNAL_H    != CAN_70_SW_PATCH_VERSION_RL78F2X_H )      \
    )
    #error "Software Version Numbers of Can.h and Can_70_RL78F2X.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_70_RL78F2X.h header file are of the same Autosar version */
#if (( CAN_AR_RELEASE_MAJOR_VERSION_EXTERNAL_H    != CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_H    )  ||  \
     ( CAN_AR_RELEASE_MINOR_VERSION_EXTERNAL_H    != CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_H    )  ||  \
     ( CAN_AR_RELEASE_REVISION_VERSION_EXTERNAL_H != CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_H )      \
    )
    #error "AUTOSAR Version Numbers of Can.h and Can_70_RL78F2X.h are different"
#endif      /* End of Autosar Version check */

/*---------------Can_70_HW.h--------------------------------------------------*/

/* Check if current file and Can_70_HW.h header file are of the same Vendor ID */
#if ((CAN_VENDOR_ID_EXTERNAL_H    != CAN_70_VENDOR_ID_HW_H))
    #error "VENDOR ID for Can.h and Can_70_HW.h are different"
#endif      /* End of Vendor Id Version check */

#if ((CAN_MODULE_ID_EXTERNAL_H    != CAN_70_MODULE_ID_HW_H))
    #error "MODULE ID for Can.h and Can_70_HW.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_70_HW.h header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_EXTERNAL_H    != CAN_70_SW_MAJOR_VERSION_HW_H) || \
     (CAN_SW_MINOR_VERSION_EXTERNAL_H    != CAN_70_SW_MINOR_VERSION_HW_H) || \
     (CAN_SW_PATCH_VERSION_EXTERNAL_H    != CAN_70_SW_PATCH_VERSION_HW_H))
    #error "Software Version Numbers of Can.h and Can_70_HW.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_70_HW.h header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_EXTERNAL_H    != CAN_70_AR_RELEASE_MAJOR_VERSION_HW_H)   || \
     (CAN_AR_RELEASE_MINOR_VERSION_EXTERNAL_H    != CAN_70_AR_RELEASE_MINOR_VERSION_HW_H)   || \
     (CAN_AR_RELEASE_REVISION_VERSION_EXTERNAL_H != CAN_70_AR_RELEASE_REVISION_VERSION_HW_H))
    #error "AUTOSAR Version Numbers of Can.h and Can_70_HW.h are different"
#endif      /* End of Autosar Version check */

/* Can_Externals.h version check end */

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* external variables                                                         */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* global constants                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/

#define CAN_START_SEC_CODE_LOCAL
#include "Can_MemMap.h"

extern bool_t LPDU_Callout_Func( uint8 Hrh, Can_IdType CanId, uint8 CanDataLegth, const uint8* CanSduPtr );

#define CAN_STOP_SEC_CODE_LOCAL
#include "Can_MemMap.h"

#endif  /* #ifndef CAN_EXTERNAL_H */
/* EOF Can_Externals.h ****************************************************************/
