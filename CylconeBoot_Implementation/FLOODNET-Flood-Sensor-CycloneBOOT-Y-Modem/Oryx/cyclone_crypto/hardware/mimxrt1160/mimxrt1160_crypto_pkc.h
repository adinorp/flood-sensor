/**
 * @file mimxrt1160_crypto_pkc.h
 * @brief i.MX RT1160 public-key hardware accelerator
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

#ifndef _MIMXRT1160_CRYPTO_PKC_H
#define _MIMXRT1160_CRYPTO_PKC_H

//Dependencies
#include "core/crypto.h"

//Public-key hardware accelerator
#ifndef MIMXRT1160_CRYPTO_PKC_SUPPORT
   #define MIMXRT1160_CRYPTO_PKC_SUPPORT DISABLED
#elif (MIMXRT1160_CRYPTO_PKC_SUPPORT != ENABLED && MIMXRT1160_CRYPTO_PKC_SUPPORT != DISABLED)
   #error MIMXRT1160_CRYPTO_PKC_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief PKHA primitive arguments
 **/

typedef struct
{
   uint8_t a[512];
   uint8_t b[512];
   uint8_t e[512];
   uint8_t p[512];
   uint8_t r[512];
} PkhaArgs;


/**
 * @brief PKHA ECC primitive arguments
 **/

typedef struct
{
   uint8_t p[66];
   uint8_t a[66];
   uint8_t b[66];
   uint8_t d[66];
   uint8_t gx[66];
   uint8_t gy[66];
   uint8_t qx[66];
   uint8_t qy[66];
} PkhaEccArgs;


//C++ guard
#ifdef __cplusplus
}
#endif

#endif
