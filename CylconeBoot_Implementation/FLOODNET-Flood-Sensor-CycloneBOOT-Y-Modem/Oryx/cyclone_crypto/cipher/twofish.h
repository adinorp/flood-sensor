/**
 * @file twofish.h
 * @brief Twofish encryption algorithm
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

#ifndef _TWOFISH_H
#define _TWOFISH_H

//Dependencies
#include "core/crypto.h"

//Twofish block size
#define TWOFISH_BLOCK_SIZE 16
//Common interface for encryption algorithms
#define TWOFISH_CIPHER_ALGO (&twofishCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Twofish algorithm context
 **/

typedef struct
{
   uint32_t k[40];
   uint32_t s1[256];
   uint32_t s2[256];
   uint32_t s3[256];
   uint32_t s4[256];
} TwofishContext;


//Twofish related constants
extern const CipherAlgo twofishCipherAlgo;

//Twofish related functions
error_t twofishInit(TwofishContext *context, const uint8_t *key, size_t keyLen);

void twofishEncryptBlock(TwofishContext *context, const uint8_t *input,
   uint8_t *output);

void twofishDecryptBlock(TwofishContext *context, const uint8_t *input,
   uint8_t *output);

void twofishDeinit(TwofishContext *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
