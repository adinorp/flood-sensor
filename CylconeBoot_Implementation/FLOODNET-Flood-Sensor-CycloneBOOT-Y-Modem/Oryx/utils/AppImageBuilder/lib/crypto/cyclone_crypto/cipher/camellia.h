/**
 * @file camellia.h
 * @brief Camellia encryption algorithm
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

#ifndef _CAMELLIA_H
#define _CAMELLIA_H

//Dependencies
#include "core/crypto.h"

//Camellia block size
#define CAMELLIA_BLOCK_SIZE 16
//Common interface for encryption algorithms
#define CAMELLIA_CIPHER_ALGO (&camelliaCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Structure describing subkey generation
 **/

typedef struct
{
   uint8_t index;
   uint8_t key;
   uint8_t shift;
   uint8_t position;
} CamelliaSubkey;


/**
 * @brief Camellia algorithm context
 **/

typedef struct
{
   uint_t nr;
   uint32_t k[16];
   uint32_t ks[68];
} CamelliaContext;


//Camellia related constants
extern const CipherAlgo camelliaCipherAlgo;

//Camellia related functions
error_t camelliaInit(CamelliaContext *context, const uint8_t *key, size_t keyLen);
void camelliaEncryptBlock(CamelliaContext *context, const uint8_t *input, uint8_t *output);
void camelliaDecryptBlock(CamelliaContext *context, const uint8_t *input, uint8_t *output);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
