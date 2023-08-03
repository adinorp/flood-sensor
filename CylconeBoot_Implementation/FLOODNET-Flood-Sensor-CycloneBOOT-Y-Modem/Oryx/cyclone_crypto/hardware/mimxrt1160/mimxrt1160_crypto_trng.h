/**
 * @file mimxrt1160_crypto_trng.h
 * @brief i.MX RT1160 true random number generator
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

#ifndef _MIMXRT1160_CRYPTO_TRNG_H
#define _MIMXRT1160_CRYPTO_TRNG_H

//Dependencies
#include "core/crypto.h"

//True random number generator
#ifndef MIMXRT1160_CRYPTO_TRNG_SUPPORT
   #define MIMXRT1160_CRYPTO_TRNG_SUPPORT ENABLED
#elif (MIMXRT1160_CRYPTO_TRNG_SUPPORT != ENABLED && MIMXRT1160_CRYPTO_TRNG_SUPPORT != DISABLED)
   #error MIMXRT1160_CRYPTO_TRNG_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//TRNG related functions
error_t trngGetRandomData(uint8_t *data, size_t length);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif