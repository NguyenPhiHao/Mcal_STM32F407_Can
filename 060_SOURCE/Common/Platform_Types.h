/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Platform_Types.h                                             */
/* Version     : v1.00.01                                                     */
/* Contents    : RL78/F2X Variable Data Types                                 */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of Platform Types                                            */
/* R22-11                                                                     */
/******************************************************************************/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/

/* [SWS_Platform_00058] */

/* [SWS_Platform_00045][SWS_Platform_00064][SWS_Platform_00057] */
#define CPU_TYPE_8        ( 8U )
#define CPU_TYPE_16       ( 16U )
#define CPU_TYPE_32       ( 32U )

/* [SWS_Platform_00044][SWS_Platform_00064] */
#define CPU_TYPE          CPU_TYPE_16

/* [SWS_Platform_00038][SWS_Platform_00057] */
#define MSB_FIRST         ( 0U )
#define LSB_FIRST         ( 1U )

/* [SWS_Platform_00039][SWS_Platform_00057] */
#define HIGH_BYTE_FIRST   ( 0U )
#define LOW_BYTE_FIRST    ( 1U )

/* [SWS_Platform_00043][SWS_Platform_00048][SWS_Platform_00049][SWS_Platform_00038] */
#define CPU_BIT_ORDER     LSB_FIRST

/* [SWS_Platform_00046][SWS_Platform_00050][SWS_Platform_00051][SWS_Platform_00039] */
#define CPU_BYTE_ORDER    LOW_BYTE_FIRST

/* [SWS_Platform_00056][SWS_Platform_00054][SWS_Platform_00055] */
#ifndef TRUE
#  define TRUE    (1U)
#endif
#ifndef FALSE
#  define FALSE   (0U)
#endif

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/
/* [SWS_Platform_00026] */
/* Add H.Kiryu */
typedef unsigned char    bool_t;

/* [SWS_Platform_00013] */
typedef unsigned char    uint8;

/* [SWS_Platform_00014] */
typedef unsigned short   uint16;

/* [SWS_Platform_00015] */
typedef unsigned long    uint32;

/* [SWS_Platform_00016] */
typedef signed char      sint8;

/* [SWS_Platform_00017] */
typedef signed short     sint16;

/* [SWS_Platform_00018] */
typedef signed long      sint32;

/* [SWS_Platform_00020] */
typedef unsigned short   uint8_least;

/* [SWS_Platform_00021] */
typedef unsigned short   uint16_least;

/* [SWS_Platform_00022] */
typedef unsigned long    uint32_least;

/* [SWS_Platform_00023] */
typedef signed short     sint8_least;

/* [SWS_Platform_00024] */
typedef signed short     sint16_least;

/* [SWS_Platform_00025] */
typedef signed long        sint32_least;

/* [SWS_Platform_00041] */
typedef float              float32;

/* [SWS_Platform_00042] */
typedef double             float64;

/* [SWS_Platform_00066] */
typedef unsigned long long uint64;

/* [SWS_Platform_00067] */
typedef signed long long   sint64;

#endif /* PLATFORM_TYPES_H */

/* Platform_Types.h ****************************************************/
