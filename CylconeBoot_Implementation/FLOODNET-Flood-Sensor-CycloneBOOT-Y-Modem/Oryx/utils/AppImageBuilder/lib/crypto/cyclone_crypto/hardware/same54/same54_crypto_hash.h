/**
 * @file same54_crypto_hash.h
 * @brief SAME54 hash hardware accelerator
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

#ifndef _SAME54_CRYPTO_HASH_H
#define _SAME54_CRYPTO_HASH_H

//Dependencies
#include "core/crypto.h"

//Hash hardware accelerator
#ifndef SAME54_CRYPTO_HASH_SUPPORT
   #define SAME54_CRYPTO_HASH_SUPPORT DISABLED
#elif (SAME54_CRYPTO_HASH_SUPPORT != ENABLED && SAME54_CRYPTO_HASH_SUPPORT != DISABLED)
   #error SAME54_CRYPTO_HASH_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief ICM region descriptor
 **/

typedef struct
{
   uint32_t raddr; ///<ICM region start address
   uint32_t rcfg;  ///<ICM region configuration
   uint32_t rctrl; ///<ICM region control
   uint32_t rnext; ///<ICM region next address
} Same54IcmDesc;


//C++ guard
#ifdef __cplusplus
}
#endif

#endif