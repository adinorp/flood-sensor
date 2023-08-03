/**
 * @file x509_csr_create.h
 * @brief CSR (Certificate Signing Request) generation
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

#ifndef _X509_CSR_CREATE_H
#define _X509_CSR_CREATE_H

//Dependencies
#include "core/crypto.h"
#include "pkix/x509_common.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//CSR related functions
error_t x509CreateCsr(const PrngAlgo *prngAlgo, void *prngContext,
   const X509CertRequestInfo *certReqInfo, const void *subjectPublicKey,
   const X509SignatureAlgoId *signatureAlgo, const void *signerPrivateKey,
   uint8_t *output, size_t *written);

error_t x509FormatCertRequestInfo(const X509CertRequestInfo *certReqInfo,
   const void *publicKey, uint8_t *output, size_t *written);

error_t x509FormatAttributes(const X509Attributes *attributes,
   uint8_t *output, size_t *written);

error_t x509FormatChallengePassword(const X509ChallengePassword *challengePwd,
   uint8_t *output, size_t *written);

error_t x509FormatExtensionRequest(const X509Extensions *extensionReq,
   uint8_t *output, size_t *written);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
