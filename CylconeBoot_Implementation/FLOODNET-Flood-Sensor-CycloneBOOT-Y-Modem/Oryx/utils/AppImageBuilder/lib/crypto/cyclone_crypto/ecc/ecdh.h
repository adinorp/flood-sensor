/**
 * @file ecdh.h
 * @brief ECDH (Elliptic Curve Diffie-Hellman) key exchange
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

#ifndef _ECDH_H
#define _ECDH_H

//Dependencies
#include "core/crypto.h"
#include "ecc/ec.h"

//X25519 supported?
#if (X25519_SUPPORT == ENABLED)
   #include "ecc/x25519.h"
#endif

//X448 supported?
#if (X448_SUPPORT == ENABLED)
   #include "ecc/x448.h"
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief ECDH context
 **/

typedef struct
{
   EcDomainParameters params; ///<EC domain parameters
   EcPrivateKey da;           ///<One's own EC private key
   EcPublicKey qa;            ///<One's own EC public key
   EcPublicKey qb;            ///<Peer's EC public key
} EcdhContext;


//ECDH related functions
void ecdhInit(EcdhContext *context);
void ecdhFree(EcdhContext *context);

error_t ecdhGenerateKeyPair(EcdhContext *context, const PrngAlgo *prngAlgo,
   void *prngContext);

error_t ecdhCheckPublicKey(const EcDomainParameters *params, EcPoint *publicKey);

error_t ecdhComputeSharedSecret(EcdhContext *context,
   uint8_t *output, size_t outputSize, size_t *outputLen);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
