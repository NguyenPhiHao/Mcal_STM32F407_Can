/**************************************************************************************************************************************************************/
/**
 * @file      : Can_GeneralTypes.h
 *              - Platform: BAT32A@brief
 *              - Autosar Version: 4.9.0
 * @version   : 1.0.0
 * @author    : Cmsemicon
 * @note      : None
 *
 * @copyright : Copyright (c) 2025 Cmsemicon Co., Ltd. All rights reserved.
 **************************************************************************************************************************************************************/
#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H
 
/**
 * @addtogroup Can_GeneralTypes
 * @brief Autosar R23-11 Can_GeneralTypes header
 * @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "ComStack_Types.h"
#include "Std_Types.h"
 
/** @defgroup Public_MacroDefinition
 *  @{
 */
#define CAN_GENERALTYPES_VENDOR_ID_H                   0x0000U
#define CAN_GENERALTYPES_MODULE_ID_H                   0x0050U
#define CAN_GENERALTYPES_SW_MAJOR_VERSION_H            0x01U
#define CAN_GENERALTYPES_SW_MINOR_VERSION_H            0x00U
#define CAN_GENERALTYPES_SW_PATCH_VERSION_H            0x00U
#define CAN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION_H    0x04U
#define CAN_GENERALTYPES_AR_RELEASE_MINOR_VERSION_H    0x09U
#define CAN_GENERALTYPES_AR_RELEASE_REVISION_VERSION_H 0x00U
 
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Std_Types.h are the same AUTOSAR version */
#if ((CAN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION_H != STD_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_GENERALTYPES_AR_RELEASE_MINOR_VERSION_H != STD_TYPES_AR_RELEASE_MINOR_VERSION_H))
#error "AutoSar Version Numbers of of Can_GeneralTypes.h and Std_Types.h are different."
#endif
#endif
 
/**
 * @brief Overlayed return value of Std_ReturnType for CAN driver API Can_Write().
 *        Transmit request could not be processed because no transmit object was available
 */
#define CAN_BUSY (0x02U)
 
/** @} end of Public_MacroDefinition */
 
/** @defgroup Public_TypeDefinition
 *  @{
 */
 
/**
 * @brief Represents the Identifier of an L-PDU. The two most significant bits specify the frame type: 00 CAN message with Standard CAN ID 01 CAN FD frame
 *        with Standard CAN ID 10 CAN message with Extended CAN ID 11 CAN FD frame with Extended CAN ID.
 */
typedef uint32 Can_IdType;
 
/**
 * @brief Represents the hardware object handles of a CAN hardware unit.
 */
typedef uint8 Can_HwHandleType;
 
/**
 * @brief This type defines a data structure which clearly provides an Hardware Object Handle including its corresponding CAN Controller and therefore CanDrv
 *        as well as the specific CanId.
 */
typedef struct Can_HwType_t {
  VAR(Can_IdType, TYPEDEF) CanId;     /*!< Standard/Extended CAN ID of CAN L-PDU */
  VAR(Can_HwHandleType, TYPEDEF) Hoh; /*!< ID of the corresponding Hardware Object Range */
  VAR(uint8, TYPEDEF) ControllerId;   /*!< ControllerId provided by CanIf clearly identify the corresponding controller */
} Can_HwType;
 
/**
 * @brief Error states of a CAN controller.
 */
typedef enum Can_ErrorStateType_t {
  CAN_ERRORSTATE_ACTIVE  = 0x00U, /*!< The CAN controller takes fully part in communication. */
  CAN_ERRORSTATE_PASSIVE = 0x01U, /*!< The CAN controller takes part in communication, but does not send active error frames. */
  CAN_ERRORSTATE_BUSOFF  = 0x02U  /*!< The CAN controller does not take part in communication. */
} Can_ErrorStateType;
 
/**
 * @brief States that are used by the several ControllerMode functions.
 */
