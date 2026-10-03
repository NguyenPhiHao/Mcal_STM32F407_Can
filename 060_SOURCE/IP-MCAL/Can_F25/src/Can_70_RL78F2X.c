/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Can_70_RL78F2X.c                                             */
/* Version     : v1.00.02                                                     */
/* Contents    : This module provides services for initiating transmissions   */
/*               and calls the callback functions of the CanIf module for     */
/*               notifying events, independently from the hardware. Also it   */
/*               provides services to control the behavior and state of the   */
/*               CAN controllers that belong to the same CAN Hardware Unit.   */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of CAN Driver                                                */
/* R22-11                                                                     */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Can.h"
#include "Can_70_RL78F2X.h"
#include "Can_70_RL78F2X_HwReg.h"
#include "CanIf_Cbk.h"
#include "SchM_Can.h"

/*----------------------------------------------------------------------------*/
/* file version information                                                   */
/*----------------------------------------------------------------------------*/
#define CAN_70_VENDOR_ID_RL78F2X_C                                 ( 70U )
#define CAN_70_MODULE_ID_RL78F2X_C                                 ( 80U )

#define CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_C                  ( 22U )
#define CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_C                  ( 11U )
#define CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_C               (  0U )

#define CAN_70_SW_MAJOR_VERSION_RL78F2X_C                          (  1U )
#define CAN_70_SW_MINOR_VERSION_RL78F2X_C                          (  0U )
#define CAN_70_SW_PATCH_VERSION_RL78F2X_C                          (  0U )

/*----------------------------------------------------------------------------*/
/* file version checks                                                        */
/*----------------------------------------------------------------------------*/

/* Check if current file and Can.h header file are of the same Vendor ID */
#if (CAN_70_VENDOR_ID_RL78F2X_C    != CAN_VENDOR_ID)
    #error "VENDOR ID for Can_70_RL78F2X.c and Can.h are different"
#endif      /* End of Vendor Id Version check */

#if (CAN_70_MODULE_ID_RL78F2X_C    != CAN_MODULE_ID)
    #error "MODULE ID for Can_70_RL78F2X.c and Can.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can.h header file are of the same Software version */
#if ((CAN_70_SW_MAJOR_VERSION_RL78F2X_C    != CAN_SW_MAJOR_VERSION)   || \
     (CAN_70_SW_MINOR_VERSION_RL78F2X_C    != CAN_SW_MINOR_VERSION)   || \
     (CAN_70_SW_PATCH_VERSION_RL78F2X_C    != CAN_SW_PATCH_VERSION))
    #error "Software Version Numbers of Can_70_RL78F2X.c and Can.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_C    != CAN_AR_RELEASE_MAJOR_VERSION)     ||  \
     (CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_C    != CAN_AR_RELEASE_MINOR_VERSION)     ||  \
     (CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_C != CAN_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Can_70_RL78F2X.c and Can.h are different"
#endif      /* End of Autosar Version check */

/*---------------Can_70_RL78F2X.h--------------------------------------------------*/

/* Check if current file and Can_70_RL78F2X.h header file are of the same Vendor ID */
#if (CAN_70_VENDOR_ID_RL78F2X_C    != CAN_70_VENDOR_ID_RL78F2X_H)
    #error "VENDOR ID for Can_70_RL78F2X.c and Can_70_RL78F2X.h are different"
#endif      /* End of Vendor Id Version check */

#if (CAN_70_MODULE_ID_RL78F2X_C    != CAN_70_MODULE_ID_RL78F2X_H)
    #error "MODULE ID for Can_70_RL78F2X.c and Can_70_RL78F2X.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_70_RL78F2X.h header file are of the same Software version */
#if ((CAN_70_SW_MAJOR_VERSION_RL78F2X_C    != CAN_70_SW_MAJOR_VERSION_RL78F2X_H) ||\
     (CAN_70_SW_MINOR_VERSION_RL78F2X_C    != CAN_70_SW_MINOR_VERSION_RL78F2X_H) ||\
     (CAN_70_SW_PATCH_VERSION_RL78F2X_C    != CAN_70_SW_PATCH_VERSION_RL78F2X_H))
    #error "Software Version Numbers of Can_70_RL78F2X.c and Can_70_RL78F2X.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_70_RL78F2X.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_C    != CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_H) ||\
     (CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_C    != CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_H) ||\
     (CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_C != CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_H))
    #error "AUTOSAR Version Numbers of Can_70_RL78F2X.c and Can_70_RL78F2X.h are different"
#endif      /* End of Autosar Version check */

/*---------------Can_70_RL78F2X_HwReg.h--------------------------------------------------*/

/* Check if current file and Can_70_RL78F2X_HwReg.h header file are of the same Vendor ID */
#if (CAN_70_VENDOR_ID_RL78F2X_C    != CAN_70_VENDOR_ID_RL78F2X_HWREG_H)
    #error "VENDOR ID for Can_70_RL78F2X.c and Can_70_RL78F2X_HwReg.h are different"
#endif      /* End of Vendor Id Version check */

#if (CAN_70_MODULE_ID_RL78F2X_C    != CAN_70_MODULE_ID_RL78F2X_HWREG_H)
    #error "MODULE ID for Can_70_RL78F2X.c and Can_70_RL78F2X_HwReg.h are different"
#endif      /* End of Module Id Version check */

/* Check if current file and Can_70_RL78F2X_HwReg.h header file are of the same Software version */
#if ((CAN_70_SW_MAJOR_VERSION_RL78F2X_C    != CAN_70_SW_MAJOR_VERSION_RL78F2X_HWREG_H) ||\
     (CAN_70_SW_MINOR_VERSION_RL78F2X_C    != CAN_70_SW_MINOR_VERSION_RL78F2X_HWREG_H) ||\
     (CAN_70_SW_PATCH_VERSION_RL78F2X_C    != CAN_70_SW_PATCH_VERSION_RL78F2X_HWREG_H))
    #error "Software Version Numbers of Can_70_RL78F2X.c and Can_70_RL78F2X_HwReg.h are different"
#endif      /* End of S/W Version check */

/* Check if current file and Can_70_RL78F2X_HwReg.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_C         != \
      CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_HWREG_H)  || \
     (CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_C         != \
      CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_HWREG_H)  || \
     (CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_C      != \
      CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_HWREG_H))
    #error "AUTOSAR Version Numbers of Can_70_RL78F2X.c and Can_70_RL78F2X_HwReg.h are different"
#endif      /* End of Autosar Version check */

#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------CanIf_Cbk.h--------------------------------------------------*/

/* Check if current file and CanIf_Cbk.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_C    != CANIF_70_AR_RELEASE_MAJOR_VERSION_CBK_H) ||\
     (CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_C    != CANIF_70_AR_RELEASE_MINOR_VERSION_CBK_H))
    #error "AUTOSAR Version Numbers of Can.c and CanIf_Cbk.h are different"
#endif      /* End of Autosar Version check */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */

#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------SchM_Can.h--------------------------------------------------*/

/* Check if current file and SchM_Can.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_C    != RTE_AR_RELEASE_MAJOR_VERSION)   ||\
     (CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_C    != RTE_AR_RELEASE_MINOR_VERSION))
    #error "AUTOSAR Version Numbers of Can.c and SchM_Can.h are different"
#endif      /* End of Autosar Version check */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */

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
/* static functions                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* static variables                                                           */
/*----------------------------------------------------------------------------*/

#define CAN_START_SEC_CONST_8
#include "Can_MemMap.h"

/* Type:Array[Enum] / Alignment:8byte */
/* Index:[GSLPSTS][GHLTSTS][GRSTSTS] */
static const Can_70_GlobalModeType tableGMode[ 2 ][ 2 ][ 2 ] = {
    {
        {
            CAN_70_GMODE_OPERATION,  /* [0][0][0] */
            CAN_70_GMODE_RESET       /* [0][0][1] */
        },
        {
            CAN_70_GMODE_HALT,       /* [0][1][0] */
            CAN_70_GMODE_OTHER       /* [0][1][1] */
        }
    },
    {
        {
            CAN_70_GMODE_OTHER,      /* [1][0][0] */
            CAN_70_GMODE_SLEEP       /* [1][0][1] */
        },
        {
            CAN_70_GMODE_OTHER,      /* [1][1][0] */
            CAN_70_GMODE_OTHER       /* [1][1][1] */
        }
    }
};
   
/* Type:Array[Enum] / Alignment:8byte */
/* Index:[CSLPSTS][CHLTSTS][CRSTSTS] */
static const Can_70_ChannelModeType tableCMode[ 2 ][ 2 ][ 2 ] = {
    {
        {
            CAN_70_CMODE_OPERATION,  /* [0][0][0] */
            CAN_70_CMODE_RESET       /* [0][0][1] */
        },
        {
            CAN_70_CMODE_HALT,       /* [0][1][0] */
                CAN_70_CMODE_OTHER   /* [0][1][1] */
        }
    },
    {
        {
            CAN_70_CMODE_OTHER,      /* [1][0][0] */
            CAN_70_CMODE_SLEEP       /* [1][0][1] */
        },
        {
            CAN_70_CMODE_OTHER,      /* [1][1][0] */
            CAN_70_CMODE_OTHER       /* [1][1][1] */
        }
    }
};

/* Type:Array[boolean] / Alignment:8byte */
/* Index:[GMODE][GMDC] */
static const bool_t tableGTransition[ 5 ][ 4 ] = {
    {
        FALSE, /* [SLEEP    ][00B] */
        FALSE, /* [SLEEP    ][01B] */
        FALSE, /* [SLEEP    ][10B] */
        TRUE   /* [SLEEP    ][11B] */
    },
    {
        TRUE,  /* [RESET    ][00B] */
        FALSE, /* [RESET    ][01B] */
        TRUE,  /* [RESET    ][10B] */
        TRUE   /* [RESET    ][11B] */
    },
    {
        TRUE,  /* [HALT     ][00B] */
        TRUE,  /* [HALT     ][01B] */
        FALSE, /* [HALT     ][10B] */
        TRUE   /* [HALT     ][11B] */
    },
    {
        FALSE, /* [OPERATION][00B] */
        TRUE,  /* [OPERATION][01B] */
        TRUE,  /* [OPERATION][10B] */
        TRUE   /* [OPERATION][11B] */
    },
    {
        TRUE,  /* [OTHER    ][00B] */
        TRUE,  /* [OTHER    ][01B] */
        TRUE,  /* [OTHER    ][10B] */
        TRUE   /* [OTHER    ][11B] */
    }
};

/* Type:Array[boolean] / Alignment:8byte */
/* Index:[CMODE][CMDC] */
static const bool_t tableCTransition[ 5 ][ 4 ] = {
    {
        FALSE, /* [SLEEP    ][00B] */
        FALSE, /* [SLEEP    ][01B] */
        FALSE, /* [SLEEP    ][10B] */
        TRUE   /* [SLEEP    ][11B] */
    },
    {
        TRUE , /* [RESET    ][00B] */
        FALSE, /* [RESET    ][01B] */
        TRUE , /* [RESET    ][10B] */
        TRUE   /* [RESET    ][11B] */
    },
    {
        TRUE,  /* [HALT     ][00B] */
        TRUE,  /* [HALT     ][01B] */
        FALSE, /* [HALT     ][10B] */
        TRUE   /* [HALT     ][11B] */
    },
    {
        FALSE, /* [OPERATION][00B] */
        TRUE,  /* [OPERATION][01B] */
        TRUE,  /* [OPERATION][10B] */
        TRUE   /* [OPERATION][11B] */
    },
    {
        TRUE,  /* [OTHER    ][00B] */
        TRUE,  /* [OTHER    ][01B] */
        TRUE,  /* [OTHER    ][10B] */
        TRUE   /* [OTHER    ][11B] */
    }
};

