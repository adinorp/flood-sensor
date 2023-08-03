/**
 * @file kmac.h
 * @brief KMAC (Keccak Message Authentication Code)
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

#ifndef _KMAC_H
#define _KMAC_H

//Dependencies
#include "core/crypto.h"
#include "xof/cshake.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief KMAC algorithm context
 **/

typedef struct
{
   CshakeContext cshakeContext;
} KmacContext;


//KMAC related constants
extern const uint8_t kmac128Oid[9];
extern const uint8_t kmac256Oid[9];

//KMAC related functions
error_t kmacCompute(uint_t strength, const void *key, size_t keyLen,
   const void *data, size_t dataLen, const char_t *custom, size_t customLen,
   uint8_t *mac, size_t macLen);

error_t kmacInit(KmacContext *context, uint_t strength, const void *key,
   size_t keyLen, const char_t *custom, size_t customLen);

void kmacUpdate(KmacContext *context, const void *data, size_t dataLen);
error_t kmacFinal(KmacContext *context, uint8_t *mac, size_t macLen);

void kmacRightEncode(size_t value, uint8_t *buffer, size_t *length);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
