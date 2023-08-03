/**
 * @file rx65n_crypto_hash.h
 * @brief RX65N hash hardware accelerator
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

#ifndef _RX65N_CRYPTO_HASH_H
#define _RX65N_CRYPTO_HASH_H

//Dependencies
#include "core/crypto.h"

//Hash hardware accelerator
#ifndef RX65N_CRYPTO_HASH_SUPPORT
   #define RX65N_CRYPTO_HASH_SUPPORT DISABLED
#elif (RX65N_CRYPTO_HASH_SUPPORT != ENABLED && RX65N_CRYPTO_HASH_SUPPORT != DISABLED)
   #error RX65N_CRYPTO_HASH_SUPPORT parameter is not valid
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
