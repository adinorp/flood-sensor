/**
 * @file xts.h
 * @brief XEX-based tweaked-codebook mode with ciphertext stealing (XTS)
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

#ifndef _XTS_H
#define _XTS_H

//Dependencies
#include "core/crypto.h"
#include "cipher/cipher_algorithms.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief XTS context
 **/

typedef struct
{
   const CipherAlgo *cipherAlgo;
   CipherContext cipherContext1;
   CipherContext cipherContext2;
} XtsContext;


//XTS related functions
error_t xtsInit(XtsContext *context, const CipherAlgo *cipherAlgo,
   const void *key, size_t keyLen);

error_t xtsEncrypt(XtsContext *context, const uint8_t *i, const uint8_t *p,
   uint8_t *c, size_t length);

error_t xtsDecrypt(XtsContext *context, const uint8_t *i, const uint8_t *c,
   uint8_t *p, size_t length);

void xtsMul(uint8_t *x, const uint8_t *a);
void xtsXorBlock(uint8_t *x, const uint8_t *a, const uint8_t *b);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
