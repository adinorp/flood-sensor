/**
 * @file cmac.h
 * @brief CMAC (Cipher-based Message Authentication Code)
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

#ifndef _CMAC_H
#define _CMAC_H

//Dependencies
#include "core/crypto.h"
#include "cipher/cipher_algorithms.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief CMAC algorithm context
 **/

typedef struct
{
   const CipherAlgo *cipher;
   CipherContext cipherContext;
   uint8_t k1[MAX_CIPHER_BLOCK_SIZE];
   uint8_t k2[MAX_CIPHER_BLOCK_SIZE];
   uint8_t buffer[MAX_CIPHER_BLOCK_SIZE];
   size_t bufferLength;
   uint8_t mac[MAX_CIPHER_BLOCK_SIZE];
} CmacContext;


//CMAC related functions
error_t cmacCompute(const CipherAlgo *cipher, const void *key, size_t keyLen,
   const void *data, size_t dataLen, uint8_t *mac, size_t macLen);

error_t cmacInit(CmacContext *context, const CipherAlgo *cipher,
   const void *key, size_t keyLen);

void cmacReset(CmacContext *context);
void cmacUpdate(CmacContext *context, const void *data, size_t dataLen);
error_t cmacFinal(CmacContext *context, uint8_t *mac, size_t macLen);

void cmacMul(uint8_t *x, const uint8_t *a, size_t n, uint8_t rb);
void cmacXorBlock(uint8_t *x, const uint8_t *a, const uint8_t *b, size_t n);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
