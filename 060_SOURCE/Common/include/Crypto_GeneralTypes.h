/******************************************************************************/
/* Copyright   :                                                              */
/* System Name : AUTOSAR MCAL                                                 */
/* File Name   : Crypto_GeneralTypes.h                                        */
/* Version     : v1.00.01                                                     */
/* Contents    : Crypto Module                                                */
/*              This file is Crypto stack's Type header.                      */
/* Author      : --                                                           */
/* Note        : --                                                           */
/* History     : --                                                           */
/******************************************************************************/
/* Specification of Crypto Driver                                             */
/* R22-11                                                                     */
/******************************************************************************/

#ifndef CRYPTO_GENERALTYPES_H
#define CRYPTO_GENERALTYPES_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "Csm_AR.h"
#include "Rte_Csm_Type.h"
#include "QINeS_Lite.h"

/*----------------------------------------------------------------------------*/
/* Crypt type definitions ( Service Interface )                               */
/*----------------------------------------------------------------------------*/
/* These defines and types are used by whole CryptoStack */

#define CSM_70_CONST const

/* Extension to Std_ReturnType */
/* [SWS_Crypto_91018] */
#define CRYPTO_E_BUSY                        ( ( Std_ReturnType )0x02U )              /* The service request failed because the service is still busy */
#define CRYPTO_E_ENTROPY_EXHAUSTED           ( ( Std_ReturnType )0x04U )              /* The service request failed because the entropy of the random number generator is exhausted */
#define CRYPTO_E_KEY_READ_FAIL               ( ( Std_ReturnType )0x06U )              /* The service request failed because read access was denied */
#define CRYPTO_E_KEY_WRITE_FAIL              ( ( Std_ReturnType )0x07U )              /* The service request failed because the writing access failed */
#define CRYPTO_E_KEY_NOT_AVAILABLE           ( ( Std_ReturnType )0x08U )              /* The service request failed because at least one required key element is not available */
#define CRYPTO_E_KEY_NOT_VALID               ( ( Std_ReturnType )0x09U )              /* The service request failed because the key is invalid */
#define CRYPTO_E_KEY_SIZE_MISMATCH           ( ( Std_ReturnType )0x0AU )              /* The service request failed because the key size does not match. */
#define CRYPTO_E_JOB_CANCELED                ( ( Std_ReturnType )0x0CU )              /* The service request failed because the Job has been canceled */
#define CRYPTO_E_KEY_EMPTY                   ( ( Std_ReturnType )0x0DU )              /* The service request failed because of uninitialized source key element. */
#define CRYPTO_E_CUSTOM_ERROR                ( ( Std_ReturnType )0x0EU )              /* Custom processing failed. */

