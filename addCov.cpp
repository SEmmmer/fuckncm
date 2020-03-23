//
// Created by Shirakami Emmmer on 2020/3/22.
//
#define Type TagLib::String::UTF8

#include <iostream>
#include <string>
#include <json-c/json.h>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tstring.h>

void readJson() {

}

void setTag() {

}

void buffer() {
    std::string title = "中文测试";
    const std::string &s = title;
    TagLib::String give_me_a_name(s, Type);

    TagLib::FileRef f("tmp/nocov.mp3");
    f.tag()->setArtist(give_me_a_name);
    f.tag()->setAlbum(s);
    f.tag()->setTitle(s);
    f.tag()->setComment(title);
    f.tag()->setGenre(title);
    f.tag()->setTrack(1);
    f.tag()->setYear(1);
    f.save();
}

int main() {
    struct json_object *im = nullptr;
    im = json_object_from_file("tmp/tmp.json");
    printf("%s\n", json_object_to_json_string(im));
    struct json_object *result = nullptr;

    result = json_object_object_get(im, "musicName");
    std::string buffer;
    printf("%s\n", json_object_to_json_string(result));

    result = json_object_object_get(im, "artist");
    printf("%s\n", json_object_to_json_string(result));

    result = json_object_object_get(im, "album");
    printf("%s\n", json_object_to_json_string(result));

    result = json_object_object_get(im, "bitrate");
    printf("%s\n", json_object_to_json_string(result));

    result = json_object_object_get(im, "format");
    printf("%s\n", json_object_to_json_string(result));


    return 0;
}
