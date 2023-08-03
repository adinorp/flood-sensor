/**
 * @file rc2.h
 * @brief RC2 block cipher
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

#ifndef _RC2_H
#define _RC2_H

//Dependencies
#include "core/crypto.h"

//RC2 block size
#define RC2_BLOCK_SIZE 8
//Common interface for encryption algorithms
#define RC2_CIPHER_ALGO (&rc2CipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief RC2 algorithm context
 **/

typedef struct
{
   union
   {
      uint16_t k[64];
      uint8_t l[128];
   };
} Rc2Context;


//RC2 related constants
extern const CipherAlgo rc2CipherAlgo;

//RC2 related functions
error_t rc2Init(Rc2Context *context, const uint8_t *key, size_t keyLen);

error_t rc2InitEx(Rc2Context *context, const uint8_t *key, size_t keyLen,
   uint_t effectiveKeyLen);

void rc2EncryptBlock(Rc2Context *context, const uint8_t *input,
   uint8_t *output);

void rc2DecryptBlock(Rc2Context *context, const uint8_t *input,
   uint8_t *output);

void rc2Deinit(Rc2Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
