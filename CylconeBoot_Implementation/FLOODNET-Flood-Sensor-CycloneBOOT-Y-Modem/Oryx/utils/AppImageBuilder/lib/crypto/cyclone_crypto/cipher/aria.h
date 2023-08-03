/**
 * @file aria.h
 * @brief ARIA encryption algorithm
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

#ifndef _ARIA_H
#define _ARIA_H

//Dependencies
#include "core/crypto.h"

//ARIA block size
#define ARIA_BLOCK_SIZE 16
//Common interface for encryption algorithms
#define ARIA_CIPHER_ALGO (&ariaCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief ARIA algorithm context
 **/

typedef struct
{
   uint_t nr;
   uint32_t k[16];
   uint32_t ek[68];
   uint32_t dk[68];
} AriaContext;


//ARIA related constants
extern const CipherAlgo ariaCipherAlgo;

//ARIA related functions
error_t ariaInit(AriaContext *context, const uint8_t *key, size_t keyLen);
void ariaEncryptBlock(AriaContext *context, const uint8_t *input, uint8_t *output);
void ariaDecryptBlock(AriaContext *context, const uint8_t *input, uint8_t *output);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
