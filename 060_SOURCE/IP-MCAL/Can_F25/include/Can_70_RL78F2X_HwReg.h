/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Can_70_RL78F2X_HwReg.h                                       */
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
#ifndef CAN_70_RL78F2X_HWREG_H
#define CAN_70_RL78F2X_HWREG_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Can_70_RL78F2X_HwReg_Dep.h"
#include "QINeS_Lite.h"

/*----------------------------------------------------------------------------*/
/* file version information                                                   */
/*----------------------------------------------------------------------------*/
#define CAN_70_VENDOR_ID_RL78F2X_HWREG_H                           ( 70U )
#define CAN_70_MODULE_ID_RL78F2X_HWREG_H                           ( 80U )

#define CAN_70_AR_RELEASE_MAJOR_VERSION_RL78F2X_HWREG_H            ( 22U )
#define CAN_70_AR_RELEASE_MINOR_VERSION_RL78F2X_HWREG_H            ( 11U )
#define CAN_70_AR_RELEASE_REVISION_VERSION_RL78F2X_HWREG_H         (  0U )

#define CAN_70_SW_MAJOR_VERSION_RL78F2X_HWREG_H                    (  1U )
#define CAN_70_SW_MINOR_VERSION_RL78F2X_HWREG_H                    (  0U )
#define CAN_70_SW_PATCH_VERSION_RL78F2X_HWREG_H                    (  0U )

