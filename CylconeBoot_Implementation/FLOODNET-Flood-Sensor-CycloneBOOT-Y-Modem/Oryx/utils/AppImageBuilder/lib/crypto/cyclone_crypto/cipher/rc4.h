/**
 * @file rc4.h
 * @brief RC4 encryption algorithm
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

#ifndef _RC4_H
#define _RC4_H

//Dependencies
#include "core/crypto.h"

//Common interface for encryption algorithms
#define RC4_CIPHER_ALGO (&rc4CipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief RC4 algorithm context
 **/

typedef struct
{
   uint_t i;
   uint_t j;
   uint8_t s[256];
} Rc4Context;


//RC4 related constants
extern const CipherAlgo rc4CipherAlgo;

//RC4 related functions
error_t rc4Init(Rc4Context *context, const uint8_t *key, size_t length);
void rc4Cipher(Rc4Context *context, const uint8_t *input, uint8_t *output, size_t length);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
