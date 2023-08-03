/**
 * @file s5d9_crypto_hash.h
 * @brief Synergy S5D9 hash hardware accelerator
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

#ifndef _S5D9_CRYPTO_HASH_H
#define _S5D9_CRYPTO_HASH_H

//Dependencies
#include "core/crypto.h"

//Hash hardware accelerator
#ifndef S5D9_CRYPTO_HASH_SUPPORT
   #define S5D9_CRYPTO_HASH_SUPPORT DISABLED
#elif (S5D9_CRYPTO_HASH_SUPPORT != ENABLED && S5D9_CRYPTO_HASH_SUPPORT != DISABLED)
   #error S5D9_CRYPTO_HASH_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
