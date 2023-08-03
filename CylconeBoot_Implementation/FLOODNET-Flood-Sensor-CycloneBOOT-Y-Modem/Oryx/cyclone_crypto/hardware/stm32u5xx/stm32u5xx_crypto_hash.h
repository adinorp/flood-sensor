/**
 * @file stm32u5xx_crypto_hash.h
 * @brief STM32U5 hash hardware accelerator
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

#ifndef _STM32U5XX_CRYPTO_HASH_H
#define _STM32U5XX_CRYPTO_HASH_H

//Dependencies
#include "core/crypto.h"

//Hash hardware accelerator
#ifndef STM32U5XX_CRYPTO_HASH_SUPPORT
   #define STM32U5XX_CRYPTO_HASH_SUPPORT DISABLED
#elif (STM32U5XX_CRYPTO_HASH_SUPPORT != ENABLED && STM32U5XX_CRYPTO_HASH_SUPPORT != DISABLED)
   #error STM32U5XX_CRYPTO_HASH_SUPPORT parameter is not valid
#endif

//ALGO bitfield
#define HASH_CR_ALGO_SHA1    0
#define HASH_CR_ALGO_MD5     HASH_CR_ALGO_0
#define HASH_CR_ALGO_SHA224  HASH_CR_ALGO_1
#define HASH_CR_ALGO_SHA256  (HASH_CR_ALGO_1 | HASH_CR_ALGO_0)

//DATATYPE bitfield
#define HASH_CR_DATATYPE_32B 0
#define HASH_CR_DATATYPE_16B HASH_CR_DATATYPE_0
#define HASH_CR_DATATYPE_8B  HASH_CR_DATATYPE_1
#define HASH_CR_DATATYPE_1B  (HASH_CR_DATATYPE_1 | HASH_CR_DATATYPE_0)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Hash related functions
error_t hashInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