/* [SWS_Csm_01047] */
typedef uint8 Crypto_AlgorithmFamilyType;
#define CRYPTO_ALGOFAM_NOT_SET               ( ( Crypto_AlgorithmFamilyType )0x00U )  /* Algorithm family is not set */
#define CRYPTO_ALGOFAM_SHA1                  ( ( Crypto_AlgorithmFamilyType )0x01U )  /* SHA1 hash */
#define CRYPTO_ALGOFAM_SHA2_224              ( ( Crypto_AlgorithmFamilyType )0x02U )  /* SHA2-224 hash */
#define CRYPTO_ALGOFAM_SHA2_256              ( ( Crypto_AlgorithmFamilyType )0x03U )  /* SHA2-256 hash */
#define CRYPTO_ALGOFAM_SHA2_384              ( ( Crypto_AlgorithmFamilyType )0x04U )  /* SHA2-384 hash */
#define CRYPTO_ALGOFAM_SHA2_512              ( ( Crypto_AlgorithmFamilyType )0x05U )  /* SHA2-512 hash */
#define CRYPTO_ALGOFAM_SHA2_512_224          ( ( Crypto_AlgorithmFamilyType )0x06U )  /* SHA2-512/224 hash */
#define CRYPTO_ALGOFAM_SHA2_512_256          ( ( Crypto_AlgorithmFamilyType )0x07U )  /* SHA2-512/256 hash */
#define CRYPTO_ALGOFAM_SHA3_224              ( ( Crypto_AlgorithmFamilyType )0x08U )  /* SHA3-224 hash */
#define CRYPTO_ALGOFAM_SHA3_256              ( ( Crypto_AlgorithmFamilyType )0x09U )  /* SHA3-256 hash */
#define CRYPTO_ALGOFAM_SHA3_384              ( ( Crypto_AlgorithmFamilyType )0x0AU )  /* SHA3-384 hash */
#define CRYPTO_ALGOFAM_SHA3_512              ( ( Crypto_AlgorithmFamilyType )0x0BU )  /* SHA3-512 hash */
#define CRYPTO_ALGOFAM_SHAKE128              ( ( Crypto_AlgorithmFamilyType )0x0CU )  /* SHAKE128 hash */
#define CRYPTO_ALGOFAM_SHAKE256              ( ( Crypto_AlgorithmFamilyType )0x0DU )  /* SHAKE256 hash */
#define CRYPTO_ALGOFAM_RIPEMD160             ( ( Crypto_AlgorithmFamilyType )0x0EU )  /* RIPEMD hash */
#define CRYPTO_ALGOFAM_BLAKE_1_256           ( ( Crypto_AlgorithmFamilyType )0x0FU )  /* BLAKE-1-256 hash */
#define CRYPTO_ALGOFAM_BLAKE_1_512           ( ( Crypto_AlgorithmFamilyType )0x10U )  /* BLAKE-1-512 hash */
#define CRYPTO_ALGOFAM_BLAKE_2s_256          ( ( Crypto_AlgorithmFamilyType )0x11U )  /* BLAKE-2s-256 hash */
#define CRYPTO_ALGOFAM_BLAKE_2s_512          ( ( Crypto_AlgorithmFamilyType )0x12U )  /* BLAKE-2s-512 hash */
#define CRYPTO_ALGOFAM_3DES                  ( ( Crypto_AlgorithmFamilyType )0x13U )  /* 3DES cipher */
#define CRYPTO_ALGOFAM_AES                   ( ( Crypto_AlgorithmFamilyType )0x14U )  /* AES cipher */
#define CRYPTO_ALGOFAM_CHACHA                ( ( Crypto_AlgorithmFamilyType )0x15U )  /* ChaCha cipher */
#define CRYPTO_ALGOFAM_RSA                   ( ( Crypto_AlgorithmFamilyType )0x16U )  /* RSA cipher */
#define CRYPTO_ALGOFAM_ED25519               ( ( Crypto_AlgorithmFamilyType )0x17U )  /* ED25518 elliptic curve */
#define CRYPTO_ALGOFAM_BRAINPOOL             ( ( Crypto_AlgorithmFamilyType )0x18U )  /* Brainpool elliptic curve */
#define CRYPTO_ALGOFAM_ECCNIST               ( ( Crypto_AlgorithmFamilyType )0x19U )  /* NIST ECC elliptic curves */
#define CRYPTO_ALGOFAM_RNG                   ( ( Crypto_AlgorithmFamilyType )0x1BU )  /* Random Number Generator */
#define CRYPTO_ALGOFAM_SIPHASH               ( ( Crypto_AlgorithmFamilyType )0x1CU )  /* SipHash */
#define CRYPTO_ALGOFAM_ECCANSI               ( ( Crypto_AlgorithmFamilyType )0x1EU )  /* Elliptic curve according to ANSI X9.62 */
#define CRYPTO_ALGOFAM_ECCSECG               ( ( Crypto_AlgorithmFamilyType )0x1FU )  /* Elliptic curve according to SEC6 */
#define CRYPTO_ALGOFAM_DRBG                  ( ( Crypto_AlgorithmFamilyType )0x20U )  /* Random number generator according to NIST SP800-90A */
#define CRYPTO_ALGOFAM_FIPS186               ( ( Crypto_AlgorithmFamilyType )0x21U )  /* Random number generator according to FIPS186 */
#define CRYPTO_ALGOFAM_PADDING_PKCS7         ( ( Crypto_AlgorithmFamilyType )0x22U )  /* Cipher padding according to PKCS.7 */
#define CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS  ( ( Crypto_AlgorithmFamilyType )0x23U )  /* Cipher padding mode. */
#define CRYPTO_ALGOFAM_PBKDF2                ( ( Crypto_AlgorithmFamilyType )0x24U )  /* Password-Based Key Derivation Function 2 */
#define CRYPTO_ALGOFAM_KDFX963               ( ( Crypto_AlgorithmFamilyType )0x25U )  /* ANSI X9.63 Public Key Cryptography */
#define CRYPTO_ALGOFAM_DH                    ( ( Crypto_AlgorithmFamilyType )0x26U )  /* Diffie-Hellman */
#define CRYPTO_ALGOFAM_SM2                   ( ( Crypto_AlgorithmFamilyType )0x27U )  /* SM2 elliptic curve algorithm */
#define CRYPTO_ALGOFAM_EEA3                  ( ( Crypto_AlgorithmFamilyType )0x28U )  /* Stream cipher based on [x01] */
#define CRYPTO_ALGOFAM_SM3                   ( ( Crypto_AlgorithmFamilyType )0x29U )  /* Chinese hash algorithm based on [x02] */
#define CRYPTO_ALGOFAM_EIA3                  ( ( Crypto_AlgorithmFamilyType )0x2AU )  /* Authentication algorithm [x01] */
#define CRYPTO_ALGOFAM_HKDF                  ( ( Crypto_AlgorithmFamilyType )0x2BU )  /* HMAC-based extract-and-expand key derivation function */
#define CRYPTO_ALGOFAM_ECDSA                 ( ( Crypto_AlgorithmFamilyType )0x2CU )  /* Elliptic-curve Digital Signatures */
#define CRYPTO_ALGOFAM_POLY1305              ( ( Crypto_AlgorithmFamilyType )0x2DU )  /* MAC calculation algorithm */
#define CRYPTO_ALGOFAM_X25519                ( ( Crypto_AlgorithmFamilyType )0x2EU )  /* Elliptic-curve X25519 for ECDH */
#define CRYPTO_ALGOFAM_ECDH                  ( ( Crypto_AlgorithmFamilyType )0x2FU )  /* Elliptic-curve Diffie Hellman */
#define CRYPTO_ALGOFAM_CUSTOM                ( ( Crypto_AlgorithmFamilyType )0xFFU )  /* Custom algorithm family */

