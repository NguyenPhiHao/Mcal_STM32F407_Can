/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Sample.h                                                     */
/* Version     : v1.00.01                                                     */
/* Contents    : Sample application header file.                              */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/

#ifndef SAMPLE_H_
#define SAMPLE_H_
/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Std_Types.h"
#if (COMPILER == COMPILER_CC)
#elif (COMPILER == COMPILER_IAR)
    #include "intrinsics.h"
#endif        

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SAMPLE_ADC_ENABLE    ( FALSE )
#define SAMPLE_CAN_ENABLE    ( FALSE )
#define SAMPLE_CRYPTO_ENABLE ( FALSE )
#define SAMPLE_DIO_ENABLE    ( FALSE )
#define SAMPLE_FLS_ENABLE    ( FALSE )
#define SAMPLE_GPT_ENABLE    ( FALSE )
#define SAMPLE_ICU_ENABLE    ( FALSE )
#define SAMPLE_LIN_ENABLE    ( TRUE )
#define SAMPLE_MCU_ENABLE    ( FALSE )
#define SAMPLE_PORT_ENABLE   ( FALSE )
#define SAMPLE_PWM_ENABLE    ( FALSE )
#define SAMPLE_SPI_ENABLE    ( FALSE )
#define SAMPLE_WDG_ENABLE    ( FALSE )

#if (COMPILER == COMPILER_CC)
#define FUNC_NO_OPERATION __nop()
#elif (COMPILER == COMPILER_IAR)
#define FUNC_NO_OPERATION __no_operation()
#endif

#if ( COMPILER == COMPILER_CC )
#define FUNC_ENABLE_INTERRUPT __EI()
#elif ( COMPILER == COMPILER_IAR )
#define FUNC_ENABLE_INTERRUPT __enable_interrupt()
#endif
/*----------------------------------------------------------------------------*/
/* const data declarations                                                    */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//* external variables                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* static variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/

#endif
