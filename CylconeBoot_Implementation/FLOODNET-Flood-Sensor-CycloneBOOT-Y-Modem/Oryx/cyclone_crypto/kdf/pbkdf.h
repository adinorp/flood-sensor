/**
 * @file pbkdf.h
 * @brief PBKDF (Password-Based Key Derivation Function)
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

#ifndef _PBKDF_H
#define _PBKDF_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//PBKDF related constants
extern const uint8_t PBKDF2_OID[9];

//PBKDF related functions
error_t pbkdf1(const HashAlgo *hash, const uint8_t *p, size_t pLen,
   const uint8_t *s, size_t sLen, uint_t c, uint8_t *dk, size_t dkLen);

error_t pbkdf2(const HashAlgo *hash, const uint8_t *p, size_t pLen,
   const uint8_t *s, size_t sLen, uint_t c, uint8_t *dk, size_t dkLen);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
