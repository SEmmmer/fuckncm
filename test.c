#include <stdio.h>
#include <json-c/json.h>
#include "test.h"


int main(int argc, char *argv[]) {

    struct json_object *im = NULL;
    im = json_object_from_file("tmp/tmp.json");
    printf("%s\n", json_object_to_json_string(im));
    struct json_object *result = NULL;

    result = json_object_object_get(im, "musicName");
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