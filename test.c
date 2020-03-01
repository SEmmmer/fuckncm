//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "base64.h"

int main() {
    unsigned char src[20] = "hello world";
    char *src1 = src;
    char massage[20];
    printf("%s\n", src);
    base64_encode(src, 20, massage);
    printf("%s\n", massage);
}