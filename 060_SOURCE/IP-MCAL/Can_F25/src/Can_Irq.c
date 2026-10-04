/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Can_Irq.c                                                    */
/* Version     : v1.00.01                                                     */
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
#include "Can_70_RL78F2X_HwReg.h"
#include "Can_Irq.h"
#include "CanIf_Cbk.h"
#include "SchM_Can.h"
#include "EcuM_Cbk.h"
#include "Det.h"
/*----------------------------------------------------------------------------*/
/* file version information                                                   */
/*----------------------------------------------------------------------------*/
#define CAN_70_VENDOR_ID_IRQ_C                                 ( 70U )
#define CAN_70_MODULE_ID_IRQ_C                                 ( 80U )
 
#define CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_C                  ( 22U )
#define CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_C                  ( 11U )
#define CAN_70_AR_RELEASE_REVISION_VERSION_IRQ_C               (  0U )
 
#define CAN_70_SW_MAJOR_VERSION_IRQ_C                          (  1U )
#define CAN_70_SW_MINOR_VERSION_IRQ_C                          (  0U )
#define CAN_70_SW_PATCH_VERSION_IRQ_C                          (  0U )
 
/*----------------------------------------------------------------------------*/
/* file version checks                                                        */
/*----------------------------------------------------------------------------*/
 
/* Can.h version check start */
 
/* Check if current file and Can.h header file are of the same Vendor ID */
#if (CAN_70_VENDOR_ID_IRQ_C    != CAN_VENDOR_ID)
    #error "VENDOR ID for Can_Irq.c and Can.h are different"
#endif      /* End of Vendor Id Version check */
#if (CAN_70_MODULE_ID_IRQ_C    != CAN_MODULE_ID)
    #error "MODULE ID for Can_Irq.c and Can.h are different"
#endif      /* End of Module Id Version check */
 
/* Check if current file and Can.h header file are of the same Software version */
#if ((CAN_70_SW_MAJOR_VERSION_IRQ_C    != CAN_SW_MAJOR_VERSION) ||\
     (CAN_70_SW_MINOR_VERSION_IRQ_C    != CAN_SW_MINOR_VERSION) ||\
     (CAN_70_SW_PATCH_VERSION_IRQ_C    != CAN_SW_PATCH_VERSION))
    #error "Software Version Numbers of Can_Irq.c and Can.h are different"
#endif      /* End of S/W Version check */
 
/* Check if current file and Can.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_C    != CAN_AR_RELEASE_MAJOR_VERSION)   ||\
     (CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_C    != CAN_AR_RELEASE_MINOR_VERSION)   ||\
     (CAN_70_AR_RELEASE_REVISION_VERSION_IRQ_C != CAN_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Can_Irq.c and Can.h are different"
#endif      /* End of Autosar Version check */
 
/*---------------Can_70_RL78F2X_HwReg.h--------------------------------------------------*/
 
/* Check if current file and Can_70_RL78F2X_HwReg.h header file are of the same Vendor ID */
#if (CAN_70_VENDOR_ID_IRQ_C    != CAN_70_VENDOR_ID_RL78F2X_HWREG_H)
    #error "VENDOR ID for Can_Irq.c and Can_70_RL78F2X_HwReg.h are different"
#endif      /* End of Vendor Id Version check */
#if (CAN_70_MODULE_ID_IRQ_C    != CAN_70_MODULE_ID_RL78F2X_HWREG_H)
    #error "MODULE ID for Can_Irq.c and Can_70_RL78F2X_HwReg.h are different"
#endif      /* End of Module Id Version check */
 
/* Check if current file and Can_70_RL78F2X_HwReg.h header file are of the same Software version */
#if ((CAN_70_SW_MAJOR_VERSION_IRQ_C    != CAN_70_SW_MAJOR_VERSION_RL78F2X_HWREG_H) ||\
     (CAN_70_SW_MINOR_VERSION_IRQ_C    != CAN_70_SW_MINOR_VERSION_RL78F2X_HWREG_H) ||\
     (CAN_70_SW_PATCH_VERSION_IRQ_C    != CAN_70_SW_PATCH_VERSION_RL78F2X_HWREG_H))
    #error "Software Version Numbers of Can_Irq.c and Can_70_RL78F2X_HwReg.h are different"
#endif      /* End of S/W Version check */
 
/* Check if current file and Can_70_RL78F2X_HwReg.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_C         != \
      CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_HWREG_H)  || \
     (CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_C         != \
      CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_HWREG_H)  || \
     (CAN_70_AR_RELEASE_REVISION_VERSION_IRQ_C      != \
      CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_HWREG_H))
    #error "AUTOSAR Version Numbers of Can_Irq.c and Can_70_RL78F2X_HwReg.h are different"
#endif      /* End of Autosar Version check */
 
/*---------------------------Can_Irq.h--------------------------------------------------*/
 