/* Type:Array[uint8] / Alignment:8byte */
/* Index:[DLC(>0x8)] */
static const uint8 dlcTable[7] = {
    12U,    /* DLC=0x9 */
    16U,    /* DLC=0xA */
    20U,    /* DLC=0xB */
    24U,    /* DLC=0xC */
    32U,    /* DLC=0xD */
    48U,    /* DLC=0xE */
    64U     /* DLC=0xF */
};

#define CAN_STOP_SEC_CONST_8
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

/* Temporary Receive Buffer(size=RxFIFO Max Length) */
static uint8 Can_70_RL78F2X_RxTempBuffer[ CAN_70_NUM_OF_CAN_CHANNEL ][ CAN_70_RL78F2X_RXFIFO_MAX ][ CAN_70_RL78F2X_RXDATAFIELD_MAX ] = { 0 };

#define CAN_STOP_SEC_VAR_INIT_LOCAL_8
#include "Can_MemMap.h"

/*----------------------------------------------------------------------------*/
/* function definitions and function style macros                             */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_CODE_LOCAL
#include "Can_MemMap.h"

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_CheckBusoff                                   */
/* Param       : (in) Controller  CAN Channel of RL78F2x(CAN0/CAN1)           */
/*             : (in) Channel     Channel                                     */
/* Return      : bool_t                 TRUE         Busoff Occur             */
/*                                      FALSE        Not Occur                */
/* Contents    : This function is used to get the Busoff Status               */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
bool_t Can_70_RL78F2X_CheckBusoff( uint8 Controller, uint8 Channel )
{
    volatile const Can_70_RL78F2X_RegCommonAType* regCommonA;
    bool_t                                        ret;
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
   
    /* Get register information */
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ Channel ].RegCommonA;
   
    ret = FALSE;
    if ( 0x0U != ( regCommonA->C0STSL & CAN_70_RL78F2X_MASK_C0STSL_BOSTS ) ) { /* C0STSL  BOSTS */
        ret = TRUE;
    }
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
    return ret;
}

