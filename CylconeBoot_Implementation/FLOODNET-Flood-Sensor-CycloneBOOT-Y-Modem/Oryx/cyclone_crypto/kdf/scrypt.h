/**
 * @file scrypt.h
 * @brief scrypt PBKDF (Password-Based Key Derivation Function)
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

#ifndef _SCRYPT_H
#define _SCRYPT_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//scrypt related functions
error_t scrypt(const char_t *password, const uint8_t *salt, size_t saltLen,
   uint_t n, uint_t r, uint_t p, uint8_t *dk, size_t dkLen);

void scryptRoMix(uint_t r, uint8_t *b, uint_t n, uint8_t *v, uint8_t *y);
void scryptBlockMix(uint_t r, uint8_t *b, uint8_t *y);
void scryptXorBlock(uint8_t *x, const uint8_t *a, const uint8_t *b, size_t n);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
