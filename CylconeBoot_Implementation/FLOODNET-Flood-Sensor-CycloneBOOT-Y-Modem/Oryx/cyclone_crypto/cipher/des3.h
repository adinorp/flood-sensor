/**
 * @file des3.h
 * @brief Triple DES (Triple Data Encryption Algorithm)
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

#ifndef _DES3_H
#define _DES3_H

//Dependencies
#include "core/crypto.h"
#include "cipher/des.h"

//Application specific context
#ifndef DES3_PRIVATE_CONTEXT
   #define DES3_PRIVATE_CONTEXT
#endif

//Triple DES block size
#define DES3_BLOCK_SIZE 8
//Common interface for encryption algorithms
#define DES3_CIPHER_ALGO (&des3CipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Triple DES algorithm context
 **/

typedef struct
{
   DesContext k1;
   DesContext k2;
   DesContext k3;
   DES3_PRIVATE_CONTEXT
} Des3Context;


//Triple DES related constants
extern const CipherAlgo des3CipherAlgo;

//Triple DES related functions
error_t des3Init(Des3Context *context, const uint8_t *key, size_t keyLen);

void des3EncryptBlock(Des3Context *context, const uint8_t *input,
   uint8_t *output);

void des3DecryptBlock(Des3Context *context, const uint8_t *input,
   uint8_t *output);

void des3Deinit(Des3Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
