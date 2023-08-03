/**
 * @file ecdsa.h
 * @brief ECDSA (Elliptic Curve Digital Signature Algorithm)
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

#ifndef _ECDSA_H
#define _ECDSA_H

//Dependencies
#include "core/crypto.h"
#include "ecc/ec.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief ECDSA signature
 **/

typedef struct
{
   Mpi r;
   Mpi s;
} EcdsaSignature;


//ECDSA related constants
extern const uint8_t ECDSA_WITH_SHA1_OID[7];
extern const uint8_t ECDSA_WITH_SHA224_OID[8];
extern const uint8_t ECDSA_WITH_SHA256_OID[8];
extern const uint8_t ECDSA_WITH_SHA384_OID[8];
extern const uint8_t ECDSA_WITH_SHA512_OID[8];
extern const uint8_t ECDSA_WITH_SHA3_224_OID[9];
extern const uint8_t ECDSA_WITH_SHA3_256_OID[9];
extern const uint8_t ECDSA_WITH_SHA3_384_OID[9];
extern const uint8_t ECDSA_WITH_SHA3_512_OID[9];

//ECDSA related functions
void ecdsaInitSignature(EcdsaSignature *signature);
void ecdsaFreeSignature(EcdsaSignature *signature);

error_t ecdsaWriteSignature(const EcdsaSignature *signature, uint8_t *data,
   size_t *length);

error_t ecdsaReadSignature(const uint8_t *data, size_t length,
   EcdsaSignature *signature);

error_t ecdsaGenerateSignature(const PrngAlgo *prngAlgo, void *prngContext,
   const EcDomainParameters *params, const EcPrivateKey *privateKey,
   const uint8_t *digest, size_t digestLen, EcdsaSignature *signature);

error_t ecdsaVerifySignature(const EcDomainParameters *params,
   const EcPublicKey *publicKey, const uint8_t *digest, size_t digestLen,
   const EcdsaSignature *signature);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
