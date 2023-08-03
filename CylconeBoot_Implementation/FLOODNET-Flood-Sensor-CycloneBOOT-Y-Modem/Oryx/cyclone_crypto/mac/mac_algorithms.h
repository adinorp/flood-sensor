/**
 * @file mac_algorithms.h
 * @brief Collection of MAC algorithms
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

#ifndef _MAC_ALGORITHMS_H
#define _MAC_ALGORITHMS_H

//Dependencies
#include "core/crypto.h"

//HMAC support?
#if (HMAC_SUPPORT == ENABLED)
   #include "mac/hmac.h"
#endif

//GMAC support?
#if (GMAC_SUPPORT == ENABLED)
   #include "mac/gmac.h"
#endif

//CMAC support?
#if (CMAC_SUPPORT == ENABLED)
   #include "mac/cmac.h"
#endif

//KMAC support?
#if (KMAC_SUPPORT == ENABLED)
   #include "mac/kmac.h"
#endif

//Poly1305 support?
#if (POLY1305_SUPPORT == ENABLED)
   #include "mac/poly1305.h"
#endif

#endif