/* [SWS_Csm_01048] */
typedef uint8 Crypto_AlgorithmModeType;
#define CRYPTO_ALGOMODE_NOT_SET              ( ( Crypto_AlgorithmModeType )0x00U )  /* Algorithm key is not set */
#define CRYPTO_ALGOMODE_ECB                  ( ( Crypto_AlgorithmModeType )0x01U )  /* Blockmode: Electronic Code Book */
#define CRYPTO_ALGOMODE_CBC                  ( ( Crypto_AlgorithmModeType )0x02U )  /* Blockmode: Cipher Block Chaining */
#define CRYPTO_ALGOMODE_CFB                  ( ( Crypto_AlgorithmModeType )0x03U )  /* Blockmode: Cipher Feedback Mode */
#define CRYPTO_ALGOMODE_OFB                  ( ( Crypto_AlgorithmModeType )0x04U )  /* Blockmode: Output Feedback Mode */
#define CRYPTO_ALGOMODE_CTR                  ( ( Crypto_AlgorithmModeType )0x05U )  /* Blockmode: Counter Mode */
#define CRYPTO_ALGOMODE_GCM                  ( ( Crypto_AlgorithmModeType )0x06U )  /* Blockmode: Galois/Counter Mode */
#define CRYPTO_ALGOMODE_XTS                  ( ( Crypto_AlgorithmModeType )0x07U )  /* XOR-encryption-based tweaked-codebook mode with ciphertext stealing */
#define CRYPTO_ALGOMODE_RSAES_OAEP           ( ( Crypto_AlgorithmModeType )0x08U )  /* RSA Optimal Asymmetric Encryption Padding */
#define CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5     ( ( Crypto_AlgorithmModeType )0x09U )  /* RSA encryption/decryption with PKCS#1 v1.5 padding */
#define CRYPTO_ALGOMODE_RSAPSS               ( ( Crypto_AlgorithmModeType )0x0AU )  /* RSA Probabilistic Signature Scheme */
#define CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5    ( ( Crypto_AlgorithmModeType )0x0BU )  /* RSA signature with PKCS#1 v1.5 */
#define CRYPTO_ALGOMODE_8ROUNDS              ( ( Crypto_AlgorithmModeType )0x0CU )  /* 8 rounds (e.g. ChaCha8) */
#define CRYPTO_ALGOMODE_12ROUNDS             ( ( Crypto_AlgorithmModeType )0x0DU )  /* 12 rounds (e.g. ChaCha12) */
#define CRYPTO_ALGOMODE_20ROUNDS             ( ( Crypto_AlgorithmModeType )0x0EU )  /* 20 rounds (e.g. ChaCha20) */
#define CRYPTO_ALGOMODE_HMAC                 ( ( Crypto_AlgorithmModeType )0x0FU )  /* Hashed-based MAC */
#define CRYPTO_ALGOMODE_CMAC                 ( ( Crypto_AlgorithmModeType )0x10U )  /* Cipher-based MAC */
#define CRYPTO_ALGOMODE_GMAC                 ( ( Crypto_AlgorithmModeType )0x11U )  /* Galois MAC */
#define CRYPTO_ALGOMODE_CTRDRBG              ( ( Crypto_AlgorithmModeType )0x12U )  /* Counter-based Deterministic Random Bit Generator */
#define CRYPTO_ALGOMODE_SIPHASH_2_4          ( ( Crypto_AlgorithmModeType )0x13U )  /* SipHash-2-4 */
#define CRYPTO_ALGOMODE_SIPHASH_4_8          ( ( Crypto_AlgorithmModeType )0x14U )  /* SipHash-4-8 */
#define CRYPTO_ALGOMODE_PXXXR1               ( ( Crypto_AlgorithmModeType )0x15U )  /* ANSI R1 curve */
#define CRYPTO_ALGOMODE_CUSTOM               ( ( Crypto_AlgorithmModeType )0xFFU )  /* Custom algorithm mode */

