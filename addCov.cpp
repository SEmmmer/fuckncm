//
// Created by Shirakami Emmmer on 2020/3/22.
//
//#define Type TagLib::String::UTF8

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

//    f.tag()->setArtist(give_me_a_name);
//    f.tag()->setAlbum(s);
//    f.tag()->setTitle(s);
//    f.tag()->setComment(title);
//    f.tag()->setGenre(title);
//    f.tag()->setTrack(1);
//    f.tag()->setYear(1);
//    f.save();
}

int main() {
//    TagLib::String::Type T = TagLib::String::UTF16;
    TagLib::FileRef f("tmp/nocov.mp3");

    struct json_object *jsonP = nullptr;
    struct json_object *result = nullptr;
    jsonP = json_object_from_file("tmp/tmp.json");

    result = json_object_object_get(jsonP, "musicName");
    std::string buffer = json_object_to_json_string(result);
    const std::string &buf = buffer;
    TagLib::String musicName(buf, TagLib::String::UTF8);
    f.tag()->setTitle(musicName);


    std::cout << buffer << std::endl;


    result = json_object_object_get(jsonP, "artist");
    printf("%s\n", json_object_to_json_string(result));

    result = json_object_object_get(jsonP, "album");
    printf("%s\n", json_object_to_json_string(result));

    result = json_object_object_get(jsonP, "bitrate");
    printf("%s\n", json_object_to_json_string(result));

    result = json_object_object_get(jsonP, "format");
    printf("%s\n", json_object_to_json_string(result));

    f.save();
    return 0;
}
