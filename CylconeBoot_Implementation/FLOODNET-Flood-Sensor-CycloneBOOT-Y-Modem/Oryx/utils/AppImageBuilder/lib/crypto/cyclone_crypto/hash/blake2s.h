/**
 * @file blake2s.h
 * @brief BLAKE2 cryptographic hash and MAC (BLAKE2s variant)
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

#ifndef _BLAKE2S_H
#define _BLAKE2S_H

//Dependencies
#include "core/crypto.h"

//BLAKE2s block size
#define BLAKE2S_BLOCK_SIZE 64

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief BLAKE2s algorithm context
 **/

typedef struct
{
   union
   {
      uint32_t h[8];
      uint8_t digest[32];
   };
   union
   {
      uint32_t m[16];
      uint8_t buffer[64];
   };
   size_t size;
   uint32_t totalSize[2];
   size_t digestSize;
} Blake2sContext;


//BLAKE2s related functions
error_t blake2sCompute(const void *key, size_t keyLen, const void *data,
   size_t dataLen, uint8_t *digest, size_t digestLen);

error_t blake2sInit(Blake2sContext *context, const void *key,
   size_t keyLen, size_t digestLen);

void blake2sUpdate(Blake2sContext *context, const void *data, size_t length);
void blake2sFinal(Blake2sContext *context, uint8_t *digest);
void blake2sProcessBlock(Blake2sContext *context, bool_t last);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
