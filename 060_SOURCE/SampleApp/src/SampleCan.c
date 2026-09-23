/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                              */
/* File Name   : SampleCan.c
/* Version     : v1.00.02
/* Contents    : Can sample application.
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "SampleCan.h"
#include "Can.h"
#include "Dio.h"

/*----------------------------------------------------------------------------*/
/* type definitions                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  macros                                                                    */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/
bool_t LPDU_Callout_Func( uint8 Hrh, Can_IdType CanId, uint8 CanDataLength, const uint8* CanSduPtr );

/*----------------------------------------------------------------------------*/
/* const data declarations                                                    */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* external variables                                                         */
/*----------------------------------------------------------------------------*/
#if ( SAMPLE_CAN_ENABLE != FALSE )
uint8 SampleCan_Step = 0U;
Std_ReturnType SampleCan_ret;
Can_ControllerStateType SampleCan_ControllerState;
uint8 SampleCan_TxData[1][8] = {
    { 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, },
};
Can_PduType SampleCan_PduData[1] = {
    /* classic CAN Tx data */
    { 0U,                        /* VAR(PduIdType, CAN_VAR)               swPduHandle; */
      8U,                        /* VAR(uint8, CAN_VAR)                   length;      */
      0x58DU,                    /* VAR(Can_IdType, CAN_VAR)              id;          */
      &SampleCan_TxData[0][0],   /* P2VAR(uint8, CAN_VAR, CAN_APPL_DATA)  sdu;         */
    },
};
#endif  /* SAMPLE_CAN_ENABLE != FALSE */

/*------------------------------------------------------------------------------*/
/* functions and function style macros                                          */
/*------------------------------------------------------------------------------*/

#if ( SAMPLE_CAN_ENABLE != FALSE )
void SampleCan( void ) {
    /* Set the CAN transceiver to normal mode before CAN communication. */
    Dio_WriteChannel( DioConf_DioChannel_DioChannel_CAN_TRANSCEIVER_MODE, STD_LOW );

    while ( 1 ) {
        FUNC_NO_OPERATION;

        switch ( SampleCan_Step ) {
        case 0:
            /* Initialize the Can module and CAN controller. */
            Can_Init( &Can_Config );
            SampleCan_Step++;
            break;

        case 1:
            /* Monitor the CAN controller operating mode */
            /* CanIf_ControllerModeIndication() that notifies the transition */
            /* of the CAN controller operating mode is executed in CanIf.c. */
            Can_MainFunction_Mode();
            SampleCan_Step++;
            break;

        case 2:
            /* Transition the CAN controller operating mode to STARTED. */
            SampleCan_ret = Can_SetControllerMode(
                CanConf_CanController_CanController,
                CAN_CS_STARTED
            );
            SampleCan_Step++;
            break;

        case 3:
            /* Monitor the CAN controller operating mode */
            /* CanIf_ControllerModeIndication() that notifies the transition */
            /* of the CAN controller operating mode is executed in CanIf.c. */
            Can_MainFunction_Mode();
            SampleCan_Step++;
            break;
        case 4:
            /* Check the CAN controller operating mode with Can_GetControllerMode(). */
            SampleCan_ret = Can_GetControllerMode(
                CanConf_CanController_CanController,
                &SampleCan_ControllerState
            );
            if ( E_OK == SampleCan_ret
              && CAN_CS_STARTED == SampleCan_ControllerState ) {
                SampleCan_Step++;
            } else {
                /* Execute Can_MainFunction_Mode(). */
                SampleCan_Step = 2U;
            }
            break;

        case 5:
            /* Request the CAN controller to send a CAN frame. */
            SampleCan_ret = Can_Write(
                CanConf_CanHardwareObject_CanHardwareObject_TX,
                &SampleCan_PduData[0]
            );
            if ( E_OK == SampleCan_ret ) {
                SampleCan_Step++;
            } else {
                /* Execute Can_MainFunction_Write(). */
                SampleCan_Step = 2U;
            }
            break;

        case 6:
            /* Monitor the completion of the transmission. */
            /* CanIf_TxConfirmation() that notifies the completion */
            /* of the transmission is executed in CanIf.c. */
            Can_MainFunction_Write();
            SampleCan_Step++;
            break;

        default:
            /* Monitor the CAN frame reception. */
            /* CanIf_RxIndication() that notifies */
            /* the CAN frame reception is executed in CanIf.c. */
            Can_MainFunction_Read();
            break;
        }
    }
}
#endif  /* SAMPLE_CAN_ENABLE != FALSE */

bool_t LPDU_Callout_Func( uint8 Hrh, Can_IdType CanId, uint8 CanDataLength, const uint8* CanSduPtr )
{
    return TRUE;
}
