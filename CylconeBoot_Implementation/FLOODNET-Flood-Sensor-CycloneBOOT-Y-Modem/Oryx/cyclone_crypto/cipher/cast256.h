/**
 * @file cast256.h
 * @brief CAST-256 encryption algorithm
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

#ifndef _CAST256_H
#define _CAST256_H

//Dependencies
#include "core/crypto.h"

//CAST-256 block size
#define CAST256_BLOCK_SIZE 16
//Common interface for encryption algorithms
#define CAST256_CIPHER_ALGO (&cast256CipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief CAST-256 algorithm context
 **/

typedef struct
{
   uint32_t km[12][4];
   uint8_t kr[12][4];
} Cast256Context;


//CAST-256 related constants
extern const CipherAlgo cast256CipherAlgo;

//CAST-256 related functions
error_t cast256Init(Cast256Context *context, const uint8_t *key, size_t keyLen);

void cast256EncryptBlock(Cast256Context *context, const uint8_t *input,
   uint8_t *output);

void cast256DecryptBlock(Cast256Context *context, const uint8_t *input,
   uint8_t *output);

void cast256Deinit(Cast256Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
