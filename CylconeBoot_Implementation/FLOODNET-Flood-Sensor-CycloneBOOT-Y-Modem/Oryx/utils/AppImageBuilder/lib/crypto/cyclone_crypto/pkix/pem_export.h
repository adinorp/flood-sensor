/**
 * @file pem_export.h
 * @brief PEM file export functions
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

#ifndef _PEM_EXPORT_H
#define _PEM_EXPORT_H

//Dependencies
#include "core/crypto.h"
#include "pkc/dh.h"
#include "pkc/rsa.h"
#include "pkc/dsa.h"
#include "ecc/ec.h"
#include "ecc/eddsa.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//PEM related functions
error_t pemExportCertificate(const uint8_t *cert, size_t certLen,
   char_t *output, size_t *written);

error_t pemExportCrl(const uint8_t *crl, size_t crlLen,
   char_t *output, size_t *written);

error_t pemExportCsr(const uint8_t *csr, size_t csrLen,
   char_t *output, size_t *written);

error_t pemExportRsaPublicKey(const RsaPublicKey *publicKey,
   char_t *output, size_t *written);

error_t pemExportRsaPrivateKey(const RsaPrivateKey *privateKey,
   char_t *output, size_t *written);

error_t pemExportRsaPssPublicKey(const RsaPublicKey *publicKey,
   char_t *output, size_t *written);

error_t pemExportRsaPssPrivateKey(const RsaPrivateKey *privateKey,
   char_t *output, size_t *written);

error_t pemExportDsaPublicKey(const DsaPublicKey *publicKey,
   char_t *output, size_t *written);

error_t pemExportDsaPrivateKey(const DsaPrivateKey *privateKey,
   char_t *output, size_t *written);

error_t pemExportEcParameters(const EcCurveInfo *curveInfo,
   char_t *output, size_t *written);

error_t pemExportEcPublicKey(const EcCurveInfo *curveInfo,
   const EcPublicKey *publicKey, char_t *output, size_t *written);

error_t pemExportEcPrivateKey(const EcCurveInfo *curveInfo,
   const EcPrivateKey *privateKey, const EcPublicKey *publicKey,
   char_t *output, size_t *written);

error_t pemExportEddsaPublicKey(const EcCurveInfo *curveInfo,
   const EddsaPublicKey *publicKey, char_t *output, size_t *written);

error_t pemExportEddsaPrivateKey(const EcCurveInfo *curveInfo,
   const EddsaPrivateKey *privateKey, char_t *output, size_t *written);

error_t pemEncodeFile(const void *input, size_t inputLen, const char_t *label,
   char_t *output, size_t *outputLen);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
