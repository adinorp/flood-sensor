/**
 * @file body.h
 * @brief App Image Builder image boby managment
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

#ifndef __BODY_H
#define __BODY_H

//Dependencies
#include <stdint.h>
#include "header.h"
#include "main.h"


/**
 * @brief Image Body definition
 **/

typedef struct
{
    uint8_t* binary;
    size_t binarySize;
    uint8_t* checkData;
    size_t checkDataSize;
} ImageBody;

//App Image Builder body related routines
int bodyMake(ImageHeader *header, ImageBody *body, CipherInfo cipherInfo);

#endif // __BODY_H
