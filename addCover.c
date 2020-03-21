//
// Created by Shirakami Emmmer on 2020/3/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("tmp/ooo.mp3", "rb");
    FILE *co = fopen("tmp/cover", "wb");
    const int size = 104;
    unsigned char message[size + 1];
    message[size] = 0;
    int coverSize = 0;
    fread(message, size, 1, fp);
    fseek(fp, 0, SEEK_SET);
    for (int i = 0; i < size; ++i) {
        fseek(fp, i, SEEK_SET);
        printf("%d ", i + 1);
        putchar(message[i]);
        printf(" %d\n", message[i]);
        fread(&coverSize, 4, 1, fp);
        if (coverSize == 327680) {
            printf(" %d---------findme\n", coverSize);

        }
    }
    unsigned char cover[327680];
    fseek(fp, 104, SEEK_SET);
    fread(cover, sizeof(cover), 1, fp);
    fwrite(cover, sizeof(cover), 1, co);
    return 0;
}
