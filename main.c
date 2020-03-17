#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include "base64.h"
#include <sys/stat.h>

void AES_Decryption(const unsigned char *data, const unsigned char *inKey, size_t size, unsigned char *outData) {
    AES_KEY key;
    private_AES_set_decrypt_key(inKey, 128, &key);
    unsigned char message[size];

    printf("\n---AES Decryption started----\n");
    for (int j = 0; j < size / 16; ++j) { AES_ecb_encrypt(data + 16 * j, message + 16 * j, &key, AES_DECRYPT); }
    for (int i = 0; i < size; ++i) { *(outData + i) = message[i]; }
    printf("\n---AES Decryption finished---\n");
}

void RC4_Decryption(const unsigned char *rc4Key, size_t size, unsigned char *keyBox) {
    printf("\n---RC4 Decryption started----\n");
    for (int j = 0; j < 256; ++j) { keyBox[j] = j; }

    int keyOffset = 0;
    unsigned char c = 0x00;
    unsigned char swap = 0x00;
    unsigned char lastByte = 0x00;

    for (int i = 0; i < 256; ++i) {
        swap = keyBox[i];
        c = (swap + lastByte + rc4Key[keyOffset]) & 0xff;
        keyOffset += 1;
        if (keyOffset >= size) { keyOffset = 0; }
        keyBox[i] = keyBox[c];
        keyBox[c] = swap;
        lastByte = c;
    }
    printf("\n---RC4 Decryption finished---\n");
}

void audioDecoding(FILE *ncmFile, FILE *outFile, const unsigned char *keyBox) {
    long position = ftell(ncmFile);
    fseek(ncmFile, 0, SEEK_END);
    long fileSize = ftell(ncmFile);
    fseek(ncmFile, position, SEEK_SET);

    int j = 0;
    unsigned char chunk[0x8000] = {0};
    int chunkLength = sizeof(chunk);

    for (long loop = 0; loop <= (fileSize - position) / chunkLength; loop++) {
        fread(chunk, chunkLength, 1, ncmFile);
        for (int i = 1; i < chunkLength + 1; ++i) {
            j = i & 0xff;
            chunk[i - 1] ^= keyBox[(keyBox[j] + keyBox[(keyBox[j] + j) & 0xff]) & 0xff];
        }
        fwrite(chunk, chunkLength, 1, outFile);
    }
}

int main() {
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
    if (memcmp(buffer, "CTENFDAM", 8) != 0) { exit(1); }//不是ncm

    //读取key的长度和数据
    int keyLength = 0;
    fseek(aSong, 2, SEEK_CUR);
    fread(&keyLength, sizeof(int), 1, aSong);
    unsigned char *keyData = (unsigned char *) malloc(keyLength);
    fread(keyData, keyLength, 1, aSong);
    for (int i = 0; i < keyLength; ++i) { keyData[i] ^= 0x64; }
    //在解密前对key做异或运算，原理未知

    unsigned char messageOfKey[keyLength];
    unsigned char rc4Key[keyLength - 17];
    //开始第一部分的解密，还原key之后用于还原媒体文件
    AES_Decryption(keyData, firstKey, keyLength, messageOfKey);
    for (int k = 17; k < keyLength; ++k) { rc4Key[k - 17] = messageOfKey[k]; }

    //第二部分的解密，用的是RC4的算法，通过rc4Key计算keyBox
    int rc4Length = sizeof(rc4Key) - 1;
    unsigned char keyBox[256];
    RC4_Decryption(rc4Key, rc4Length, keyBox);

    //回到文件继续读取meta，其中包含了歌曲的主要信息
    int metaLength = 0;
    fread(&metaLength, sizeof(int), 1, aSong);
    unsigned char *metaData = (unsigned char *) malloc(metaLength);
    fread(metaData, metaLength, 1, aSong);
    for (int i = 0; i < metaLength; ++i) { metaData[i] ^= 0x63; }
    //解密前进行异或运算，原理未知

    unsigned char metaData2[metaLength - 22];
    unsigned char messageOfMeta[metaLength];
    base64_decode(metaData + 22, metaLength - 22, metaData2);
    AES_Decryption(metaData2, secondKey, metaLength, messageOfMeta);
    for (int n = 0; n < metaLength - 22; ++n) { if (messageOfMeta[n] == 0x7D) { messageOfMeta[n + 1] = 0; }}
    //解密并且进行输出，之后有精力会考虑加入json字典

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
    audioDecoding(aSong, newSong, keyBox);

    free(keyData);
    free(metaData);
    keyData = NULL;
    metaData = NULL;
    return 0;
}