/* Check if current file and Can_Irq.h header file are of the same Vendor ID */
#if (CAN_70_VENDOR_ID_IRQ_C    != CAN_70_VENDOR_ID_IRQ_H)
    #error "VENDOR ID for Can_Irq.c and Can_Irq.h are different"
#endif      /* End of Vendor Id Version check */
#if (CAN_70_MODULE_ID_IRQ_C    != CAN_70_MODULE_ID_IRQ_H)
    #error "MODULE ID for Can_Irq.c and Can_Irq.h are different"
#endif      /* End of Vendor Id Version check */
 
/* Check if current file and Can_Irq.h header file are of the same Software version */
#if ((CAN_70_SW_MAJOR_VERSION_IRQ_C    != CAN_70_SW_MAJOR_VERSION_IRQ_H) ||\
     (CAN_70_SW_MINOR_VERSION_IRQ_C    != CAN_70_SW_MINOR_VERSION_IRQ_H) ||\
     (CAN_70_SW_PATCH_VERSION_IRQ_C    != CAN_70_SW_PATCH_VERSION_IRQ_H))
    #error "Software Version Numbers of Can_Irq.c and Can_Irq.h are different"
#endif      /* End of S/W Version check */
 
/* Check if current file and Can_Irq.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_C    != CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_H)   ||\
     (CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_C    != CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_H)   ||\
     (CAN_70_AR_RELEASE_REVISION_VERSION_IRQ_C != CAN_70_AR_RELEASE_REVISION_VERSION_IRQ_H))
    #error "AUTOSAR Version Numbers of Can_Irq.c and Can_Irq.h are different"
#endif      /* End of Autosar Version check */
 
#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------CanIf_Cbk.h--------------------------------------------------*/
 
/* Check if current file and CanIf_Cbk.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_C    != CANIF_70_AR_RELEASE_MAJOR_VERSION_CBK_H)   ||\
     (CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_C    != CANIF_70_AR_RELEASE_MINOR_VERSION_CBK_H))
    #error "AUTOSAR Version Numbers of Can.c and CanIf_Cbk.h are different"
#endif      /* End of Autosar Version check */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */
 
#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------EcuM_Cbk.h--------------------------------------------------*/
 
/* Check if current file and EcuM_Cbk.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_C != ECUM_AR_RELEASE_MAJOR_VERSION_CBK_H)   ||\
     (CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_C != ECUM_AR_RELEASE_MINOR_VERSION_CBK_H))
    #error "AUTOSAR Version Numbers of Can.c and EcuM_Cbk.h are different"
#endif      /* End of Autosar Version check */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */
 
#if ( QINES_MCAL_VERSION_NO_CHECK != TRUE )
/*---------------Det.h -------------------------------------------------------*/
 
/* Check if DET for CAN is enabled or not */
#if( CAN_DEV_ERROR_DETECT != FALSE )
/* Check if current file and Det.h header file are of the same Autosar version */
#if ((CAN_70_AR_RELEASE_MAJOR_VERSION_IRQ_C    != DET_AR_RELEASE_MAJOR_VERSION)   ||\
     (CAN_70_AR_RELEASE_MINOR_VERSION_IRQ_C    != DET_AR_RELEASE_MINOR_VERSION))
    #error "AUTOSAR Version Numbers of Can_Irq.c and Det.h are different"
#endif      /* End of Autosar Version check */
#endif      /* #if( CAN_DEV_ERROR_DETECT != FALSE ) */
#endif /* #if ( QINES_MCAL_VERSION_NO_CHECK != TRUE ) */
 
/* Can_Irq.c version check end */
 
/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/
 
/*----------------------------------------------------------------------------*/
/*                  Interrupt Service Routines                                */
/*----------------------------------------------------------------------------*/
#define CAN_START_SEC_CODE_LOCAL
#include "Can_MemMap.h"
 
