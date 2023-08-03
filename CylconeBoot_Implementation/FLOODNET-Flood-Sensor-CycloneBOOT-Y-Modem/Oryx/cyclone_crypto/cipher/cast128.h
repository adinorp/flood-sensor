/**
 * @file cast128.h
 * @brief CAST-128 encryption algorithm
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

#ifndef _CAST128_H
#define _CAST128_H

//Dependencies
#include "core/crypto.h"

//CAST-128 block size
#define CAST128_BLOCK_SIZE 8
//Common interface for encryption algorithms
#define CAST128_CIPHER_ALGO (&cast128CipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief CAST-128 algorithm context
 **/

typedef struct
{
   uint_t nr;
   uint32_t km[16];
   uint32_t kr[16];
} Cast128Context;


//CAST-128 related constants
extern const CipherAlgo cast128CipherAlgo;

//CAST-128 related functions
error_t cast128Init(Cast128Context *context, const uint8_t *key, size_t keyLen);

void cast128EncryptBlock(Cast128Context *context, const uint8_t *input,
   uint8_t *output);

void cast128DecryptBlock(Cast128Context *context, const uint8_t *input,
   uint8_t *output);

void cast128Deinit(Cast128Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
