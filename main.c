#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myfun.h"
//#include "/usr/local/Cellar/openssl/1.0.2t/include/openssl/aes.h"
//just for fun, LOL
#include <openssl/aes.h>
#include <ctype.h>

int main() {


    char firstKey[128] = "687A4852416D736F356B496E62617857";
    char secondKey[128] = "2331346C6A6B5F215C5D2630553C2728";

    FILE *aSong;
    aSong = fopen("tmp/test.ncm", "r");

    char buffer[9];
    const char ncmFile[9] = "CTENFDAM";
    fread(buffer, 8, 1, aSong);

    if (strcmp(buffer, ncmFile) != 0) {}//不是ncm

    printf("%s\n", buffer);

    char keyLength[9];
    fseek(aSong, 10, SEEK_SET);
    fread(keyLength, 4, 1, aSong);

    printf("%s", keyLength);


    return 0;
}