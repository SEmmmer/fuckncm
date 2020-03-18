#include <stdio.h>
#include <json-c/json.h>

void test_jsonc() {

    struct json_object *infor_object = NULL;
    infor_object = json_object_new_object();
    if (NULL == infor_object) {
        printf("new json object failed.\n");
        return;
    }

    struct json_object *para_object = NULL;
    para_object = json_object_new_object();
    if (NULL == para_object) {
        json_object_put(infor_object);//free
        printf("new json object failed.\n");
        return;
    }

    struct json_object *array_object = NULL;
    array_object = json_object_new_array();
    if (NULL == array_object) {
        json_object_put(infor_object);//free
        json_object_put(para_object);//free
        printf("new json object failed.\n");
        return;
    }

    /*添加json值类型到数组中*/
    json_object_array_add(array_object, json_object_new_int(256));
    json_object_array_add(array_object, json_object_new_int(257));
    json_object_array_add(array_object, json_object_new_int(258));

    json_object_object_add(para_object, "DeviceId", json_object_new_string("sn_iso_9000"));
    json_object_object_add(para_object, "MacAddr", json_object_new_string("AA:BB:CC:DD:EE:FF"));
    json_object_object_add(para_object, "Visible", json_object_new_int(1));

    /*添加json名称和值到json对象集合中*/
    json_object_object_add(infor_object, "method", json_object_new_string("GetSystemInfo"));
    json_object_object_add(infor_object, "param", para_object);
    json_object_object_add(infor_object, "id", json_object_new_string("101"));

    /*添加数组集合到json对象中*/
    json_object_object_add(infor_object, "array", array_object);

    printf("%s\n", json_object_to_json_string(infor_object));

    struct json_object *result_object = NULL;

    result_object = json_object_object_get(infor_object, "method");

    printf("%s\n", json_object_to_json_string(result_object));;

    result_object = json_object_object_get(infor_object, "param");

    printf("%s\n", json_object_to_json_string(result_object));

    result_object = json_object_object_get(infor_object, "array");

    printf("%s\n", json_object_to_json_string(result_object));

    for (int i = 0; i < json_object_array_length(result_object); i++) {
        struct json_object *obj = json_object_array_get_idx(result_object, i);
        printf("\t[%d]=%s\n", i, json_object_to_json_string(obj));
    }

    json_object_put(infor_object);//free

}

void json2() {
    struct json_object *musicName = NULL;
    musicName = json_object_new_object();
    if (NULL == musicName) {
        printf("new json object failed.\n");
        return;
    }

    struct json_object *format = NULL;
    format = json_object_new_object();
    if (NULL == format) {
        json_object_put(musicName);//free
        printf("new json object failed.\n");
        return;
    }

    struct json_object *artist = NULL;
    artist = json_object_new_array();
    if (NULL == artist) {
        json_object_put(musicName);//free
        json_object_put(format);//free
        printf("new json object failed.\n");
        return;
    }
    struct json_object *album = NULL;
    album = json_object_new_array();
    if (NULL == album) {
        json_object_put(musicName);//free
        json_object_put(format);//free
        json_object_put(artist);//free
        printf("new json object failed.\n");
        return;
    }

    json_object_from_file("tmp/tmp.json");
}


int main(int argc, char *argv[]) {

//    test_jsonc();
    json2();
    void *app = json_object_from_file("tmp/tmp.json");
    printbuf_free()
    return 0;
}