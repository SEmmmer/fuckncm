//
// Created by Shirakami Emmmer on 2020/2/27.
//

#ifndef FUCKNCM_MYFUN_H
#define FUCKNCM_MYFUN_H

//十六进制字符转二进制字符
void Print_hex_to_Bin(char c) {
    char x[17][5] =
            {
                    "0000", "0001", "0010", "0011",
                    "0100", "0101", "0110", "0111",
                    "1000", "1001", "1010", "1011",
                    "1100", "1101", "1110", "1111",
            };
    int n = 16;
    if (c >= 'a' && c <= 'f') n = c - 'a' + 10;
    if (c >= 'A' && c <= 'F') n = c - 'A' + 10;
    if (c >= '0' && c <= '9') n = c - '0';
    printf("%s", x[n]);
}

#endif //FUCKNCM_MYFUN_H
