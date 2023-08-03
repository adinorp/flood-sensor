/**
 * @file mars.h
 * @brief MARS encryption algorithm
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

#ifndef _MARS_H
#define _MARS_H

//Dependencies
#include "core/crypto.h"

//MARS block size
#define MARS_BLOCK_SIZE 16
//Common interface for encryption algorithms
#define MARS_CIPHER_ALGO (&marsCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief MARS algorithm context
 **/

typedef struct
{
   uint32_t k[40];
} MarsContext;


//MARS related constants
extern const CipherAlgo marsCipherAlgo;

//MARS related functions
error_t marsInit(MarsContext *context, const uint8_t *key, size_t keyLen);

void marsEncryptBlock(MarsContext *context, const uint8_t *input,
   uint8_t *output);

void marsDecryptBlock(MarsContext *context, const uint8_t *input,
   uint8_t *output);

void marsDeinit(MarsContext *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
