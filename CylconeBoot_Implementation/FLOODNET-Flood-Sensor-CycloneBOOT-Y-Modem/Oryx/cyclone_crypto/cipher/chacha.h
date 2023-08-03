/**
 * @file chacha.h
 * @brief ChaCha encryption algorithm
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

#ifndef _CHACHA_H
#define _CHACHA_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief ChaCha algorithm context
 **/

typedef struct
{
   uint_t nr;
   uint32_t state[16];
   uint32_t block[16];
   size_t pos;
} ChachaContext;


//ChaCha related functions
error_t chachaInit(ChachaContext *context, uint_t nr, const uint8_t *key,
   size_t keyLen, const uint8_t *nonce, size_t nonceLen);

void chachaCipher(ChachaContext *context, const uint8_t *input,
   uint8_t *output, size_t length);

void chachaProcessBlock(ChachaContext *context);

void chachaDeinit(ChachaContext *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
