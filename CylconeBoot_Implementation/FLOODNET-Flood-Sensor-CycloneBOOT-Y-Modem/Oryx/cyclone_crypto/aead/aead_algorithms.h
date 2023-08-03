/**
 * @file cipher_algorithms.h
 * @brief Collection of AEAD algorithms
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

#ifndef _AEAD_ALGORITHMS_H
#define _AEAD_ALGORITHMS_H

//Dependencies
#include "core/crypto.h"

//GCM mode support?
#if (GCM_SUPPORT == ENABLED)
   #include "aead/gcm.h"
#endif

//CCM mode support?
#if (CCM_SUPPORT == ENABLED)
   #include "aead/ccm.h"
#endif

//ChaCha20Poly1305 support?
#if (CHACHA20_POLY1305_SUPPORT == ENABLED)
   #include "aead/chacha20_poly1305.h"
#endif

#endif
