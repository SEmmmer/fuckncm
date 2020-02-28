#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myfun.h"
//#include "/usr/local/Cellar/openssl/1.0.2t/include/openssl/aes.h"
//just for fun, LOL
#include <openssl/aes.h>
#include <ctype.h>

int main() {

    const char ncmFile[] = "CTENFDAM";

    char firstKey[] = {0x68, 0x7A, 0x48, 0x52, 0x41, 0x6D, 0x73, 0x6F, 0x35, 0x6B, 0x49, 0x6E, 0x62, 0x61, 0x78, 0x57};
    char secondKey[] = {0x23, 0x31, 0x34, 0x6C, 0x6A, 0x6B, 0x5F, 0x21, 0x5C, 0x5D, 0x26, 0x30, 0x55, 0x3C, 0x27, 0x28};

    FILE *aSong;
    aSong = fopen("tmp/test.ncm", "r");

    char buffer[8];
    fread(buffer, 8, 1, aSong);
    if (strcmp(buffer, ncmFile) != 0) {}//不是ncm

    int keyLength = 0;
    fseek(aSong, 10, SEEK_SET);
    fread(&keyLength, 4, 1, aSong);

    char *keyData = (char *) malloc(keyLength);
    fread(keyData, keyLength, 1, aSong);

    printf("%s", keyData);
//    int data = private_AES_set_decrypt_key()
    return 0;
}