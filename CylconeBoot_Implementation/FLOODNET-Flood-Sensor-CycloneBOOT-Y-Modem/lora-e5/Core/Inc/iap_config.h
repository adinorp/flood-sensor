/**
 * @file iap_config.h
 * @brief CycloneBOOT IAP configuration file
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2021-2022 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneBOOT Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.0
 **/

#ifndef _IAP_CONFIG_H
#define _IAP_CONFIG_H

#include "main.h"

//Trace level for CycloneBOOT IAP stack debugging
#define IAP_TRACE_LEVEL          TRACE_LEVEL_ERROR 	//Trace are deactivated because they are sent on the same UART as Y-Modem
													//and they cannot be used at the same time on the same UART !!!

//IAP Single Bank Mode support
#define IAP_SINGLE_BANK_SUPPORT ENABLED
//IAP Dual Bank Mode support
#define IAP_DUAL_BANK_SUPPORT DISABLED

//IAP external flash memory encryption support
#define IAP_EXT_MEM_ENCRYPTION_SUPPORT DISABLED

//IAP fallback support
#define IAP_FALLBACK_SUPPORT DISABLED

//Bootloader size (sum of occupied sector size)
#define BOOTLOADER_SIZE 32768 // 32K, supposing it occupies the first 2 Flash sectors

#if defined(IAP_SCENARIO_2)

//IAP encryption support
#define IAP_ENCRYPTION_SUPPORT ENABLED
//Verification Integrity support
#define VERIFY_INTEGRITY_SUPPORT ENABLED
//Verification Authentication support
#define VERIFY_AUTHENTICATION_SUPPORT ENABLED

#elif defined(IAP_SCENARIO_3)

//IAP encryption support
#define IAP_ENCRYPTION_SUPPORT ENABLED
//Verification Integrity support
#define VERIFY_INTEGRITY_SUPPORT ENABLED
//Verification Signature support
#define VERIFY_SIGNATURE_SUPPORT ENABLED
//Verification RSA signature algorithm support
#define VERIFY_RSA_SUPPORT ENABLED

#else

//Verification Integrity support
#define VERIFY_INTEGRITY_SUPPORT ENABLED

#endif

#endif //!_IAP_CONFIG_H
