/**
 * @file esp32_crypto_hash.h
 * @brief ESP32 hash hardware accelerator
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

#ifndef _ESP32_CRYPTO_HASH_H
#define _ESP32_CRYPTO_HASH_H

//Dependencies
#include "core/crypto.h"

//Hash hardware accelerator
#ifndef ESP32_CRYPTO_HASH_SUPPORT
   #define ESP32_CRYPTO_HASH_SUPPORT DISABLED
#elif (ESP32_CRYPTO_HASH_SUPPORT != ENABLED && ESP32_CRYPTO_HASH_SUPPORT != DISABLED)
   #error ESP32_CRYPTO_HASH_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Hash related functions
void esp32ShaInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
