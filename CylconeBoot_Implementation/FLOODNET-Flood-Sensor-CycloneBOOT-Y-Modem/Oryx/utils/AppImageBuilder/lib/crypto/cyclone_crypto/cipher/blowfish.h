/**
 * @file blowfish.h
 * @brief Blowfish encryption algorithm
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

#ifndef _BLOWFISH_H
#define _BLOWFISH_H

//Dependencies
#include "core/crypto.h"

//Blowfish block size
#define BLOWFISH_BLOCK_SIZE 8
//Common interface for encryption algorithms
#define BLOWFISH_CIPHER_ALGO (&blowfishCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Blowfish algorithm context
 **/

typedef struct
{
   uint32_t p[18];
   uint32_t s1[256];
   uint32_t s2[256];
   uint32_t s3[256];
   uint32_t s4[256];
} BlowfishContext;


//Blowfish related constants
extern const CipherAlgo blowfishCipherAlgo;

//Blowfish related functions
error_t blowfishInit(BlowfishContext *context, const uint8_t *key,
   size_t keyLen);

error_t blowfishInitState(BlowfishContext *context);

error_t blowfishExpandKey(BlowfishContext *context, const uint8_t *salt,
   size_t saltLen, const uint8_t *key, size_t keyLen);

void blowfishEncryptBlock(BlowfishContext *context, const uint8_t *input,
   uint8_t *output);

void blowfishDecryptBlock(BlowfishContext *context, const uint8_t *input,
   uint8_t *output);

void blowfishXorBlock(uint8_t *data, const uint8_t *salt, size_t saltLen,
   size_t *saltIndex);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
