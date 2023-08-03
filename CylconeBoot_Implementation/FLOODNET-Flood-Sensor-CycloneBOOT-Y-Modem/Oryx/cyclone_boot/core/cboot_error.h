/**
 * @file error.h
 * @brief Error codes description
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

#ifndef _CBOOT_ERROR_H
#define _CBOOT_ERROR_H

//Dependencies
#include "error.h"

// C++ guard
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Error codes
 **/

typedef enum
{

    CBOOT_NO_ERROR = ERROR_PARTIAL_MATCH + 1,      ///< CBOOT Success
    CBOOT_ERROR_FAILURE,                           ///< CBOOT error code

    CBOOT_ERROR_INVALID_PARAMETERS,

    CBOOT_ERROR_INVALID_IMAGE_HEADER,
    CBOOT_ERROR_INVALID_IMAGE_CHECK,
    CBOOT_ERROR_MISSING_IMAGE_CHECK_METHOD,
    CBOOT_ERROR_INCOMPATIBLE_IMAGE_APP_VERSION,

    CBOOT_ERROR_INVALID_IMAGE_INTEGRITY_TAG,
    CBOOT_ERROR_INVALID_IMAGE_AUTHENTICATION_TAG,

    CBOOT_ERROR_INVALID_IMAGE_APP,

    CBOOT_ERROR_IMAGE_NOT_READY,

    CBOOT_ERROR_INVALID_STATE,

    CBOOT_ERROR_BUFFER_OVERFLOW,

} cboot_error_t;

// C++ guard
#ifdef __cplusplus
}
#endif

#endif