typedef enum Can_ControllerStateType_t {
  CAN_CS_UNINIT  = 0x00U, /*!< CAN controller state UNINIT. */
  CAN_CS_STARTED = 0x01U, /*!< CAN controller state STARTED. */
  CAN_CS_STOPPED = 0x02U, /*!< CAN controller state STOPPED. */
  CAN_CS_SLEEP   = 0x03U  /*!< CAN controller state SLEEP. */
} Can_ControllerStateType;
 
/**
 * @brief The enumeration represents a superset of CAN Error Types which typical CAN HW is able to report. That means not all CAN HW will be able to support the
 *        complete set.
 */
typedef enum Can_ErrorType_t {
  CAN_ERROR_BIT_MONITORING1       = 0x01U, /*!< A 0 was transmitted and a 1 was read back. */
  CAN_ERROR_BIT_MONITORING0       = 0x02U, /*!< A 1 was transmitted and a 0 was read back. */
  CAN_ERROR_BIT                   = 0x03U, /*!< The HW reports a CAN bit error but cannot report distinguish between bit monitoring1 and bit monitoring0. */
  CAN_ERROR_CHECK_ACK_FAILED      = 0x04U, /*!< Acknowledgement check failed. */
  CAN_ERROR_ACK_DELIMITER         = 0x05U, /*!< Acknowledgement delimiter check failed. */
  CAN_ERROR_ARBITRATION_LOST      = 0x06U, /*!< The sender lost in arbitration. */
  CAN_ERROR_OVERLOAD              = 0x07U, /*!< CAN overload detected via an overloadframe. Indicates that the receive buffers of a receiver are full. */
  CAN_ERROR_CHECK_FORM_FAILED     = 0x08U, /*!< Violations of the fixed frame format. */
  CAN_ERROR_CHECK_STUFFING_FAILED = 0x09U, /*!< Stuffing bits not as expected. */
  CAN_ERROR_CHECK_CRC_FAILED      = 0x0AU, /*!< CRC failed. */
  CAN_ERROR_BUS_LOCK              = 0x0BU  /*!< Bus lock (Bus is stuck to dominant level). */
} Can_ErrorType;
 
/**
 * @brief Variables of this type are used to express time stamps based on relative time.
 *        Value range: * Seconds: 0 .. 4.294.967.295s (circa 136 years)
 *                     * Nanoseconds: 0 .. 999.999.999n
 */
typedef struct Can_TimeStampType_t {
  VAR(uint32, TYPEDEF) nanoseconds; /*!< Nanoseconds part of the time. */
  VAR(uint32, TYPEDEF) seconds;     /*!< Seconds part of the time. */
} Can_TimeStampType;
 
/**
 * @brief This type unites PduId (swPduHandle), SduLength (length), SduData (sdu), and CanId (id) for any CAN L-SDU.
 */
typedef struct Can_PduType_t {
  VAR(PduIdType, TYPEDEF) swPduHandle;  /*!< CAN L-PDU = Data Link Layer Protocol Data Unit. */
  VAR(uint8, TYPEDEF) length;           /*!< The L-PDU Handle = defined and placed inside the CanIf module layer. */
  VAR(Can_IdType, TYPEDEF) id;          /*!< DLC = Data Length Code (part of L-PDU that describes the SDU length). */
  P2VAR(uint8, TYPEDEF, AUTOMATIC) sdu; /*!< CAN L-SDU = Link Layer Service Data Unit. Data that is transported inside the L-PDU. */
} Can_PduType;
 
/** @} end of group Public_TypeDefinition */
 
/** @defgroup Global_VariableDeclaration
 *  @{
 */
 
/** @} end of group Global_VariableDeclaration */
 
/** @defgroup Public_FunctionDeclaration
 *  @{
 */
 
/** @} end of group Public_FunctionDeclaration */
 
#ifdef __cplusplus
}
#endif
 
/** @} end of group Can_GeneralTypes */
 
#endif /* CAN_GENERALTYPES_H */
 