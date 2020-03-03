//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "WjCryptLib_Rc4.h"

int main() {
    Rc4Context ijk;
    unsigned char massage[20] = {0};
    unsigned char code[20] = {0};
    unsigned char code_code[20] = {0};
    unsigned char key[20] = {0};
    Rc4Initialise(&ijk, key, 20, 0);
    Rc4XorWithKey()
    return 0;
}