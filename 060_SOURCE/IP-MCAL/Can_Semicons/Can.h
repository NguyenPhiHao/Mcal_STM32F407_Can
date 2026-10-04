/*------------------------------------------------------------------------------------------------|
| Project Name| AUTOSAR MCAL                                                                      |
| File Name   | Can.h                                                                             |
| Description:|                                                                                   |
|             | Microcontrollers: STM32F407                                                       |
|             | Compiler        : GCC IAR GHS TASKING                                             |
|             | Technical Ref   : AUTOSAR_SWS_CANDriver.pdf (4.4.0)                               |
|-------------------------------------------------------------------------------------------------|
| COPYRIGHT                                                                                       |
|-------------------------------------------------------------------------------------------------|
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|-------------------------------------------------------------------------------------------------|
| FILE DESCRIPTION                                                                                |
|-------------------------------------------------------------------------------------------------|
| File        | Can.h                                                                             |
| Module      | CAN                                                                               |
| Version     | 1.00.00                                                                           |
| Contents    | This module provides services for initiating transmissions and calls the callback |
|             | functions of the CanIf module for notifying events, independently from            |
|             | the hardware. Also it provides services to control the behavior and state         |
|             | of the CAN controllers that belong to the same CAN Hardware Unit.                 |
|-------------------------------------------------------------------------------------------------|
| AUTHOR IDENTITY                                                                                 |
|-------------------------------------------------------------------------------------------------|
| Author      | HaoNP                                                                             |
| Company     | H-Car Autosar Technology Inc.                                                     |
| Note        | --                                                                                |
|-------------------------------------------------------------------------------------------------|
| REVISION CONTROL HISTORY                                                                        |
|-------------------------------------------------------------------------------------------------|
| V1.00.00 | 01/01/2025 | HaoNP    | [CAN-ID-001] Initial Version.                                |
|                                  |                                                              |
|------------------------------------------------------------------------------------------------*/

#ifndef CAN_H
#define CAN_H
 
#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------------------------|
| INCLUDES                                                                                        |
|------------------------------------------------------------------------------------------------*/
#include "Can_Types.h"
 
/** @defgroup Public_MacroDefinition
 *  @{
 */
#define CAN_VENDOR_ID_H                   0x0000U
#define CAN_MODULE_ID_H                   0x0050U
#define CAN_SW_MAJOR_VERSION_H            0x01U
#define CAN_SW_MINOR_VERSION_H            0x00U
#define CAN_SW_PATCH_VERSION_H            0x00U
#define CAN_AR_RELEASE_MAJOR_VERSION_H    0x04U
#define CAN_AR_RELEASE_MINOR_VERSION_H    0x09U
#define CAN_AR_RELEASE_REVISION_VERSION_H 0x00U
 
/* Check if current file and Can_Types.h are of the same vendor */
#if (CAN_VENDOR_ID_H != CAN_TYPES_VENDOR_ID_H)
#error "Can.h and Can_Types.h have different vendor ids"
#endif
 
/* Check if current file and Can_Types.h are the same Module Id. */
#if (CAN_MODULE_ID_H != CAN_TYPES_MODULE_ID_H)
#error "Module ID Numbers of Can.h and Can_Types.h are different."
#endif
 
/* Check if current file and Can_Types.h are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_H != CAN_TYPES_SW_MAJOR_VERSION_H) || \
     (CAN_SW_MINOR_VERSION_H != CAN_TYPES_SW_MINOR_VERSION_H) || \
     (CAN_SW_PATCH_VERSION_H != CAN_TYPES_SW_PATCH_VERSION_H))
#error "Software Version Numbers of Can.h and Can_Types.h"
#endif
 
/* Check if current file and Can_Types.h are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_H    != CAN_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_H    != CAN_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_AR_RELEASE_REVISION_VERSION_H != CAN_TYPES_AR_RELEASE_REVISION_VERSION_H))
#error "AutoSar Version Numbers of Can.h and Can_Types.h"
#endif
 
#if (STD_ON == CAN_DEV_ERROR_DETECT)
/**
 * @brief Definition of development errors in module Can.
 */
