/**
 * @file trivium.h
 * @brief Trivium stream cipher
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

#ifndef _TRIVIUM_H
#define _TRIVIUM_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Trivium algorithm context
 **/

typedef struct
{
   uint8_t s[36];
} TriviumContext;


//Trivium related functions
error_t triviumInit(TriviumContext *context, const uint8_t *key,
   size_t keyLen, const uint8_t *iv, size_t ivLen);

void triviumCipher(TriviumContext *context, const uint8_t *input,
   uint8_t *output, size_t length);

uint8_t triviumGenerateBit(TriviumContext *context);
uint8_t triviumGenerateByte(TriviumContext *context);

void triviumDeinit(TriviumContext *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
