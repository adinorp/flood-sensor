/**
 * @file esp32_s3_crypto_hash.h
 * @brief ESP32-S3 hash hardware accelerator
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

#ifndef _ESP32_S3_CRYPTO_HASH_H
#define _ESP32_S3_CRYPTO_HASH_H

//Dependencies
#include "core/crypto.h"

//Hash hardware accelerator
#ifndef ESP32_S3_CRYPTO_HASH_SUPPORT
   #define ESP32_S3_CRYPTO_HASH_SUPPORT DISABLED
#elif (ESP32_S3_CRYPTO_HASH_SUPPORT != ENABLED && ESP32_S3_CRYPTO_HASH_SUPPORT != DISABLED)
   #error ESP32_S3_CRYPTO_HASH_SUPPORT parameter is not valid
#endif

//AES Mode register
#define SHA_MODE_SHA1       0x00000000
#define SHA_MODE_SHA224     0x00000001
#define SHA_MODE_SHA256     0x00000002
#define SHA_MODE_SHA384     0x00000003
#define SHA_MODE_SHA512     0x00000004
#define SHA_MODE_SHA512_224 0x00000005
#define SHA_MODE_SHA512_256 0x00000006
#define SHA_MODE_SHA512_T   0x00000007

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Hash related functions
void esp32s3ShaInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
