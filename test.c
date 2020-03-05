//
// Created by Shirakami Emmmer on 2020/3/1.
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "WjCryptLib_Rc4.h"

int main() {
//    crc32 = f.read(4)
//    crc32 = struct.unpack('<I', bytes(crc32))[0]
//    f.seek(5, 1)
//
//    image_size = f.read(4)
//    image_size = struct.unpack('<I', bytes(image_size))[0]
//    image_data = f.read(image_size)
//
//    file_name = meta_data['musicName'] + '.' + meta_data['format']

    FILE *newSong;
    newSong = fopen("tmp/out.mp3", "wb");
    unsigned char chunk[0x8000] = {0};
    int chunk_length = sizeof(chunk);
//    m = open(os.path.join(os.path.split(file_path)[0],file_name),'wb')
//    chunk = bytearray()
//    while True:
//        chunk = bytearray(f.read(0x8000))
//        chunk_length = len(chunk)
//        if not chunk:
//          break
//        for i in range(1,chunk_length+1):
//          j = i & 0xff;
//          chunk[i-1] ^= key_box[(key_box[j] + key_box[(key_box[j] + j) & 0xff]) & 0xff]
//        m.write(chunk)
//    m.close()
//    f.close()

    return 0;
}