#if( ( CAN_70_RX_INTERRUPT_PROCESSING == TRUE ) || ( CAN_70_RX_MIXED_PROCESSING == TRUE ) )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_Isr_Reception                                         */
/* Param       : (in)canChannel      CAN Channel of RL78F2x(CAN0/CAN1)        */
/* Return      : void                                                         */
/* Contents    : Refers to the CAN controller register and performs           */
/*               reception processing.                                        */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_Isr_Reception_CANX( uint8 canChannel )
{
    volatile Can_70_RL78F2X_RegCommonCType*       regCommonC;
    volatile const Can_70_RL78F2X_RegCommonDType* regCommonD;
    uint8_least                                   objCnt;
    bool_t                                        dataExist;
    uint32                                        id;
    uint8                                         dlc;
    uint16                                        timeStamp;
    uint8*                                        bufPtr;
    uint8                                         dataLen;
    bool_t                                        calloutRet;
    Can_HwType                                    mailBox;
    PduInfoType                                   pduInfo;
    uint8                                         contorllerId;
    uint8                                         channelId;
    const Can_HardwareObjectType*                 canHardwareObject;
    const Can_ControllerType*                     canController;
    uint8_least                                   controllerIndex;
 
    /* Check the CAN channel range */
    if ( canChannel >= CAN_70_NUM_OF_CAN_CHANNEL ) {
        return;
    }
 
    /* Search for the controller settings */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
        if ( canChannel == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
#if( CAN_70_RX_POLLING_PROCESSING == TRUE )
 
    /* Skip processing if using polling.  */
    if ( CAN_PROCESSING_POLLING == canController->CanRxProcessing ) {
        return;
    }
 
#endif /* #if( CAN_70_RX_POLLING_PROCESSING == TRUE ) */
 
    contorllerId = canChannel;
    channelId = 0U;  /* tentative */
    regCommonD = Can_70_CanControllerRegInfo[ contorllerId ].RegCommonD;
 
    for ( objCnt = 0U; objCnt < CAN_70_RL78F2X_RXFIFO_MAX; objCnt++ ) {
       
        /* Get Hardware Object. */
        if ( CAN_70_NUM_OF_HARDWARE_OBJECT > Can_70_IndxexRxHwObj[ controllerIndex ][ objCnt ]  ) {
            canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ Can_70_IndxexRxHwObj[ controllerIndex ][ objCnt ] ];
 
#if( CAN_70_RX_MIXED_PROCESSING == TRUE )
 
            /* Skip processing if using polling.  */
            if ( CAN_PROCESSING_MIXED == canController->CanRxProcessing ) {
                if ( TRUE == canHardwareObject->CanHardwareObjectUsesPolling ) {
                    canHardwareObject = NULL_PTR;
                }
            }
 
#endif /* #if( CAN_70_RX_MIXED_PROCESSING == TRUE ) */
 
        } else {
            canHardwareObject = NULL_PTR;
        }
       
        if ( NULL_PTR != canHardwareObject ) {
            regCommonC = Can_70_CanControllerRegInfo[ contorllerId ].RegCommonC[ objCnt ];
           
            /* Select a can controller */
            CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( contorllerId );
 
            /* Check interrupt flag. */
            /* See (1) in HW manual F24(figure 18-46) / F25(figure 19-46) */
            if ( 0U != ( regCommonD->RFISTS &
                       ( CAN_70_RL78F2X_MASK_RFISTS_RF0IF << objCnt ) ) ) {
                       
                /* Clear interrupt flag. */
                regCommonC->RFSTS &= ~CAN_70_RL78F2X_MASK_RFSTS_RFIF;
               
                /* Release the can controller */
                CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
                /* Check the existence of received data. */
                /* See (4) in HW manual F24(figure 18-46) / F25(figure 19-46) */
                dataExist = Can_70_HW_CheckRxBuffer( contorllerId, channelId, ( uint8 )objCnt );
                       
                while ( TRUE == dataExist ) {
                   
                    /* Get received data from receive FIFO buffer. */
                    Can_70_HW_GetRxBuffer( contorllerId, channelId, ( uint8 )objCnt, &id, &dlc,
                                           &timeStamp, &bufPtr, &dataLen );
                   
                    /* If a callout function is set in the configuration, execute the callout function. */
                    /* Do not process if the return value of the callout function is FALSE. */
                    calloutRet = TRUE;
                    if ( NULL_PTR != CAN_LPDU_RECEIVE_CALLOUT_FUNCTION ) {
                        calloutRet = ( *CAN_LPDU_RECEIVE_CALLOUT_FUNCTION )( ( uint8 )objCnt,
                                                                             ( Can_IdType )id,
                                                                             dataLen, bufPtr );
                    }
                    if ( TRUE == calloutRet ) {
                       
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
                   
                        /* Update ingress timestamp data. */
                        Can_70_IngressTimeStampData[ controllerIndex ][ objCnt ].Enable = TRUE;
                        Can_70_IngressTimeStampData[ controllerIndex ][ objCnt ].Hrh = ( Can_HwHandleType )canHardwareObject->CanObjectId;
                        Can_70_IngressTimeStampData[ controllerIndex ][ objCnt ].TimeStamp = timeStamp;
                   
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
                   
                        /* CanIf_RxIndication() parameter. */
                        mailBox.CanId = ( Can_IdType )id;
                        mailBox.Hoh = ( Can_HwHandleType )canHardwareObject->CanObjectId;
                        mailBox.ControllerId = canController->CanControllerId;
 
                        /* CanIf_RxIndication() parameter. */
                        pduInfo.SduDataPtr = bufPtr;
                        pduInfo.MetaDataPtr = ( uint8* )( &id );
                        pduInfo.SduLength = dataLen;
                       
                        /*  Notify completion of receiving. */
                        CanIf_RxIndication( &mailBox, &pduInfo);
                       
                    }
                       
                    /* Update receive FIFO pointer. */
                    Can_70_RL78F2X_UpdateRxBuffer( contorllerId, channelId, ( uint8 )objCnt );
                   
                    /* Check the existence of received data. */
                    /* See (4) in HW manual F24(figure 18-46) / F25(figure 18-46) */
                    dataExist = Can_70_HW_CheckRxBuffer( contorllerId, channelId, ( uint8 )objCnt );
                }
            } else {
                /* Release the can controller */
                CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
            }
        }
    }
}
#endif /* #if( ( CAN_70_RX_INTERRUPT_PROCESSING == TRUE ) || ( CAN_70_RX_MIXED_PROCESSING == TRUE ) ) */
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_Isr_GlobalError                                       */
/* Param       : (in)canChannel      CAN Channel of RL78F2x(CAN0/CAN1)        */
/* Return      : void                                                         */
/* Contents    : Refers to the CAN controller register and notifies           */
/*               Det of the error.                                            */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_Isr_GlobalError_CANX( uint8 canChannel )
{
    volatile const Can_70_RL78F2X_RegCommonBType* regCommonB;
    volatile Can_70_RL78F2X_RegCommonCType*       regCommonC;
    uint8_least                                   rxCnt;
    uint8_least                                   contorllerId;
 
    /* Check the CAN channel range */
    if ( canChannel >= CAN_70_NUM_OF_CAN_CHANNEL ) {
        return;
    }
 
    contorllerId = canChannel;
    regCommonB =  Can_70_CanControllerRegInfo[ contorllerId ].RegCommonB;
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( contorllerId );
   
    /* Check message lost detection. */
    if ( 0U != ( regCommonB->GERFLL & CAN_70_RL78F2X_MASK_GERFLL_MES ) ) {
       
        /* Clear interrupt flag */
        /* See chapter F24(18.3.14) / F25(19.3.14) of HW manual. */
        for ( rxCnt = 0U; rxCnt < CAN_70_RL78F2X_RXFIFO_MAX; rxCnt++ ) {
            regCommonC = Can_70_CanControllerRegInfo[ contorllerId ].RegCommonC[ rxCnt ];
            regCommonC->RFSTS &= ~CAN_70_RL78F2X_MASK_RFSTS_RFMLT;
        }
       
        /* Report runtime error */
        ( void )Det_ReportRuntimeError( ( uint16 )CAN_MODULE_ID, ( uint8 )CAN_INDEX,
                                        ( uint8 )CAN_SID_MAINFUNCTION_READ, ( uint8 )CAN_E_DATALOST );
       
    }
 
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
 
#if( ( CAN_70_TX_INTERRUPT_PROCESSING == TRUE ) || ( CAN_70_TX_MIXED_PROCESSING == TRUE ) )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_Isr_Transmission                                      */
/* Param       : (in)canChannel      CAN Channel of RL78F2x(CAN0/CAN1)        */
/* Return      : void                                                         */
/* Contents    : Refers to the CAN controller register and performs           */
/*               transmission completion processing.                          */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_Isr_Transmission_CANX( uint8 canChannel )
{
    volatile Can_70_RL78F2X_RegCommonEType* regCommonE;
    uint8_least                             objCnt;
    uint8                                   contorllerId;
    uint8                                   channelId;
    const Can_HardwareObjectType*           canHardwareObject;
    uint8_least                             controllerIndex;
    const Can_ControllerType*               canController;
 
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
    volatile Can_70_RL78F2X_RegCommonGType* regCommonG;
    uint8_least                             timestampCnt;
    uint8                                   objIdList[ CAN_70_RL78F2X_THL_MAX ];
    uint8                                   num;
    uint8                                   objId;
    uint16                                  timestampList[ CAN_70_RL78F2X_THL_MAX ];
    uint16                                  timeStamp;
    PduIdType                               txPduId;
    Can_70_EgressTimeStampType*             pEgress;
    Can_70_EgressTimeStampType              egressWork[ CAN_70_NUM_OF_EGRESS ];
    uint8_least                             indexEgress;
    uint8_least                             indexEgressWork;
   
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
    /* Check the CAN channel range */
    if ( canChannel >= CAN_70_NUM_OF_CONTROLLER ) {
        return;
    }
 
    /* Search for the controller settings */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
        if ( canChannel == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
#if( CAN_70_TX_POLLING_PROCESSING == TRUE )
 
    /* Skip processing if using polling.  */
    if ( CAN_PROCESSING_POLLING == canController->CanTxProcessing ) {
        return;
    }
 
#endif /* #if( CAN_70_TX_POLLING_PROCESSING == TRUE ) */
   
    contorllerId = canChannel;
    channelId  = 0U;  /* tentative */    
    regCommonE = Can_70_CanControllerRegInfo[ contorllerId ].ChannelRegInfo[ channelId ].RegCommonE;
 
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( contorllerId );
 
    /* Transmission completion interrupt processing */
    for ( objCnt = 0U; objCnt < CAN_70_RL78F2X_TXBUFFER_MAX; objCnt++ ) {
       
        /* Get Hardware Object. */
        if ( CAN_70_NUM_OF_HARDWARE_OBJECT > Can_70_IndxexTxHwObj[ controllerIndex ][ objCnt ].IndexTxHwObj  ) {
            canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ Can_70_IndxexTxHwObj[ controllerIndex ][ objCnt ].IndexTxHwObj ];
 
#if ( CAN_70_TX_MIXED_PROCESSING == TRUE )
 
            /* Skip processing if using polling.  */
            if ( CAN_PROCESSING_MIXED == canController->CanTxProcessing ) {
                if ( TRUE == canHardwareObject->CanHardwareObjectUsesPolling ) {
                    canHardwareObject = NULL_PTR;
                }
            }
 
#endif /* #if( CAN_70_TX_MIXED_PROCESSING == TRUE ) */
 
        } else {
            canHardwareObject = NULL_PTR;
        }
       
        if ( NULL_PTR != canHardwareObject ) {
            if ( CAN_70_RL78F2X_BIT_TMSTS_TMTRF_SENT == ( regCommonE->TMSTS[ objCnt ]
                                                        & CAN_70_RL78F2X_MASK_TMSTS_TMTRF ) ) {
                /* Clear interrupt flag */
                regCommonE->TMSTS[ objCnt ] &= ~CAN_70_RL78F2X_MASK_TMSTS_TMTRF;
               
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
 
                /* Check send request information. */
                if ( ( FALSE == Can_70_TxRequestInfo[ controllerIndex ][ objCnt ].Timestamp )
                  && ( TRUE  == Can_70_TxRequestInfo[ controllerIndex ][ objCnt ].Enable ) ) {
             
#else /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
       
                /* Check send request information. */
                if ( TRUE  == Can_70_TxRequestInfo[ controllerIndex ][ objCnt ].Enable ) {
             
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
 
                    /* Notify completion of sending. */
                    CanIf_TxConfirmation( Can_70_TxRequestInfo[ controllerIndex ][ objCnt ].CanTxPduId );
                   
                    /* Clear send request information. */
                    Can_70_TxRequestInfo[ controllerIndex ][ objCnt ].Enable = FALSE;
                   
                }
            /* Because the volatile variable is referenced twice, check it twice. */
            } else if ( ( CAN_70_RL78F2X_BIT_TMSTS_TMTRF_ABORT == ( regCommonE->TMSTS[ objCnt ]
                                                                & CAN_70_RL78F2X_MASK_TMSTS_TMTRF ) )
                     || ( CAN_70_RL78F2X_BIT_TMSTS_TMTRF_SENT_ABORT == ( regCommonE->TMSTS[ objCnt ]
                                                                & CAN_70_RL78F2X_MASK_TMSTS_TMTRF ) ) ) {
                /* Clear interrupt flag */
                regCommonE->TMSTS[ objCnt ] &= ~CAN_70_RL78F2X_MASK_TMSTS_TMTRF;
            } else {
                /* CAN_70_RL78F2X_BIT_TMSTS_TMTRF_NOREQ */
            }
        }
    }
   
#if ( CAN_GLOBAL_TIME_SUPPORT == TRUE )
   
    regCommonG = Can_70_CanControllerRegInfo[ contorllerId ].ChannelRegInfo[ channelId ].RegCommonG;
 
    /* Transmission history interrupt processing */
    if ( 0U != ( CAN_70_RL78F2X_MASK_THLSTS_THLIF & regCommonG->THLSTS ) ) {
        /* Clear interrupt flag */
        regCommonG->THLSTS &= ~CAN_70_RL78F2X_MASK_THLSTS_THLIF;
       
        Can_70_HW_GetSendHistory( contorllerId, channelId, &objIdList[ 0U ], &timestampList[ 0U ], &num );
       
        for ( timestampCnt = 0U; timestampCnt < num; timestampCnt++ ) {
           
            objId = objIdList[ timestampCnt ];
           
            /* Get Hardware Object. */
            if ( CAN_70_NUM_OF_HARDWARE_OBJECT > Can_70_IndxexTxHwObj[ controllerIndex ][ objId ].IndexTxHwObj ) {
                canHardwareObject = &( Can_70_ConfigPtr->CanConfigSet )->CanHardwareObject[ Can_70_IndxexTxHwObj[ controllerIndex ][ objId ].IndexTxHwObj ];
               
#if ( CAN_70_TX_MIXED_PROCESSING == TRUE )
 
                /* Skip processing if using polling.  */
                if ( CAN_PROCESSING_MIXED == canController->CanTxProcessing ) {
                    if ( TRUE == canHardwareObject->CanHardwareObjectUsesPolling ) {
                        canHardwareObject = NULL_PTR;
                    }
                }
 
#endif /* #if( CAN_70_TX_MIXED_PROCESSING == TRUE ) */
 
            } else {
                canHardwareObject = NULL_PTR;
            }
       
            if ( ( NULL_PTR != canHardwareObject )
              && ( TRUE == Can_70_TxRequestInfo[ controllerIndex ][ objId ].Enable ) ) {
                txPduId = Can_70_TxRequestInfo[ controllerIndex ][ objId ].CanTxPduId;
                timeStamp = timestampList[ timestampCnt ];
               
                /* Initialize egressWork. */
                for ( indexEgressWork = 0U; indexEgressWork < CAN_70_NUM_OF_EGRESS; indexEgressWork++ ) {
                    egressWork[ indexEgressWork ].Enable = FALSE;
                    egressWork[ indexEgressWork ].TxPduId = 0U;
                    egressWork[ indexEgressWork ].TimeStamp = 0U;
                }
           
                /* Copy records in Can_70_EgressTimeStampData to egressWork. ( excluding the same PduId record ) */
                indexEgressWork = 0U;
                for ( indexEgress = 0U; indexEgress < CAN_70_NUM_OF_EGRESS; indexEgress++ ) {
                   
                    pEgress = &Can_70_EgressTimeStampData[ controllerIndex ][ objId ][ indexEgress ];
                   
                    if ( TRUE == pEgress->Enable ) {
                        if ( txPduId != pEgress->TxPduId ) {
                            egressWork[ indexEgressWork ].Enable = pEgress->Enable;
                            egressWork[ indexEgressWork ].TxPduId = pEgress->TxPduId;
                            egressWork[ indexEgressWork ].TimeStamp = pEgress->TimeStamp;
                            indexEgressWork++;
                        }
                    } else {
                        break;
                    }
                }
           
                /* Copy records in EgressWork to Can_70_EgressTimeStampData. */
                if ( CAN_70_NUM_OF_EGRESS <= indexEgressWork ) {
                    indexEgress = 0U;
                    for ( indexEgressWork = 1U; indexEgressWork < CAN_70_NUM_OF_EGRESS; indexEgressWork++ ) {
                        pEgress = &Can_70_EgressTimeStampData[ controllerIndex ][ objId ][ indexEgress ];
                        pEgress->Enable = egressWork[ indexEgressWork ].Enable;
                        pEgress->TxPduId = egressWork[ indexEgressWork ].TxPduId;
                        pEgress->TimeStamp = egressWork[ indexEgressWork ].TimeStamp;
                        indexEgress++;
                    }
                } else {
                    for ( indexEgress = 0U; indexEgress < indexEgressWork; indexEgress++ ) {
                        pEgress = &Can_70_EgressTimeStampData[ controllerIndex ][ objId ][ indexEgress ];
                        pEgress->Enable = egressWork[ indexEgress ].Enable;
                        pEgress->TxPduId = egressWork[ indexEgress ].TxPduId;
                        pEgress->TimeStamp = egressWork[ indexEgress ].TimeStamp;
                    }
                }
               
                /* Add a record. */
                pEgress = &Can_70_EgressTimeStampData[ controllerIndex ][ objId ][ indexEgress ];
                pEgress->Enable = TRUE;
                pEgress->TxPduId = txPduId;
                pEgress->TimeStamp = timeStamp;
               
                /* Notify completion of sending. */
                CanIf_TxConfirmation( Can_70_TxRequestInfo[ controllerIndex ][ objId ].CanTxPduId );
               
                /* Clear send request information. */
                Can_70_TxRequestInfo[ controllerIndex ][ objId ].Enable = FALSE;
               
            }
        }
    }
 
#endif /* #if ( CAN_GLOBAL_TIME_SUPPORT == TRUE ) */
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
}
#endif /* #if #if( ( CAN_70_TX_INTERRUPT_PROCESSING == TRUE ) || ( CAN_70_TX_MIXED_PROCESSING == TRUE ) ) */
 
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_Isr_ChannelError                                      */
/* Param       : (in)canChannel      CAN Channel of RL78F2x(CAN0/CAN1)        */
/* Return      : void                                                         */
/* Contents    : Refers to the register of the CAN controller and notifies    */
/*               the upper layer of the error.                                */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_Isr_ChannelError_CANX( uint8 canChannel )
{
    volatile Can_70_RL78F2X_RegCommonAType* regCommonA;
    uint8                                   controllerId;
    uint8                                   channelId;
    const Can_ControllerType*               canController;
    uint8_least                             controllerIndex;
   
#if ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE )
   
    uint8                                   rxErrorCounter;
    uint8                                   txErrorCounter;
   
#endif /* ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE ) */
 
#if ( ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE ) || ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE ) )
 
    uint16                                  regValL;
 
#endif /* #if ( ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE ) || ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE ) ) */
 
    /* Check the CAN channel range */
    if ( canChannel >= CAN_70_NUM_OF_CAN_CHANNEL ) {
        return;
    }
 
    /* Search for the controller settings */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
        if ( canChannel == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
    controllerId = canChannel;
    channelId    = 0U;  /* tentative */
 
    /* Get register information */
    regCommonA = Can_70_CanControllerRegInfo[ controllerId ].ChannelRegInfo[ channelId ].RegCommonA;
   
    /* Select a can controller */
    CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( controllerId );
 
#if ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE )
 
    /* Get register value */
    regValL = regCommonA->C0ERFLL;
 
#elif ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE )
 
    if ( CAN_PROCESSING_INTERRUPT == canController->CanBusoffProcessing ) {
        /* Get register value */
        regValL = regCommonA->C0ERFLL;
    } else {
        regValL = 0U;
    }
 
#endif /* #elif ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE ) */
   
    /* Clear interrupt flag ( except BUSOFF ) */
    regCommonA->C0ERFLL &= ~( CAN_70_RL78F2X_MASK_C0ERFLL_ADERR
                            | CAN_70_RL78F2X_MASK_C0ERFLL_B0ERR
                            | CAN_70_RL78F2X_MASK_C0ERFLL_B1ERR
                            | CAN_70_RL78F2X_MASK_C0ERFLL_CERR
                            | CAN_70_RL78F2X_MASK_C0ERFLL_AERR
                            | CAN_70_RL78F2X_MASK_C0ERFLL_FERR
                            | CAN_70_RL78F2X_MASK_C0ERFLL_SERR
                            | CAN_70_RL78F2X_MASK_C0ERFLL_ALF
                            | CAN_70_RL78F2X_MASK_C0ERFLL_BLF
                            | CAN_70_RL78F2X_MASK_C0ERFLL_OVLF
                            | CAN_70_RL78F2X_MASK_C0ERFLL_BORF
                            | CAN_70_RL78F2X_MASK_C0ERFLL_EPF
                            | CAN_70_RL78F2X_MASK_C0ERFLL_EWF
                            | CAN_70_RL78F2X_MASK_C0ERFLL_BEF );
   
    /* Release the can controller */
    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
#if ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE )
   
    /* Check error passive */
    if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_EPF ) ) {
        /* Select a can controller */
        CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( controllerId );
 
        rxErrorCounter = ( uint8 )( regCommonA->C0STSH & CAN_70_RL78F2X_MASK_C0STSH_REC );
        txErrorCounter = ( uint8 )( regCommonA->C0STSH &
                                  ( CAN_70_RL78F2X_MASK_C0STSH_TEC >> 8U ) );
 
        /* Release the can controller */
        CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
        CanIf_ControllerErrorStatePassive( controllerId, ( uint16 )rxErrorCounter, ( uint16 )txErrorCounter );
    }
   
    /* Check from bus errors that seem to occur frequently. */
    if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_ALF ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_ARBITRATION_LOST );
 
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_AERR ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_CHECK_ACK_FAILED );
       
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_SERR ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_CHECK_STUFFING_FAILED );
       
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_OVLF ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_OVERLOAD );
       
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_BLF ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_BUS_LOCK );
       
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_CERR ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_CHECK_CRC_FAILED );
       
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_ADERR ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_ACK_DELIMITER );
       
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_FERR ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_CHECK_FORM_FAILED );
       
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_B1ERR ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_BIT_MONITORING1 );
       
    } else if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_B0ERR ) ) {
        CanIf_ErrorNotification( controllerId, CAN_ERROR_BIT_MONITORING0 );
       
    } else {
        /* Do nothing */
        /* Other errors not specified by AUTOSAR, will not be reported. */
    }
   
