/**
 * @file sama5d3_crypto_cipher.h
 * @brief SAMA5D3 cipher hardware accelerator
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

#ifndef _SAMA5D3_CRYPTO_CIPHER_H
#define _SAMA5D3_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef SAMA5D3_CRYPTO_CIPHER_SUPPORT
   #define SAMA5D3_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (SAMA5D3_CRYPTO_CIPHER_SUPPORT != ENABLED && SAMA5D3_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error SAMA5D3_CRYPTO_CIPHER_SUPPORT parameter is not valid
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
