/**
 * @file iap.h
 * @brief CycloneBOOT IAP User API
 *
 * @section License
 *
 * Copyright (C) 2021-2023 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneBOOT Ultimate.
 *
 * This software is provided under a commercial license. You may
 * use this software under the conditions stated in the license
 * terms. This source code cannot be redistributed.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.1
 **/

#ifndef _IAP_H
#define _IAP_H

//Dependencies
#include <stdint.h>
#include "iap_config.h"
#include "core/flash.h"
#include "core/crypto.h"
#include "hash/hash_algorithms.h"
#include "core/crc32.h"
#if ((IAP_ENCRYPTION_SUPPORT == ENABLED) || \
    ((IAP_SINGLE_BANK_SUPPORT == ENABLED) && \
    (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)))
#include "security/cipher.h"
#endif
#include "security/verify.h"
#include "error.h"
#include "core/cboot_error.h"

//CycloneBOOT Version string
#define CYCLONE_BOOT_IAP_VERSION_STRING "2.1.0"
//CycloneBOOT Major version
#define CYCLONE_BOOT_IAP_MAJOR_VERSION 2
//CycloneBOOT Minor version
#define CYCLONE_BOOT_IAP_MINOR_VERSION 1
//CycloneBOOT Revision number
#define CYCLONE_BOOT_IAP_REV_NUMBER 0

//IAP single bank internal flash memory mode support
#ifndef IAP_SINGLE_BANK_SUPPORT
#define IAP_SINGLE_BANK_SUPPORT DISABLED
#elif (IAP_SINGLE_BANK_SUPPORT != ENABLED && IAP_SINGLE_BANK_SUPPORT != DISABLED)
   #error IAP_SINGLE_BANK_SUPPORT  parameter is not valid
#endif

//IAP dual bank internal flash memory mode support
#ifndef IAP_DUAL_BANK_SUPPORT
#define IAP_DUAL_BANK_SUPPORT ENABLED
#elif (IAP_DUAL_BANK_SUPPORT != ENABLED && IAP_DUAL_BANK_SUPPORT != DISABLED)
   #error IAP_DUAL_BANK_SUPPORT  parameter is not valid
#endif

//IAP fallback support
#ifndef IAP_FALLBACK_SUPPORT
#define IAP_FALLBACK_SUPPORT DISABLED
#elif (IAP_FALLBACK_SUPPORT != ENABLED && IAP_FALLBACK_SUPPORT != DISABLED)
   #error IAP_FALLBACK_SUPPORT  parameter is not valid
#endif

//Acceptabled internal memory mode
#if ((IAP_SINGLE_BANK_SUPPORT == ENABLED && IAP_DUAL_BANK_SUPPORT == ENABLED) || \
(IAP_SINGLE_BANK_SUPPORT == DISABLED && IAP_DUAL_BANK_SUPPORT == DISABLED))
   #error Exactly one of the following parameters MUST be enabled: \
IAP_SINGLE_BANK_SUPPORT - \
IAP_DUAL_BANK_SUPPORT
#endif

//IAP external memory encryption support
#ifndef IAP_EXT_MEM_ENCRYPTION_SUPPORT
#define IAP_EXT_MEM_ENCRYPTION_SUPPORT DISABLED
#elif (IAP_EXT_MEM_ENCRYPTION_SUPPORT != ENABLED && IAP_EXT_MEM_ENCRYPTION_SUPPORT != DISABLED)
   #error IAP_EXT_MEM_ENCRYPTION_SUPPORT  parameter is not valid
#endif

//Acceptable external memory encryption activation
#if ((IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED && IAP_SINGLE_BANK_SUPPORT == DISABLED))
   #error Encryption of external memory is available only in Signel Bank mode
#endif

//Cipher support
#ifndef IAP_ENCRYPTION_SUPPORT
   #define IAP_ENCRYPTION_SUPPORT DISABLED
#elif (IAP_ENCRYPTION_SUPPORT != ENABLED && IAP_ENCRYPTION_SUPPORT != DISABLED)
   #error IAP_ENCRYPTION_SUPPORT parameter is not valid
#endif

#if (IAP_ENCRYPTION_SUPPORT == ENABLED)
#include "security/cipher.h"
#endif

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
#if (VERIFY_INTEGRITY_SUPPORT == DISABLED)
//Force activation of VERIFY_INTEGRITY_SUPPORT when IAP_SINGLE_BANK_SUPPORT is activated.
#error Integrity support (VERIFY_INTEGRITY_SUPPORT) MUST be enabled when using CycloneBOOT in Single Bank Mode!
#endif
#endif

//Signature size
#define IAP_MAX_CHECK_DATA_SIZE 512


//Forward declaration of IapContext structure
struct _IapContext;
#define IapContext struct _IapContext

/**
 * @brief Random data generation callback function
 **/

typedef error_t (*IapRandCallback)(uint8_t *data, size_t length);


/**
 *@brief Supported authentication algorithms
 **/

typedef enum
{
   IAP_AUTH_NONE,
   IAP_AUTH_HMAC
} IapAuthAlgo;


