/**
 * @file mk6x_crypto_cipher.h
 * @brief Kinetis K6x cipher hardware accelerator
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

#ifndef _MK6X_CRYPTO_CIPHER_H
#define _MK6X_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef MK6X_CRYPTO_CIPHER_SUPPORT
   #define MK6X_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (MK6X_CRYPTO_CIPHER_SUPPORT != ENABLED && MK6X_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error MK6X_CRYPTO_CIPHER_SUPPORT parameter is not valid
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
