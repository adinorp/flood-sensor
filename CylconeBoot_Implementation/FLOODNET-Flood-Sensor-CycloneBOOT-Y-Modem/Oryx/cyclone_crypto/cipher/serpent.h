/**
 * @file serpent.h
 * @brief Serpent encryption algorithm
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

#ifndef _SERPENT_H
#define _SERPENT_H

//Dependencies
#include "core/crypto.h"

//Serpent block size
#define SERPENT_BLOCK_SIZE 16
//Common interface for encryption algorithms
#define SERPENT_CIPHER_ALGO (&serpentCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Serpent algorithm context
 **/

typedef struct
{
   uint32_t k[33][4];
} SerpentContext;


//Serpent related constants
extern const CipherAlgo serpentCipherAlgo;

//Serpent related functions
error_t serpentInit(SerpentContext *context, const uint8_t *key, size_t keyLen);

void serpentEncryptBlock(SerpentContext *context, const uint8_t *input,
   uint8_t *output);

void serpentDecryptBlock(SerpentContext *context, const uint8_t *input,
   uint8_t *output);

void serpentDeinit(SerpentContext *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
