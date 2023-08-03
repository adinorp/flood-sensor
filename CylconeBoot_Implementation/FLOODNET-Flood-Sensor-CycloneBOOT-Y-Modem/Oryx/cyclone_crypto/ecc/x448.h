/**
 * @file x448.h
 * @brief X448 function implementation
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

#ifndef _X448_H
#define _X448_H

//Dependencies
#include "core/crypto.h"
#include "ecc/curve448.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief X448 working state
 **/

typedef struct
{
   uint32_t k[14];
   uint32_t u[14];
   uint32_t x1[14];
   uint32_t z1[14];
   uint32_t x2[14];
   uint32_t z2[14];
   uint32_t t1[14];
   uint32_t t2[14];
} X448State;


//X448 related functions
error_t x448(uint8_t *r, const uint8_t *k, const uint8_t *u);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
