/**
 * @file iap_fallaback.h
 * @brief CycloneBOOT IAP Fallback Functions API
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

#ifndef _IAP_FALLBACK_H
#define _IAP_FALLBACK_H

//Dependencies
#include "error.h"
#include "iap_config.h"

//CycloneBOOT Dual Bank IAP fallback routines
error_t iapFallbackStart(void);

#endif //!_IAP_FALLBACK_H
