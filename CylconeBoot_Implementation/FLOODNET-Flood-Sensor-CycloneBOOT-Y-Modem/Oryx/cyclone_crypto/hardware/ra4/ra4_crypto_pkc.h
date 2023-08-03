/**
 * @file ra4_crypto_pkc.h
 * @brief RA4 public-key hardware accelerator
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

#ifndef _RA4_CRYPTO_PKC_H
#define _RA4_CRYPTO_PKC_H

//Dependencies
#include "hw_sce_private.h"
#include "core/crypto.h"

//Public-key hardware accelerator
#ifndef RA4_CRYPTO_PKC_SUPPORT
   #define RA4_CRYPTO_PKC_SUPPORT DISABLED
#elif (RA4_CRYPTO_PKC_SUPPORT != ENABLED && RA4_CRYPTO_PKC_SUPPORT != DISABLED)
   #error RA4_CRYPTO_PKC_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief RSA primitive arguments
 **/

typedef struct
{
   uint32_t n[128];
   uint32_t d[128];
   uint32_t e[1];
   uint32_t m[128];
   uint32_t c[128];
   uint32_t key[160];
   uint32_t wrappedKey[256];
} Ra4RsaArgs;


/**
 * @brief EC primitive arguments
 **/

typedef struct
{
   uint32_t params[48];
   uint32_t g[24];
   uint32_t d[12];
   uint32_t q[24];
   uint32_t digest[12];
   uint32_t signature[24];
   uint32_t wrappedKey[32];
} Ra4EcArgs;


//C++ guard
#ifdef __cplusplus
}
#endif

#endif
