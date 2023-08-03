/**
 * @file chacha20_poly1305.h
 * @brief ChaCha20Poly1305 AEAD
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

#ifndef _CHACHA20_POLY1305_H
#define _CHACHA20_POLY1305_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//ChaCha20Poly1305 related functions
error_t chacha20Poly1305Encrypt(const uint8_t *k, size_t kLen,
   const uint8_t *n, size_t nLen, const uint8_t *a, size_t aLen,
   const uint8_t *p, uint8_t *c, size_t length, uint8_t *t, size_t tLen);

error_t chacha20Poly1305Decrypt(const uint8_t *k, size_t kLen,
   const uint8_t *n, size_t nLen, const uint8_t *a, size_t aLen,
   const uint8_t *c, uint8_t *p, size_t length, const uint8_t *t, size_t tLen);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