/*----------------------------------------------------------------------------*/
/* file version checks                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/

/* See chapter F24(18.3.1) / F25(19.3.1) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_C0NCFGH_NTSEG2        ( ( uint16 )0xFE00U )
#define CAN_70_RL78F2X_MASK_C0NCFGH_NTSEG1        ( ( uint16 )0x01FEU )
#define CAN_70_RL78F2X_MASK_C0NCFGH_NSJW          ( ( uint16 )0x0001U )
#define CAN_70_RL78F2X_MASK_C0NCFGL_NSJW          ( ( uint16 )0xFC00U )
#define CAN_70_RL78F2X_MASK_C0NCFGL_NBRP          ( ( uint16 )0x03FFU )

/* See chapter F24(18.3.2) / F25(19.3.2) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_C0CTRH_ROM            ( ( uint16 )0x8000U )
#define CAN_70_RL78F2X_MASK_C0CTRH_BFT            ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_C0CTRH_CTMS           ( ( uint16 )0x0600U )
#define CAN_70_RL78F2X_MASK_C0CTRH_CTME           ( ( uint16 )0x0100U )
#define CAN_70_RL78F2X_MASK_C0CTRH_ERRD           ( ( uint16 )0x0080U )
#define CAN_70_RL78F2X_MASK_C0CTRH_BOM            ( ( uint16 )0x0060U )
#define CAN_70_RL78F2X_MASK_C0CTRH_TDCVFIE        ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_C0CTRH_SOCOIE         ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_C0CTRH_EOCOIE         ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_C0CTRH_TAIE           ( ( uint16 )0x0001U )
#define CAN_70_RL78F2X_MASK_C0CTRL_ALIE           ( ( uint16 )0x8000U )
#define CAN_70_RL78F2X_MASK_C0CTRL_BLIE           ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_C0CTRL_OLIE           ( ( uint16 )0x2000U )
#define CAN_70_RL78F2X_MASK_C0CTRL_BORIE          ( ( uint16 )0x1000U )
#define CAN_70_RL78F2X_MASK_C0CTRL_BOEIE          ( ( uint16 )0x0800U )
#define CAN_70_RL78F2X_MASK_C0CTRL_EPIE           ( ( uint16 )0x0400U )
#define CAN_70_RL78F2X_MASK_C0CTRL_EWIE           ( ( uint16 )0x0200U )
#define CAN_70_RL78F2X_MASK_C0CTRL_BEIE           ( ( uint16 )0x0100U )
#define CAN_70_RL78F2X_MASK_C0CTRL_RTBO           ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_C0CTRL_CSLPR          ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_C0CTRL_CHMDC          ( ( uint16 )0x0003U )

/* See chapter F24(18.3.3) / F25(19.3.3) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_C0STSH_TEC            ( ( uint16 )0xFF00U )
#define CAN_70_RL78F2X_MASK_C0STSH_REC            ( ( uint16 )0x00FFU )
#define CAN_70_RL78F2X_MASK_C0STSL_COMSTS         ( ( uint16 )0x0080U )
#define CAN_70_RL78F2X_MASK_C0STSL_BOSTS          ( ( uint16 )0x0010U )
#define CAN_70_RL78F2X_MASK_C0STSL_EPSTS          ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_C0STSL_CSLPSTS        ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_C0STSL_CHLTSTS        ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_C0STSL_CRSTSTS        ( ( uint16 )0x0001U )

/* See chapter F24(18.3.4) / F25(19.3.4) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_C0ERFLL_ADERR         ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_B0ERR         ( ( uint16 )0x2000U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_B1ERR         ( ( uint16 )0x1000U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_CERR          ( ( uint16 )0x0800U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_AERR          ( ( uint16 )0x0400U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_FERR          ( ( uint16 )0x0200U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_SERR          ( ( uint16 )0x0100U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_ALF           ( ( uint16 )0x0080U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_BLF           ( ( uint16 )0x0040U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_OVLF          ( ( uint16 )0x0020U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_BORF          ( ( uint16 )0x0010U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_BOEF          ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_EPF           ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_EWF           ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_C0ERFLL_BEF           ( ( uint16 )0x0001U )

/* See chapter F24(18.3.5) / F25(19.3.5) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_C0DCFGH_DSJW          ( ( uint16 )0x0F00U )
#define CAN_70_RL78F2X_MASK_C0DCFGH_DTSEG2        ( ( uint16 )0x000FU )
#define CAN_70_RL78F2X_MASK_C0DCFGL_DTSEG1        ( ( uint16 )0x1F00U )
#define CAN_70_RL78F2X_MASK_C0DCFGL_DBRP          ( ( uint16 )0x00FFU )

/* See chapter F24(18.3.6) / F25(19.3.6) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_C0FDCFGH_CLOE         ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_C0FDCFGH_REFE         ( ( uint16 )0x2000U )
#define CAN_70_RL78F2X_MASK_C0FDCFGH_FDOE         ( ( uint16 )0x1000U )
#define CAN_70_RL78F2X_MASK_C0FDCFGH_TDCO         ( ( uint16 )0x00FFU )
#define CAN_70_RL78F2X_MASK_C0FDCFGL_RPNMD        ( ( uint16 )0x3000U )
#define CAN_70_RL78F2X_MASK_C0FDCFGL_ESIC         ( ( uint16 )0x0400U )
#define CAN_70_RL78F2X_MASK_C0FDCFGL_TDCE         ( ( uint16 )0x0200U )
#define CAN_70_RL78F2X_MASK_C0FDCFGL_TDCOC        ( ( uint16 )0x0100U )
#define CAN_70_RL78F2X_MASK_C0FDCFGL_EOCCFG       ( ( uint16 )0x0007U )

/* See chapter F24(18.3.11) / F25(19.3.11) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GCFGH_ITRCP           ( ( uint16 )0xFFFFU )
#define CAN_70_RL78F2X_MASK_GCFGL_TSSS            ( ( uint16 )0x1000U )
#define CAN_70_RL78F2X_MASK_GCFGL_TSP             ( ( uint16 )0x0F00U )
#define CAN_70_RL78F2X_MASK_GCFGL_CMPOC           ( ( uint16 )0x0020U )
#define CAN_70_RL78F2X_MASK_GCFGL_DCS             ( ( uint16 )0x0010U )
#define CAN_70_RL78F2X_MASK_GCFGL_MME             ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_GCFGL_DRE             ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_GCFGL_DCE             ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_GCFGL_TPRI            ( ( uint16 )0x0001U )

/* See chapter F24(18.3.12) / F25(19.3.12) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GCTRH_TSRST           ( ( uint16 )0x0001U )
#define CAN_70_RL78F2X_MASK_GCTRL_CMPOFIE         ( ( uint16 )0x0800U )
#define CAN_70_RL78F2X_MASK_GCTRL_THLEIE          ( ( uint16 )0x0400U )
#define CAN_70_RL78F2X_MASK_GCTRL_MEIE            ( ( uint16 )0x0200U )
#define CAN_70_RL78F2X_MASK_GCTRL_DEIE            ( ( uint16 )0x0100U )
#define CAN_70_RL78F2X_MASK_GCTRL_GSLPR           ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_GCTRL_GMDC            ( ( uint16 )0x0003U )

/* See chapter F24(18.3.13) / F25(19.3.13) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GSTS_GRAMINIT         ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_GSTS_GSLPSTS          ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_GSTS_GHLTSTS          ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_GSTS_GRSTSTS          ( ( uint16 )0x0001U )

/* See chapter F24(18.3.14) / F25(19.3.14) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GERFLH_EEF            ( ( uint16 )0x0001U )
#define CAN_70_RL78F2X_MASK_GERFLL_MES            ( ( uint16 )0x0002U )

/* See chapter F24(18.3.16) / F25(19.3.16) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GTSC_TS               ( ( uint16 )0xFFFFU )

/* See chapter F24(18.3.17) / F25(19.3.17) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GAFLECTR_AFLDAE       ( ( uint16 )0x0100U )

/* See chapter F24(18.3.18) / F25(19.3.18) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GAFLCFG_RNC           ( ( uint16 )0x001FU )

/* See chapter F24(18.3.19) / F25(19.3.19) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GAFLIDH_GAFLIDE       ( ( uint16 )0x8000U )
#define CAN_70_RL78F2X_MASK_GAFLIDH_GAFLRTR       ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_GAFLIDH_GAFLLB        ( ( uint16 )0x2000U )
#define CAN_70_RL78F2X_MASK_GAFLIDH_GAFLID        ( ( uint16 )0x1FFFU )
#define CAN_70_RL78F2X_MASK_GAFLIDL_GAFLID        ( ( uint16 )0xFFFFU )

/* See chapter F24(18.3.20) / F25(19.3.20) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GAFLMH_GAFLIDEM       ( ( uint16 )0x8000U )
#define CAN_70_RL78F2X_MASK_GAFLMH_GAFLRTRM       ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_GAFLMH_GAFLIFL1       ( ( uint16 )0x2000U )
#define CAN_70_RL78F2X_MASK_GAFLMH_GAFLIDM_H      ( ( uint16 )0x1FFFU )
#define CAN_70_RL78F2X_MASK_GAFLML_GAFLIDM_L      ( ( uint16 )0xFFFFU )

/* See chapter F24(18.3.21) / F25(19.3.21) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GAFLP0H_GAFLPTR       ( ( uint16 )0xFFFFU )
#define CAN_70_RL78F2X_MASK_GAFLP0L_GAFLRMV       ( ( uint16 )0x8000U )
#define CAN_70_RL78F2X_MASK_GAFLP0L_GAFLRMDP      ( ( uint16 )0x1F00U )
#define CAN_70_RL78F2X_MASK_GAFLP0L_GAFLIFL0      ( ( uint16 )0x0080U )
#define CAN_70_RL78F2X_MASK_GAFLP0L_GAFLDLC       ( ( uint16 )0x000FU )

/* See chapter F24(18.3.22) / F25(19.3.22) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GAFLP1L_GAFLFDP_1     ( ( uint16 )0x0100U )
#define CAN_70_RL78F2X_MASK_GAFLP1L_GAFLFDP_2     ( ( uint16 )0x0003U )

/* See chapter F24(18.3.25) / F25(19.3.25) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_RFCC_RFIM             ( ( uint16 )0x1000U )
#define CAN_70_RL78F2X_MASK_RFCC_RFDC             ( ( uint16 )0x0700U )
#define CAN_70_RL78F2X_MASK_RFCC_RFPLS            ( ( uint16 )0x0070U )
#define CAN_70_RL78F2X_MASK_RFCC_RFIE             ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_RFCC_RFE              ( ( uint16 )0x0001U )

/* See chapter F24(18.3.26) / F25(19.3.26) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_RFSTS_RFMC            ( ( uint16 )0x3F00U )
#define CAN_70_RL78F2X_MASK_RFSTS_RFIF            ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_RFSTS_RFMLT           ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_RFSTS_RFFLL           ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_RFSTS_RFEMP           ( ( uint16 )0x0001U )

/* See chapter F24(18.3.27) / F25(19.3.27) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_RFPCTR_RFPC           ( ( uint16 )0x00FFU )

/* See chapter F24(18.3.34) / F25(19.3.34) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_RFISTS_RF1IF          ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_RFISTS_RF0IF          ( ( uint16 )0x0001U )

/* See chapter F24(18.3.35) / F25(19.3.35) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_TMC_TMOM              ( ( uint8  )0x04U )
#define CAN_70_RL78F2X_MASK_TMC_TMTAR             ( ( uint8  )0x02U )
#define CAN_70_RL78F2X_MASK_TMC_TMTR              ( ( uint8  )0x01U )

/* See chapter F24(18.3.36) / F25(19.3.36) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_TMSTS_TMTARM          ( ( uint8  )0x10U )
#define CAN_70_RL78F2X_MASK_TMSTS_TMTRM           ( ( uint8  )0x08U )
#define CAN_70_RL78F2X_MASK_TMSTS_TMTRF           ( ( uint8  )0x06U )
#define CAN_70_RL78F2X_MASK_TMSTS_TMTSTS          ( ( uint8  )0x01U )

/* See chapter F24(18.3.41) / F25(19.3.41) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_TMIEC_TMIE3           ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_TMIEC_TMIE2           ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_TMIEC_TMIE1           ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_TMIEC_TMIE0           ( ( uint16 )0x0001U )

/* See chapter F24(18.3.42) / F25(19.3.42) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_THLCC_THLDTE          ( ( uint16 )0x0400U )
#define CAN_70_RL78F2X_MASK_THLCC_THLIM           ( ( uint16 )0x0200U )
#define CAN_70_RL78F2X_MASK_THLCC_THLIE           ( ( uint16 )0x0100U )
#define CAN_70_RL78F2X_MASK_THLCC_THLE            ( ( uint16 )0x0001U )

/* See chapter F24(18.3.43) / F25(19.3.43) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_THLSTS_THLMC          ( ( uint16 )0x0F00U )
#define CAN_70_RL78F2X_MASK_THLSTS_THLIF          ( ( uint16 )0x0008U )
#define CAN_70_RL78F2X_MASK_THLSTS_THLELT         ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_THLSTS_THLFLL         ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_THLSTS_THLEMP         ( ( uint16 )0x0001U )

/* See chapter F24(18.3.44) / F25(19.3.44) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_THLACC0H_TMTS         ( ( uint16 )0xFFFFU )
#define CAN_70_RL78F2X_MASK_THLACC0L_BN           ( ( uint16 )0x0018U )
#define CAN_70_RL78F2X_MASK_THLACC0L_BT           ( ( uint16 )0x0003U )

/* See chapter F24(18.3.46) / F25(19.3.46) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_THLPCTR_THLPC         ( ( uint16 )0x00FFU )

/* See chapter F24(18.3.50) / F25(19.3.50) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_GFDCFG_TSCCFG         ( ( uint16 )0x0300U )
#define CAN_70_RL78F2X_MASK_GFDCFG_RPED           ( ( uint16 )0x0001U )

/* See chapter F24(18.3.67) / F25(19.3.67) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_CFDGRWC_KEY           ( ( uint16 )0xFF00U )
#define CAN_70_RL78F2X_MASK_CFDGRWC_RPAGE         ( ( uint16 )0x0003U )

/* See chapter F24(18.5.5) / F25(19.5.5) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_RFIDH_RFIDE           ( ( uint16 )0x8000U )
#define CAN_70_RL78F2X_MASK_RFIDH_RFRTR           ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_RFIDH_RFID            ( ( uint16 )0x1FFFU )
#define CAN_70_RL78F2X_MASK_RFIDL_RFID            ( ( uint16 )0xFFFFU )

/* See chapter F24(18.5.7) / F25(19.5.7) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_RFFDSTSH_RFPTR        ( ( uint16 )0xFFFFU )
#define CAN_70_RL78F2X_MASK_RFFDSTSL_RFIFL        ( ( uint16 )0x0300U )
#define CAN_70_RL78F2X_MASK_RFFDSTSL_RFFDF        ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_RFFDSTSL_RFBRS        ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_RFFDSTSL_RFESI        ( ( uint16 )0x0001U )

/* See chapter F24(18.5.13) / F25(19.5.13) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_TMIDH_TMIDE           ( ( uint16 )0x8000U )
#define CAN_70_RL78F2X_MASK_TMIDH_TMRTR           ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_TMIDH_THLEN           ( ( uint16 )0x2000U )
#define CAN_70_RL78F2X_MASK_TMIDH_TMID_H          ( ( uint16 )0x1FFFU )
#define CAN_70_RL78F2X_MASK_TMIDL_TMID_L          ( ( uint16 )0xFFFFU )

/* See chapter F24(18.5.14) / F25(19.5.14) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_TMPTRH_TMDLC          ( ( uint16 )0xF000U )
 
/* See chapter F24(18.5.15) / F25(19.5.15) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_TMFDCTRH_TMPTR        ( ( uint16 )0xFFFFU )
#define CAN_70_RL78F2X_MASK_TMFDCTRL_TMIFL        ( ( uint16 )0x0300U )
#define CAN_70_RL78F2X_MASK_TMFDCTRL_TMFDF        ( ( uint16 )0x0004U )
#define CAN_70_RL78F2X_MASK_TMFDCTRL_TMBRS        ( ( uint16 )0x0002U )
#define CAN_70_RL78F2X_MASK_TMFDCTRL_TMESI        ( ( uint16 )0x0001U )

/* See chapter F24(18.5.16) / F25(19.5.16) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_TMDF_TMDB             ( ( uint16 )0xFFFFU )

/* See chapter F24(28.3.4) / F25(29.3.4) of the hardware manual. */
#define CAN_70_RL78F2X_MASK_CFDECCTL_EMCA_W_EN    ( ( uint16 )0x4000U )
#define CAN_70_RL78F2X_MASK_CFDECCTL_ECERVF       ( ( uint16 )0x0040U )
#define CAN_70_RL78F2X_MASK_CFDECCTL_EC2EDIC      ( ( uint16 )0x0010U )

