cmake_minimum_required(VERSION 3.15)
project(fuckncm C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/Cellar/openssl/1.0.2t/include)
include_directories(/usr/local/Cellar/json-c/0.13.1/include)

link_directories(/usr/local/Cellar/openssl/1.0.2t/lib)
link_directories(/usr/local/Cellar/json-c/0.13.1/lib)


add_executable(fuckncm main.c otherFun/base64.c)
add_executable(test test.c)

target_link_libraries(fuckncm ssl crypto)
target_link_libraries(test json-c)


add_library(base64 STATIC otherFun/base64.c)
target_link_libraries(fuckncm base64)
target_link_libraries(test base64)
