/**
 * @file stm32l5xx_crypto_cipher.h
 * @brief STM32L5 cipher hardware accelerator
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

#ifndef _STM32L5XX_CRYPTO_CIPHER_H
#define _STM32L5XX_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef STM32L5XX_CRYPTO_CIPHER_SUPPORT
   #define STM32L5XX_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (STM32L5XX_CRYPTO_CIPHER_SUPPORT != ENABLED && STM32L5XX_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error STM32L5XX_CRYPTO_CIPHER_SUPPORT parameter is not valid
#endif

//KEYSIZE bitfield
#define AES_CR_KEYSIZE_128B        0
#define AES_CR_KEYSIZE_256B        AES_CR_KEYSIZE

//GCMPH bitfield
#define AES_CR_GCMPH_INIT          0
#define AES_CR_GCMPH_HEADER        AES_CR_GCMPH_0
#define AES_CR_GCMPH_PAYLOAD       AES_CR_GCMPH_1
#define AES_CR_GCMPH_FINAL         (AES_CR_GCMPH_1 | AES_CR_GCMPH_0)

//CHMOD bitfield
#define AES_CR_CHMOD_ECB           0
#define AES_CR_CHMOD_CBC           AES_CR_CHMOD_0
#define AES_CR_CHMOD_CTR           AES_CR_CHMOD_1
#define AES_CR_CHMOD_GCM_GMAC      (AES_CR_CHMOD_0 | AES_CR_CHMOD_1)
#define AES_CR_CHMOD_CCM           AES_CR_CHMOD_2

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
