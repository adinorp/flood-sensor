/**
 * @file curve448.h
 * @brief Curve448 elliptic curve (constant-time implementation)
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

#ifndef _CURVE448_H
#define _CURVE448_H

//Dependencies
#include "core/crypto.h"

//Length of the elliptic curve
#define CURVE448_BIT_LEN 448
#define CURVE448_BYTE_LEN 56
#define CURVE448_WORD_LEN 14

//A24 constant
#define CURVE448_A24 39082

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Curve448 related functions
void curve448SetInt(uint32_t *a, uint32_t b);
void curve448Add(uint32_t *r, const uint32_t *a, const uint32_t *b);
void curve448AddInt(uint32_t *r, const uint32_t *a, uint32_t b);
void curve448Sub(uint32_t *r, const uint32_t *a, const uint32_t *b);
void curve448SubInt(uint32_t *r, const uint32_t *a, uint32_t b);
void curve448Mul(uint32_t *r, const uint32_t *a, const uint32_t *b);
void curve448MulInt(uint32_t *r, const uint32_t *a, uint32_t b);
void curve448Red(uint32_t *r, const uint32_t *a, uint32_t h);
void curve448Sqr(uint32_t *r, const uint32_t *a);
void curve448Pwr2(uint32_t *r, const uint32_t *a, uint_t n);
void curve448Inv(uint32_t *r, const uint32_t *a);

uint32_t curve448Sqrt(uint32_t *r, const uint32_t *a, const uint32_t *b);

void curve448Copy(uint32_t *a, const uint32_t *b);
void curve448Swap(uint32_t *a, uint32_t *b, uint32_t c);

void curve448Select(uint32_t *r, const uint32_t *a, const uint32_t *b,
   uint32_t c);

uint32_t curve448Comp(const uint32_t *a, const uint32_t *b);

void curve448Import(uint32_t *a, const uint8_t *data);
void curve448Export(uint32_t *a, uint8_t *data);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
