//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "base64.h"
#include "WjCryptLib_Rc4.h"

int main() {
//    key_data = bytearray(key_data)
//    key_box = bytearray(range(256))
    unsigned char key_data[128] = {0};
    unsigned char key_box[256] = {0};
//    c = 0
//    last_byte = 0
//    key_offset = 0
    int c = 0;
    int last_byte = 0;
    int key_offset = 0;
    int swap = 0;

    for (int i = 0; i < 256; ++i) {
        swap = key_box[i];
        c = (swap + last_byte + key_data[key_offset]) & 0xff;
    }
//    for i in range(256):
//    swap = key_box[i]
//    c = (swap + last_byte + key_data[key_offset]) & 0xff
//    key_offset += 1
//    if key_offset >= key_length: key_offset = 0
//    key_box[i] = key_box[c]
//    key_box[c] = swap
//    last_byte = c
    return 0;
}