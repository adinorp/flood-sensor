/**
 * @file gcm.h
 * @brief Galois/Counter Mode (GCM)
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

#ifndef _GCM_H
#define _GCM_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief GCM context
 **/

typedef struct
{
   const CipherAlgo *cipherAlgo; ///<Cipher algorithm
   void *cipherContext;          ///<Cipher algorithm context
   uint32_t m[16][4];            ///<Precalculated table
} GcmContext;


//GCM related functions
error_t gcmInit(GcmContext *context, const CipherAlgo *cipherAlgo,
   void *cipherContext);

error_t gcmEncrypt(GcmContext *context, const uint8_t *iv,
   size_t ivLen, const uint8_t *a, size_t aLen, const uint8_t *p,
   uint8_t *c, size_t length, uint8_t *t, size_t tLen);

error_t gcmDecrypt(GcmContext *context, const uint8_t *iv,
   size_t ivLen, const uint8_t *a, size_t aLen, const uint8_t *c,
   uint8_t *p, size_t length, const uint8_t *t, size_t tLen);

void gcmMul(GcmContext *context, uint8_t *x);
void gcmXorBlock(uint8_t *x, const uint8_t *a, const uint8_t *b, size_t n);
void gcmIncCounter(uint8_t *x);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