/* -------------------------------------------------------------------------- */

/* C0CTRL register bit value. */
#define CAN_70_RL78F2X_BIT_C0CTRL_CHMDC_RESET     ( ( uint16 )0x0001U )

/* CFDGRWC register bit value. */
#define CAN_70_RL78F2X_BIT_CFDGRWC_KEY_VALUE      ( ( uint16 )0xC400U )
#define CAN_70_RL78F2X_BIT_CFDGRWC_RPAGE_0        ( ( uint16 )0x0000U )
#define CAN_70_RL78F2X_BIT_CFDGRWC_RPAGE_1        ( ( uint16 )0x0001U )

/* TMSTS_ register bit value. */
#define CAN_70_RL78F2X_BIT_TMSTS_TMTRF_NOREQ      ( ( uint8 )0x00U )
#define CAN_70_RL78F2X_BIT_TMSTS_TMTRF_ABORT      ( ( uint8 )0x02U )
#define CAN_70_RL78F2X_BIT_TMSTS_TMTRF_SENT       ( ( uint8 )0x04U )
#define CAN_70_RL78F2X_BIT_TMSTS_TMTRF_SENT_ABORT ( ( uint8 )0x06U )

/* GCFGL register bit value. */
#define CAN_70_RL78F2X_BIT_GCFGL_TSP              ( ( uint16 )0x0F00U ) /* 32768 */

