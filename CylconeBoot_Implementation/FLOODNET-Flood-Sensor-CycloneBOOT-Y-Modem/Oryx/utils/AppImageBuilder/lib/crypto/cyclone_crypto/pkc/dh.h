/**
 * @file dh.h
 * @brief Diffie-Hellman key exchange
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

#ifndef _DH_H
#define _DH_H

//Dependencies
#include "core/crypto.h"
#include "mpi/mpi.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Diffie-Hellman parameters
 **/

typedef struct
{
   Mpi p; ///<Prime modulus
   Mpi g; ///<Generator
} DhParameters;


/**
 * @brief Diffie-Hellman context
 **/

typedef struct
{
   DhParameters params; //Diffie-Hellman parameters
   Mpi xa;              ///<One's own private value
   Mpi ya;              ///<One's own public value
   Mpi yb;              ///<Peer's public value
} DhContext;


//Diffie-Hellman related functions
void dhInit(DhContext *context);
void dhFree(DhContext *context);

error_t dhGenerateKeyPair(DhContext *context,
   const PrngAlgo *prngAlgo, void *prngContext);

error_t dhCheckPublicKey(DhParameters *params, const Mpi *publicKey);

error_t dhComputeSharedSecret(DhContext *context,
   uint8_t *output, size_t outputSize, size_t *outputLen);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
