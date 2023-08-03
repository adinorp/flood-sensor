/**
 * @file lpc55xx_crypto_pkc.h
 * @brief LPC5500 public-key hardware accelerator
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

#ifndef _LPC55XX_CRYPTO_PKC_H
#define _LPC55XX_CRYPTO_PKC_H

//Dependencies
#include "core/crypto.h"

//Public-key hardware accelerator
#ifndef LPC55XX_CRYPTO_PKC_SUPPORT
   #define LPC55XX_CRYPTO_PKC_SUPPORT DISABLED
#elif (LPC55XX_CRYPTO_PKC_SUPPORT != ENABLED && LPC55XX_CRYPTO_PKC_SUPPORT != DISABLED)
   #error LPC55XX_CRYPTO_PKC_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief EC primitive arguments
 **/

typedef struct
{
   uint32_t rx[18];
   uint32_t ry[18];
   uint32_t sx[18];
   uint32_t sy[18];
   uint32_t d[18];
} Lpc55xxEcArgs;


//C++ guard
#ifdef __cplusplus
}
#endif

#endif
