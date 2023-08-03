/**
 * @file sam4c_crypto.h
 * @brief SAM4C hardware cryptographic accelerator
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

#ifndef _SAM4C_CRYPTO_H
#define _SAM4C_CRYPTO_H

//Device-specific definitions
#if defined(__SAM4C4C_0__)
   #include "sam4c4c_0.h"
#elif defined(__SAM4C4C_1__)
   #include "sam4c4c_1.h"
#elif defined(__SAM4C8C_0__)
   #include "sam4c8c_0.h"
#elif defined(__SAM4C8C_1__)
   #include "sam4c8c_1.h"
#elif defined(__SAM4C16C_0__)
   #include "sam4c16c_0.h"
#elif defined(__SAM4C16C_1__)
   #include "sam4c16c_1.h"
#elif defined(__SAM4C32C_0__)
   #include "sam4c32c_0.h"
#elif defined(__SAM4C32C_1__)
   #include "sam4c32c_1.h"
#elif defined(__SAM4C32E_0__)
   #include "sam4c32e_0.h"
#elif defined(__SAM4C32E_1__)
   #include "sam4c32e_1.h"
#elif defined(__SAM4CP16B_0__)
   #include "sam4cp16b_0.h"
#elif defined(__SAM4CP16B_1__)
   #include "sam4cp16b_1.h"
#elif defined(__SAM4CP16C_0__)
   #include "sam4cp16c_0.h"
#elif defined(__SAM4CP16C_1__)
   #include "sam4cp16c_1.h"
#elif defined(__SAM4CMP8C_0__)
   #include "sam4cmp8c_0.h"
#elif defined(__SAM4CMP8C_1__)
   #include "sam4cmp8c_1.h"
#elif defined(__SAM4CMP16C_0__)
   #include "sam4cmp16c_0.h"
#elif defined(__SAM4CMP16C_1__)
   #include "sam4cmp16c_1.h"
#elif defined(__SAM4CMS4C_0__)
   #include "sam4cms4c_0.h"
#elif defined(__SAM4CMS4C_1__)
   #include "sam4cms4c_1.h"
#elif defined(__SAM4CMS8C_0__)
   #include "sam4cms8c_0.h"
#elif defined(__SAM4CMS8C_1__)
   #include "sam4cms8c_1.h"
#elif defined(__SAM4CMS16C_0__)
   #include "sam4cms16c_0.h"
#elif defined(__SAM4CMS16C_1__)
   #include "sam4cms16c_1.h"
#elif defined(__SAM4CMP32C_0__)
   #include "sam4cmp32c_0.h"
#elif defined(__SAM4CMP32C_1__)
   #include "sam4cmp32c_1.h"
#elif defined(__SAM4CMS32C_0__)
   #include "sam4cms32c_0.h"
#elif defined(__SAM4CMS32C_1__)
   #include "sam4cms32c_1.h"
#endif

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Global variables
extern OsMutex sam4cCryptoMutex;

//SAM4C hardware cryptographic accelerator related functions
error_t sam4cCryptoInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