#if(CAN_70_WAKEUP_SUPPORT == TRUE)
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_CheckWakeup                                   */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*               (in) Channel           ChannelID                             */
/* Return      : bool_t                 TRUE         Wakeup Occur             */
/*                                      FALSE        Not Occur                */
/* Contents    : This functions polls the Wakeup Flag and returns true or     */
/*               false based on that                                          */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
bool_t Can_70_RL78F2X_CheckWakeup( uint8 Controller, uint8 Channel )
{
    volatile const Can_70_RL78F2X_RegIfxType* regIfx;
    bool_t                                    ret;
   
    ( void )Channel;    /* unused */
   
    /* Get register information */
    regIfx = Can_70_CanControllerRegInfo[ Controller ].RegIfx[ Can_70_InterruptBitAssign[Controller].RCANxWUP.index ];
   
    ret = FALSE;
    if ( 0x0U != ( regIfx->IF & Can_70_InterruptBitAssign[Controller].RCANxWUP.bit ) ) {
        ret = TRUE;
    }
   
    return ret;
}
#endif  /* #if(CAN_70_WAKEUP_SUPPORT == TRUE) */

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_GetMode                                       */
/* Param       : (in) Controller           CAN Channel of RL78F2x(CAN0/CAN1)  */
/*               (out) CtrlStateInfo       Controller State Information       */
/* Return      : void                                                         */
/* Contents    : Refers to the CAN controller register and returns operating  */
/*               mode information.                                            */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_GetMode( uint8 Controller, Can_70_ControllerStateInfoType* CtrlStateInfo )
{
    volatile const Can_70_RL78F2X_RegMkxType*     regMkx;
    volatile const Can_70_RL78F2X_RegCommonAType* regCommonA;
    volatile const Can_70_RL78F2X_RegCommonBType* regCommonB;
    bool_t                                        bitRCAN0WUPMK;
    bool_t                                        bitGRAMINIT;
    uint8                                         bitGSLPSTS;
    uint8                                         bitGHLTSTS;
    uint8                                         bitGRSTSTS;
    uint8                                         bitGMDC;
    uint8                                         bitCSLPSTS;
    uint8                                         bitCHLTSTS;
    uint8                                         bitCRSTSTS;
    uint8                                         bitCMDC;
   
    /* Get register information */
    regMkx = Can_70_CanControllerRegInfo[ Controller ].RegMkx[ Can_70_InterruptBitAssign[ Controller ].RCANxWUP.index ];
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonA;
    regCommonB = Can_70_CanControllerRegInfo[ Controller ].RegCommonB;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Analyze register values related to CAN controller status.*/    
    if ( 0U == ( Can_70_InterruptBitAssign[ Controller ].RCANxWUP.bit & regMkx->MK ) ) {
        bitRCAN0WUPMK = TRUE;
    } else {
        bitRCAN0WUPMK = FALSE;
    }
   
    if ( 0U == ( CAN_70_RL78F2X_MASK_GSTS_GRAMINIT & regCommonB->GSTS ) ) {
        bitGRAMINIT = TRUE;
    } else {
        bitGRAMINIT = FALSE;
    }
   
    if ( 0U != ( CAN_70_RL78F2X_MASK_GSTS_GSLPSTS & regCommonB->GSTS ) ) {
        bitGSLPSTS = 1U;
    } else {
        bitGSLPSTS = 0U;
    }
 
    if ( 0U != ( CAN_70_RL78F2X_MASK_GSTS_GHLTSTS & regCommonB->GSTS ) ) {
        bitGHLTSTS = 1U;
    } else {
        bitGHLTSTS = 0U;
    }
 
    if ( 0U != ( CAN_70_RL78F2X_MASK_GSTS_GRSTSTS & regCommonB->GSTS ) ) {
        bitGRSTSTS = 1U;
    } else {
        bitGRSTSTS = 0U;
    }
   
    bitGMDC = ( uint8 )( CAN_70_RL78F2X_MASK_GCTRL_GMDC & regCommonB->GCTRL );
   
    if ( 0U != ( CAN_70_RL78F2X_MASK_C0STSL_CSLPSTS & regCommonA->C0STSL ) ) {
        bitCSLPSTS = 1U;
    } else {
        bitCSLPSTS = 0U;
    }
 
    if ( 0U != ( CAN_70_RL78F2X_MASK_C0STSL_CHLTSTS & regCommonA->C0STSL ) ) {
        bitCHLTSTS = 1U;
    } else {
        bitCHLTSTS = 0U;
    }
 
    if ( 0U != ( CAN_70_RL78F2X_MASK_C0STSL_CRSTSTS & regCommonA->C0STSL ) ) {
        bitCRSTSTS = 1U;
    } else {
        bitCRSTSTS = 0U;
    }
   
    bitCMDC = ( uint8 )( CAN_70_RL78F2X_MASK_C0CTRL_CHMDC & regCommonA->C0CTRL );
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
    /* Set return value. */
    CtrlStateInfo->GlobalMode = tableGMode[ bitGSLPSTS ][ bitGHLTSTS ][ bitGRSTSTS ];
    CtrlStateInfo->ChannelMode = tableCMode[ bitCSLPSTS ][ bitCHLTSTS ][ bitCRSTSTS ];
    CtrlStateInfo->WakeupInterrupt = bitRCAN0WUPMK;
    CtrlStateInfo->InTransition = tableGTransition[ CtrlStateInfo->GlobalMode ][ bitGMDC ]
                         & tableCTransition[ CtrlStateInfo->ChannelMode ][ bitCMDC ];
    CtrlStateInfo->RamInitialization = bitGRAMINIT;
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetGlobalMode                                 */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/* Return      : Can_70_GlobalModeType  global mode                           */
/* Contents    : Update CAN controller registers and set global mode.         */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetGlobalMode( uint8 Controller, Can_70_GlobalModeType GlobalMode )
{
    volatile Can_70_RL78F2X_RegCommonBType* regCommonB;
   
    /* Get register information */
    regCommonB = Can_70_CanControllerRegInfo[ Controller ].RegCommonB;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* GlobalMode is set to CAN_70_GMODE_RESET or CAN_70_GMODE_OPERATION */
    if ( CAN_70_GMODE_RESET == GlobalMode ) {
        regCommonB->GCTRL &= ( ~CAN_70_RL78F2X_MASK_GCTRL_GSLPR );
    } else { /* CAN_70_GMODE_OPERATION */
        regCommonB->GCTRL &= ( ~CAN_70_RL78F2X_MASK_GCTRL_GMDC );
    }
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetChannelMode                                */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/*             : (in) ChannelMode       Channel mode                          */
/* Return      : void                                                         */
/* Contents    : Update CAN controller registers and set channel mode.        */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetChannelMode( uint8 Controller, uint8 Channel, Can_70_ChannelModeType ChannelMode )
{
    volatile Can_70_RL78F2X_RegCommonAType* regCommonA;
    uint8                                   bitCSLPSTS;
    uint16                                  bit;
   
    /* Get register information */
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ Channel ].RegCommonA;
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Check if channel mode is sleep. */
    bit = regCommonA->C0STSL & CAN_70_RL78F2X_MASK_C0STSL_CSLPSTS;
    if ( 0U != bit ) {
        bitCSLPSTS = 1U;
    } else {
        bitCSLPSTS = 0U;
    }
 
 
    /* ChannelMode is set to CAN_70_CMODE_RESET or CAN_70_CMODE_OPERATION */
    if ( CAN_70_CMODE_RESET == ChannelMode ) {
        if ( 1U == bitCSLPSTS ) {
            /* Turn off sleep mode and transition to reset mode.*/
            regCommonA->C0CTRL &= ( ~CAN_70_RL78F2X_MASK_C0CTRL_CSLPR );
        } else {
            /* Transition to reset mode. */
            regCommonA->C0CTRL &= ( ~CAN_70_RL78F2X_MASK_C0CTRL_CHMDC );
            regCommonA->C0CTRL |= CAN_70_RL78F2X_BIT_C0CTRL_CHMDC_RESET;
        }
    } else { /* CAN_70_CMODE_OPERATION */
        /* Transition to operation mode. */
        regCommonA->C0CTRL &= ( ~CAN_70_RL78F2X_MASK_C0CTRL_CHMDC );
    }
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetClock                                      */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/* Param       : (in) ClockSource       Clock Source(0x00:fCLK, 0x10:X1clock) */
/* Return      : void                                                         */
/* Contents    : Update the CAN controller register and configure the clock   */
/*               settings.                                                    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetClock( uint8 Controller, uint8 ClockSource )
{
    volatile Can_70_RL78F2X_RegCommonBType* regCommonB;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Get register information */
    regCommonB = Can_70_CanControllerRegInfo[ Controller ].RegCommonB;
   
    regCommonB->GCFGL &= ( ~CAN_70_RL78F2X_MASK_GCFGL_DCS );
    regCommonB->GCFGL |= ClockSource;
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetBaudrate                                   */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) CanConfigSet      Configuration set                     */
/*             : (in) BaudRateConfigID  Baurate configuration ID              */
/* Return      : void                                                         */
/* Contents    : Update the CAN controller register and set the baud rate.    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetBaudrate( uint8 Controller, const Can_ConfigSetType* CanConfigSet, uint16 BaudRateConfigID )
{
    volatile Can_70_RL78F2X_RegCommonAType*   regCommonA;
    uint32                                    CanCpuClock;
    const Can_ControllerBaudrateConfigType*   pBaudrateConfig;
    uint32                                    configBaudrate;
    uint8                                     configPropSeg;
    uint8                                     configSeg1;
    uint8                                     configSeg2;
    uint8                                     configJumpWidth;
    uint16                                    propSegAndSeg1;
    uint16                                    bitNTSEG2;
    uint16                                    bitNTSEG1;
    uint16                                    bitNSJW_H;
    uint16                                    bitNSJW_L;
    uint16                                    bitNBRP;
    uint16                                    regC0NCFGH;
    uint16                                    regC0NCFGL;
    uint16                                    bit;
    uint16                                    numOfTq;
    uint32                                    nbrb;
    const Can_ControllerType*                 canController;
    uint8_least                               controllerIndex;
 
#if ( CAN_70_USE_CANFD == TRUE )
   
    volatile Can_70_RL78F2X_RegCommonJType*   regCommonJ;
    const Can_ControllerFdBaudrateConfigType* pFdBaudrateConfig;
    uint8                                     confSspOffset;
    uint16                                    bitDTSEG2;
    uint16                                    bitDTSEG1;
    uint16                                    bitDSJW;
    uint16                                    bitDBRP;
    uint16                                    bitCLOE;
    uint16                                    bitTDCO;
    uint16                                    bitTDCE;
    uint16                                    regC0DCFGH;
    uint16                                    regC0DCFGL;
    uint16                                    regC0FDCFGH;
    uint16                                    regC0FDCFGL;
   
#endif /* #if ( CAN_70_USE_CANFD == TRUE ) */
   
    /* search can controller setting */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &(CanConfigSet)->CanController[ controllerIndex ];
        if ( Controller == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    CanCpuClock = canController->CanCpuClockRef;
   
    /* Determine baud rate configuration by parameter BaudRateConfigID. */
    if ( CAN_70_NUM_OF_BAUDRATE_TABLE ==  BaudRateConfigID ) {
        pBaudrateConfig = canController->CanControllerDefaultBaudrate;
    } else {
        pBaudrateConfig = &( canController->CanControllerBaudRateConfig[ BaudRateConfigID ] );
    }
   
    /* Get parameters used to set baud rate. */
    configBaudrate = pBaudrateConfig->CanControllerBaudRate;
    configPropSeg = pBaudrateConfig->CanControllerPropSeg;
    configSeg1 = pBaudrateConfig->CanControllerSeg1;
    configSeg2 = pBaudrateConfig->CanControllerSeg2;
    configJumpWidth = pBaudrateConfig->CanControllerSyncJumpWidth;
   
    /* Check if parameters are in valid range. */
    propSegAndSeg1 = ( uint16 )configPropSeg + ( uint16 )configSeg1;
    if ( ( ( 2U <= propSegAndSeg1  ) && ( 256U >= propSegAndSeg1 ) )
      && ( ( 2U <= configSeg2      ) && ( 128U >= configSeg2 ) )
      && ( ( 1U <= configJumpWidth ) && ( 128U >= configJumpWidth ) ) ) {
       
        /* Generate and set register values. */
        numOfTq = 1U + propSegAndSeg1 + ( uint16 )configSeg2;
        nbrb = ( ( uint32 )( CanCpuClock ) / ( configBaudrate * ( uint32 )numOfTq ) ) - ( uint32 )1U;
       
        bit = ( uint16 )configSeg2 - 1U;
        bitNTSEG2 =  bit << 9U;
       
        bit = propSegAndSeg1 - 1U;
        bitNTSEG1 = bit << 1U;
       
        bit = ( uint16 )configJumpWidth - 1U;
        bitNSJW_H = bit >> 7U;
        bitNSJW_L = bit << 10U;
       
        bitNBRP = ( uint16 )nbrb & CAN_70_RL78F2X_MASK_C0NCFGL_NBRP;
       
        regC0NCFGH = bitNTSEG2 | bitNTSEG1 | bitNSJW_H;
        regC0NCFGL = bitNSJW_L | bitNBRP;
       
        regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonA;
        regCommonA->C0NCFGH = regC0NCFGH;
        regCommonA->C0NCFGL = regC0NCFGL;
    } else {
        /* Nothing */
    }
   
#if ( CAN_70_USE_CANFD == TRUE )
   
    /* Check if CAN FD baud rate configuration exists. */
    pFdBaudrateConfig = pBaudrateConfig->CanControllerFdBaudrateConfig;
    regCommonJ = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonJ;
    if ( NULL_PTR != pFdBaudrateConfig ) {
       
        /* Get parameters used to set baud rate. */
        configBaudrate = pFdBaudrateConfig->CanControllerFdBaudRate;
        configPropSeg = pFdBaudrateConfig->CanControllerPropSeg;
        configSeg1 = pFdBaudrateConfig->CanControllerSeg1;
        configSeg2 = pFdBaudrateConfig->CanControllerSeg2;
        configJumpWidth = pFdBaudrateConfig->CanControllerSyncJumpWidth;
        confSspOffset = pFdBaudrateConfig->CanControllerSspOffset;
       
        /* Check if parameters are in valid range. */
        propSegAndSeg1 = ( uint16 )configPropSeg + ( uint16 )configSeg1;
        if ( ( ( 2U <= propSegAndSeg1  ) && ( 32U >= propSegAndSeg1 ) )
          && ( ( 2U <= configSeg2      ) && ( 16U >= configSeg2 ) )
          && ( ( 1U <= configJumpWidth ) && ( 16U >= configJumpWidth ) ) ) {
           
            /* Generate and set register values. */
            numOfTq = 1U + propSegAndSeg1 + ( uint16 )configSeg2;
            nbrb = ( ( uint32 )( CanCpuClock ) / ( configBaudrate * ( uint32 )numOfTq ) ) - ( uint32 )1U ;
           
            bit = ( uint16 )configSeg2 - 1U;
            bitDTSEG2 = bit;
           
            bit = propSegAndSeg1 - 1U;
            bitDTSEG1 = bit << 8U;
           
            bit = ( uint16 )configJumpWidth - 1U;
            bitDSJW =  bit << 8U;
           
            bitDBRP = ( uint16 )nbrb & CAN_70_RL78F2X_MASK_C0DCFGL_DBRP;
           
            bit = ( uint16 )confSspOffset;
            bitTDCO = bit;
           
            /* Transceiver delay compensation */
            /* See chapter F24(18.15.1.5) / F25(19.15.1.5) of the hardware manual. */
            if ( 0U == bitDBRP) {
                /* TDCE should only be allowed if DBRP is 0. */
                bitTDCE = CAN_70_RL78F2X_MASK_C0FDCFGL_TDCE;
            } else {
                bitTDCE = 0U;
            }
           
            regC0DCFGH = bitDSJW | bitDTSEG2;
            regC0DCFGL = bitDTSEG1 | bitDBRP;
           
            regCommonJ->C0DCFGH = regC0DCFGH;
            regCommonJ->C0DCFGL = regC0DCFGL;
           
            regC0FDCFGH = regCommonJ->C0FDCFGH;
            regC0FDCFGH &= ~( CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE | CAN_70_RL78F2X_MASK_C0FDCFGH_TDCO );
            regC0FDCFGH |= bitTDCO; /* bit CLOE is 0 */
            regCommonJ->C0FDCFGH = regC0FDCFGH;
           
            regC0FDCFGL = regCommonJ->C0FDCFGL;
            regC0FDCFGL &= ~( CAN_70_RL78F2X_MASK_C0FDCFGL_TDCOC | CAN_70_RL78F2X_MASK_C0FDCFGL_TDCE );
            regC0FDCFGL |= bitTDCE; /* bit TDCOC is 0 */
            regCommonJ->C0FDCFGL = regC0FDCFGL;
           
        } else {
            /* Nothing */
        }
    } else {
       
        /* Clear CAN FD baud rate settings. */
        bitCLOE = CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE;
       
        regC0FDCFGH = regCommonJ->C0FDCFGH;
        regC0FDCFGH &= ~( CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE | CAN_70_RL78F2X_MASK_C0FDCFGH_TDCO );
        regC0FDCFGH |= bitCLOE;  /* bit bitTDCO is 0 */
        regCommonJ->C0FDCFGH = regC0FDCFGH;
       
        regC0FDCFGL = regCommonJ->C0FDCFGL;
        /* Do not allow transceiver delay compensation when not using CAN FD. */
        regC0FDCFGL &= ~( CAN_70_RL78F2X_MASK_C0FDCFGL_TDCOC | CAN_70_RL78F2X_MASK_C0FDCFGL_TDCE );
        regCommonJ->C0FDCFGL = regC0FDCFGL;
       
    }
   
#endif /* #if ( CAN_70_USE_CANFD == TRUE ) */
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetAfl                                        */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) CanConfigSet      Configuration set                     */
/* Return      : void                                                         */
/* Contents    : Update the CAN controller register and perform AFL settings. */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetAfl( uint8 Controller, const Can_ConfigSetType* CanConfigSet )
{
    volatile Can_70_RL78F2X_RegCommonBType* regCommonB;
    volatile Can_70_RL78F2X_RegCommonIType* regCommonI;
    volatile Can_70_RL78F2X_RegPage0AType*  regPage0A;
    const Can_HardwareObjectType*           pHwObject;
    uint16                                  regGAFLMH;
    uint16                                  bitRNC;
    uint16                                  bitGAFLIDE;
    uint16                                  bitGAFLIDH;
    uint16                                  bitGAFLIDL;
    uint16                                  bitGAFLIDMH;
    uint16                                  bitGAFLIDML;
    uint16                                  bitGAFLFDP;
    uint16                                  bitGAFLIDEM;
    uint8_least                             index;
    uint8_least                             indexList[ CAN_70_RL78F2X_AFL_MAX ];
    uint8_least                             controllerIndex;
    uint8_least                             objectIndex;
    const Can_ControllerType*               canController;
   
    /* search can controller setting */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &(CanConfigSet)->CanController[ controllerIndex ];
        if ( Controller == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
    /* initialize array */
    for ( index = 0U; index < CAN_70_RL78F2X_AFL_MAX; index++ ) {
        indexList[ index ] = 0U;
    }
   
    /* Get register information */
    regCommonB = Can_70_CanControllerRegInfo[ Controller ].RegCommonB;
    regCommonI = Can_70_CanControllerRegInfo[ Controller ].RegCommonI;
 
    /* For reception rules registration, see chapter F24(18.7.4) / F25(19.7.4) in the HW manual. */
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Permission to write reception rules. */
    regCommonB->GAFLECTR |= CAN_70_RL78F2X_MASK_GAFLECTR_AFLDAE;
   
    /* Count and register reception rules. */
    bitRNC = 0U;
    for ( index = 0U; index < CAN_70_NUM_OF_HARDWARE_OBJECT; index++ ) {
        pHwObject = &( CanConfigSet->CanHardwareObject[ index ] );
        if ( ( CAN_70_RECEIVE == pHwObject->CanObjectType )
          && ( NULL_PTR != pHwObject->CanHwFilter )
          && ( canController->CanControllerId == pHwObject->CanControllerRef->CanControllerId ) ) {
            indexList[ bitRNC ] = index;
            bitRNC++;
        } else {
            /* Nothing */
        }
 
        if ( CAN_70_RL78F2X_AFL_MAX <= bitRNC ) {
            break;
        } else {
            /* Nothing */
        }
    }
    regCommonB->GAFLCFG = bitRNC & CAN_70_RL78F2X_MASK_GAFLCFG_RNC;
 
    /* Set the CAN RAM access window to page 0 to register the reception rule. */
    /* See chapter F24(18.14) / F25(19.14) of HW manual. */
    regCommonI->CFDGRWC = CAN_70_RL78F2X_BIT_CFDGRWC_KEY_VALUE
                        | CAN_70_RL78F2X_BIT_CFDGRWC_RPAGE_0;
   
    /* Register reception rules. */
    for ( index = 0U; index < ( uint8_least )bitRNC; index++ ) {
 
        pHwObject = &( CanConfigSet->CanHardwareObject[  indexList[ index ] ] ) ;
 
        /* GAFLIDH */
        if ( CAN_70_STANDARD == pHwObject->CanIdType ) {
            bitGAFLIDE = 0U;
        } else {
            bitGAFLIDE = CAN_70_RL78F2X_MASK_GAFLIDH_GAFLIDE;
        }
       
        bitGAFLIDH =  ( uint16 )( ( pHwObject->CanHwFilter )->CanHwFilterCode >> 16U );
        bitGAFLIDH &= CAN_70_RL78F2X_MASK_GAFLIDH_GAFLID;
 
        /* GAFLIDH */
        bitGAFLIDL =  ( uint16 )( pHwObject->CanHwFilter )->CanHwFilterCode;
       
        bitGAFLIDMH =  ( uint16 )( ( pHwObject->CanHwFilter )->CanHwFilterMask >> 16U );
        bitGAFLIDMH &= CAN_70_RL78F2X_MASK_GAFLMH_GAFLIDM_H;
       
        /* GAFLML */
        bitGAFLIDML =  ( uint16 )( pHwObject->CanHwFilter )->CanHwFilterMask;
       
        /* GAFLP1L */
        bitGAFLFDP = 0U;
        for ( objectIndex = 0U; objectIndex < CAN_70_RL78F2X_RXFIFO_MAX; objectIndex++ ) {
            if ( Can_70_IndxexRxHwObj[ controllerIndex ][ objectIndex ] == indexList[ index ] ) {
                if ( 1U == objectIndex ) {
                    bitGAFLFDP = CAN_70_RL78F2X_BIT_GAFLP1L_GAFLFDP_1;
                } else {
                    bitGAFLFDP = CAN_70_RL78F2X_BIT_GAFLP1L_GAFLFDP_0;
                }
                break;
            } else {
                /* do nothing */
            }
        }
       
        /* GAFLIDEM */
        if ( CAN_70_MIXED == pHwObject->CanIdType ) {
            bitGAFLIDEM = 0U;
        } else {
            bitGAFLIDEM = CAN_70_RL78F2X_MASK_GAFLMH_GAFLIDEM;
        }
       
        regPage0A = Can_70_CanControllerRegInfo[ Controller ].RegPage0A[ index ];
 
        regPage0A->GAFLIDH = ( bitGAFLIDE | bitGAFLIDH );
 
        regPage0A->GAFLIDL &= ( ~CAN_70_RL78F2X_MASK_GAFLIDL_GAFLID );
        regPage0A->GAFLIDL |= bitGAFLIDL;
 
        regGAFLMH = regPage0A->GAFLMH;
        regGAFLMH &= ~( CAN_70_RL78F2X_MASK_GAFLMH_GAFLIDEM
                      | CAN_70_RL78F2X_MASK_GAFLMH_GAFLRTRM
                      | CAN_70_RL78F2X_MASK_GAFLMH_GAFLIDM_H );
        regGAFLMH |= ( bitGAFLIDEM
                      | CAN_70_RL78F2X_MASK_GAFLMH_GAFLRTRM
                      | bitGAFLIDMH );
       
        regPage0A->GAFLMH = regGAFLMH;
 
        regPage0A->GAFLML = bitGAFLIDML;
       
        regPage0A->GAFLP1L &= ( ~CAN_70_RL78F2X_MASK_GAFLP1L_GAFLFDP_2 );
        regPage0A->GAFLP1L |= bitGAFLFDP;
 
    }
   
    /* Prohibit writing of reception rules. */
    regCommonB->GAFLECTR &= ~CAN_70_RL78F2X_MASK_GAFLECTR_AFLDAE;
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
   
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_GetRxErrorCounter                             */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/* Return      : uint8  Rx error counter                                      */
/* Contents    : Refers to the CAN controller register and returns            */
/*               the reception error counter.                                 */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
uint8 Can_70_RL78F2X_GetRxErrorCounter( uint8 Controller, uint8 Channel )
{
    volatile const Can_70_RL78F2X_RegCommonAType* regCommonA;
    uint8   rxErrCounter;
 
    /* Get register information */
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ Channel ].RegCommonA;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Get RX error counter */
    rxErrCounter = ( uint8 )( regCommonA->C0STSH & CAN_70_RL78F2X_MASK_C0STSH_REC );
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
    return rxErrCounter;
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_GetTxErrorCounter                             */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/* Return      : uint8  Tx error counter                                      */
/* Contents    : Refers to the CAN controller register and returns            */
/*               the transmission error counter.                              */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
uint8 Can_70_RL78F2X_GetTxErrorCounter( uint8 Controller, uint8 Channel )
{
    volatile const Can_70_RL78F2X_RegCommonAType* regCommonA;
    uint8   txErrCounter;
 
    /* Get register information */
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ Channel ].RegCommonA;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Get TX error counter */
    txErrCounter = ( uint8 )( ( regCommonA->C0STSH & CAN_70_RL78F2X_MASK_C0STSH_TEC ) >> 8U );
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
    return txErrCounter;
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetBuffer                                     */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) CanConfigSet      Configuration set                     */
/* Return      : void                                                         */
/* Contents    : Update CAN controller registers and configure buffer         */
/*               settings.                                                    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetBuffer( uint8 Controller, const Can_ConfigSetType* CanConfigSet )
{
    volatile Can_70_RL78F2X_RegCommonCType* regCommonC;
    const Can_HardwareObjectType*           pHwObject;
    uint16                                  regRFCC;
    uint16                                  bitRFDC;
    uint16                                  bitRFPLS;
    uint8                                   objectId;
    uint16                                  objectCount;
    uint16                                  objectPayloadLength;
    uint8_least                             index;
    uint8_least                             controllerIndex;
    uint8_least                             objectIndex;
    const Can_ControllerType*               canController;
 
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
   
    volatile Can_70_RL78F2X_RegCommonGType* regCommonG;
    uint16                                  regTHLCC;
   
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
   
    /* search can controller setting */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &(CanConfigSet)->CanController[ controllerIndex ];
        if ( Controller == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    for ( index = 0U; index < CAN_70_NUM_OF_HARDWARE_OBJECT; index++ ) {
       
        pHwObject = &( CanConfigSet->CanHardwareObject[ index ] );
 
        if ( CAN_70_RECEIVE == pHwObject->CanObjectType ) {
            /* Configure settings for the receive FIFO buffer.*/
            /* See chapter F24(18.8) / F25(19.8) of HW manual. */
            for ( objectIndex = 0U; objectIndex < CAN_70_RL78F2X_RXFIFO_MAX; objectIndex++ ) {
                if ( Can_70_IndxexRxHwObj[ controllerIndex ][ objectIndex ] == index ) {
                    objectId = ( uint8 )objectIndex;
                    objectCount = ( uint16 )pHwObject->CanHwObjectCount;
                    objectPayloadLength = ( uint16 )pHwObject->CanObjectPayloadLength;
 
                    bitRFDC = ( ( uint16 )( objectCount  << 8U ) ) & CAN_70_RL78F2X_MASK_RFCC_RFDC;
                    bitRFPLS = ( uint16 )( objectPayloadLength << 4U ) & CAN_70_RL78F2X_MASK_RFCC_RFPLS;
 
                    regCommonC = Can_70_CanControllerRegInfo[ Controller ].RegCommonC[ objectId ];
                    regRFCC =  regCommonC->RFCC;
                    regRFCC &= ~( CAN_70_RL78F2X_MASK_RFCC_RFIM
                                | CAN_70_RL78F2X_MASK_RFCC_RFDC
                                | CAN_70_RL78F2X_MASK_RFCC_RFPLS );
                    regRFCC |= CAN_70_RL78F2X_MASK_RFCC_RFIM | bitRFDC | bitRFPLS;
                    regCommonC->RFCC = regRFCC;
                    break;
                } else {
                    /* do nothing */
                }
            }
 
        } else {
            /* Nothing */
        }
    }
   
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
   
    /* Configure settings for the sending history buffer. */
    /* See chapter F24(18.10.4) / F25(19.10.4) of HW manual. */
    regCommonG = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonG;
    regTHLCC = regCommonG->THLCC;
    regTHLCC &= ~( CAN_70_RL78F2X_MASK_THLCC_THLDTE
                   | CAN_70_RL78F2X_MASK_THLCC_THLIM );
    regTHLCC |= CAN_70_RL78F2X_MASK_THLCC_THLDTE
                | CAN_70_RL78F2X_MASK_THLCC_THLIM;
    regCommonG->THLCC = regTHLCC;
 
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetCanCommon                                  */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/* Return      : void                                                         */
/* Contents    : Update the registers of the CAN controller and perform       */
/*               CAN settings (settings common to classic CAN and CAN FD).    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetCanCommon( uint8 Controller )
{
    volatile Can_70_RL78F2X_RegCommonAType* regCommonA;
    volatile Can_70_RL78F2X_RegCommonBType* regCommonB;
    volatile Can_70_RL78F2X_RegCommonJType* regCommonJ;
    uint16                                  regC0CTRH;
    uint16                                  regGCFGL;
    uint16                                  regC0FDCFGH;
    uint16                                  regC0FDCFGL;
   
    /* Get register information */
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonA;
    regCommonB = Can_70_CanControllerRegInfo[ Controller ].RegCommonB;
    regCommonJ = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonJ;
   
    /* Configure CAN settings. */
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* C0CTRH */
    regC0CTRH = regCommonA->C0CTRH;
    regC0CTRH &= ~( CAN_70_RL78F2X_MASK_C0CTRH_ROM
                  | CAN_70_RL78F2X_MASK_C0CTRH_BFT
                  | CAN_70_RL78F2X_MASK_C0CTRH_CTMS
                  | CAN_70_RL78F2X_MASK_C0CTRH_CTME
                  | CAN_70_RL78F2X_MASK_C0CTRH_ERRD
                  | CAN_70_RL78F2X_MASK_C0CTRH_BOM );
    regC0CTRH |= CAN_70_RL78F2X_MASK_C0CTRH_BOM;
    regCommonA->C0CTRH = regC0CTRH;
   
    /* C0CTRL */
    regCommonA->C0CTRL &= ~( CAN_70_RL78F2X_MASK_C0CTRL_RTBO );
   
    /* GCFGH */
    regCommonB->GCFGH &= ~( CAN_70_RL78F2X_MASK_GCFGH_ITRCP );
   
    /* GCFGL */
    regGCFGL = regCommonB->GCFGL;
    regGCFGL &= ~( CAN_70_RL78F2X_MASK_GCFGL_TSSS
                 | CAN_70_RL78F2X_MASK_GCFGL_TSP
                 | CAN_70_RL78F2X_MASK_GCFGL_CMPOC
                 | CAN_70_RL78F2X_MASK_GCFGL_MME
                 | CAN_70_RL78F2X_MASK_GCFGL_DRE
                 | CAN_70_RL78F2X_MASK_GCFGL_DCE
                 | CAN_70_RL78F2X_MASK_GCFGL_TPRI );
    regGCFGL |= CAN_70_RL78F2X_BIT_GCFGL_TSP & CAN_70_RL78F2X_MASK_GCFGL_TSP;
    regCommonB->GCFGL = regGCFGL;
   
    /* GCTRH */
    regCommonB->GCTRH &= ~( CAN_70_RL78F2X_MASK_GCTRH_TSRST );
   
    /* GCTRL */
    /* Nothing */
   
    /* C0FDCFGH */
    regC0FDCFGH = regCommonJ->C0FDCFGH;
    regC0FDCFGH &= ~( CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE
                    | CAN_70_RL78F2X_MASK_C0FDCFGH_REFE
                    | CAN_70_RL78F2X_MASK_C0FDCFGH_FDOE
                    | CAN_70_RL78F2X_MASK_C0FDCFGH_TDCO );
    regC0FDCFGH |= CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE;
    regCommonJ->C0FDCFGH = regC0FDCFGH;
   
    /* C0FDCFGL */
    regC0FDCFGL = regCommonJ->C0FDCFGL;
    regC0FDCFGL &= ~( CAN_70_RL78F2X_MASK_C0FDCFGL_RPNMD
                    | CAN_70_RL78F2X_MASK_C0FDCFGL_ESIC
                    | CAN_70_RL78F2X_MASK_C0FDCFGL_TDCE
                    | CAN_70_RL78F2X_MASK_C0FDCFGL_TDCOC
                    | CAN_70_RL78F2X_MASK_C0FDCFGL_EOCCFG );
    regCommonJ->C0FDCFGL = regC0FDCFGL;
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_GetTimestampCounter                           */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/* Return      : uint16  Timestamp counter                                    */
/* Contents    : Refers to the CAN controller register and returns            */
/*               the timestamp counter.                                       */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
uint16 Can_70_RL78F2X_GetTimestampCounter( uint8 Controller )
{
    volatile const Can_70_RL78F2X_RegCommonBType* regCommonB;
    uint16  timeStampCounter;
 
    /* Get register information */
    regCommonB = Can_70_CanControllerRegInfo[ Controller ].RegCommonB;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Get Time stamp counter */
    timeStampCounter = regCommonB->GTSC;
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
    return timeStampCounter;
}

/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SendRequest                                   */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) TxBufNo           Tx buffer number                      */
/*             : (in) PduInfo           PDU information                       */
/*             : (in) TimeStamp         Output timestamp flag                 */
/*             : (in) RateSwitch        Baurate switch flag                   */
/*             : (in) PaddingValue      Padding data                          */
/* Return      : void                                                         */
/* Contents    : Update the CAN controller register and issue                 */
/*               a transmission request.                                      */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SendRequest( uint8 Controller, uint8 TxBufNo, const Can_PduType* PduInfo,
                                bool_t TimeStamp, bool_t RateSwitch, uint8 PaddingValue )
{
    bool_t                                  canfd;
    uint32                                  id;
    uint8                                   length;
    uint8                                   dlc;
    uint8                                   dlcLength;
    uint8_least                             index;    
    volatile Can_70_RL78F2X_RegPage1CType*  regPage1C;
    volatile Can_70_RL78F2X_RegPage1DType*  regPage1D;
    volatile Can_70_RL78F2X_RegCommonEType* regCommonE;
    volatile Can_70_RL78F2X_RegCommonGType* regCommonG;
    uint16                                  regTMFDCTRL;
    uint8                                   regTMC;
    uint16                                  bitTMIDE;
    uint16                                  bitTHLEN;
    uint16                                  bitTHLE;
    uint16                                  bitTMID_H;
    uint16                                  bitTMID_L;
    uint16                                  bitTMDLC;
    uint16                                  bitTMFDF;
    uint16                                  bitTMBRS;
   
    id = ( uint32 )PduInfo->id;
    length = ( uint8 )PduInfo->length;
   
    /* Select maximum DLC value. */
    if ( 0U != ( ( uint32 )CAN_70_MASK_CANID_CANFD & id ) ) {
        canfd = TRUE;
        dlcLength = 64U;
    } else {
        canfd = FALSE;
        dlcLength = 8U;
    }
   
    /* Calculate DLC from data length. */
    /* See detailed design document. */
    if ( length > dlcLength ) {
        return;
    } else if ( length > 8U ) {
        if ( length < 29U ) {
            dlc = 7U + ( ( length - 1U ) >> 2U );
        } else {
            dlc = 12U + ( ( length - 1U ) >> 4U );
        }
        dlcLength = dlcTable[ dlc - 9U ];        
    } else {
        dlc = length;
        dlcLength = length;
    }
   
    /* TMIDE */
    if ( 0U != ( ( ( uint32 )CAN_70_MASK_CANID_EXTEND ) & id ) ) {
        bitTMIDE = CAN_70_RL78F2X_MASK_TMIDH_TMIDE;
    } else {
        bitTMIDE = 0U;
    }
   
    /* THLEN,THLE */
    if ( TRUE == TimeStamp ) {
        bitTHLEN = CAN_70_RL78F2X_MASK_TMIDH_THLEN;
        bitTHLE = CAN_70_RL78F2X_MASK_THLCC_THLE;
    } else {
        bitTHLEN = 0U;
        bitTHLE = 0U;
    }
   
    /* TMID */
    bitTMID_H = ( uint16 )( id >> 16U);
    bitTMID_L = ( uint16 )( id & CAN_70_RL78F2X_MASK_TMIDL_TMID_L );
   
    /* TMDLC */
    bitTMDLC = ( uint16 )dlc;
    bitTMDLC = bitTMDLC << 12U;
   
    /* TMFDF */
    if ( TRUE ==  canfd ) {
        bitTMFDF = CAN_70_RL78F2X_MASK_TMFDCTRL_TMFDF;
    } else {
        bitTMFDF = 0U;
    }
   
    /* TMBRS */
    if ( TRUE ==  RateSwitch ) {
        bitTMBRS = CAN_70_RL78F2X_MASK_TMFDCTRL_TMBRS;
    } else {
        bitTMBRS = 0U;
    }
 
    /* Interrupts are disabled during register operations for transmission requests. */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_00();
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_NO_EXCLUSIVE( Controller );
 
    /* Sending history buffer */
    regCommonG = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonG;
    regCommonG->THLCC |= bitTHLE;
   
    /* Entry */
    regPage1C = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegPage1C[ TxBufNo ];
    regPage1C->TMIDH = ( bitTMIDE | bitTHLEN | bitTMID_H );
    regPage1C->TMIDL = bitTMID_L;
    regPage1C->TMPTRH &= ( ~CAN_70_RL78F2X_MASK_TMPTRH_TMDLC );
    regPage1C->TMPTRH |= bitTMDLC;
    regPage1C->TMFDCTRH = 0U;
    regTMFDCTRL = regPage1C->TMFDCTRL;
    regTMFDCTRL &= ~( CAN_70_RL78F2X_MASK_TMFDCTRL_TMIFL
                    | CAN_70_RL78F2X_MASK_TMFDCTRL_TMFDF
                    | CAN_70_RL78F2X_MASK_TMFDCTRL_TMBRS
                    | CAN_70_RL78F2X_MASK_TMFDCTRL_TMESI );
    regTMFDCTRL |= bitTMFDF | bitTMBRS;
    regPage1C->TMFDCTRL = regTMFDCTRL;
   
    /* Write send data. */
    regPage1D = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegPage1D[ TxBufNo ];
    for ( index = 0U; index < length; index++ ) {        
        regPage1D->TMDF[ index ] = PduInfo->sdu[ index ];
    }
    for ( /* Nothing */ ; index < dlcLength; index++ ) {
        /* Padding */
        regPage1D->TMDF[ index ] = PaddingValue;
    }
   
    /* Request to send. */
    regCommonE = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonE;
    regTMC = regCommonE->TMC[ TxBufNo ];
    regTMC &= ~( CAN_70_RL78F2X_MASK_TMC_TMOM
               | CAN_70_RL78F2X_MASK_TMC_TMTAR
               | CAN_70_RL78F2X_MASK_TMC_TMTR );
    regTMC |= CAN_70_RL78F2X_MASK_TMC_TMTR;
    regCommonE->TMC[ TxBufNo ] = regTMC;
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_NO_EXCLUSIVE();
 
    /* Interrupts are enabled. */
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_00();
 
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SwReset                                       */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/* Return      : void                                                         */
/* Contents    : Change the CAN controller register and reset the SW.         */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SwReset( uint8 Controller )
{
    volatile Can_70_RL78F2X_RegCommonIType* regCommonI;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Get register information */
    regCommonI = Can_70_CanControllerRegInfo[ Controller ].RegCommonI;
   
    /* Set C4H to GRSTC bit15-8(KEY[7:0]) */
    /* Set 1   to GRSTC bit0   (SRST    ) */
    regCommonI->GRSTC = 0xC401U;
   
    /* Set C4H to GRSTC bit15-8(KEY[7:0]) */
    /* Set 0   to GRSTC bit0   (SRST    ) */
    regCommonI->GRSTC = 0xC400U;
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_ClearWakeup                                   */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/* Return      : void                                                         */
/* Contents    : Change the CAN controller register and                       */
/*               clear wakeup detection.                                      */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_ClearWakeup( uint8 Controller, uint8 Channel )
{
    volatile Can_70_RL78F2X_RegIfxType* regIfx;
   
    ( void )Channel;    /* unused */
   
    /* Get register information */
    regIfx = Can_70_CanControllerRegInfo[ Controller ].RegIfx[ Can_70_InterruptBitAssign[Controller].RCANxWUP.index ];
   
    /* Set 0 to RCAN0WUPIF bit */
    regIfx->IF &= ~Can_70_InterruptBitAssign[Controller].RCANxWUP.bit;
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_DisableInterrupt                              */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/* Return      : void                                                         */
/* Contents    : Disable all interrupts from the CAN controller               */
/*               related to Can.                                              */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_DisableInterrupt( uint8 Controller )
{
    volatile Can_70_RL78F2X_RegMkxType*     regMkx[ CAN_70_RL78F2X_INTERRUPT_FLAG_MAX ];
    volatile Can_70_RL78F2X_RegCommonCType* regCommonC[ CAN_70_RL78F2X_RXFIFO_MAX ];
    volatile Can_70_RL78F2X_RegCommonBType* regCommonB;
    volatile Can_70_RL78F2X_RegCommonFType* regCommonF;
    volatile Can_70_RL78F2X_RegCommonGType* regCommonG;
    volatile Can_70_RL78F2X_RegCommonAType* regCommonA;
    volatile Can_70_RL78F2X_RegCfdecctlType QL_70_NEAR * regCfdecctl;
    uint8_least                             cnt;
    uint8                                   maskBit[ CAN_70_RL78F2X_INTERRUPT_FLAG_MAX ];
   
    /* Get register information */
    for ( cnt = 0U; cnt < CAN_70_RL78F2X_INTERRUPT_FLAG_MAX; cnt++ ) {
        regMkx[ cnt ] = Can_70_CanControllerRegInfo[ Controller ].RegMkx[ cnt ];
        maskBit[ cnt ] = 0U;
    }
    for ( cnt = 0U; cnt < CAN_70_RL78F2X_RXFIFO_MAX; cnt++ ) {
        regCommonC[ cnt ] = Can_70_CanControllerRegInfo[ Controller ].RegCommonC[ cnt ];
    }
    regCommonB = Can_70_CanControllerRegInfo[ Controller ].RegCommonB;
    regCommonF = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0 ].RegCommonF;
    regCommonG = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0 ].RegCommonG;
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0 ].RegCommonA;
    regCfdecctl = Can_70_CanControllerRegInfo[ Controller ].RegCfdecctl;
   
    /* setup mask bit */
    maskBit[ Can_70_InterruptBitAssign[ Controller ].RCANxERR .index ] |= Can_70_InterruptBitAssign[ Controller ].RCANxERR .bit;
    maskBit[ Can_70_InterruptBitAssign[ Controller ].RCANxWUP .index ] |= Can_70_InterruptBitAssign[ Controller ].RCANxWUP .bit;
    maskBit[ Can_70_InterruptBitAssign[ Controller ].RCANxTRM .index ] |= Can_70_InterruptBitAssign[ Controller ].RCANxTRM .bit;
    maskBit[ Can_70_InterruptBitAssign[ Controller ].RCANxGRFR.index ] |= Can_70_InterruptBitAssign[ Controller ].RCANxGRFR.bit;
    maskBit[ Can_70_InterruptBitAssign[ Controller ].RCANxGERR.index ] |= Can_70_InterruptBitAssign[ Controller ].RCANxGERR.bit;
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Disable interrupts */
    /* See interrupt settings sheet in supplementary material. */
    for ( cnt = 0U; cnt < CAN_70_RL78F2X_INTERRUPT_FLAG_MAX; cnt++ ) {
        regMkx[ cnt ]->MK |= maskBit[ cnt ];
    }
    for ( cnt = 0U; cnt < CAN_70_RL78F2X_RXFIFO_MAX; cnt++ ) {
        regCommonC[ cnt ]->RFCC &= ~CAN_70_RL78F2X_MASK_RFCC_RFIE;
    }
    regCommonB->GCTRL  &= ~CAN_70_RL78F2X_MASK_GCTRL_MEIE;
    regCommonF->TMIEC  &= ~( CAN_70_RL78F2X_MASK_TMIEC_TMIE3
                           | CAN_70_RL78F2X_MASK_TMIEC_TMIE2
                           | CAN_70_RL78F2X_MASK_TMIEC_TMIE1
                           | CAN_70_RL78F2X_MASK_TMIEC_TMIE0 );
    regCommonG->THLCC  &= ~CAN_70_RL78F2X_MASK_THLCC_THLIE;
    regCommonA->C0CTRL &= ~( CAN_70_RL78F2X_MASK_C0CTRL_BEIE
                           | CAN_70_RL78F2X_MASK_C0CTRL_EPIE
                           | CAN_70_RL78F2X_MASK_C0CTRL_BOEIE
                           | CAN_70_RL78F2X_MASK_C0CTRL_OLIE
                           | CAN_70_RL78F2X_MASK_C0CTRL_BLIE
                           | CAN_70_RL78F2X_MASK_C0CTRL_ALIE );
 
 
    /* Disable 2bit error detection interrupt (EC2EDIC) */
    regCfdecctl->CFDECCTL &= ~CAN_70_RL78F2X_MASK_CFDECCTL_EC2EDIC;
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_EnableInterrupt                               */
/* Param       : (in) Controller         CAN Channel of RL78F2x(CAN0/CAN1)    */
/*             : (in) CanConfigSet       Configuration set                    */
/*             : (in) ControllerStatus   Controller operation mode            */
/*             : (in) TxBufferUsesPolling Tx Buffer uses polling              */
/*             : (in) RxBufferUsesPolling Rx Buffer uses polling              */
/* Return      : void                                                         */
/* Contents    : Allows interrupts from the CAN controller related to         */
/*               Can according to the specified operation mode.               */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_EnableInterrupt( uint8 Controller, const Can_ConfigSetType* CanConfigSet,
                                     Can_ControllerStateType ControllerStatus,
                                     const bool_t* TxBufferUsesPolling,
                                     const bool_t* RxBufferUsesPolling )
{
    volatile Can_70_RL78F2X_RegMkxType*     regMkx[ CAN_70_RL78F2X_INTERRUPT_FLAG_MAX ];
    volatile Can_70_RL78F2X_RegCommonCType* regCommonC[ CAN_70_RL78F2X_RXFIFO_MAX ];
    volatile Can_70_RL78F2X_RegCommonBType* regCommonB;
    volatile Can_70_RL78F2X_RegCommonFType* regCommonF;
    volatile Can_70_RL78F2X_RegCommonGType* regCommonG;
    volatile Can_70_RL78F2X_RegCommonAType* regCommonA;
    volatile Can_70_RL78F2X_RegCfdecctlType QL_70_NEAR * regCfdecctl;
    uint8_least                             cnt;
    const Can_ControllerType*               canController;
    const Can_70_InterruptBitAssignType*    interruptBit;
    uint8_least                             controllerIndex;
   
    /* search can controller setting */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &(CanConfigSet)->CanController[ controllerIndex ];
        if ( Controller == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
    /* Get register information */
    for ( cnt = 0U; cnt < CAN_70_RL78F2X_INTERRUPT_FLAG_MAX; cnt++ ) {
        regMkx[ cnt ] = Can_70_CanControllerRegInfo[ Controller ].RegMkx[ cnt ];
    }
    for ( cnt = 0U; cnt < CAN_70_RL78F2X_RXFIFO_MAX; cnt++ ) {
        regCommonC[ cnt ] = Can_70_CanControllerRegInfo[ Controller ].RegCommonC[ cnt ];
    }
    regCommonB = Can_70_CanControllerRegInfo[ Controller ].RegCommonB;
    regCommonF = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0 ].RegCommonF;
    regCommonG = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0 ].RegCommonG;
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0 ].RegCommonA;
    regCfdecctl = Can_70_CanControllerRegInfo[ Controller ].RegCfdecctl;
 
    interruptBit = &Can_70_InterruptBitAssign[ Controller ];
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    if ( CAN_CS_STARTED == ControllerStatus ) {
       
#if ( CAN_70_RX_INTERRUPT_PROCESSING == TRUE )
       
        if ( CAN_PROCESSING_INTERRUPT == canController->CanRxProcessing ) {
            if ( ( FALSE == RxBufferUsesPolling[ 1U ] )
              && ( FALSE == RxBufferUsesPolling[ 0U ] ) ) {
                /* RX related, enable */
                regMkx[ interruptBit->RCANxGRFR.index ]->MK &= ~interruptBit->RCANxGRFR.bit;
                for ( cnt = 0U; cnt < CAN_70_RL78F2X_RXFIFO_MAX; cnt++ ) {
                    regCommonC[ cnt ]->RFCC |= CAN_70_RL78F2X_MASK_RFCC_RFIE;
                }
            }
        }
 
#endif /* #if ( CAN_70_RX_INTERRUPT_PROCESSING == TRUE ) */
       
#if ( CAN_70_RX_POLLING_PROCESSING == TRUE )
       
        if ( CAN_PROCESSING_POLLING == canController->CanRxProcessing ) {
            if ( ( TRUE == RxBufferUsesPolling[ 1U ] )
              && ( TRUE == RxBufferUsesPolling[ 0U ] ) ) {
                /* RX related, disable */
                regMkx[ interruptBit->RCANxGRFR.index ]->MK |= interruptBit->RCANxGRFR.bit;
                for ( cnt = 0U; cnt < CAN_70_RL78F2X_RXFIFO_MAX; cnt++ ) {
                    regCommonC[ cnt ]->RFCC &= ~CAN_70_RL78F2X_MASK_RFCC_RFIE;
                }
            }
        }
 
#endif /* #if ( CAN_70_RX_POLLING_PROCESSING == TRUE ) */
       
#if ( CAN_70_RX_MIXED_PROCESSING == TRUE )
 
        if ( CAN_PROCESSING_MIXED == canController->CanRxProcessing ) {
            /* RX related, mixed */
            regMkx[ interruptBit->RCANxGRFR.index ]->MK &= ~interruptBit->RCANxGRFR.bit;
            for ( cnt = 0U; cnt < CAN_70_RL78F2X_RXFIFO_MAX; cnt++ ) {
                if ( FALSE == RxBufferUsesPolling[ cnt ] ) {
                    regCommonC[ cnt ]->RFCC |= CAN_70_RL78F2X_MASK_RFCC_RFIE;
                } else {
                    regCommonC[ cnt ]->RFCC &= ~CAN_70_RL78F2X_MASK_RFCC_RFIE;
                }
            }
        }
       
#endif /* #if ( CAN_70_RX_MIXED_PROCESSING == TRUE ) */
       
#if ( CAN_70_TX_INTERRUPT_PROCESSING == TRUE )
       
        if ( CAN_PROCESSING_INTERRUPT == canController->CanTxProcessing ) {
            if ( ( FALSE == TxBufferUsesPolling[ 3U ] )
              && ( FALSE == TxBufferUsesPolling[ 2U ] )
              && ( FALSE == TxBufferUsesPolling[ 1U ] )
              && ( FALSE == TxBufferUsesPolling[ 0U ] ) ) {
                /* TX related, enable */
                regMkx[ interruptBit->RCANxTRM.index ]->MK &= ~interruptBit->RCANxTRM.bit;
                regCommonF->TMIEC |= CAN_70_RL78F2X_MASK_TMIEC_TMIE3
                                   | CAN_70_RL78F2X_MASK_TMIEC_TMIE2
                                   | CAN_70_RL78F2X_MASK_TMIEC_TMIE1
                                   | CAN_70_RL78F2X_MASK_TMIEC_TMIE0;
                regCommonG->THLCC |= CAN_70_RL78F2X_MASK_THLCC_THLIE;
            }
        }
 
#endif /* #if ( CAN_70_TX_INTERRUPT_PROCESSING == TRUE ) */
       
#if ( CAN_70_TX_POLLING_PROCESSING == TRUE )
       
        if ( CAN_PROCESSING_POLLING == canController->CanTxProcessing ) {
            if ( ( TRUE == TxBufferUsesPolling[ 3U ] )
              && ( TRUE == TxBufferUsesPolling[ 2U ] )
              && ( TRUE == TxBufferUsesPolling[ 1U ] )
              && ( TRUE == TxBufferUsesPolling[ 0U ] ) ) {
                /* TX related, disable */
                regMkx[ interruptBit->RCANxTRM.index ]->MK |= interruptBit->RCANxTRM.bit;
                regCommonF->TMIEC  &= ~( CAN_70_RL78F2X_MASK_TMIEC_TMIE3
                                       | CAN_70_RL78F2X_MASK_TMIEC_TMIE2
                                       | CAN_70_RL78F2X_MASK_TMIEC_TMIE1
                                       | CAN_70_RL78F2X_MASK_TMIEC_TMIE0 );
                regCommonG->THLCC  &= ~CAN_70_RL78F2X_MASK_THLCC_THLIE;
            }
        }
       
#endif /* #if ( CAN_70_TX_POLLING_PROCESSING == TRUE ) */
 
#if ( CAN_70_TX_MIXED_PROCESSING == TRUE )
 
        if ( CAN_PROCESSING_MIXED == canController->CanTxProcessing ) {
            /* TX related, mixed */
            regMkx[ interruptBit->RCANxTRM.index ]->MK &= ~interruptBit->RCANxTRM.bit;
            if ( FALSE == TxBufferUsesPolling[ 3U ] ) {
                regCommonF->TMIEC |= CAN_70_RL78F2X_MASK_TMIEC_TMIE3;
            } else {
                regCommonF->TMIEC &= ~CAN_70_RL78F2X_MASK_TMIEC_TMIE3;
            }
            if ( FALSE == TxBufferUsesPolling[ 2U ] ) {
                regCommonF->TMIEC |= CAN_70_RL78F2X_MASK_TMIEC_TMIE2;
            } else {
                regCommonF->TMIEC &= ~CAN_70_RL78F2X_MASK_TMIEC_TMIE2;
            }
            if ( FALSE == TxBufferUsesPolling[ 1U ] ) {
                regCommonF->TMIEC |= CAN_70_RL78F2X_MASK_TMIEC_TMIE1;
            } else {
                regCommonF->TMIEC &= ~CAN_70_RL78F2X_MASK_TMIEC_TMIE1;
            }
            if ( FALSE == TxBufferUsesPolling[ 0U ] ) {
                regCommonF->TMIEC |= CAN_70_RL78F2X_MASK_TMIEC_TMIE0;
            } else {
                regCommonF->TMIEC &= ~CAN_70_RL78F2X_MASK_TMIEC_TMIE0;
            }
           
            /* The transmission history buffer is polled because the target transmission buffer cannot be specified. */
            regCommonG->THLCC  &= ~CAN_70_RL78F2X_MASK_THLCC_THLIE;
        }
 
#endif /* #if ( CAN_70_TX_MIXED_PROCESSING == TRUE ) */
       
        /* Error related, enable */
        regMkx[ interruptBit->RCANxGERR.index ]->MK &= ~interruptBit->RCANxGERR.bit;
        regCommonB->GCTRL |= CAN_70_RL78F2X_MASK_GCTRL_MEIE;
        regMkx[ interruptBit->RCANxERR.index ]->MK &= ~interruptBit->RCANxERR.bit;
        regCommonA->C0CTRL |= CAN_70_RL78F2X_MASK_C0CTRL_BEIE
                            | CAN_70_RL78F2X_MASK_C0CTRL_EPIE
                            | CAN_70_RL78F2X_MASK_C0CTRL_OLIE
                            | CAN_70_RL78F2X_MASK_C0CTRL_BLIE
                            | CAN_70_RL78F2X_MASK_C0CTRL_ALIE;
       
#if ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE )
       
        if ( CAN_PROCESSING_INTERRUPT == canController->CanBusoffProcessing ) {
            /* Busoff related, enable */
            regCommonA->C0CTRL |= CAN_70_RL78F2X_MASK_C0CTRL_BOEIE;
        }
 
#endif /* #if ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE ) */
       
#if ( CAN_70_BUSOFF_POLLING_PROCESSING == TRUE )
       
        if ( CAN_PROCESSING_POLLING == canController->CanBusoffProcessing ) {
            /* Busoff related, disable */
            regCommonA->C0CTRL &= ~CAN_70_RL78F2X_MASK_C0CTRL_BOEIE;
        }
 
#endif /* #if ( CAN_70_BUSOFF_POLLING_PROCESSING == TRUE ) */
       
        /* Wakeup related, disable */
        regMkx[ interruptBit->RCANxWUP.index ]->MK |= interruptBit->RCANxWUP.bit;
       
        /* ECC related, enable */
        /* Enable 2bit error detection interrupt (EC2EDIC) */
        regCfdecctl->CFDECCTL |= CAN_70_RL78F2X_MASK_CFDECCTL_EC2EDIC;
       
    } else if ( CAN_CS_STOPPED == ControllerStatus ) {
       
        /* RX related, disable */
        regMkx[ interruptBit->RCANxGRFR.index ]->MK |= interruptBit->RCANxGRFR.bit;
        for ( cnt = 0U; cnt < CAN_70_RL78F2X_RXFIFO_MAX; cnt++ ) {
            regCommonC[ cnt ]->RFCC &= ~CAN_70_RL78F2X_MASK_RFCC_RFIE;
        }
       
        /* TX related, disable */
        regMkx[ interruptBit->RCANxTRM.index ]->MK |= interruptBit->RCANxTRM.bit;
        regCommonF->TMIEC  &= ~( CAN_70_RL78F2X_MASK_TMIEC_TMIE3
                               | CAN_70_RL78F2X_MASK_TMIEC_TMIE2
                               | CAN_70_RL78F2X_MASK_TMIEC_TMIE1
                               | CAN_70_RL78F2X_MASK_TMIEC_TMIE0 );
        regCommonG->THLCC  &= ~CAN_70_RL78F2X_MASK_THLCC_THLIE;
       
        /* Error related, enable */
        regMkx[ interruptBit->RCANxGERR.index ]->MK &= ~interruptBit->RCANxGERR.bit;
        regCommonB->GCTRL |= CAN_70_RL78F2X_MASK_GCTRL_MEIE;
        regMkx[ interruptBit->RCANxERR.index ]->MK &= ~interruptBit->RCANxERR.bit;
        regCommonA->C0CTRL |= ( CAN_70_RL78F2X_MASK_C0CTRL_BEIE
                               | CAN_70_RL78F2X_MASK_C0CTRL_EPIE
                               | CAN_70_RL78F2X_MASK_C0CTRL_OLIE
                               | CAN_70_RL78F2X_MASK_C0CTRL_BLIE
                               | CAN_70_RL78F2X_MASK_C0CTRL_ALIE );
 
        /* Busoff related, disable */
        regCommonA->C0CTRL &= ~( CAN_70_RL78F2X_MASK_C0CTRL_BOEIE );
       
        /* Wakeup related, disable */
        regMkx[ interruptBit->RCANxWUP.index ]->MK |= interruptBit->RCANxWUP.bit;
 
        /* ECC related, enable */
        /* Enable 2bit error detection interrupt (EC2EDIC) */
        regCfdecctl->CFDECCTL |= CAN_70_RL78F2X_MASK_CFDECCTL_EC2EDIC;
       
    } else if ( CAN_CS_SLEEP == ControllerStatus ) {
       
        /* RX related, disable */
        regMkx[ interruptBit->RCANxGRFR.index ]->MK |= interruptBit->RCANxGRFR.bit;
        for ( cnt = 0U; cnt < CAN_70_RL78F2X_RXFIFO_MAX; cnt++ ) {
            regCommonC[ cnt ]->RFCC &= ~CAN_70_RL78F2X_MASK_RFCC_RFIE;
        }
       
        /* TX related, disable */
        regMkx[ interruptBit->RCANxTRM.index ]->MK |= interruptBit->RCANxTRM.bit;
        regCommonF->TMIEC  &= ~( CAN_70_RL78F2X_MASK_TMIEC_TMIE3
                               | CAN_70_RL78F2X_MASK_TMIEC_TMIE2
                               | CAN_70_RL78F2X_MASK_TMIEC_TMIE1
                               | CAN_70_RL78F2X_MASK_TMIEC_TMIE0 );
        regCommonG->THLCC  &= ~CAN_70_RL78F2X_MASK_THLCC_THLIE;
       
        /* Error related, enable */
        regMkx[ interruptBit->RCANxGERR.index ]->MK &= ~interruptBit->RCANxGERR.bit;
        regCommonB->GCTRL |= CAN_70_RL78F2X_MASK_GCTRL_MEIE;
        regMkx[ interruptBit->RCANxERR.index ]->MK &= ~interruptBit->RCANxERR.bit;
        regCommonA->C0CTRL |= ( CAN_70_RL78F2X_MASK_C0CTRL_BEIE
                               | CAN_70_RL78F2X_MASK_C0CTRL_EPIE
                               | CAN_70_RL78F2X_MASK_C0CTRL_OLIE
                               | CAN_70_RL78F2X_MASK_C0CTRL_BLIE
                               | CAN_70_RL78F2X_MASK_C0CTRL_ALIE );
       
        /* Busoff related, disable */
        regCommonA->C0CTRL &= ~CAN_70_RL78F2X_MASK_C0CTRL_BOEIE;
   
#if ( ( CAN_70_WAKEUP_SUPPORT == TRUE ) && ( CAN_70_WAKEUP_INTERRUPT_PROCESSING == TRUE ) )
 
        if ( ( TRUE == canController->CanWakeupSupport )
          && ( CAN_PROCESSING_INTERRUPT == canController->CanWakeupProcessing ) ) {
            /* Wakeup related, enable */
            regMkx[ interruptBit->RCANxWUP.index ]->MK &= ~interruptBit->RCANxWUP.bit;
        } else {
            /* Wakeup related, disable */
            regMkx[ interruptBit->RCANxWUP.index ]->MK |= interruptBit->RCANxWUP.bit;
        }
 
#else /* #if ( ( CAN_70_WAKEUP_SUPPORT == TRUE ) && ( CAN_70_WAKEUP_INTERRUPT_PROCESSING == TRUE ) ) */
       
        /* Wakeup related, disable */
        regMkx[ interruptBit->RCANxWUP.index ]->MK |= interruptBit->RCANxWUP.bit;
       
#endif
       
        /* ECC related, enable */
        /* Enable 2bit error detection interrupt (EC2EDIC) */
        regCfdecctl->CFDECCTL |= CAN_70_RL78F2X_MASK_CFDECCTL_EC2EDIC;
 
    } else {
        /* CAN_CS_UNINIT == ControllerStatus */
        /* Do nothing */
    }
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetRamWindow                                  */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Page              Page number                           */
/* Return      : void                                                         */
/* Contents    : Update CAN controller registers and set RAM window page.     */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetRamWindow( uint8 Controller, uint16 Page )
{
    volatile Can_70_RL78F2X_RegCommonIType* regCommonI;
   
    uint16 regCFDGRWC;
   
    /* Get register information */
    regCommonI = Can_70_CanControllerRegInfo[ Controller ].RegCommonI;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Key value and page number must be set at the same time. */
    /* See chapter F24(18.3.67) / F25(19.3.67) of HW manual. */
    regCFDGRWC = regCommonI->CFDGRWC;
    regCFDGRWC &= ~( CAN_70_RL78F2X_MASK_CFDGRWC_KEY | CAN_70_RL78F2X_MASK_CFDGRWC_RPAGE );
    regCFDGRWC |= CAN_70_RL78F2X_BIT_CFDGRWC_KEY_VALUE | ( CAN_70_RL78F2X_MASK_CFDGRWC_RPAGE & Page );
    regCommonI->CFDGRWC = regCFDGRWC;
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_EnableRxFifo                                  */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) CanConfigSet      Configuration set                     */
/* Return      : void                                                         */
/* Contents    : Update CAN controller registers and enabel Rx FIFO.          */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_EnableRxFifo( uint8 Controller, const Can_ConfigSetType* CanConfigSet )
{
    volatile Can_70_RL78F2X_RegCommonCType* regCommonC;
    const Can_HardwareObjectType*           pHwObject;
    uint8                                   objectId;
    uint8_least                             index;
    uint8_least                             controllerIndex;
    uint8_least                             objectIndex;
    const Can_ControllerType*               canController;
   
    /* search can controller setting */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &(CanConfigSet)->CanController[ controllerIndex ];
        if ( Controller == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    for ( index = 0U; index < CAN_70_NUM_OF_HARDWARE_OBJECT; index++ ) {
       
        pHwObject = &( CanConfigSet->CanHardwareObject[ index ] );
 
        if ( canController->CanControllerId == pHwObject->CanControllerRef->CanControllerId ) {
            if ( CAN_70_RECEIVE == pHwObject->CanObjectType ) {
                for ( objectIndex = 0U; objectIndex < CAN_70_RL78F2X_RXFIFO_MAX; objectIndex++ ) {
                    if ( Can_70_IndxexRxHwObj[ controllerIndex ][ objectIndex ] == index ) {
                        objectId = ( uint8 )objectIndex;
                        regCommonC = Can_70_CanControllerRegInfo[ Controller ].RegCommonC[ objectId ];
                       
                        regCommonC->RFCC &= ( ~CAN_70_RL78F2X_MASK_RFCC_RFE );
                        regCommonC->RFCC |= CAN_70_RL78F2X_MASK_RFCC_RFE;
                        break;
                    } else {
                        /* do nothing */
                    }
                }
            } else {
                /* Nothing */
            }
        } else {
            /* do nothing */
        }
    }
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_GetTxBufferStatus                             */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) TxBufNo           Tx buffer number                      */
/* Return      : CAN_70_TxBufStatInfoType  Tx buffer status                   */
/* Contents    : Refers to the CAN controller register and returns            */
/*               the status of the specified transmit buffer.                 */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
CAN_70_TxBufStatInfoType Can_70_RL78F2X_GetTxBufferStatus( uint8 Controller, uint8 TxBufNo )
{
    CAN_70_TxBufStatInfoType                      ret;
    volatile const Can_70_RL78F2X_RegCommonEType* regCommonE;
    uint8                                         bitTMTRF;
   
    /* Get register information */
    regCommonE = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonE;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
   
    /* Analyze send buffer status.*/
    /* See detailed design document. */
    if ( 0U != ( regCommonE->TMSTS[ TxBufNo ] & CAN_70_RL78F2X_MASK_TMSTS_TMTSTS ) ) {
        ret = CAN_70_TXBUFSTAT_SENDING;
    } else {
        bitTMTRF = ( regCommonE->TMSTS[ TxBufNo ] & CAN_70_RL78F2X_MASK_TMSTS_TMTRF );
        if ( CAN_70_RL78F2X_BIT_TMSTS_TMTRF_NOREQ == bitTMTRF ) {
            ret = CAN_70_TXBUFSTAT_EMP;
        } else if ( CAN_70_RL78F2X_BIT_TMSTS_TMTRF_SENT == bitTMTRF) {
            ret = CAN_70_TXBUFSTAT_SENT;
        } else {
            ret = CAN_70_TXBUFSTAT_OTHER;
        }
    }
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
   
    return ret;
 
}
 
 
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_GetErrorStatus                                */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/*             : (out) comStatus        Communication status                  */
/*             : (out) errorPassiveStatus  Error passive status               */
/* Return      : void                                                         */
/* Contents    : Refers to the register of the CAN controller and returns     */
/*               the error status.                                            */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_GetErrorStatus( uint8 Controller, uint8 Channel,
                                    bool_t* comStatus, bool_t* errorPassiveStatus )
{
    volatile const Can_70_RL78F2X_RegCommonAType* regCommonA;
   
    /* Get register information */
    regCommonA = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ Channel ].RegCommonA;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
   
    /* Check communication status */
    if ( 0x0U != ( regCommonA->C0STSL & CAN_70_RL78F2X_MASK_C0STSL_COMSTS ) ) { /* C0STSL COMSTS */
        *comStatus = TRUE;
    } else {
        *comStatus = FALSE;
    }
   
    /* Check error passive status */
    if ( 0x0U != ( regCommonA->C0STSL & CAN_70_RL78F2X_MASK_C0STSL_EPSTS ) ) { /* C0STSL EPSTS */
        *errorPassiveStatus = TRUE;
    } else {
        *errorPassiveStatus = FALSE;
    }
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetEcc                                        */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/* Return      : void                                                         */
/* Contents    : Update the CAN controller register and perform ECC settings. */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetEcc( uint8 Controller )
{
    volatile Can_70_RL78F2X_RegCfdecctlType QL_70_NEAR * regCfdecctl;
   
    /* Get register information */
    regCfdecctl = Can_70_CanControllerRegInfo[ Controller ].RegCfdecctl;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
   
    /* Enable ECC error check (ECERVF) */
    /* Enable 2bit error detection interrupt (EC2EDIC) */
    regCfdecctl->CFDECCTL
        = CAN_70_RL78F2X_MASK_CFDECCTL_EMCA_W_EN
        | CAN_70_RL78F2X_MASK_CFDECCTL_ECERVF
        | CAN_70_RL78F2X_MASK_CFDECCTL_EC2EDIC;
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_ClearTxBufferStatus                           */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) TxBufNo           Tx buffer number                      */
/* Return      : void                                                         */
/* Contents    : Refers to the CAN controller register and clears             */
/*               the status of the specified transmit buffer.                 */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_ClearTxBufferStatus( uint8 Controller, uint8 TxBufNo )
{
    volatile Can_70_RL78F2X_RegCommonEType* regCommonE;
 
    /* Get register information */
    regCommonE = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonE;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
   
    /* Clear transmit buffer status.*/
    regCommonE->TMC[ TxBufNo ] &= ~CAN_70_RL78F2X_MASK_TMC_TMTR;    
    regCommonE->TMSTS[ TxBufNo ] &= ~CAN_70_RL78F2X_MASK_TMSTS_TMTRF;
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_GetSendHistory                                */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/*             : (out) ObjectId         ObjectID                              */
/*             : (out) timeStampCounter Timestamp couter                      */
/*             : (out) timeStampNum     Timestamp number                      */
/* Return      : void                                                         */
/* Contents    : Refers to the CAN controller register and returns            */
/*               transmission history buffer information.                     */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_GetSendHistory( uint8 Controller, uint8 Channel, uint8* ObjectId,
                                    uint16* timeStampCounter, uint8* timeStampNum )
{
    volatile Can_70_RL78F2X_RegCommonGType*      regCommonG;
    volatile const Can_70_RL78F2X_RegPage1EType* regPage1E;
    uint8_least                                  index;
   
    /* Get register information */
    regCommonG = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ Channel ].RegCommonG;
    regPage1E = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ Channel ].RegPage1E;
   
    /* Initialize output parameters. */
    ObjectId[ 0U ] = 0U;
    timeStampCounter[ 0U ] = 0U;
    *timeStampNum = 0U;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
   
    /* Reading records from send history buffer.*/
    for ( index = 0U; index < CAN_70_RL78F2X_THL_MAX; index++ ){
        if ( 0U != ( CAN_70_RL78F2X_MASK_THLSTS_THLEMP & regCommonG->THLSTS ) ) {
            break;
        } else{
            timeStampCounter[ index ] = regPage1E->THLACC0H;
            ObjectId[ index ] = ( uint8 )( ( regPage1E->THLACC0L & CAN_70_RL78F2X_MASK_THLACC0L_BN )
                                    >> 3U );
            ( *timeStampNum )++;
           
            if ( 0U != ( CAN_70_RL78F2X_MASK_THLCC_THLE & regCommonG->THLCC ) ) {
                regCommonG->THLPCTR =  CAN_70_RL78F2X_MASK_THLPCTR_THLPC;
            } else {
                /* Nothing */
            }
        }
    }
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_CheckRxBuffer                                 */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/*             : (in) ObjectId          ObjectId                              */
/* Return      : bool_t  Existence of received data                           */
/* Contents    : Refers to the CAN controller register and returns            */
/*               the status of the receive buffer (receive FIFO buffer).      */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
bool_t Can_70_RL78F2X_CheckRxBuffer( uint8 Controller, uint8 Channel, uint8 ObjectId )
{
    bool_t                                        ret;
    volatile const Can_70_RL78F2X_RegCommonCType* regCommonC;
   
    ret = FALSE;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
   
    /* Channel is for for future use */
    /* Currently does nothing if a channel other than 0 is specified */
    if ( 0U == Channel ) {
        if ( CAN_70_RL78F2X_RXFIFO_MAX > ObjectId ) {
            regCommonC = Can_70_CanControllerRegInfo[ Controller ].RegCommonC[ ObjectId ];
            if ( 0U == ( CAN_70_RL78F2X_MASK_RFSTS_RFEMP & regCommonC->RFSTS ) ) {
                ret = TRUE;
            }
        }
    }
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
   
    return ret;
 
}
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_GetRxBuffer                                   */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/*             : (in) ObjectId          ObjectID                              */
/*             : (out) id               CAN ID                                */
/*             : (out) dlc              DLC                                   */
/*             : (out) rxTimestamp      Rx timestamp counter                  */
/*             : (out) rxBuffer         Rx buffer                             */
/*             : (out) size             Rx data size (Byte)                   */
/* Return      : void                                                         */
/* Contents    : Refers to the CAN controller register and returns            */
/*               receive buffer (receive FIFO buffer) information.            */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_GetRxBuffer( uint8 Controller, uint8 Channel, uint8 ObjectId, uint32* id,
                                 uint8* dlc, uint16* rxTimestamp, uint8** rxBuffer, uint8* size )
{
    uint32                                       tmpId;
    volatile const Can_70_RL78F2X_RegPage1AType* regPage1A;
    volatile Can_70_RL78F2X_RegPage1BType*       regPage1B;
    uint8_least                                  bufIndex;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Channel is for for future use */
    /* Currently does nothing if a channel other than 0 is specified */
    if ( 0U == Channel ) {
        /* Get register information */
        regPage1A = Can_70_CanControllerRegInfo[ Controller ].RegPage1A[ ObjectId ];
        regPage1B = Can_70_CanControllerRegInfo[ Controller ].RegPage1B[ ObjectId ];
       
        /* CAN ID */
        tmpId = ( uint32 )regPage1A->RFIDH << 16U ;
        *id = tmpId | ( uint32 )regPage1A->RFIDL;
 
        /* FDF */
        if ( 0U != ( CAN_70_RL78F2X_MASK_RFFDSTSL_RFFDF & regPage1A->RFFDSTSL ) ) {
            /* CAN FD */
            *id |= 0x40000000U;
        } else {
            /* Classical-CAN */
            *id &= 0xBFFFFFFFU;
        }
       
        /* DLC */
        *dlc = ( uint8 )( regPage1A->RFPTRH >> 12U );
       
        /* Time stamp */
        *rxTimestamp = regPage1A->RFPTRL;
       
        /* SDU */
        if ( 8U >= *dlc ) {
            *size = *dlc;
        } else {
            *size = dlcTable[ *dlc - 9U ];
        }
 
        /* Receive data into a temporary buffer */
        for ( bufIndex = 0U; bufIndex < *size; bufIndex++ ) {
            Can_70_RL78F2X_RxTempBuffer[ Controller ][ ObjectId ][ bufIndex ] = regPage1B->RFDF[ bufIndex ];
        }
        *rxBuffer = ( uint8* )&( Can_70_RL78F2X_RxTempBuffer[ Controller ][ ObjectId ][ 0U ] );
    }
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_UpdateRxBuffer                                */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) Channel           ChannelID                             */
/*             : (in) ObjectId          ObjectID                              */
/* Return      : void                                                         */
/* Contents    : Change the CAN controller register and update                */
/*               the receive buffer (receive FIFO buffer).                    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_UpdateRxBuffer( uint8 Controller, uint8 Channel, uint8 ObjectId )
{
    volatile Can_70_RL78F2X_RegCommonCType* regCommonC;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Channel is for for future use */
    /* Currently does nothing if a channel other than 0 is specified */
    if ( 0U == Channel ) {
        /* Get register information */
        regCommonC = Can_70_CanControllerRegInfo[ Controller ].RegCommonC[ ObjectId ];
 
        /* Update receive FIFO pointer. */
        /* See chapter F24(18.3.27) / F25(19.3.27) of HW manual. */
        if ( 0U == ( CAN_70_RL78F2X_MASK_RFSTS_RFEMP & regCommonC->RFSTS ) ) {
            regCommonC->RFPCTR = 0x00FFU;
        }
    }
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
#if ( CAN_70_USE_CANFD == TRUE )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_RL78F2X_SetCanFd                                      */
/* Param       : (in) Controller        CAN Channel of RL78F2x(CAN0/CAN1)     */
/*             : (in) CanConfigSet      Configuration set                     */
/* Return      : void                                                         */
/* Contents    : Update the CAN controller register and perform CAN FD        */
/*               settings (CAN FD-specific settings).                         */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_RL78F2X_SetCanFd( uint8 Controller, const Can_ConfigSetType* CanConfigSet )
{
    const Can_ControllerBaudrateConfigType* pBaudrateConfig;
 
    volatile Can_70_RL78F2X_RegCommonHType* regCommonH;
    volatile Can_70_RL78F2X_RegCommonJType* regCommonJ;
    uint16                                  regC0FDCFGH;
    uint16                                  regC0FDCFGL;
    uint16                                  bitCLOE;
    uint16                                  bitTDCO;
    uint16                                  bitTDCOC;
    const Can_ControllerType*               canController;
    uint8_least                             controllerIndex;
 
    /* search can controller setting */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &(CanConfigSet)->CanController[ controllerIndex ];
        if ( Controller == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
    /* Determine CAN mode by configuration. */
    pBaudrateConfig = canController->CanControllerDefaultBaudrate;
    if ( NULL_PTR != pBaudrateConfig->CanControllerFdBaudrateConfig ) {
        /* CAN FD Mode */
        bitCLOE = 0U;
        bitTDCO = ( pBaudrateConfig->CanControllerFdBaudrateConfig )->CanControllerSspOffset;
        bitTDCOC = CAN_70_RL78F2X_MASK_C0FDCFGL_TDCOC;
    } else {
        /* CAN Only Mode */
        bitCLOE = CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE;
        bitTDCO = 0U;
        bitTDCOC = 0U;
    }
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( Controller );
 
    /* Configure settings related to CAN FD. */
    regCommonH = Can_70_CanControllerRegInfo[ Controller ].RegCommonH;
   
    regCommonH->GFDCFG &= ~( CAN_70_RL78F2X_MASK_GFDCFG_TSCCFG | CAN_70_RL78F2X_MASK_GFDCFG_RPED );
   
    regCommonJ = Can_70_CanControllerRegInfo[ Controller ].ChannelRegInfo[ 0U ].RegCommonJ;
   
    regC0FDCFGH = regCommonJ->C0FDCFGH;
    regC0FDCFGH &= ~( CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE | CAN_70_RL78F2X_MASK_C0FDCFGH_TDCO );
    regC0FDCFGH |= ( CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE & bitCLOE )
                 | ( CAN_70_RL78F2X_MASK_C0FDCFGH_TDCO & bitTDCO );
    regCommonJ->C0FDCFGH = regC0FDCFGH;
   
    regC0FDCFGL = regCommonJ->C0FDCFGL;
    regC0FDCFGL &= ~( CAN_70_RL78F2X_MASK_C0FDCFGL_TDCOC );
    regC0FDCFGL |= CAN_70_RL78F2X_MASK_C0FDCFGL_TDCOC & bitTDCOC;
    regCommonJ->C0FDCFGL = regC0FDCFGL;
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
#endif /* #if ( CAN_70_USE_CANFD == TRUE ) */
 
#define CAN_STOP_SEC_CODE_LOCAL
#include "Can_MemMap.h"
/* EOF Can_70_RL78F2X.c ****************************************************************/
 
