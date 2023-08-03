/**
 * @file lpc54xxx_crypto_trng.h
 * @brief LPC54000 true random number generator
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

#ifndef _LPC54XXX_CRYPTO_TRNG_H
#define _LPC54XXX_CRYPTO_TRNG_H

//Dependencies
#include "core/crypto.h"

//True random number generator
#ifndef LPC54XXX_CRYPTO_TRNG_SUPPORT
   #define LPC54XXX_CRYPTO_TRNG_SUPPORT ENABLED
#elif (LPC54XXX_CRYPTO_TRNG_SUPPORT != ENABLED && LPC54XXX_CRYPTO_TRNG_SUPPORT != DISABLED)
   #error LPC54XXX_CRYPTO_TRNG_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//TRNG related functions
error_t trngInit(void);
error_t trngGetRandomData(uint8_t *data, size_t length);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