#define CAN_E_PARAM_POINTER                  ((uint8)0x01U) /*!< API Service called with wrong parameter */
#define CAN_E_PARAM_HANDLE                   ((uint8)0x02U) /*!< API Service called with wrong parameter */
#define CAN_E_PARAM_DATA_LENGTH              ((uint8)0x03U) /*!< API Service called with wrong parameter */
#define CAN_E_PARAM_CONTROLLER               ((uint8)0x04U) /*!< API Service called with wrong parameter */
#define CAN_E_UNINIT                         ((uint8)0x05U) /*!< API Service used without initialization */
#define CAN_E_TRANSITION                     ((uint8)0x06U) /*!< Invalid transition for the current mode */
#define CAN_E_PARAM_BAUDRATE                 ((uint8)0x07U) /*!< Parameter Baudrate has an invalid value */
#define CAN_E_INIT_FAILED                    ((uint8)0x09U) /*!< Invalid configuration set selection     */
#define CAN_E_PARAM_LPDU                     ((uint8)0x0AU) /*!< API service called with invalid PDU ID  */
#endif /* (STD_ON == CAN_DEV_ERROR_DETECT) */
 
/**
 * @brief Definiton of runtime errors in module Can.
 */
#define CAN_E_DATALOST                       ((uint8)0x01U) /*!< Received CAN message is lost */
 
/**
 * @brief Definition service ID in module Can.
 */
#define CAN_INIT_ID                          ((uint8)0x00U)
#define CAN_SET_CONTROLLER_MODE_ID           ((uint8)0x03U)
#define CAN_DISABLE_CONTROLLER_INTERRUPTS_ID ((uint8)0x04U)
#define CAN_ENABLE_CONTROLLER_INTERRUPTS_ID  ((uint8)0x05U)
#define CAN_WRITE_ID                         ((uint8)0x06U)
#define CAN_GET_VERSION_INFO_ID              ((uint8)0x07U)
#define CAN_MAIN_FUNCTION_READ_ID            ((uint8)0x08U)
#define CAN_CHECK_WAKEUP_ID                  ((uint8)0x0BU)
#define CAN_SET_BAUDRATE_ID                  ((uint8)0x0FU)
#define CAN_DEINIT_ID                        ((uint8)0x10U)
#define CAN_GET_CONTROLLER_ERROR_STATE_ID    ((uint8)0x11U)
#define CAN_GET_CONTROLLER_MODE_ID           ((uint8)0x12U)
#define CAN_GET_CONTROLLER_RX_ERROR_COUNTER  ((uint8)0x30U)
#define CAN_GET_CONTROLLER_TX_ERROR_COUNTER  ((uint8)0x31U)
#define CAN_GET_CURRENT_TIME                 ((uint8)0x32U)
#define CAN_ENABLE_EGRESS_TIMESTAMP          ((uint8)0x33U)
#define CAN_GET_EGRESS_TIMESTAMP             ((uint8)0x34U)
#define CAN_GET_INGRESS_TIMESTAMP            ((uint8)0x35U)
#define CAN_LOOPBACKTEST_ID                  ((uint8)0x7FU)
 
/** @} end of Public_MacroDefinition */
 
/** @defgroup Public_TypeDefinition
 *  @{
 */
 
/** @} end of group Public_TypeDefinition */
 
/** @defgroup Global_VariableDeclaration
 *  @{
 */
CAN_CONFIG_EXT
/** @} end of group Global_VariableDeclaration */
 
/** @defgroup Public_FunctionDeclaration
 *  @{
 */
#define CAN_START_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
/**
 * @brief        This function initializes the module.
 *
 * @details      Initializes the CAN module with the provided configuration parameters. This function sets up initial settings for the CAN controller,
 *               allocates necessary resources, and prepares the module for operation.
 *
 * @param[in]    Config: Pointer to driver configuration.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_001, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100, SDD_CAN_101, SDD_CAN_102
 */
FUNC(void, CAN_CODE_SLOW) Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Config);
 