typedef uint8 Crypto_ProcessingType;
#define CRYPTO_PROCESSING_ASYNC              ( ( Crypto_ProcessingType )0x00U )
#define CRYPTO_PROCESSING_SYNC               ( ( Crypto_ProcessingType )0x01U )

/* [SWS_Csm_01028] */
typedef uint8 Crypto_JobStateType;
#define CRYPTO_JOBSTATE_IDLE                 ( ( Crypto_JobStateType )0x00U )
#define CRYPTO_JOBSTATE_ACTIVE               ( ( Crypto_JobStateType )0x01U )

/* [SWS_Csm_01031] */
typedef uint8 Crypto_ServiceInfoType;
#define CRYPTO_HASH                          ( ( Crypto_ServiceInfoType )0x00U )
#define CRYPTO_MACGENERATE                   ( ( Crypto_ServiceInfoType )0x01U )
#define CRYPTO_MACVERIFY                     ( ( Crypto_ServiceInfoType )0x02U )
#define CRYPTO_ENCRYPT                       ( ( Crypto_ServiceInfoType )0x03U )
#define CRYPTO_AEADENCRYPT                   ( ( Crypto_ServiceInfoType )0x04U )
#define CRYPTO_AEADDECRYPT                   ( ( Crypto_ServiceInfoType )0x05U )
#define CRYPTO_SIGNATUREGENERATE             ( ( Crypto_ServiceInfoType )0x06U )
#define CRYPTO_SIGNATUREVERIFY               ( ( Crypto_ServiceInfoType )0x07U )
#define CRYPTO_RANDOMGENERATE                ( ( Crypto_ServiceInfoType )0x08U )
#define CRYPTO_RANDOMSEED                    ( ( Crypto_ServiceInfoType )0x0BU )
#define CRYPTO_KEYGENERATE                   ( ( Crypto_ServiceInfoType )0x0CU )
#define CRYPTO_KEYGENERATE                   ( ( Crypto_ServiceInfoType )0x0DU )
#define CRYPTO_KEYDERIVE                     ( ( Crypto_ServiceInfoType )0x0EU )
#define CRYPTO_KEYEXCHANGECALCPUBVAL         ( ( Crypto_ServiceInfoType )0x0FU )
#define CRYPTO_KEYEXCHANGECALCSECRET         ( ( Crypto_ServiceInfoType )0x10U )
#define CRYPTO_KEYSETVALID                   ( ( Crypto_ServiceInfoType )0x13U )
#define CRYPTO_KEYSETINVALID                 ( ( Crypto_ServiceInfoType )0x14U )
#define CRYPTO_CUSTOM_SERVICE                ( ( Crypto_ServiceInfoType )0x15U )