/* GAFLP1L register bit value. */
#define CAN_70_RL78F2X_BIT_GAFLP1L_GAFLFDP_0      ( ( uint16 )0x0001U ) /* RX FIFO 0 */
#define CAN_70_RL78F2X_BIT_GAFLP1L_GAFLFDP_1      ( ( uint16 )0x0002U ) /* RX FIFO 1 */

/* CFDWINR register bit value. */
#define CAN_70_RL78F2X_BIT_CFDWINR_CSEL0_CAN0     ( ( uint8 )0x00U )    /* 0b: CAN0 selected */
#define CAN_70_RL78F2X_BIT_CFDWINR_CSEL0_CAN1     ( ( uint8 )0x01U )    /* 1b: CAN1 selected */

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/

typedef struct {
    volatile uint8     IF ;         /* FFFE0H, FFFE1H, FFFE2H, FFFE3H, FFFD0H, FFFD1H, FFFD2H, FFFD3H */
} Can_70_RL78F2X_RegIfxType;

typedef struct {
    volatile uint8     MK ;         /* FFFE4H, FFFE5H, FFFE6H, FFFE7H, FFFD4H, FFFD5H, FFFD6H, FFFD7H */
} Can_70_RL78F2X_RegMkxType;

typedef struct {
    volatile uint16    C0NCFGL;     /* F0300H */
    volatile uint16    C0NCFGH;     /* F0302H */
    volatile uint16    C0CTRL;      /* F0304H */
    volatile uint16    C0CTRH;      /* F0306H */
    volatile uint16    C0STSL;      /* F0308H */
    volatile uint16    C0STSH;      /* F030AH */
    volatile uint16    C0ERFLL;     /* F030CH */
    volatile uint16    C0ERFLH;     /* F030EH */
} Can_70_RL78F2X_RegCommonAType;