/**
 * @brief        This function returns the version information of this module.
 *
 * @details      Returns the version information of the CAN module. Typically includes software version, vendor ID, and other relevant details about the
 *               implementation.
 *
 * @param[in]    versioninfo: Pointer to where to store the version information of this module.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_002, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo);
 
/**
 * @brief        This function de-initializes the module.
 *
 * @details      De-initializes and releases the CAN module. This function resets the controller to its default state, frees allocated resources, and stops all
 *               CAN-related activities.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_003, SDD_CAN_025, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100, SDD_CAN_102
 */
FUNC(void, CAN_CODE_SLOW) Can_DeInit(void);
 
#if (STD_ON == CAN_SET_BAUDRATE_API)
/**
 * @brief        This service shall set the baud rate configuration of the CAN controller. Depending on necessary baud rate modifications the controller might
 *
 * @details      Sets or changes the baud rate configuration of the CAN controller. Allows dynamic adjustment of the CAN network communication speed.
 *
 * @param[in]    Controller: CAN controller, whose baud rate shall be set.
 * @param[in]    BaudRateConfigID: References a baud rate configuration by ID (see CanController BaudRateConfigID).
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Service request accepted, setting of (new) baud rate started.
 * @retval       E_NOT_OK: Service request not accepted.
 *
 * @Design       SDD_CAN_004, SDD_CAN_024, SDD_CAN_025, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetBaudrate(VAR(uint8, AUTOMATIC) Controller, VAR(uint16, AUTOMATIC) BaudRateConfigID);
#endif /* STD_ON == CAN_SET_BAUDRATE_API */
 
/**
 * @brief        This function performs software triggered state transitions of the CAN controller State machine.
 *
 * @details      Performs software-triggered state transitions of the CAN controller, such as switching between Start, Stop, or Sleep modes.
 *
 * @param[in]    Controller: CAN controller for which the status shall be changed.
 * @param[in]    Transition: Transition value to request new CAN controller state.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Request accepted.
 * @retval       E_NOT_OK: Request not accepted, a development error occurred.
 *
 * @Design       SDD_CAN_005, SDD_CAN_024, SDD_CAN_025, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100, SDD_CAN_102
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetControllerMode(VAR(uint8, AUTOMATIC) Controller, VAR(Can_ControllerStateType, AUTOMATIC) Transition);
 
/**
 * @brief        This function disables all interrupts for this CAN controller.
 *
 * @details      Disables all interrupts for the specified CAN controller. Used to protect critical operations from being interrupted.
 *
 * @param[in]    Controller: CAN controller for which interrupts shall be disabled.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_006, SDD_CAN_024, SDD_CAN_026, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_DisableControllerInterrupts(VAR(uint8, AUTOMATIC) Controller);
 
/**
 * @brief        This function enables all allowed interrupts.
 *
 * @details      Enables all allowed interrupts for the specified CAN controller, allowing the controller to respond to real-time events.
 *
 * @param[in]    Controller: CAN controller for which interrupts shall be disabled.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_007, SDD_CAN_024, SDD_CAN_026, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_EnableControllerInterrupts(VAR(uint8, AUTOMATIC) Controller);
 
#if (STD_ON == CAN_WAKEUP_SUPPORT)
/**
 * @brief        This function checks if a wakeup has occurred for the given controller.
 *
 * @details      Checks if a wakeup event has occurred for the given CAN controller, typically to detect external triggers that bring the controller out of
 *               Sleep mode.
 *
 * @param[in]    Controller: CAN controller for which interrupts shall be disabled.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: API call has been accepted.
 * @retval       E_NOT_OK: API call has not been accepted.
 *
 * @Design       SDD_CAN_008, SDD_CAN_024, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckWakeup(VAR(uint8, AUTOMATIC) Controller);
#endif /* STD_ON == CAN_WAKEUP_SUPPORT */
 
