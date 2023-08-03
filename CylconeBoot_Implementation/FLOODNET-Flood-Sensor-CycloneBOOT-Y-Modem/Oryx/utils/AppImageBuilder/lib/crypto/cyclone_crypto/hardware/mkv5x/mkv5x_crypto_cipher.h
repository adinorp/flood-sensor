/**
 * @file mkv5x_crypto_cipher.h
 * @brief Kinetis KV5x cipher hardware accelerator
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

#ifndef _MKV5X_CRYPTO_CIPHER_H
#define _MKV5X_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef MKV5X_CRYPTO_CIPHER_SUPPORT
   #define MKV5X_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (MKV5X_CRYPTO_CIPHER_SUPPORT != ENABLED && MKV5X_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error MKV5X_CRYPTO_CIPHER_SUPPORT parameter is not valid
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
