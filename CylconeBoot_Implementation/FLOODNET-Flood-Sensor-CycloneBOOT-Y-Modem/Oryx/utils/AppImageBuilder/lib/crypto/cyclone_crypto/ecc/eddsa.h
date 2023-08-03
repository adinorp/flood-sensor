/**
 * @file eddsa.h
 * @brief EdDSA (Edwards-Curve Digital Signature Algorithm)
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

#ifndef _EDDSA_H
#define _EDDSA_H

//Dependencies
#include "core/crypto.h"
#include "ecc/ec.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief EdDSA public key
 **/

typedef struct
{
   Mpi q; ///<Public key
} EddsaPublicKey;


/**
 * @brief EdDSA private key
 **/

typedef struct
{
   Mpi d;      ///<Private key
   Mpi q;      ///<Public key
   int_t slot; ///<Private key slot
} EddsaPrivateKey;


/**
 * @brief Message chunk descriptor
 **/

typedef struct
{
   const void *buffer;
   size_t length;
} EddsaMessageChunk;


//EdDSA related functions
void eddsaInitPublicKey(EddsaPublicKey *key);
void eddsaFreePublicKey(EddsaPublicKey *key);

void eddsaInitPrivateKey(EddsaPrivateKey *key);
void eddsaFreePrivateKey(EddsaPrivateKey *key);


//C++ guard
#ifdef __cplusplus
}
#endif

//Ed25519 supported?
#if (ED25519_SUPPORT == ENABLED)
   #include "ecc/ed25519.h"
#endif

//Ed448 supported?
#if (ED448_SUPPORT == ENABLED)
   #include "ecc/ed448.h"
#endif

#endif