/**
 * @brief        This service obtains the error state of the CAN controller.
 *
 * @details      Obtains the current error state of the CAN controller, including conditions like Bus-off, Error Passive, or Error Warning.
 *
 * @param[in]    ControllerId: Abstracted CanIf ControllerId which is assigned to a CAN controller, which is requested for ErrorState.
 * @param[out]   ErrorStatePtr: Pointer to a memory location, where the error state of the CAN controller will be stored.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Error state request has been accepted.
 * @retval       E_NOT_OK:  Error state request has not been accepted.
 *
 * @Design       SDD_CAN_009, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerErrorState(VAR(uint8, AUTOMATIC) ControllerId,
                                                                P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) ErrorStatePtr);
 
/**
 * @brief        This service reports about the current status of the requested CAN controller.
 *
 * @details      Reports the current operating mode of the requested CAN controller, such as Active, Stopped, or Sleeping.
 *
 * @param[in]    Controller: CAN controller for which interrupts shall be disabled.
 * @param[out]   ControllerModePtr: Pointer to a memory location, where the current mode of the CAN controller will be stored.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Description.
 * @retval       E_NOT_OK: Description.
 *
 * @Design       SDD_CAN_010, SDD_CAN_024, SDD_CAN_025, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerMode(VAR(uint8, AUTOMATIC) Controller,
                                                          P2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_DATA) ControllerModePtr);
 
/**
 * @brief        Returns the Rx error counter for a CAN controller. This value might not be available for all CAN controllers, in which case E_NOT_OK would
 *               be returned.
 *
 * @details      Returns the value of the receive (Rx) error counter for the CAN controller. Useful for diagnosing problems with data reception. Please note
 *               that the value of the counter might not be correct at the moment the API returns it, because the Rx counter is handled asynchronously in
 *               hardware. Applications should not trust this value for any assumption about the current bus state.
 *
 * @param[in]    ControllerId: CAN controller, whose current Rx error counter shall be acquired.
 * @param[out]   RxErrorCounterPtr: Pointer to a memory location, where the current Rx error counter of the CAN controller will be stored.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Rx error counter available.
 * @retval       E_NOT_OK: Wrong ControllerId, or Rx error counter not available.
 *
 * @Design       SDD_CAN_011, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerRxErrorCounter(VAR(uint8, AUTOMATIC) ControllerId,
                                                                    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) RxErrorCounterPtr);
 
/**
 * @brief        Returns the Tx error counter for a CAN controller. This value might not be available for all CAN controllers, in which case E_NOT_OK would
 *               be returned.
 *
 * @details      Returns the value of the transmit (Tx) error counter for the CAN controller. Helps monitor and analyze transmission issues. Please note
 *               that the value of the counter might not be correct at the moment the API returns it, because the Tx counter is handled asynchronously in
 *               hardware. Applications should not trust this value for any assumption about the current bus state.
 *
 * @param[in]    ControllerId: CAN controller, whose current Rx error counter shall be acquired.
 * @param[out]   TxErrorCounterPtr: Pointer to a memory location, where the current Tx error counter of the CAN controller will be stored.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Tx error counter available.
 * @retval       E_NOT_OK: Wrong ControllerId, or Tx error counter not available.
 *
 * @Design       SDD_CAN_012, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerTxErrorCounter(VAR(uint8, AUTOMATIC) ControllerId,
                                                                    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) TxErrorCounterPtr);
 
#if (STD_ON == CAN_GLOBAL_TIME_SUPPORT)
/**
 * @brief        Returns a time value out of the HW registers according to the capability of the HW.
 *
 * @details      Retrieves a time value from the hardware registers, often used for timestamping functions within CAN communication. Can_GetCurrentTime may
 *               be called within an exclusive area.
 *
 * @param[in]    ControllerId: Index of the addresses CAN controller.
 * @param[out]   timeStampPtr: Current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Successful.
 * @retval       E_NOT_OK: Failed.
 *
 * @Design       SDD_CAN_013, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetCurrentTime(VAR(uint8, AUTOMATIC) ControllerId, P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) timeStampPtr);
 
/**
 * @brief        Activates egress time stamping on a dedicated HTH.
 *
 * @details      Activates egress (transmit) timestamping on a dedicated HTH. Some HW does store once the egress time stamp marker and some HW needs it always
 *               before transmission. There will be no ""disable"" functionality, due to the fact, that the message type is always ""time stamped"" by network
 *               design.
 *
 * @param[in]    Hth: information which HW-transmit handle shall be used for enabling the time stamp.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_014, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_EnableEgressTimeStamp(VAR(Can_HwHandleType, AUTOMATIC) Hth);
 
/**
 * @brief        Reads back the egress time stamp on a dedicated message object. It needs to be called within the TxConfirmation() function.
 *
 * @details      Reads back the egress timestamp from a dedicated message object, providing the time that a specific message was transmitted.
 *
 * @param[in]    TxPduId: L-PDU handle of CAN L-PDU for which the time stamp shall be returned.
 * @param[in]    Hth: HW-transmit handle for which the egress timestamp shall be retrieved.
 * @param[out]   timeStampPtr: Current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Success.
 * @retval       E_NOT_OK: Failed to read time stamp.
 *
 * @Design       SDD_CAN_015, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetEgressTimeStamp(VAR(PduIdType, AUTOMATIC) TxPduId,
                                                           VAR(Can_HwHandleType, AUTOMATIC) Hth,
                                                           P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) timeStampPtr);
 
/**
 * @brief        Reads back the ingress time stamp on a dedicated message object. It needs to be called within the RxIndication() function.
 *
 * @details      Reads back the ingress (receive) timestamp from a dedicated message object, useful for analyzing message arrival times.
 *
 * @param[in]    Hrh: HW-receive handle for which the ingress timestamp shall be retrieved.
 * @param[out]   timeStampPtr: Current time stamp.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Success.
 * @retval       E_NOT_OK: Failed to read time stamp.
 *
 * @Design       SDD_CAN_016, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetIngressTimeStamp(VAR(Can_HwHandleType, AUTOMATIC) Hrh,
                                                            P2VAR(Can_TimeStampType, AUTOMATIC, CAN_APPL_DATA) timeStampPtr);
#endif /* STD_ON == CAN_GLOBAL_TIME_SUPPORT */
 
