#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "/usr/local/Cellar/openssl/1.0.2t/include/openssl/aes.h"
//just for fun, LOL
#include <openssl/aes.h>
#include <ctype.h>

int main() {

    const unsigned char ncmFile[] = "CTENFDAM";

    const unsigned char firstKey[] = {0x68, 0x7A, 0x48, 0x52, 0x41, 0x6D, 0x73, 0x6F,
                                      0x35, 0x6B, 0x49, 0x6E, 0x62, 0x61, 0x78, 0x57};
    const unsigned char secondKey[] = {0x23, 0x31, 0x34, 0x6C, 0x6A, 0x6B, 0x5F, 0x21,
                                       0x5C, 0x5D, 0x26, 0x30, 0x55, 0x3C, 0x27, 0x28};
//
//    FILE *aSong;
//    aSong = fopen("tmp/test.ncm", "rb");
//
//    unsigned char buffer[8];
//    fread(buffer, 8, 1, aSong);
//    if (memcmp(buffer, ncmFile, 8) != 0) { exit(1); }//不是ncm
//
//    int keyLength = 0;
//    fseek(aSong, 10, SEEK_SET);
//    fread(&keyLength, 4, 1, aSong);

//    unsigned char *keyData = (unsigned char *) malloc(keyLength);
//    fread(keyData, keyLength, 1, aSong);
    unsigned char Data[] = "Segmentation occurs while calling these two function with key-size=192 and 256";

    printf("%s\n", Data);
    AES_KEY encode;
    private_AES_set_encrypt_key(firstKey, 128, &encode);
    AES_KEY decode;
    private_AES_set_decrypt_key(firstKey, 128, &decode);

    unsigned char massage1[128];
    unsigned char massage2[128];

    printf("---AES Decryption started----\n");
    for (int j = 0; j < 8; ++j) {
        AES_ecb_encrypt(Data + j * 16, massage1 + j * 16, &encode, AES_ENCRYPT);
    }
    printf("密文：%s\n", massage1);
    for (int i = 0; i < 8; ++i) {
        AES_ecb_encrypt(massage1 + i * 16, massage2 + i * 16, &decode, AES_DECRYPT);
    }

    printf("解密后结果：%s\n", massage2);
    printf("---AES Decryption finished---\n");
    return 0;
}