#endif /* ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE ) */
   
#if ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE )
   
    if ( 0U != ( regValL & CAN_70_RL78F2X_MASK_C0ERFLL_BOEF ) ) {
        /* Select a can controller */
        CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( controllerId );
 
        /* Clear interrupt flag ( BUSOFF ) */
        regCommonA->C0ERFLL &= ~CAN_70_RL78F2X_MASK_C0ERFLL_BOEF;
 
        /* Release the can controller */
        CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
        /* Bus off mode transition */
        Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_BUSOFF;
        Can_70_HW_DisableInterrupt( controllerId );
        Can_70_HW_SetChannelMode( controllerId, channelId, CAN_70_CMODE_RESET );
    }
   
#endif /* #if ( CAN_70_BUSOFF_INTERRUPT_PROCESSING == TRUE ) */
   
}
 
#if ( ( CAN_70_WAKEUP_SUPPORT == TRUE ) && ( CAN_70_WAKEUP_INTERRUPT_PROCESSING == TRUE ) )
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_Isr_Wakeup                                            */
/* Param       : (in)canChannel      CAN Channel of RL78F2x(CAN0/CAN1)        */
/* Return      : void                                                         */
/* Contents    : Refers to the register of the CAN controller and notifies    */
/*               the upper layer of the wakeup.                               */
/* Author      : --                                                           */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_Isr_Wakeup_CANX( uint8 canChannel )
{
    uint8                       controllerId;
    uint8                       channelId;
    EcuM_WakeupSourceType       wakeupSource;
    const Can_ControllerType*   canController;
    uint8_least                 controllerIndex;
   
    /* Check the CAN channel range */
    if ( canChannel >= CAN_70_NUM_OF_CAN_CHANNEL ) {
        return;
    }
 
    /* Search for the controller settings */
    for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
        canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
        if ( canChannel == canController->CanQChannelId ) {
            break;
        } else {
            canController = NULL_PTR;
        }
    }
    if ( NULL_PTR == canController ) {
        return;
    }
 
    /* Skip processing if this controller not support wakeup.  */
    if ( FALSE == canController->CanWakeupSupport ) {
        return;
    }
 
