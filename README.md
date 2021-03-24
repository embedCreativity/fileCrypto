# fileCrypto
Simple AES File Encryption

USAGE: ./fileCrypto inputFile outputFile keyfile

AES-128 in CTR mode is a symmetrical encryption technique. Passing plaintext as input will result in ciphertext output.
Conversely, passing ciphertext as input will result in the original plaintext output.

fileCrypto is an example app that will read the first 32 bytes of the 'keyfile' to use as the initialization vector (IV)
and the key for the AES algorithm. Protect the keyfile from disclosure and you should be fine to share the encrypted
output file across a network with reasonable security. The recipient of the encrypted file needs to have a copy of the
keyfile to retrieve the original plaintext source file.

