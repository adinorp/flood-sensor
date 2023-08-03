/**
 * @file present.h
 * @brief PRESENT encryption algorithm
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

#ifndef _PRESENT_H
#define _PRESENT_H

//Dependencies
#include "core/crypto.h"

//PRESENT block size
#define PRESENT_BLOCK_SIZE 8
//Common interface for encryption algorithms
#define PRESENT_CIPHER_ALGO (&presentCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief PRESENT algorithm context
 **/

typedef struct
{
   uint64_t ks[32];
} PresentContext;


//PRESENT related constants
extern const CipherAlgo presentCipherAlgo;

//PRESENT related functions
error_t presentInit(PresentContext *context, const uint8_t *key,
   size_t keyLen);

void presentEncryptBlock(PresentContext *context, const uint8_t *input,
   uint8_t *output);

void presentDecryptBlock(PresentContext *context, const uint8_t *input,
   uint8_t *output);

void presentDeinit(PresentContext *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