typedef struct {
    volatile uint16    GIPVL;       /* F0310H */
    volatile uint16    GIPVH;       /* F0312H */
    volatile uint16    GCFGL;       /* F0314H */
    volatile uint16    GCFGH;       /* F0316H */
    volatile uint16    GCTRL;       /* F0318H */
    volatile uint16    GCTRH;       /* F031AH */
    volatile uint16    GSTS;        /* F031CH */
    volatile uint8     dummy1[2];   /* F031EH */
    volatile uint16    GERFLL;      /* F0320H */
    volatile uint16    GERFLH;      /* F0322H */
    volatile uint16    GTSC;        /* F0324H */
    volatile uint8     dummy2[2];   /* F0326H */
    volatile uint16    GAFLECTR;    /* F0328H */
    volatile uint8     dummy3[4];   /* F032AH */
    volatile uint16    GAFLCFG;     /* F032EH */
    volatile uint16    RMNB;        /* F0330H */
    volatile uint8     dummy4[2];   /* F0332H */
    volatile uint16    RMND;        /* F0334H */
    volatile uint8     dummy5[2];   /* F0336H */
    volatile uint16    RMIEC;       /* F0338H */
} Can_70_RL78F2X_RegCommonBType;

typedef struct {
    volatile uint16    RFCC;        /* F033CH, F0340H */
    volatile uint8     dummy1[6];   /* F033EH, F0342H */
    volatile uint16    RFSTS;       /* F0344H, F0348H */
    volatile uint8     dummy2[6];   /* F0346H, F034AH */
    volatile uint16    RFPCTR;      /* F034CH, F0350H */
} Can_70_RL78F2X_RegCommonCType;

