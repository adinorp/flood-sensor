/**
 * @file stm32l0xx_crypto_cipher.h
 * @brief STM32L0 cipher hardware accelerator
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

#ifndef _STM32L0XX_CRYPTO_CIPHER_H
#define _STM32L0XX_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef STM32L0XX_CRYPTO_CIPHER_SUPPORT
   #define STM32L0XX_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (STM32L0XX_CRYPTO_CIPHER_SUPPORT != ENABLED && STM32L0XX_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error STM32L0XX_CRYPTO_CIPHER_SUPPORT parameter is not valid
#endif

//CHMOD bitfield
#define AES_CR_CHMOD_ECB           0
#define AES_CR_CHMOD_CBC           AES_CR_CHMOD_0
#define AES_CR_CHMOD_CTR           AES_CR_CHMOD_1

//MODE bitfield
#define AES_CR_MODE_ENCRYPTION     0
#define AES_CR_MODE_KEY_DERIVATION AES_CR_MODE_0
#define AES_CR_MODE_DECRYPTION     AES_CR_MODE_1

//DATATYPE bitfield
#define AES_CR_DATATYPE_32B        0
#define AES_CR_DATATYPE_16B        AES_CR_DATATYPE_0
#define AES_CR_DATATYPE_8B         AES_CR_DATATYPE_1
#define AES_CR_DATATYPE_1B         (AES_CR_DATATYPE_1 | AES_CR_DATATYPE_0)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Cipher related functions
error_t crypInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
