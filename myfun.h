//
// Created by Shirakami Emmmer on 2020/2/27.
//

#ifndef FUCKNCM_MYFUN_H
#define FUCKNCM_MYFUN_H

void AES_Decryption(const unsigned char *data, const unsigned char *inKey, size_t size, unsigned char *outData) {
    AES_KEY key;
    private_AES_set_decrypt_key(inKey, 128, &key);
    unsigned char message[size];

    for (int j = 0; j < size / 16; ++j) { AES_ecb_encrypt(data + 16 * j, message + 16 * j, &key, AES_DECRYPT); }
    for (int i = 0; i < size; ++i) { *(outData + i) = message[i]; }
}

void RC4_Decryption(const unsigned char *rc4Key, size_t size, unsigned char *keyBox) {
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

#endif //FUCKNCM_MYFUN_H