typedef struct {
    volatile uint16    FESTS;       /* F0360H */
    volatile uint8     dummy1[2];   /* F0362H */
    volatile uint16    FFSTS;       /* F0364H */
    volatile uint8     dummy2[2];   /* F0366H */
    volatile uint16    FMSTS;       /* F0368H */
    volatile uint8     dummy3[2];   /* F036AH */
    volatile uint16    RFISTS;      /* F036CH */
} Can_70_RL78F2X_RegCommonDType;

typedef struct {
    volatile uint8     TMC[4];      /* F0370H, F0371H, F0372H, F0373H */
    volatile uint8     TMSTS[4];    /* F0374H, F0375H, F0376H, F0377H */
} Can_70_RL78F2X_RegCommonEType;

typedef struct {
    volatile uint16    TMTRSTS;     /* F0378H, (F037AH) */
    volatile uint8     dummy1[2];   /* F037AH, (F037CH) */
    volatile uint16    TMTARSTS;    /* F037CH, (F037EH) */
    volatile uint8     dummy2[2];   /* F037EH, (F0380H) */
    volatile uint16    TMTCSTS;     /* F0380H, (F0382H) */
    volatile uint8     dummy3[2];   /* F0382H, (F0384H) */
    volatile uint16    TMTASTS;     /* F0384H, (F0386H) */
    volatile uint8     dummy4[2];   /* F0386H, (F0388H) */
    volatile uint16    TMIEC;       /* F0388H, (F038AH) */
} Can_70_RL78F2X_RegCommonFType;

