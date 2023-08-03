/**
 * @file pkcs8_key_format.h
 * @brief PKCS #8 key formatting
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

#ifndef _PKCS8_KEY_FORMAT_H
#define _PKCS8_KEY_FORMAT_H

//Dependencies
#include "core/crypto.h"
#include "pkc/rsa.h"
#include "pkc/dsa.h"
#include "ecc/ec.h"
#include "ecc/eddsa.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Key formatting functions
error_t pkcs8FormatRsaPrivateKey(const RsaPrivateKey *privateKey,
   uint8_t *output, size_t *written);

error_t pkcs8FormatDsaPrivateKey(const DsaPrivateKey *privateKey,
   uint8_t *output, size_t *written);

error_t pkcs8FormatEcPrivateKey(const EcCurveInfo *curveInfo,
   const EcPrivateKey *privateKey, const EcPublicKey *publicKey,
   uint8_t *output, size_t *written);

error_t pkcs8FormatEcPublicKey(const EcCurveInfo *curveInfo,
   const EcPublicKey *publicKey, uint8_t *output, size_t *written);

error_t pkcs8FormatEddsaPrivateKey(const EcCurveInfo *curveInfo,
   const EddsaPrivateKey *privateKey, uint8_t *output, size_t *written);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
