/**
 * @file eddsa.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL CRYPTO_TRACE_LEVEL

//Dependencies
#include "core/crypto.h"
#include "ecc/eddsa.h"
#include "mpi/mpi.h"
#include "debug.h"

//Check crypto library configuration
#if (ED25519_SUPPORT == ENABLED || ED448_SUPPORT == ENABLED)


/**
 * @brief Initialize an EdDSA public key
 * @param[in] key Pointer to the EdDSA public key to initialize
 **/

void eddsaInitPublicKey(EddsaPublicKey *key)
{
   //Initialize multiple precision integer
   mpiInit(&key->q);
}


/**
 * @brief Release an EdDSA public key
 * @param[in] key Pointer to the EdDSA public key to free
 **/

void eddsaFreePublicKey(EddsaPublicKey *key)
{
   //Free multiple precision integer
   mpiFree(&key->q);
}


/**
 * @brief Initialize an EdDSA private key
 * @param[in] key Pointer to the EdDSA private key to initialize
 **/

void eddsaInitPrivateKey(EddsaPrivateKey *key)
{
   //Initialize multiple precision integers
   mpiInit(&key->d);
   mpiInit(&key->q);

   //Initialize private key slot
   key->slot = -1;
}


/**
 * @brief Release an EdDSA private key
 * @param[in] key Pointer to the EdDSA public key to free
 **/

void eddsaFreePrivateKey(EddsaPrivateKey *key)
{
   //Free multiple precision integers
   mpiFree(&key->d);
   mpiFree(&key->q);
}

#endif
