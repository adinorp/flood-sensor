/**
 * @file base64url.h
 * @brief Base64url encoding scheme
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

#ifndef _BASE64URL_H
#define _BASE64URL_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Base64url encoding related functions
void base64urlEncode(const void *input, size_t inputLen, char_t *output,
   size_t *outputLen);

error_t base64urlDecode(const char_t *input, size_t inputLen, void *output,
   size_t *outputLen);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
