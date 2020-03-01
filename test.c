//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdio.h>
#include "base64.h"

int main(int argc, char *argv[]) {

    unsigned char src[] = "hello world123456789";
    char massage[128] = {0};
    size_t src_len = sizeof(src) - 1;
    size_t out_len;

    printf("%zd\n", sizeof(src));
    base64_encode(src, 128, massage);
    printf("%s\n", src);
    printf("%s\n", massage);

    return 0;
}