/* [SWS_Csm_01022] Key Element Ids */
/* Service : MAC */
#define CRYPTO_KE_MAC_KEY                  ( ( uint8 )1U )
#define CRYPTO_KE_MAC_PROOF                ( ( uint8 )2U )

/* Service : Signature */
/* #define CRYPTO_KE_SIGNATURE_KEY         ( ( uint8 )1U ) */
#define CRYPTO_KE_SIGNATURE_CURVETYPE      ( ( uint8 )29U )

/* Service : Random */
#define CRYPTO_KE_RANDOM_SEED_STATE       ( ( uint8 )3U )
#define CRYPTO_KE_RANDOM_ALGORITHM        ( ( uint8 )4U )

/* Service : Cipher */
#define CRYPTO_KE_CIPHER_KEY              ( ( uint8 )1U )
#define CRYPTO_KE_CIPHER_PROOF            ( ( uint8 )2U )
#define CRYPTO_KE_CIPHER_IV               ( ( uint8 )5U )
#define CRYPTO_KE_CIPHER_2NDKEY           ( ( uint8 )7U )

/* Service : Key Change */
#define CRYPTO_KE_KEYEXCHANGE_BASE        ( ( uint8 )8U )
#define CRYPTO_KE_KEYEXCHANGE_PRIVKEY     ( ( uint8 )9U )
#define CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY   ( ( uint8 )10U )
#define CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE ( ( uint8 )11U )
#define CRYPTO_KE_KEYEXCHANGE_ALGORITHM   ( ( uint8 )12U )
#define CRYPTO_KE_KEYEXCHANGE_CURVETYPE   ( ( uint8 )29U )

/* Service : Key Derivation */
#define CRYPTO_KE_KEYDERIVATION_PASSWORD  ( ( uint8 )11U )
#define CRYPTO_KE_KEYDERIVATION_SALT      ( ( uint8 )13U )
#define CRYPTO_KE_KEYDERIVATION_ITERATIONS ( ( uint8 )14U )
#define CRYPTO_KE_KEYDERIVATION_ALGORITHM ( ( uint8 )15U )
#define CRYPTO_KE_KEYDERIVATION_CURVETYPE ( ( uint8 )29U )

/* Service : Key Generate */
#define CRYPTO_KE_KEYGENERATE_KEY         ( ( uint8 )1U )
#define CRYPTO_KE_KEYGENERATE_SEED        ( ( uint8 )16U )
#define CRYPTO_KE_KEYGENERATE_ALGORITHM   ( ( uint8 )17U )
#define CRYPTO_KE_KEYGENERATE_CURVETYPE   ( ( uint8 )29U )

