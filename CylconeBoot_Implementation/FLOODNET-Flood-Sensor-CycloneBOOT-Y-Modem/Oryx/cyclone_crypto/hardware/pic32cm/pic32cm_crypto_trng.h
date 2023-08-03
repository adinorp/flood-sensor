/**
 * @file pic32cm_crypto_trng.h
 * @brief PIC32CM true random number generator
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

#ifndef _PIC32CM_CRYPTO_TRNG_H
#define _PIC32CM_CRYPTO_TRNG_H

//Dependencies
#include "core/crypto.h"

//True random number generator
#ifndef PIC32CM_CRYPTO_TRNG_SUPPORT
   #define PIC32CM_CRYPTO_TRNG_SUPPORT ENABLED
#elif (PIC32CM_CRYPTO_TRNG_SUPPORT != ENABLED && PIC32CM_CRYPTO_TRNG_SUPPORT != DISABLED)
   #error PIC32CM_CRYPTO_TRNG_SUPPORT parameter is not valid
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