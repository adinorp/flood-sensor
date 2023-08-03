/**
 * @file x509_key_parse.h
 * @brief Parsing of ASN.1 encoded keys
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

#ifndef _X509_KEY_PARSE_H
#define _X509_KEY_PARSE_H

//Dependencies
#include "core/crypto.h"
#include "pkix/x509_common.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Key parsing functions
error_t x509ParseSubjectPublicKeyInfo(const uint8_t *data, size_t length,
   size_t *totalLength, X509SubjectPublicKeyInfo *subjectPublicKeyInfo);

error_t x509ParseAlgorithmIdentifier(const uint8_t *data, size_t length,
   size_t *totalLength, X509SubjectPublicKeyInfo *subjectPublicKeyInfo);

error_t x509ParseRsaPublicKey(const uint8_t *data, size_t length,
   X509RsaPublicKey *rsaPublicKey);

error_t x509ParseRsaPssParameters(const uint8_t *data, size_t length,
   X509RsaPssParameters *rsaPssParams);

error_t x509ParseRsaPssHashAlgo(const uint8_t *data, size_t length,
   X509RsaPssParameters *rsaPssParams);

error_t x509ParseRsaPssMaskGenAlgo(const uint8_t *data, size_t length,
   X509RsaPssParameters *rsaPssParams);

error_t x509ParseRsaPssMaskGenHashAlgo(const uint8_t *data, size_t length,
   X509RsaPssParameters *rsaPssParams);

error_t x509ParseRsaPssSaltLength(const uint8_t *data, size_t length,
   X509RsaPssParameters *rsaPssParams);

error_t x509ParseDsaPublicKey(const uint8_t *data, size_t length,
   X509DsaPublicKey *dsaPublicKey);

error_t x509ParseDsaParameters(const uint8_t *data, size_t length,
   X509DsaParameters *dsaParams);

error_t x509ParseEcPublicKey(const uint8_t *data, size_t length,
   X509EcPublicKey *ecPublicKey);

error_t x509ParseEcParameters(const uint8_t *data, size_t length,
   X509EcParameters *ecParams);

error_t x509ImportRsaPublicKey(const X509SubjectPublicKeyInfo *publicKeyInfo,
   RsaPublicKey *publicKey);

error_t x509ImportDsaPublicKey(const X509SubjectPublicKeyInfo *publicKeyInfo,
   DsaPublicKey *publicKey);

error_t x509ImportEcPublicKey(const X509SubjectPublicKeyInfo *publicKeyInfo,
   EcPublicKey *publicKey);

error_t x509ImportEcParameters(const X509EcParameters *ecParams,
   EcDomainParameters *params);

error_t x509ImportEddsaPublicKey(const X509SubjectPublicKeyInfo *publicKeyInfo,
   EddsaPublicKey *publicKey);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
