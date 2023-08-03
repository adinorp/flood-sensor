/**
 * @file stm32f2xx_crypto_cipher.h
 * @brief STM32F2 cipher hardware accelerator
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

#ifndef _STM32F2XX_CRYPTO_CIPHER_H
#define _STM32F2XX_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef STM32F2XX_CRYPTO_CIPHER_SUPPORT
   #define STM32F2XX_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (STM32F2XX_CRYPTO_CIPHER_SUPPORT != ENABLED && STM32F2XX_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error STM32F2XX_CRYPTO_CIPHER_SUPPORT parameter is not valid
#endif

//KEYSIZE bitfield
#define CRYP_CR_KEYSIZE_128B      0
#define CRYP_CR_KEYSIZE_192B      CRYP_CR_KEYSIZE_0
#define CRYP_CR_KEYSIZE_256B      CRYP_CR_KEYSIZE_1

//DATATYPE bitfield
#define CRYP_CR_DATATYPE_32B      0
#define CRYP_CR_DATATYPE_16B      CRYP_CR_DATATYPE_0
#define CRYP_CR_DATATYPE_8B       CRYP_CR_DATATYPE_1
#define CRYP_CR_DATATYPE_1B       (CRYP_CR_DATATYPE_1 | CRYP_CR_DATATYPE_0)

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
