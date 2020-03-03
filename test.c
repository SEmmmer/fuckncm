//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    const int key_length = 20;
//    key_data = bytearray(key_data)
//    key_box = bytearray(range(256))
    unsigned char key_data[20] = {0};
    unsigned char key_box[20] = {0};
//    c = 0
//    last_byte = 0
//    key_offset = 0
    unsigned char c = 0;
    unsigned char last_byte = 0;
    unsigned char key_offset = 0;
    unsigned char swap = 0;
    printf("key_box = %s\n", key_box);
    printf("key_data = %s\n", key_data);
    printf("===================\n");

    for (int i = 0; i < 20; ++i) {
        swap = key_box[i];
        c = (swap + last_byte + key_data[key_offset]) & 0xff;
        key_offset += 1;
        if (key_offset >= key_length) { key_offset = 0; }
        key_box[i] = key_box[c];
        key_box[c] = swap;
        last_byte = c;
    }
//    for i in range(256):
//      swap = key_box[i]
//      c = (swap + last_byte + key_data[key_offset]) & 0xff
//      key_offset += 1
//      if key_offset >= key_length: key_offset = 0
//      key_box[i] = key_box[c]
//      key_box[c] = swap
//      last_byte = c

    printf("key_box = %s\n", key_box);
    printf("key_data = %s\n", key_data);
    printf("===================\n");

    return 0;
}