//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdio.h>
#include "/usr/local/Cellar/base64/include/libbase64.h"

int main(int argc, char *argv[]) {

    char src[] = "hello world123456789";
    char massage[128] = {0};
    size_t src_len = sizeof(src) - 1;
    size_t out_len;

    printf("%zd\n", sizeof(src));
    base64_encode(src, sizeof(src) - 1, massage, &out_len, 0);

//    base64_decode();
    printf("%s\n", src);

    return 0;
}
