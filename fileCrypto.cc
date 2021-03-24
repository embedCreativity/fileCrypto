/************************************************************************
*  Copyright (C) 2021 Embed Creativity LLC
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
************************************************************************/

#include "fileCrypto.h"

extern CryptoInterface_T cryptoIntf;

bool FileCrypto::SetKey(char* keyFile)
{
    fileHandle = fopen(keyFile, "r");
    if ( fileHandle == NULL ) {
        return false;
    }

    if ( KEY_LEN != fread(key, 1, KEY_LEN, fileHandle) ) {
        return false;
    }

    if ( IV_LEN != fread(iv, 1, IV_LEN, fileHandle) ) {
        return false;
    }

    fclose(fileHandle);
    fileHandle = NULL;
    return true;
}

bool FileCrypto::FileEncrypt ( char* plainTextFile, char* cipherTextFile )
{
	CryptoHandle_T* cryptoHandle;
    uint8_t* plainData;
    uint8_t* cipherData;
    uint32_t fileLen;

    fileHandle = fopen(plainTextFile, "r");
    if ( fileHandle == NULL ) {
        return false;
    }
    fseek(fileHandle, 0, SEEK_END);
    fileLen = ftell(fileHandle);
    rewind(fileHandle);

    plainData = (uint8_t*)malloc(fileLen);
    if ( plainData == NULL ) {
        fclose(fileHandle);
        return false;
    }
    cipherData = (uint8_t*)malloc(fileLen);
    if (cipherData == NULL ) {
        fclose(fileHandle);
        free(plainData);
        return false;
    }

    if ( fileLen != fread(plainData, 1, fileLen, fileHandle) ) {
        fclose(fileHandle);
        free(plainData);
        free(cipherData);
        return false;
    }
    fclose(fileHandle);

    cryptoHandle = (CryptoHandle_T*)cryptoIntf.CreateCryptoHandle(this->iv, this->key);
    if ( cryptoHandle == NULL ) {
        free(plainData);
        free(cipherData);
        return false;
    }
    cryptoIntf.Encrypt(cryptoHandle, plainData, cipherData, fileLen);
    cryptoIntf.FreeCryptoHandle(cryptoHandle);
    free(plainData);

    fileHandle = fopen(cipherTextFile, "w");
    if ( fileHandle == NULL ) {
        free(cipherData);
        return false;
    }

    fwrite(cipherData, 1, fileLen, fileHandle);
    fclose(fileHandle);
    free(cipherData);
    return true;
}

bool FileCrypto::FileDecrypt ( char* cipherTextFile, char* plainTextFile )
{
    return FileEncrypt(cipherTextFile, plainTextFile);
}

// Main entry point
int main ( int argc, char *argv[] )
{
	FileCrypto crypto;

    if ( argc != 4 ) {
        printf("USAGE: fileCrypto infile outfile keyfile\n\n");
        return -1;
    }

    if ( !crypto.SetKey(argv[3]) ) {
        printf("Failed setting key\n");
        return -1;
    }

    if ( !crypto.FileEncrypt(argv[1], argv[2]) ) {
        printf("Failed encrypting\n");
        return -1;
    } else {
        printf("Encryption successful\n");
    }

	return 0;
}