/**
 * @brief        This function is called by CanIf to pass a CAN message to CanDrv for transmission.
 *
 * @details      Called by CanIf to pass a CAN message to CanDrv for transmission. Ensures the message is sent through the correct controller and handled
 *               appropriately.
 *
 * @param[in]    Hth: information which HW-transmit handle shall be used for transmit. Implicitly this is also the information about the controller to use
 *                    because the Hth numbers are unique inside one hardware unit.
 * @param[in]    PduInfo: Pointer to SDU user memory, Data Length and Identifier.
 *
 * @return       Std_ReturnType.
 * @retval       E_OK: Write command has been accepted.
 * @retval       E_NOT_OK: development error occurred.
 * @retval       CAN_BUSY: No TX hardware buffer available or pre-emptive call of Can_Write that can't be implemented re-entrant (see Can_ReturnType)
 *
 * @Design       SDD_CAN_017, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_Write(VAR(Can_HwHandleType, AUTOMATIC) Hth, P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo);
 
/**
 * @brief        This function performs the polling of TX confirmation when CAN_TX_PROCESSING is set to POLLING.
 *
 * @details      Performs polling for TX (transmit) confirmation events when CAN_TX_PROCESSING is configured for polling mode. This function checks for
 *               completed transmissions and reports them to higher layers.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_018, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Write(void);
 
/**
 * @brief        This function performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
 *
 * @details      Performs polling for RX (receive) indication events when CAN_RX_PROCESSING is configured for polling. This function scans for received CAN
 *               messages and notifies higher layers.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_019, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Read(void);
 
/**
 * @brief        This function performs the polling of bus-off events that are configured statically as 'to be polled'.
 *
 * @details      Performs polling for bus-off events that are statically configured to be polled. This function monitors the CAN controller for bus-off status
 *               and handles recovery or notification as required.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_020, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_BusOff(void);
 
#if (STD_ON == CAN_WAKEUP_SUPPORT)
/**
 * @brief        This function performs the polling of wake-up events that are configured statically as 'to be polled'.
 *
 * @details      Performs polling for wake-up events that are statically configured to be polled. This function detects if the CAN controller has been woken up
 *               from sleep mode and reports the event.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_021
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Wakeup(void);
#endif /* STD_ON == CAN_WAKEUP_SUPPORT */
 
