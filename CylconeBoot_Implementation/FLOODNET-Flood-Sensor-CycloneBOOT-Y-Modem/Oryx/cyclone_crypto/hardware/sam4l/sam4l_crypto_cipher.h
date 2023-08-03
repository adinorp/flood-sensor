/**
 * @file sam4l_crypto_cipher.h
 * @brief SAM4L cipher hardware accelerator
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

#ifndef _SAM4L_CRYPTO_CIPHER_H
#define _SAM4L_CRYPTO_CIPHER_H

//Dependencies
#include "core/crypto.h"

//Cipher hardware accelerator
#ifndef SAM4L_CRYPTO_CIPHER_SUPPORT
   #define SAM4L_CRYPTO_CIPHER_SUPPORT DISABLED
#elif (SAM4L_CRYPTO_CIPHER_SUPPORT != ENABLED && SAM4L_CRYPTO_CIPHER_SUPPORT != DISABLED)
   #error SAM4L_CRYPTO_CIPHER_SUPPORT parameter is not valid
#endif

//CFBS bitfield
#define AESA_MODE_CFBS_128BIT AESA_MODE_CFBS(0)
#define AESA_MODE_CFBS_64BIT  AESA_MODE_CFBS(1)
#define AESA_MODE_CFBS_32BIT  AESA_MODE_CFBS(2)
#define AESA_MODE_CFBS_16BIT  AESA_MODE_CFBS(3)
#define AESA_MODE_CFBS_8BIT   AESA_MODE_CFBS(4)

//OPMODE bitfield
#define AESA_MODE_OPMODE_ECB  AESA_MODE_OPMODE(0)
#define AESA_MODE_OPMODE_CBC  AESA_MODE_OPMODE(1)
#define AESA_MODE_OPMODE_CFB  AESA_MODE_OPMODE(2)
#define AESA_MODE_OPMODE_OFB  AESA_MODE_OPMODE(3)
#define AESA_MODE_OPMODE_CTR  AESA_MODE_OPMODE(4)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