/* Crypto_InputOutputRedirectionConfigType */
/* [SWS_Csm_01024] */
typedef uint8 Crypto_InputOutputRedirectionConfigType;
#define CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT    ( ( Crypto_InputOutputRedirectionConfigType )0x01U )
#define CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT  ( ( Crypto_InputOutputRedirectionConfigType )0x02U )
#define CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT   ( ( Crypto_InputOutputRedirectionConfigType )0x04U )
#define CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT   ( ( Crypto_InputOutputRedirectionConfigType )0x10U )
#define CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT ( ( Crypto_InputOutputRedirectionConfigType )0x20U )

/* [SWS_Csm_01008] */
typedef struct {
    Crypto_AlgorithmFamilyType  family;
    Crypto_AlgorithmFamilyType  secondaryFamily;
    uint32                      keyLength;
    Crypto_AlgorithmModeType    mode;
} Crypto_AlgorithmInfoType;

/* [SWS_Csm_01009] */
typedef struct {
    CSM_70_CONST uint8 QL_70_FAR *    inputPtr;
    uint32                             inputLength;
    CSM_70_CONST uint8 *               secondaryInputPtr;
    uint32                             secondaryInputLength;
    CSM_70_CONST uint8 *               tertiaryInputPtr;
    uint32                             tertiaryInputLength;
    CSM_70_CONST uint8 *               outputPtr;
    uint32 *                           outputLengthPtr;
    CSM_70_CONST uint8 *               secondaryOutputPtr;
    uint32 *                           secondaryOutputLengthPtr;
    Crypto_VerifyResultType *         verifyPtr;
    Crypto_OperationModeType           mode;
} Crypto_JobPrimitiveInputOutputType;

/* [SWS_Csm_01010] */
typedef struct {
    CSM_70_CONST uint32 jobId;
    CSM_70_CONST uint32 jobPriority;
} Crypto_JobInfoType;

/* [SWS_Csm_01011] */
typedef struct {
    CSM_70_CONST uint32                   resultLength;
    CSM_70_CONST Crypto_ServiceInfoType   service;
    CSM_70_CONST Crypto_AlgorithmInfoType algorithm;
} Crypto_PrimitiveInfoType;

/* [SWS_Csm_01012] */
typedef struct {
    CSM_70_CONST uint32                         callbackId;
    CSM_70_CONST Crypto_PrimitiveInfoType*      primitiveInfo;
    CSM_70_CONST uint32                         secureCounterId;
    CSM_70_CONST Crypto_ProcessingType          processingType;
    CSM_70_CONST bool_t                         callbackUpdateNotification;
} Crypto_JobPrimitiveInfoType;

/* [SWS_Csm_91026] */
typedef struct {
    uint8   redirectionConfig;
    uint32  inputKeyId;
    uint32  inputKeyElementId;
    uint32  secondaryInputKeyId;
    uint32  secondaryInputKeyElementId;
    uint32  tertiaryInputKeyId;
    uint32  tertiaryInputKeyElementId;
    uint32  outputKeyId;
    uint32  outputKeyElementId;
    uint32  secondaryOutputKeyId;
    uint32  secondaryOutputKeyElementId;
} Crypto_JobRedirectionInfoType;

/* [SWS_Csm_01013] */
typedef struct {
    CSM_70_CONST uint32                       jobId;
    Crypto_JobStateType                       state;
    Crypto_JobPrimitiveInputOutputType        PrimitiveInputOutput;
    CSM_70_CONST Crypto_JobPrimitiveInfoType* jobPrimitiveInfoRef;
    CSM_70_CONST Crypto_JobInfoType*          jobInfoRef;
    Crypto_JobRedirectionInfoType*            jobRedirectionInfoRef;
    uint32                                    cryptoKeyId;
    uint32                                    targetCryptoKeyId;
    CSM_70_CONST uint32                       jobPriority;
} Crypto_JobType;

/*----------------------------------------------------------------------------*/
/* macros                                                                     */
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

#endif /* #ifndef CRYPTO_GENERALTYPES_H */

/* EOF Crypto_GeneralTypes.h */
