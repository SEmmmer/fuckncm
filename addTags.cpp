//
// Created by Shirakami Emmmer on 2020/3/22.
//
#include <string>
#include <json-c/json.h>
#include <taglib/mpegfile.h>
#include <taglib/flacfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/fileref.h>
#include <taglib/tstring.h>
#include <taglib/attachedpictureframe.h>


void fixStr(std::string &str, size_t size) {
    for (int i = 0; i < size; ++i) { str[i] = str[i + 1]; }
    for (int j = size;; --j) {
        if (str[j] == 0x22) {
            str[j] = '\0';
            break;
        }
    }
}

std::string addArtist(struct json_object *jsonFile) {
    struct json_object *iter = nullptr;
    struct json_object *result = json_object_object_get(jsonFile, "artist");

    std::string allArtist;
    std::string eachArtist;

    for (int i = 0; i < json_object_array_length(result); ++i) {
        iter = json_object_array_get_idx(result, i);
        iter = json_object_array_get_idx(iter, 0);
        eachArtist = json_object_to_json_string(iter);
        fixStr(eachArtist, eachArtist.size());

        if (i == json_object_array_length(result) - 1) {
            allArtist += eachArtist;
            break;
        } else {
            eachArtist[eachArtist.size() - 1] = 0x20;
            eachArtist[eachArtist.size() - 2] = 0x2C;
            allArtist += eachArtist;
        }
    }
    return allArtist;
}

long readCover(FILE *cover) {
    fseek(cover, 0, SEEK_END);
    long size = ftell(cover);
    fseek(cover, 0, SEEK_SET);
    return size;
}

void setTags(json_object *jsonP, FILE *cover) {
    TagLib::Tag *tags;
    std::string buffer;
    TagLib::File *rawSong;
    struct json_object *result = nullptr;
    unsigned char bCover[readCover(cover)];
    fread(bCover, readCover(cover), 1, cover);
    TagLib::ByteVector vectorCover(reinterpret_cast<const char *>(bCover), readCover(cover));

    result = json_object_object_get(jsonP, "musicName");
    buffer = json_object_to_json_string(result);
    fixStr(buffer, buffer.size());
    TagLib::String musicName(buffer, TagLib::String::UTF8);
    TagLib::String artist(addArtist(jsonP), TagLib::String::UTF8);
    result = json_object_object_get(jsonP, "album");
    buffer = json_object_to_json_string(result);
    fixStr(buffer, buffer.size());
    TagLib::String album(buffer, TagLib::String::UTF8);

    buffer = json_object_to_json_string(json_object_object_get(jsonP, "format"));
    fixStr(buffer, buffer.size());

    if (memcmp(buffer.c_str(), "flac", 3) == 0) {
        rawSong = new TagLib::FLAC::File("tmp/out.flac");
        tags = rawSong->tag();
        tags->setTitle(musicName);
        tags->setArtist(artist);
        tags->setAlbum(album);

        auto picture = new TagLib::FLAC::Picture;
        picture->setMimeType("image/jpeg");
        picture->setType(TagLib::FLAC::Picture::FrontCover);
        picture->setData(vectorCover);
        dynamic_cast<TagLib::FLAC::File *>(rawSong)->addPicture(picture);

        rawSong->save();
    } else if (memcmp(buffer.c_str(), "mp3", 3) == 0) {
        rawSong = new TagLib::MPEG::File("tmp/out.mp3");
        tags = dynamic_cast<TagLib::MPEG::File *>(rawSong)->ID3v2Tag(true);
        tags->setTitle(musicName);
        tags->setArtist(artist);
        tags->setAlbum(album);

        auto picture = new TagLib::ID3v2::AttachedPictureFrame;
        picture->setMimeType("image/jpeg");
        picture->setPicture(vectorCover);
        dynamic_cast<TagLib::ID3v2::Tag *>(tags)->addFrame(picture);
        rawSong->save();
    }
};


int main() {
    auto cover = fopen("tmp/cover.jpeg", "rb");
    auto jsonP = json_object_from_file("tmp/tmp.json");
    setTags(jsonP, cover);
    return 0;
}