/**
 * @brief        This function performs the polling of CAN controller mode transitions.
 *
 * @details      Performs polling for CAN controller mode transitions. This function checks for changes in the controller's operating mode (such as Start,
 *               Stop, or Sleep) and notifies upper layers.
 *
 * @param[in]    None.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_022, SDD_CAN_024, SDD_CAN_025, SDD_CAN_027
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Mode(void);
 
/**
 * @brief        This function performs a CAN controller Loopback test to verify proper operation.
 *
 * @details      Perform the loopback testing function for diagnostic and validation purposes.
 *
 * @param[in]    p_CtrlId_u8: Controller Id.
 * @param[in]    p_PduInfo_ptr: Pointer to SDU user memory, Data Length and Identifier.
 * @param[in]    p_Mode_en: Loopback mode test type.
 * @param[in]    p_TimeoutMs_u32: Timeout value for Loopback test.
 *
 * @return       Can_LoopBackTestResultType.
 * @retval       CAN_LOOPBACK_PASS: Loopback test is pass.
 * @retval       CAN_LOOPBACK_TIMEOUT: Loopback test has timeout error.
 * @retval       CAN_LOOPBACK_DATA_MISMATCH: Loopback test has data mismatch error.
 *
 * @Design       SDD_CAN_023, SDD_CAN_024, SDD_CAN_027, SDD_CAN_099, SDD_CAN_100
 */
FUNC(Can_LoopBackTestResultType, CAN_CODE_SLOW) Can_LoopBackTest(CONST(uint8, AUTOMATIC) p_CtrlId_u8,
                                                                 P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) p_PduInfo_ptr,
                                                                 CONST(Can_LoopBackModeType, AUTOMATIC) p_Mode_en,
                                                                 CONST(uint32, AUTOMATIC) p_TimeoutMs_u32);
 
#define CAN_STOP_SEC_CODE_SLOW
#include "Can_MemMap.h"
 
#if ((STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || \
     (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"
 
#if (STD_ON == CAN_TX_INTERRUPT_PROCESSING)
/**
 * @brief        This function process the CAN controller transmit in interrupt.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_043, SDD_CAN_024
 */
FUNC(void, CAN_CODE_FAST) Can_TxIsrHandler(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* STD_ON == CAN_TX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_RX_INTERRUPT_PROCESSING)
/**
 * @brief        This function process the CAN controller receive in interrupt.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_043, SDD_CAN_024
 */
FUNC(void, CAN_CODE_FAST) Can_RxIsrHandler(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* STD_ON == CAN_RX_INTERRUPT_PROCESSING */
 
#if (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING)
/**
 * @brief        This function process the CAN controller busoff event in interrupt.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_043, SDD_CAN_024
 */
FUNC(void, CAN_CODE_FAST) Can_BusOffIsrHandler(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING */
 
#if ((STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION))
/**
 * @brief        This function process the CAN controller error in interrupt.
 *
 * @param[in]    p_CtrlOffset_u8: Controller offset value.
 *
 * @return       None.
 *
 * @Design       SDD_CAN_043, SDD_CAN_024
 */
FUNC(void, CAN_CODE_FAST) Can_ErrorIsrHandler(CONST(uint8, AUTOMATIC) p_CtrlOffset_u8);
#endif /* (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION) */
 
#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"
#endif /* ((STD_ON == CAN_TX_INTERRUPT_PROCESSING) || (STD_ON == CAN_RX_INTERRUPT_PROCESSING) || (STD_ON == CAN_BUSOFF_INTERRUPT_PROCESSING) || \
           (STD_ON == CAN_SECURITY_EVENT_REPORTING) || (STD_ON == CAN_ECC_DETECTION)) */
/** @} end of group Public_FunctionDeclaration */
 
#ifdef __cplusplus
}
#endif
 
/** @} end of group Can */
 
#endif /* CAN_H */
 