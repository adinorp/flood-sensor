/**
 * @file rc6.h
 * @brief RC6-32/20 block cipher
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

#ifndef _RC6_H
#define _RC6_H

//Dependencies
#include "core/crypto.h"

//RC6 block size
#define RC6_BLOCK_SIZE 16
//Maximum length of the encryption key in bytes
#define RC6_MAX_KEY_SIZE 32
//Number of rounds
#define RC6_NB_ROUNDS 20

//Common interface for encryption algorithms
#define RC6_CIPHER_ALGO (&rc6CipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief RC6 algorithm context
 **/

typedef struct
{
   uint32_t l[RC6_MAX_KEY_SIZE / 4];
   uint32_t s[2 * RC6_NB_ROUNDS + 4];
} Rc6Context;


//RC6 related constants
extern const CipherAlgo rc6CipherAlgo;

//RC6 related functions
error_t rc6Init(Rc6Context *context, const uint8_t *key, size_t keyLen);

void rc6EncryptBlock(Rc6Context *context, const uint8_t *input,
   uint8_t *output);

void rc6DecryptBlock(Rc6Context *context, const uint8_t *input,
   uint8_t *output);

void rc6Deinit(Rc6Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