typedef struct {
    volatile uint16    THLCC;       /* F0398H, (F039AH) */
    volatile uint8     dummy1[2];   /* F039AH, (F039CH) */
    volatile uint16    THLSTS;      /* F039CH, (F039EH) */
    volatile uint8     dummy2[2];   /* F039EH, (F03A0H) */
    volatile uint16    THLPCTR;     /* F03A0H, (F03A2H) */
    volatile uint8     dummy3[2];   /* F03A2H, (F03A4H) */
    volatile uint16    GTINTSTS;    /* F03A4H, (F03A6H) */
} Can_70_RL78F2X_RegCommonGType;

typedef struct {
    volatile uint16    GFDCFG;      /* F03B0H */
} Can_70_RL78F2X_RegCommonHType;

typedef struct {
    volatile uint16    GRSTC;       /* F03D8H */
    volatile uint8     dummy1[2];   /* F03DAH */
    volatile uint16    CFDGRWC;     /* F03DCH */
} Can_70_RL78F2X_RegCommonIType;

typedef struct {
    volatile uint16    C0DCFGL;     /* F0400H */
    volatile uint16    C0DCFGH;     /* F0402H */
    volatile uint16    C0FDCFGL;    /* F0404H */
    volatile uint16    C0FDCFGH;    /* F0406H */
    volatile uint16    C0FDCTRL;    /* F0408H */
    volatile uint16    C0FDCTRH;    /* F040AH */
    volatile uint16    C0FDSTSL;    /* F040CH */
    volatile uint16    C0FDSTSH;    /* F040EH */
    volatile uint16    C0FDCRCL;    /* F0410H */
    volatile uint16    C0FDCRCH;    /* F0412H */
} Can_70_RL78F2X_RegCommonJType;

typedef struct {
    volatile uint16    GAFLIDL;     /* F0420H, F0420H+(10H*i)[i=0-15], F0510H */
    volatile uint16    GAFLIDH;     /* F0422H, F0422H+(10H*i)[i=0-15], F0512H */
    volatile uint16    GAFLML;      /* F0424H, F0424H+(10H*i)[i=0-15], F0514H */
    volatile uint16    GAFLMH;      /* F0426H, F0426H+(10H*i)[i=0-15], F0516H */
    volatile uint16    GAFLP0L;     /* F0428H, F0428H+(10H*i)[i=0-15], F0518H */
    volatile uint16    GAFLP0H;     /* F042AH, F042AH+(10H*i)[i=0-15], F051AH */
    volatile uint16    GAFLP1L;     /* F042CH, F042CH+(10H*i)[i=0-15], F051CH */
} Can_70_RL78F2X_RegPage0AType;

typedef struct {
    volatile uint16    RFIDL;       /* F0420H, F046CH */
    volatile uint16    RFIDH;       /* F0422H, F046EH */
    volatile uint16    RFPTRL;      /* F0424H, F0470H */
    volatile uint16    RFPTRH;      /* F0426H, F0472H */
    volatile uint16    RFFDSTSL;    /* F0428H, F0474H */
    volatile uint16    RFFDSTSH;    /* F042AH, F0476H */
} Can_70_RL78F2X_RegPage1AType;

typedef struct {
    volatile uint8     RFDF[ CAN_70_RL78F2X_RXDATAFIELD_MAX ]; /* F042CH, F042CH+(4CH*k)+(4*p)[k=0-1,p=0-15], F04B8H */
} Can_70_RL78F2X_RegPage1BType;

