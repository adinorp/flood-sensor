/**
 * @file crypto_config.h
 * @brief CycloneCrypto configuration file
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

#ifndef _CRYPTO_CONFIG_H
#define _CRYPTO_CONFIG_H

//Desired trace level (for debugging purposes)
#define CRYPTO_TRACE_LEVEL TRACE_LEVEL_INFO

//Multiple precision integer support
#define MPI_SUPPORT ENABLED
//Assembly optimizations for time-critical routines
#define MPI_ASM_SUPPORT DISABLED

//Base64 encoding support
#define BASE64_SUPPORT ENABLED
//Base64url encoding support
#define BASE64URL_SUPPORT DISABLED

#if defined(IAP_SCENARIO_1)

#elif defined(IAP_SCENARIO_2)

//HMAC support
#define HMAC_SUPPORT ENABLED
//AES support
#define AES_SUPPORT ENABLED
//CBC mode support
#define CBC_SUPPORT ENABLED

#elif defined(IAP_SCENARIO_3)

//AES support
#define AES_SUPPORT ENABLED
//CBC mode support
#define CBC_SUPPORT ENABLED
//RSA support
#define RSA_SUPPORT ENABLED
//Elliptic curve cryptography support
#define EC_SUPPORT ENABLED
//ECDSA support
#define ECDSA_SUPPORT ENABLED

#else

#endif

#endif
