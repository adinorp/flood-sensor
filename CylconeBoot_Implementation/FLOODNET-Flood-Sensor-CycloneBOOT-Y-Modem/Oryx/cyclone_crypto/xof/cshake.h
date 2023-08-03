/**
 * @file cshake.h
 * @brief cSHAKE128 and cSHAKE256 (customizable SHAKE function)
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

#ifndef _CSHAKE_H
#define _CSHAKE_H

//Dependencies
#include "core/crypto.h"
#include "xof/keccak.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief cSHAKE algorithm context
 **/

typedef struct
{
   size_t nameLen;
   size_t customLen;
   KeccakContext keccakContext;
} CshakeContext;


//cSHAKE related functions
error_t cshakeCompute(uint_t strength, const void *input, size_t inputLen,
   const char_t *name, size_t nameLen, const char_t *custom, size_t customLen,
   uint8_t *output, size_t outputLen);

error_t cshakeInit(CshakeContext *context, uint_t strength, const char_t *name,
   size_t nameLen, const char_t *custom, size_t customLen);

void cshakeAbsorb(CshakeContext *context, const void *input, size_t length);
void cshakeFinal(CshakeContext *context);
void cshakeSqueeze(CshakeContext *context, uint8_t *output, size_t length);

void cshakeLeftEncode(size_t value, uint8_t *buffer, size_t *length);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
