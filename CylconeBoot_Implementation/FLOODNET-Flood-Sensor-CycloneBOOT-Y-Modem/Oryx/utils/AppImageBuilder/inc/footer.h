/**
 * @file footer.h
 * @brief App Image Builder image footer managment
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

#ifndef __FOOTER_H
#define __FOOTER_H

//Dependencies
#include <string.h>
#include "body.h"
#include "utils.h"

//App Image builder footer related routines
int footerMake(ImageHeader *header, ImageBody *body, CipherInfo *cipherInfo, CheckDataInfo *checkDataInfo, char* check_data);

#endif // __FOOTER_H
