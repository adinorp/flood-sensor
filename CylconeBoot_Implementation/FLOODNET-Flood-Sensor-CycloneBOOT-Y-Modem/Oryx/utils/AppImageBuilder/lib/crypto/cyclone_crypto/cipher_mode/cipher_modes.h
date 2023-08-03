/**
 * @file cipher_modes.h
 * @brief Block cipher modes of operation
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

#ifndef _CIPHER_MODES_H
#define _CIPHER_MODES_H

//Dependencies
#include "core/crypto.h"

//ECB mode support?
#if (ECB_SUPPORT == ENABLED)
   #include "cipher_mode/ecb.h"
#endif

//CBC mode support?
#if (CBC_SUPPORT == ENABLED)
   #include "cipher_mode/cbc.h"
#endif

//CFB mode support?
#if (CFB_SUPPORT == ENABLED)
   #include "cipher_mode/cfb.h"
#endif

//OFB mode support?
#if (OFB_SUPPORT == ENABLED)
   #include "cipher_mode/ofb.h"
#endif

//CTR mode support?
#if (CTR_SUPPORT == ENABLED)
   #include "cipher_mode/ctr.h"
#endif

//XTS mode support?
#if (XTS_SUPPORT == ENABLED)
   #include "cipher_mode/xts.h"
#endif

#endif
