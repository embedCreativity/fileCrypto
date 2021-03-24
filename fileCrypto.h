/************************************************************************
  Copyright (C) 2021 Embed Creativity LLC
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
************************************************************************/

#ifndef __FILE_CRYPTO__
#define __FILE_CRYPTO__

#define KEY_LEN	16
#define IV_LEN  16

#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include "crypto/crypto.h"

class FileCrypto {
public:
    bool SetKey(char* keyFile);
    bool FileEncrypt(char* plainTextFile, char* cipherTextFile);
    bool FileDecrypt(char* cipherTextFile, char* plainTextFile);

private:
    uint8_t key[KEY_LEN];
    uint8_t iv[IV_LEN];
    FILE* fileHandle;
};

#endif