typedef struct {
    volatile uint16    TMIDL;       /* F0504H, F0550H, F059CH, F05E8H */
    volatile uint16    TMIDH;       /* F0506H, F0552H, F059EH, F05EAH */
    volatile uint8     dummy1[2];   /* F0508H, F0554H, F05A0H, F05ECH */
    volatile uint16    TMPTRH;      /* F050AH, F0556H, F05A2H, F05EEH */
    volatile uint16    TMFDCTRL;    /* F050CH, F0558H, F05A4H, F05F0H */
    volatile uint16    TMFDCTRH;    /* F050EH, F055AH, F05A6H, F05F2H */
} Can_70_RL78F2X_RegPage1CType;

typedef struct {
    volatile uint8     TMDF[ CAN_70_RL78F2X_TXDATAFIELD_MAX ]; /* F0510H, F0510H+(4CH*m)+(4*p)[m=0-3,p=0-15], F067EH */
} Can_70_RL78F2X_RegPage1DType;

typedef struct {
    volatile uint16    THLACC0L;    /* F0640H */
    volatile uint16    THLACC0H;    /* F0642H */
    volatile uint16    THLACC1L;    /* F0644H */
    volatile uint16    THLACC1H;    /* F0646H */
} Can_70_RL78F2X_RegPage1EType;

typedef struct {
    volatile uint16    CFDECCTL;    /* F07C0H */
} Can_70_RL78F2X_RegCfdecctlType;

typedef struct {
    Can_70_RL78F2X_RegCommonAType*       RegCommonA;
    Can_70_RL78F2X_RegCommonEType*       RegCommonE;
    Can_70_RL78F2X_RegCommonFType*       RegCommonF;
    Can_70_RL78F2X_RegCommonGType*       RegCommonG;
    Can_70_RL78F2X_RegCommonJType*       RegCommonJ;
    Can_70_RL78F2X_RegPage1CType*        RegPage1C[ CAN_70_RL78F2X_TXBUFFER_MAX ];
    Can_70_RL78F2X_RegPage1DType*        RegPage1D[ CAN_70_RL78F2X_TXBUFFER_MAX ];
    Can_70_RL78F2X_RegPage1EType*        RegPage1E;
} Can_70_RL78F2X_CanChannelRegInfoType;

typedef struct {
    Can_70_RL78F2X_RegIfxType*           RegIfx[ CAN_70_RL78F2X_INTERRUPT_FLAG_MAX ];
    Can_70_RL78F2X_RegMkxType*           RegMkx[ CAN_70_RL78F2X_INTERRUPT_FLAG_MAX ];
    Can_70_RL78F2X_RegCommonBType*       RegCommonB;
    Can_70_RL78F2X_RegCommonCType*       RegCommonC[ CAN_70_RL78F2X_RXFIFO_MAX ];
    Can_70_RL78F2X_RegCommonDType*       RegCommonD;
    Can_70_RL78F2X_RegCommonHType*       RegCommonH;
    Can_70_RL78F2X_RegCommonIType*       RegCommonI;
    Can_70_RL78F2X_RegPage0AType*        RegPage0A[ CAN_70_RL78F2X_AFL_MAX ];
    Can_70_RL78F2X_RegPage1AType*        RegPage1A[ CAN_70_RL78F2X_RXFIFO_MAX ];
    Can_70_RL78F2X_RegPage1BType*        RegPage1B[ CAN_70_RL78F2X_RXFIFO_MAX ];
    Can_70_RL78F2X_RegCfdecctlType*      RegCfdecctl;
    Can_70_RL78F2X_CanChannelRegInfoType ChannelRegInfo[ CAN_70_RL78F2X_CHANNEL_MAX ];
} Can_70_RL78F2X_CanControllerRegInfoType;

/*----------------------------------------------------------------------------*/
/* external variables                                                         */
/*----------------------------------------------------------------------------*/
extern volatile const Can_70_RL78F2X_CanControllerRegInfoType Can_70_CanControllerRegInfo[ CAN_70_NUM_OF_CAN_CHANNEL ];
extern const Can_70_InterruptBitAssignType Can_70_InterruptBitAssign[ CAN_70_NUM_OF_CAN_CHANNEL ];

#endif  /* #ifndef CAN_70_RL78F2X_HWREG_H */
/* EOF Can_70_RL78F2X_HwReg.h *************************************************/
