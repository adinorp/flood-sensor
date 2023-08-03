/**
 * @file salsa20.h
 * @brief Salsa20 encryption algorithm
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

#ifndef _SALSA20_H
#define _SALSA20_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Salsa20 related functions
void salsa20ProcessBlock(const uint8_t *input, uint8_t *output, uint_t nr);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
