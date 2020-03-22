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

void buffer(){
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




    return 0;
}
