/**
 * @file esp32_s3_crypto_cipher.h
 * @brief ESP32-S3 cipher hardware accelerator
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

#ifndef _ESP32_S3_CRYPTO_CIPHER_H
#define _ESP32_S3_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef ESP32_S3_CRYPTO_CIPHER_SUPPORT
   #define ESP32_S3_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (ESP32_S3_CRYPTO_CIPHER_SUPPORT != ENABLED && ESP32_S3_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error ESP32_S3_CRYPTO_CIPHER_SUPPORT parameter is not valid
#endif

//AES Operation Mode register
#define AES_MODE_ENC          0x00000000
#define AES_MODE_DEC          0x00000004
#define AES_MODE_128_BITS     0x00000000
#define AES_MODE_256_BITS     0x00000002

//Endianness Configuration register
#define AES_ENDIAN_DEFAULT    0x0000003F

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Cipher related functions
void esp32s3AesInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
