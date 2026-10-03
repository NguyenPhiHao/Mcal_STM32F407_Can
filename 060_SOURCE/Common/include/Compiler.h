/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Compiler.h                                                   */
/* Version     : v1.00.00                                                     */
/* Contents    : Macros for the abstraction of compiler specific keywords.    */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/

#ifndef COMPILER_H
#define COMPILER_H
/* Compiler definition */
#define COMPILER_CC  (1)
#define COMPILER_IAR (2)

#if defined (__CCRL__)
    #define COMPILER COMPILER_CC
#elif defined (__IAR_SYSTEMS_ICC__)
    #define COMPILER COMPILER_IAR
#else
    /* Unknown compiler error */
    #error  "Non-supported compiler."
#endif
/* Definitions */
#define     AUTOMATIC
#define     TYPEDEF
#define     NULL_PTR        ((void *)0)

#define     _INTERRUPT_

/* CC-RL */
#define     INLINE          __inline
#define     LOCAL_INLINE    static __inline
/* CC-RL */

/* Macros for functions */
#define     FUNC(rettype, memclass ) rettype
#define     FUNC_P2CONST(rettype, ptrclass, memclass) const rettype *
#define     FUNC_P2VAR(rettype, ptrclass, memclass) rettype *

/* Macros for pointers */
#define     P2VAR(ptrtype, memclass, ptrclass) ptrtype *
#define     P2CONST(ptrtype, memclass, ptrclass) const ptrtype *
#define     CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const
#define     CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

#define     P2FUNC(rettype, ptrclass, fctname) rettype (* fctname)
#define     CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)

/* Keywords for constants */
#define     CONST(consttype, memclass) const consttype

/* Keywords for variables */
#define     VAR(vartype, memclass) vartype

#endif
