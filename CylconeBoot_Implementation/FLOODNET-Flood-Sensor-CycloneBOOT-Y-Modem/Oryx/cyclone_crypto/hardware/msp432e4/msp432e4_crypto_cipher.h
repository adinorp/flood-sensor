/**
 * @file msp432e4_crypto_cipher.h
 * @brief MSP432E4 cipher hardware accelerator
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

#ifndef _MSP432E4_CRYPTO_CIPHER_H
#define _MSP432E4_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef MSP432E4_CRYPTO_CIPHER_SUPPORT
   #define MSP432E4_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (MSP432E4_CRYPTO_CIPHER_SUPPORT != ENABLED && MSP432E4_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error MSP432E4_CRYPTO_CIPHER_SUPPORT parameter is not valid
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