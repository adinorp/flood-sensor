/**
 * @file idea.h
 * @brief IDEA encryption algorithm
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

#ifndef _IDEA_H
#define _IDEA_H

//Dependencies
#include "core/crypto.h"

//IDEA block size
#define IDEA_BLOCK_SIZE 8
//Common interface for encryption algorithms
#define IDEA_CIPHER_ALGO (&ideaCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief IDEA algorithm context
 **/

typedef struct
{
   uint16_t ek[52];
   uint16_t dk[52];
} IdeaContext;


//IDEA related constants
extern const CipherAlgo ideaCipherAlgo;

//IDEA related functions
error_t ideaInit(IdeaContext *context, const uint8_t *key, size_t keyLen);
void ideaEncryptBlock(IdeaContext *context, const uint8_t *input, uint8_t *output);
void ideaDecryptBlock(IdeaContext *context, const uint8_t *input, uint8_t *output);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
