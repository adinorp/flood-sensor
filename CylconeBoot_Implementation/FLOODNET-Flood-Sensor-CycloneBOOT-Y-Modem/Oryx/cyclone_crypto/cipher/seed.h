/**
 * @file seed.h
 * @brief SEED encryption algorithm
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

#ifndef _SEED_H
#define _SEED_H

//Dependencies
#include "core/crypto.h"

//SEED block size
#define SEED_BLOCK_SIZE 16
//Common interface for encryption algorithms
#define SEED_CIPHER_ALGO (&seedCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SEED algorithm context
 **/

typedef struct
{
   uint32_t ks[32];
} SeedContext;


//SEED related constants
extern const CipherAlgo seedCipherAlgo;

//SEED related functions
error_t seedInit(SeedContext *context, const uint8_t *key, size_t keyLen);

void seedEncryptBlock(SeedContext *context, const uint8_t *input,
   uint8_t *output);

void seedDecryptBlock(SeedContext *context, const uint8_t *input,
   uint8_t *output);

void seedDeinit(SeedContext *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