#if ( CAN_70_WAKEUP_POLLING_PROCESSING == TRUE )
 
    /* Skip processing if using polling.  */
    if ( CAN_PROCESSING_POLLING == canController->CanWakeupProcessing ) {
        return;
    }
 
#endif /* #if ( CAN_70_WAKEUP_POLLING_PROCESSING == TRUE ) */
 
    controllerId = canChannel;
    channelId    = 0U;  /* tentative */
   
    /* [SWS_Can_00364] */
    wakeupSource = canController->CanWakeupSourceRef;
    EcuM_CheckWakeup( wakeupSource );
   
    /* Clear interrupt flag */
    /* Clear flag after notification according to AUTOSAR wakeup sequence.  */
    /* See AUTOSAR EcuM SWS Figure 9.5: CAN controller wake up by interrupt */
    Can_70_RL78F2X_ClearWakeup( controllerId, channelId );
   
    /* Wakeup mode transition */
    Can_70_ControllerStatusAction[ controllerIndex ] = CAN_TO_WAKEUP;
    Can_70_HW_DisableInterrupt( controllerId );
}
#endif /* #if ( ( CAN_70_WAKEUP_SUPPORT == TRUE ) && ( CAN_70_WAKEUP_INTERRUPT_PROCESSING == TRUE ) ) */
 
