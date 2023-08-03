/**
 * @file iap_misc.h
 * @brief CycloneBOOT IAP Miscellaneous Functions API
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

#ifndef _IAP_MISC_H
#define _IAP_MISC_H

//Dependancies
#include "iap/iap.h"
#include "core/image.h"

//CycloneBOOT IAP miscellaneous related functions
error_t iapInitPrimaryMemory(IapSettings *settings, IapContext *context);
error_t iapInitSecondaryMemory(IapSettings *settings, IapContext *context);
error_t iapInitInputImage(IapSettings *settings, IapContext *context);
error_t iapInitOutputImage(IapSettings *settings, IapContext *context);
error_t iapWrite(ImageContext *context, const uint8_t *data, size_t length, uint8_t flag);
error_t iapGetImageHeaderFromSlot(SlotDesc *slot, ImageHeader *header);

#endif // !_IAP_MISC_H
