/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Std_Types.h                                                  */
/* Version     : v1.00.00                                                     */
/* Contents    : AUTOSAR Stndard Variable Data Types                          */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of Standard Types                                            */
/* R22-11                                                                     */
/******************************************************************************/

/* [SWS_Std_00014] */
#ifndef STD_TYPES_H
#define STD_TYPES_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Platform_Types.h"
#include "Compiler.h"

/*----------------------------------------------------------------------------*/
/*  type definitions                                                          */
/*----------------------------------------------------------------------------*/
/* [SWS_Std_00005] */
typedef uint8 Std_ReturnType;

/* [SWS_Std_00015] */
typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8  sw_major_version;
    uint8  sw_minor_version;
    uint8  sw_patch_version;
} Std_VersionInfoType;

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/
/* [SWS_Std_00006][SWS_Std_00011] */
#ifndef E_OK
#define E_OK                    ((Std_ReturnType)0)
#endif
#define E_NOT_OK                ((Std_ReturnType)1)

#define E_NO_DTC_AVAILABLE      ((Std_ReturnType)2)
#define E_SESSION_NOT_ALLOWED   ((Std_ReturnType)4)
#define E_PROTOCOL_NOT_ALLOWED  ((Std_ReturnType)5)
#define E_REQUEST_NOT_ACCEPTED  ((Std_ReturnType)8)
#define E_REQUEST_ENV_NOK       ((Std_ReturnType)9)
#define E_PENDING               ((Std_ReturnType)10)
#define E_COMPARE_KEY_FAILED    ((Std_ReturnType)11)
#define E_FORCE_RCRRP           ((Std_ReturnType)12)
#define DCM_E_PENDING          (( Std_ReturnType ) 2u )
#define DCM_E_FORCE_RCRRP      (( Std_ReturnType ) 3u )

/* Det error code for EcuM AlarmClock. */
#define ECUM_E_EARLIER_ACTIVE   (( Std_ReturnType ) 3u )
#define ECUM_E_PAST             (( Std_ReturnType ) 4u )
#define ECUM_E_NOT_ACTIVE       (( Std_ReturnType ) 5u )

/* [SWS_Std_00007] */
#define STD_HIGH                (0x01U)
#define STD_LOW                 (0x00U)

/* [SWS_Std_00013] */
#define STD_ACTIVE              (0x01U)
#define STD_IDLE                (0x00U)

/* [SWS_Std_00010] */
#define STD_ON                  (0x01U)
#define STD_OFF                 (0x00U)

#define STD_UNF                 ((uint8)0x02U)

#ifndef NULL
#define NULL                    (0)
#endif

#ifndef MIN
#define MIN                     (_x,_y) (((_x) < (_y)) ? (_x) : (_y))
#endif
#ifndef MAX
#define MAX                     (_x,_y) (((_x) > (_y)) ? (_x) : (_y))
#endif

/* Interim support for the ECUSAR */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION      (22U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION      (11U)
#define STD_TYPES_AR_RELEASE_REVISION_VERSION   (0U)

#endif /* STD_TYPES_H */
/* Std_Types.h ****************************************************************/