/******************************************************************************/
/* ModuleID    : CAN_MODULE_ID (080)                                          */
/* ServiceID   : --                                                           */
/* Name        : Can_70_Isr_CanRamEcc                                         */
/* Param       : void                                                         */
/* Return      : void                                                         */
/* Contents    : Refers to the register of the CAN controller and notifies    */
/*               the upper layer of the error in response                     */
/*               to ECC error detection.                                      */
/* Note        : --                                                           */
/******************************************************************************/
void Can_70_Isr_CanRamEcc( void )
{
    volatile Can_70_RL78F2X_RegCommonBType* regCommonB;
    const Can_ControllerType*               canController;
    uint8                                   canChannelIndex;
    uint8                                   controllerIndex;
#if ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE )
    uint8                                   controllerId;
#endif /* ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE ) */
 
    /* Check CAN0/CAN1 RAM Error */
    for ( canChannelIndex = 0U; canChannelIndex < CAN_70_NUM_OF_CAN_CHANNEL; canChannelIndex++ ) {
        /* Search for the controller settings */
        for ( controllerIndex = 0U; controllerIndex < CAN_70_NUM_OF_CONTROLLER; controllerIndex++ ) {
            canController = &( Can_70_ConfigPtr->CanConfigSet )->CanController[ controllerIndex ];
            if ( canChannelIndex == canController->CanQChannelId ) {
                /* Select a can controller */
                CAN_70_CONTROLLER_SELECT_WITH_EXCLUSIVE( canChannelIndex );
 
                regCommonB = Can_70_CanControllerRegInfo[ canChannelIndex ].RegCommonB;
                if ( 0U != ( regCommonB->GERFLH & CAN_70_RL78F2X_MASK_GERFLH_EEF ) ) {
                    /* Clear interrupt flag */
                    regCommonB->GERFLH &= ~CAN_70_RL78F2X_MASK_GERFLH_EEF;
           
                    /* Release the can controller */
                    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
 
#if ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE )
                    controllerId = canController->CanControllerId;
                    /* Notify CAN_ERROR_BIT when detecting ECC error. */
                    CanIf_ErrorNotification( controllerId, CAN_ERROR_BIT );
       
#endif /* ( CAN_ENABLE_SECURITY_EVENT_REPORTING == TRUE ) */
 
                } else {
                    /* Release the can controller */
                    CAN_70_CONTROLLER_RELEASE_WITH_EXCLUSIVE();
                }
                break;
            } else {
                /* do nothing */
            }
        }
    }
}
 
#define CAN_STOP_SEC_CODE_LOCAL
#include "Can_MemMap.h"
/* EOF Can_Irq.c ****************************************************************/
 