/**
 *@brief Supported signature algorithms
 **/

typedef enum
{
   IAP_SIGN_NONE,
   IAP_SIGN_RSA,
   IAP_SIGN_ECDSA
} IapSignAlgo;


/**
 * @brief IAP Crypto settings
 **/

typedef struct
{
#if ((IAP_ENCRYPTION_SUPPORT == ENABLED) || \
    ((IAP_SINGLE_BANK_SUPPORT == ENABLED) && \
    (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)))
   const CipherAlgo *cipherAlgo;                   ///<Image cipher algorithm
   CipherMode cipherMode;                          ///<Image cipher mode
   const char_t *cipherKey;                        ///<Image cipher key
   size_t cipherKeyLen;                            ///<Image cipher key size
#endif
   VerifySettings verifySettings;                 ///<Various crypto settings for image verification
} IapCryptoSettings;


/**
 * @brief IAP user settings
 **/

typedef struct
{
   uint32_t appVersion;                         ///<Version of the current running application
   const FlashDriver *primaryFlashDriver;       ///<Driver of the primary (internal) flash memory driver
   IapCryptoSettings imageInCrypto;             ///<Cryptographic settings used to manage an update image
#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
   const FlashDriver *secondaryFlashDriver;     ///<Driver of the secondary (external) flash memory driver
   IapCryptoSettings imageOutCrypto;            ///<Cryptographic settings used to generate the update image
   uint16_t addrSlot1;                          ///<Address of the first slot in secondary memory
   size_t sizeSlot1;                            ///<Size of the first slot in secondary memory
#if (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   const char_t *psk;                           ///<PSK key used to encrypt the output image
   uint32_t pskSize;                            ///<Size of the PSK key used to encrypt the output image
#endif
#if IAP_FALLBACK_SUPPORT == ENABLED
    uint32_t addrSlot2;                         ///<Address of the second slot in secondary memory
    size_t sizeSlot2;                           ///<Size of the second slot in secondary memory
#endif
#endif
}IapSettings;


/**
 * @brief IAP states
 **/

typedef enum
{
   IAP_STATE_IDLE,
   IAP_STATE_RECV_APP_HEADER,
   IAP_STATE_RECV_APP_DATA,
   IAP_STATE_RECV_APP_CHECK,
   IAP_STATE_VALIDATE_APP,
   IAP_STATE_APP_REBOOT
} IapState;


/**
 * @brief Image context
 **/

typedef struct
{
   uint16_t imgIdx;                                   ///<Image index number
   struct _IapContext *iapContext;                    ///<Pointer to the parent IAP context

   uint32_t firmwareAddr;                             ///<Image firmware data write address
   size_t firmwareLength;                             ///<Image data firmware length
   uint32_t pos;                                      ///<Image current firmware data write position
   size_t written;                                    ///<Current written firmware data byte number

   uint8_t state;                                     ///<Image process state

   uint8_t buffer[128];                               ///<Image processing buffer
   uint8_t *bufferPos;                                ///<Position in image processing buffer
   size_t bufferLen;                                  ///<Number of byte in image processing buffer

#if (IAP_ENCRYPTION_SUPPORT == ENABLED || \
    ((IAP_SINGLE_BANK_SUPPORT == ENABLED) && \
    (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)))
   CipherEngine cipherEngine;                         ///<Image cipher engine
   bool_t ivRetrieved;
#endif
   VerifyContext verifyContext;                       ///<Image verification settings
   uint8_t checkData[IAP_MAX_CHECK_DATA_SIZE];        ///<Image check data buffer
   uint8_t *checkDataPos;                             ///<Position in image check data buffer
   size_t checkDataLen;                               ///<Current number of byte in image check data buffer
   size_t checkDataSize;                              ///<Image check data buffer size

   SlotDesc *slotInfo;                                ///<Image flash memory slot
} ImageContext;


/**
 * @brief IAP context
 **/

struct _IapContext
{
   IapSettings settings;      ///<IAP user settings

   FlashDesc primaryMem;      ///<Primary flash memory descriptor
   FlashDesc secondaryMem;    ///<Secondary (external) flash memory descriptor

   ImageContext imageInput;   ///<Input image (received update image) context
   ImageContext imageOutput;  ///<Output image context
};

//CycloneBOOT IAP application related functions
void iapGetDefaultSettings(IapSettings *settings);
char_t *iapGetVersion(void);
error_t iapRegisterRandCallback(IapRandCallback callback);
cboot_error_t iapInit(IapContext *context, const IapSettings *settings);
cboot_error_t iapUpdate(IapContext *context, const void *data, size_t length);
cboot_error_t iapFinalize(IapContext *context);
cboot_error_t iapReboot(IapContext *context);

//Extern device MCU related function
extern uint32_t mcuGetVtorOffset(void);
extern void mcuSystemReset(void);
extern void mcuJumpToApplication(uint32_t address);

//Random data generation callback function
extern IapRandCallback iapRandCallback;

#endif // !_IAP_H
