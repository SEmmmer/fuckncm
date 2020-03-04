//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "WjCryptLib_Rc4.h"

int main() {
//    key_data = bytearray(key_data)
    unsigned char key_data[] = "60720177239789146097691462E7fT49x7dof9OKCgg9cdvhEuezy3iZCL1nFvBFd1T4uSktAJKmwZXsijPbijliionVUXXg9plTbXEclAE9Lb\0";
    int key_length = sizeof(key_data) / sizeof(key_data[0]);
    //    key_box = bytearray(range(256))
    unsigned char key_box[256] = {0};
//    c = 0
//    last_byte = 0
//    key_offset = 0
    unsigned char c = 0x00;
    unsigned char last_byte = 0x00;
    int key_offset = 0;
    unsigned char swap = 0x00;
    printf("%s\n", key_box);
    printf("%s\n", key_data);

//    for i in range(256):
//        swap = key_box[i]
//        c = (swap + last_byte + key_data[key_offset]) & 0xff
//        key_offset += 1
//        if key_offset >= key_length:
//            key_offset = 0
//        key_box[i] = key_box[c]
//        key_box[c] = swap
//        last_byte = c

    for (int i = 0; i < 256; ++i) {
        swap = key_box[i];
        c = (swap + last_byte + key_data[key_offset]) & 0xff;
        key_offset += 1;
        if (key_offset >= key_length){key_offset=0;}
        key_box[i] = key_box[c];
        key_box[c] = swap;
        last_byte = c;
    }
    printf("%s\n", key_box);
    printf("%s\n", key_data);

    return 0;
//    上面这部分是标准RC4-KSA算法（Key-scheduling algorithm
}