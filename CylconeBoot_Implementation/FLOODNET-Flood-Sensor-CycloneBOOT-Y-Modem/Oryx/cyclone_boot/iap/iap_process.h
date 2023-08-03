/**
 * @file iap_process.h
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

#ifndef _IAP_PROCESS_H
#define _IAP_PROCESS_H

//Dependencies
#include "iap/iap.h"
#include "iap_config.h"

//CycloneBOOT IAP process related functions
error_t iapProcessAppHeader(ImageContext *context);
error_t iapProcessAppData(ImageContext *context);
error_t iapProcessAppCheck(ImageContext* context);
error_t iapProcessAppCipherIv(ImageContext *context);
error_t iapProcessInputImage(ImageContext *context);
error_t iapProcessOutputImage(ImageContext *context, uint8_t *data, size_t length);
#if IAP_DUAL_BANK_SUPPORT == ENABLED
error_t iapProcessOutputImageDualBank(ImageContext *context, uint8_t *data, size_t length);
#else
error_t iapProcessOutputImageSingleBank(ImageContext *context, uint8_t *data, size_t length);
#endif

#endif // !_IAP_PROCESS_H
