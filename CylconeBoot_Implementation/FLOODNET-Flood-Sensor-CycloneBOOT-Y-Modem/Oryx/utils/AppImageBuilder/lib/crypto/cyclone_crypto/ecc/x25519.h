/**
 * @file x25519.h
 * @brief X25519 function implementation
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

#ifndef _X25519_H
#define _X25519_H

//Dependencies
#include "core/crypto.h"
#include "ecc/curve25519.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief X25519 working state
 **/

typedef struct
{
   uint32_t k[8];
   uint32_t u[8];
   uint32_t x1[8];
   uint32_t z1[8];
   uint32_t x2[8];
   uint32_t z2[8];
   uint32_t t1[8];
   uint32_t t2[8];
} X25519State;


//X25519 related functions
error_t x25519(uint8_t *r, const uint8_t *k, const uint8_t *u);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
