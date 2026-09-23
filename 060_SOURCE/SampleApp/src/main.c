/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : main.c                                                       */
/* Version     : v1.00.01                                                     */
/* Contents    : Main processing of samples.                                  */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Can.h"
#include "SampleMcu.h"
#include "SamplePort.h"
#include "SampleDio.h"
#include "SampleCan.h"


/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* const data declarations                                                    */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* external variables                                                         */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* static variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* functions and function style macros                                        */
/*----------------------------------------------------------------------------*/
void main( void ) {

#if ( SAMPLE_MCU_ENABLE != FALSE )
    SampleMcu();
#endif /* #if ( SAMPLE_MCU_ENABLE != FALSE ) */
    Mcu_PllStatusType   pllSts;

    /* Initialization of clock and cpu mode for RL78/F24 100pin sample board */
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuConf_McuClockSettingConfig_0 );

    do {
        /* check PLL is loked before call Mcu_DistibutePllClock() */
        pllSts = Mcu_GetPllStatus();
    } while( MCU_PLL_UNLOCKED == pllSts );
    Mcu_DistributePllClock();    /* activate the PLL clock */

    Mcu_SetMode( MCU_MODE_NORMAL );

#if ( SAMPLE_PORT_ENABLE != FALSE )
    SamplePort();
#endif /* #if ( SAMPLE_PORT_ENABLE != FALSE ) */

    Port_Init( &Port_Config );


#if ( SAMPLE_DIO_ENABLE != FALSE )
    SampleDio();
#endif /* #if ( SAMPLE_DIO_ENABLE != FALSE ) */

#if ( SAMPLE_CAN_ENABLE != FALSE )
    SampleCan();
#endif /* #if ( SAMPLE_CAN_ENABLE != FALSE ) */

    /* End of program */
    while ( TRUE ) {
        FUNC_NO_OPERATION;
    }
}