/**
 * @file gmac.h
 * @brief GMAC (Galois Message Authentication Code)
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

#ifndef _GMAC_H
#define _GMAC_H

//Dependencies
#include "core/crypto.h"
#include "cipher/cipher_algorithms.h"

//Precalculated table width, in bits
#ifndef GMAC_TABLE_W
   #define GMAC_TABLE_W 4
#elif (GMAC_TABLE_W != 4 && GMAC_TABLE_W != 8)
   #error GMAC_TABLE_W parameter is not valid
#endif

//4-bit or 8-bit precalculated table?
#if (GMAC_TABLE_W == 4)
   #define GMAC_TABLE_N 16
   #define GMAC_REVERSE_BITS(n) reverseInt4(n)
#else
   #define GMAC_TABLE_N 256
   #define GMAC_REVERSE_BITS(n) reverseInt8(n)
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief GMAC algorithm context
 **/

typedef struct
{
   const CipherAlgo *cipher;
   CipherContext cipherContext;
   uint32_t m[GMAC_TABLE_N][4];
   uint8_t s[16];
   uint8_t buffer[16];
   size_t bufferLength;
   uint64_t totalLength;
   uint8_t mac[16];
} GmacContext;


//GMAC related functions
error_t gmacCompute(const CipherAlgo *cipher, const void *key, size_t keyLen,
   const uint8_t *iv, size_t ivLen, const void *data, size_t dataLen,
   uint8_t *mac, size_t macLen);

error_t gmacInit(GmacContext *context, const CipherAlgo *cipher,
   const void *key, size_t keyLen);

error_t gmacReset(GmacContext *context, const uint8_t *iv, size_t ivLen);
void gmacUpdate(GmacContext *context, const void *data, size_t dataLen);
error_t gmacFinal(GmacContext *context, uint8_t *mac, size_t macLen);

void gmacMul(GmacContext *context, uint8_t *x);
void gmacXorBlock(uint8_t *x, const uint8_t *a, const uint8_t *b, size_t n);
void gmacIncCounter(uint8_t *x);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
