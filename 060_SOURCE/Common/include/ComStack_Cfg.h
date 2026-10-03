/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : ComStack_Cfg.h                                               */
/* Version     : v1.00.00                                                     */
/* Contents    : This file is ComStack’s type configuration header.           */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of Communication Stack Types                                 */
/* R22-11                                                                     */
/******************************************************************************/
#ifndef COMSTACK_CFG_H
#define COMSTACK_CFG_H

/*----------------------------------------------------------------------------*/
/* 8 API specification                                                       */
/*----------------------------------------------------------------------------*/
/* [SWS_COMTYPE_00005] */
typedef uint16   PduIdType;       /* 8.1.1 : PDU ID / 0 ... <PduIdMax> */
/* [SWS_COMTYPE_00008] */
typedef uint32   PduLengthType;   /* 8.1.2 : PDU Length / 0 ... <PduLengthMax> */

#endif /* COMSTACK_CFG_H */

/* End of ComStack_Cfg.h */
