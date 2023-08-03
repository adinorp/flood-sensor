/**
 * @file cli.h
 * @brief App Image Builder cli managment
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

#ifndef __CLI_H
#define __CLI_H

//Dependencies
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lib/cargs/include/cargs.h"

// Error code to signify a 'correct' CLI config, even when 'required' options are not present.
// For example, -v or --version and -h or --help
#define CLI_OK 2


/**
 * This is a custom project configuration structure where you can store the
 * parsed information.
 **/

struct builder_cli_configuration {
    const char *input;               // Required
    const char *output;              // Required
    const char *firmware_index;      // Optional
    bool padding;                    // if passed, a padding of 1024 bytes between header and body is added.
    const char *firmware_version;    // Optional, unless using anti-rollback
    const char *encryption_algo;     // Optional, unless encryption is required. AES-CBC by default as of v1
    const char *encryption_key;      // Optional
    const char *authentication_algo; // Optional, unless authentication is required. Supported algorithms: HMAC-[md5,sha256,sha512]
    const char *authentication_key;  // Optional
    const char *signature_algo;      // Optional
    const char* signature_key;       // Optional, unless signature is required. Supported algorithms: ecdsa-sha256, rsa-sha256,
    const char* integrity_algo;      // Optional. CRC32 is chosen by default. Supported algorithms: MD5, SHA26, SHA512
    bool verbose;                    // if passed, extra output will be passed to STDOUT
    bool version;                    // if passed, CLI version will be passed to STDOUT
    bool help;                      // if passed, a help message will be passed to STDOUT
};

//App Image Builder cli related routines
int parse_options(int argc, char **argv, struct builder_cli_configuration *cli_options);

#endif // __CLI_H
