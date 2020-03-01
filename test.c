//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdint.h>
#include <stdlib.h>
#include "base64.h"

int main() {
    char src[20] = "hello world";
    char *src1 = src;
    unsigned char massage[20];

    base64_decode(src, 20, massage);
}