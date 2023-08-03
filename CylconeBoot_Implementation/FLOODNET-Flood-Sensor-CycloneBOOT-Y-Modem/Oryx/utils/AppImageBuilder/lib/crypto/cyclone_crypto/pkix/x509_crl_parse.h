/**
 * @file x509_crl_parse.h
 * @brief CRL (Certificate Revocation List)
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

#ifndef _X509_CRL_PARSE_H
#define _X509_CRL_PARSE_H

//Dependencies
#include "core/crypto.h"
#include "pkix/x509_common.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//CRL related functions
error_t x509ParseCrl(const uint8_t *data, size_t length,
   X509CrlInfo *crlInfo);

error_t x509ParseTbsCertList(const uint8_t *data, size_t length,
   size_t *totalLength, X509TbsCertList *tbsCertList);

error_t x509ParseCrlVersion(const uint8_t *data, size_t length,
   size_t *totalLength, X509Version *version);

error_t x509ParseRevokedCertificates(const uint8_t *data, size_t length,
   size_t *totalLength, X509TbsCertList *tbsCertList);

error_t x509ParseRevokedCertificate(const uint8_t *data, size_t length,
   size_t *totalLength, X509RevokedCertificate *revokedCertificate);

error_t x509ParseCrlExtensions(const uint8_t *data, size_t length,
   size_t *totalLength, X509CrlExtensions *crlExtensions);

error_t x509ParseCrlNumber(bool_t critical, const uint8_t *data,
   size_t length, X509CrlNumber *crlNumber);

error_t x509ParseDeltaCrlIndicator(bool_t critical, const uint8_t *data,
   size_t length, X509DeltaCrlIndicator *deltaCrlIndicator);

error_t x509ParseIssuingDistrPoint(bool_t critical, const uint8_t *data,
   size_t length, X509IssuingDistrPoint *issuingDistrPoint);

error_t x509ParseCrlEntryExtensions(const uint8_t *data, size_t length,
   size_t *totalLength, X509CrlEntryExtensions *crlEntryExtensions);

error_t x509ParseReasonCode(bool_t critical, const uint8_t *data,
   size_t length, X509CrlReason *reasonCode);

error_t x509ParseInvalidityDate(bool_t critical, const uint8_t *data,
   size_t length, X509InvalidityDate *invalidityDate);

error_t x509ParseCertificateIssuer(bool_t critical, const uint8_t *data,
   size_t length, X509CertificateIssuer *certificateIssuer);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
