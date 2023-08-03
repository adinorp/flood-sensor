/**
 * @file shake.h
 * @brief SHAKE128 and SHAKE256 extendable-output functions
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

#ifndef _SHAKE_H
#define _SHAKE_H

//Dependencies
#include "core/crypto.h"
#include "xof/keccak.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHAKE algorithm context
 **/

typedef struct
{
   KeccakContext keccakContext;
} ShakeContext;


//SHAKE related constants
extern const uint8_t shake128Oid[9];
extern const uint8_t shake256Oid[9];

//SHAKE related functions
error_t shakeCompute(uint_t strength, const void *input, size_t inputLen,
   uint8_t *output, size_t outputLen);

error_t shakeInit(ShakeContext *context, uint_t strength);
void shakeAbsorb(ShakeContext *context, const void *input, size_t length);
void shakeFinal(ShakeContext *context);
void shakeSqueeze(ShakeContext *context, uint8_t *output, size_t length);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
