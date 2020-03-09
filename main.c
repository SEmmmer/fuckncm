#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "/usr/local/Cellar/openssl/1.0.2t/include/openssl/aes.h"
//just for fun, LOL
#include <openssl/aes.h>
#include "base64.h"
#include "WjCryptLib_Rc4.h"
#include <sys/stat.h>

int file_size(char *filename) {
    struct stat buf;
    stat(filename, &buf);
    int size = buf.st_size;
    return size;
}

int main() {

    const unsigned char ncmFile[] = "CTENFDAM";

    const unsigned char firstKey[] = {0x68, 0x7A, 0x48, 0x52, 0x41, 0x6D, 0x73, 0x6F,
                                      0x35, 0x6B, 0x49, 0x6E, 0x62, 0x61, 0x78, 0x57};
    const unsigned char secondKey[] = {0x23, 0x31, 0x34, 0x6C, 0x6A, 0x6B, 0x5F, 0x21,
                                       0x5C, 0x5D, 0x26, 0x30, 0x55, 0x3C, 0x27, 0x28};
    //两段从天上掉下来的密钥
    FILE *aSong = NULL;
    FILE *newSong = NULL;
    aSong = fopen("tmp/test.ncm", "rb");
    newSong = fopen("tmp/out.mp3", "wb");

    unsigned char buffer[8];
    fread(buffer, 8, 1, aSong);
    if (memcmp(buffer, ncmFile, 8) != 0) { exit(1); }//不是ncm

    //读取key的长度和数据
    int keyLength = 0;
    fseek(aSong, 2, SEEK_CUR);
    fread(&keyLength, 4, 1, aSong);
    unsigned char *keyData = (unsigned char *) malloc(keyLength);
    fread(keyData, keyLength, 1, aSong);
    for (int i = 0; i < keyLength; ++i) {
        keyData[i] ^= 0x64;
    }
    //在解密前对key做异或运算，原理未知

    AES_KEY key;
    private_AES_set_decrypt_key(firstKey, 128, &key);
    unsigned char massageOfKey[keyLength];
    unsigned char rc4Key[keyLength - 17];

    //开始第一部分的解密，还原key之后用于还原媒体文件
    printf("\n---AES Decryption started----\n");
    for (int j = 0; j < keyLength / 16; ++j) {
        AES_ecb_encrypt(keyData + 16 * j, massageOfKey + 16 * j, &key, AES_DECRYPT);
    }
    for (int k = 17; k < keyLength; ++k) {
        putchar(massageOfKey[k]);
        rc4Key[k - 17] = massageOfKey[k];
    }
    printf("\n---AES Decryption finished---\n");

    //第二部分的解密，用的是RC4的算法，通过rc4Key计算key_box
    //这里代码风格有一些不一样
    printf("\n---RC4 Decryption started----\n");
    int key_length = sizeof(rc4Key) - 1;
    unsigned char key_box[256] = {0};
    for (int j = 0; j < 256; ++j) { key_box[j] = j; }

    unsigned char c = 0x00;
    unsigned char last_byte = 0x00;
    int key_offset = 0;
    unsigned char swap = 0x00;

    for (int i = 0; i < 256; ++i) {
        swap = key_box[i];
        c = (swap + last_byte + rc4Key[key_offset]) & 0xff;
        key_offset += 1;
        if (key_offset >= key_length) { key_offset = 0; }
        key_box[i] = key_box[c];
        key_box[c] = swap;
        last_byte = c;
    }
    for (int m = 0; m < 256; ++m) {
        putchar(key_box[m]);
    }
    printf("\n---RC4 Decryption finished---\n");

    //回到文件继续读取meta，其中包含了歌曲的主要信息
    int metaLength = 0;
    fread(&metaLength, 4, 1, aSong);
    unsigned char *metaData = (unsigned char *) malloc(metaLength);

    fread(metaData, metaLength, 1, aSong);
    unsigned char messageOfMeta_row[metaLength - 22];
    unsigned char messageOfMeta[metaLength];
    for (int i = 0; i < metaLength; ++i) {
        metaData[i] ^= 0x63;
    }
    //解密前进行异或运算，原理未知
    base64_decode(metaData + 22, metaLength - 22, messageOfMeta_row);

    AES_KEY meta;
    private_AES_set_decrypt_key(secondKey, 128, &meta);

    //解密并且进行输出，之后有精力会考虑加入json字典
    printf("\n---AES Decryption started----\n");
    for (int l = 0; l < metaLength / 16; ++l) {
        AES_ecb_encrypt(messageOfMeta_row + 16 * l, messageOfMeta + 16 * l, &meta, AES_DECRYPT);
    }
    for (int n = 0; n < metaLength - 22; ++n) {
        if (messageOfMeta[n] == 0x7D) {
            messageOfMeta[n + 1] = 0;
        }
    }
    printf("%s", messageOfMeta);
    printf("\n---AES Decryption finished---\n");

    fseek(aSong, 5, SEEK_CUR);
    //获得歌曲的封面信息
    int imageSpace = 0;
    int imageSize = 0;
    fread(&imageSpace, 4, 1, aSong);
    fread(&imageSize, 4, 1, aSong);
    unsigned char imageData[imageSize];
    fread(&imageData, imageSize, 1, aSong);
    fseek(aSong, imageSpace - imageSize, SEEK_CUR);

    //最重要的部分，对文件进行解密还原出mp3文件
    unsigned char chunk[0x8000] = {0};
    int chunk_length = sizeof(chunk);
    int j = 0;
    int fileSize = file_size("tmp/test.ncm");
    int position = ftell(aSong);
    for (int loop = 0; loop <= (fileSize - position) / 32768; loop++) {
        fread(chunk, chunk_length, 1, aSong);
        for (int i = 1; i < chunk_length + 1; ++i) {
            j = i & 0xff;
            chunk[i - 1] ^= key_box[(key_box[j] + key_box[(key_box[j] + j) & 0xff]) & 0xff];
        }
        fwrite(chunk, chunk_length, 1, newSong);
    }
    printf("\n\n---Decoding Finished---");
    free(keyData);
    free(metaData);
    keyData = NULL;
    metaData = NULL;
    return 0;
}