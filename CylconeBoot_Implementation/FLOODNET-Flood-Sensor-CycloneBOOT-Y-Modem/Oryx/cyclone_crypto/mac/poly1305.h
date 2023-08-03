/**
 * @file poly1305.h
 * @brief Poly1305 message-authentication code
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

#ifndef _POLY1305_H
#define _POLY1305_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Poly1305 context
 **/

typedef struct
{
   uint32_t r[4];
   uint32_t s[4];
   uint64_t a[8];
   uint8_t buffer[17];
   size_t size;
} Poly1305Context;


//Poly1305 related functions
void poly1305Init(Poly1305Context *context, const uint8_t *key);
void poly1305Update(Poly1305Context *context, const void *data, size_t length);
void poly1305Final(Poly1305Context *context, uint8_t *tag);

void poly1305ProcessBlock(Poly1305Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
