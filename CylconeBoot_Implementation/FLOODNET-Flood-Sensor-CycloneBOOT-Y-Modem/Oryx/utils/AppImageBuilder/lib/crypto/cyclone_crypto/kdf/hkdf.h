/**
 * @file hkdf.h
 * @brief HKDF (HMAC-based Key Derivation Function)
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

#ifndef _HKDF_H
#define _HKDF_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//HKDF related functions
error_t hkdf(const HashAlgo *hash, const uint8_t *ikm, size_t ikmLen,
   const uint8_t *salt, size_t saltLen, const uint8_t *info, size_t infoLen,
   uint8_t *okm, size_t okmLen);

error_t hkdfExtract(const HashAlgo *hash, const uint8_t *ikm, size_t ikmLen,
   const uint8_t *salt, size_t saltLen, uint8_t *prk);

error_t hkdfExpand(const HashAlgo *hash, const uint8_t *prk, size_t prkLen,
   const uint8_t *info, size_t infoLen, uint8_t *okm, size_t okmLen);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
