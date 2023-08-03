/**
 * @file curve25519.h
 * @brief Curve25519 elliptic curve (constant-time implementation)
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

#ifndef _CURVE25519_H
#define _CURVE25519_H

//Dependencies
#include "core/crypto.h"

//Length of the elliptic curve
#define CURVE25519_BIT_LEN 255
#define CURVE25519_BYTE_LEN 32
#define CURVE25519_WORD_LEN 8

//A24 constant
#define CURVE25519_A24 121666

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Curve25519 related functions
void curve25519SetInt(uint32_t *a, uint32_t b);
void curve25519Add(uint32_t *r, const uint32_t *a, const uint32_t *b);
void curve25519AddInt(uint32_t *r, const uint32_t *a, uint32_t b);
void curve25519Sub(uint32_t *r, const uint32_t *a, const uint32_t *b);
void curve25519SubInt(uint32_t *r, const uint32_t *a, uint32_t b);
void curve25519Mul(uint32_t *r, const uint32_t *a, const uint32_t *b);
void curve25519MulInt(uint32_t *r, const uint32_t *a, uint32_t b);
void curve25519Red(uint32_t *r, const uint32_t *a);
void curve25519Sqr(uint32_t *r, const uint32_t *a);
void curve25519Pwr2(uint32_t *r, const uint32_t *a, uint_t n);
void curve25519Inv(uint32_t *r, const uint32_t *a);

uint32_t curve25519Sqrt(uint32_t *r, const uint32_t *a, const uint32_t *b);

void curve25519Copy(uint32_t *a, const uint32_t *b);
void curve25519Swap(uint32_t *a, uint32_t *b, uint32_t c);

void curve25519Select(uint32_t *r, const uint32_t *a, const uint32_t *b,
   uint32_t c);

uint32_t curve25519Comp(const uint32_t *a, const uint32_t *b);

void curve25519Import(uint32_t *a, const uint8_t *data);
void curve25519Export(uint32_t *a, uint8_t *data);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
