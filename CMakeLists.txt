cmake_minimum_required(VERSION 3.15)
project(fuckncm C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/Cellar/openssl/1.0.2t/include)
include_directories(/usr/local/Cellar/json-c/0.13.1/include)
include_directories(/usr/local/Cellar/taglib/1.11.1/include)

link_directories(/usr/local/Cellar/openssl/1.0.2t/lib)
link_directories(/usr/local/Cellar/json-c/0.13.1/lib)
link_directories(/usr/local/Cellar/taglib/1.11.1/lib)


add_executable(fuckncm main.c otherFun/base64.c)
add_executable(test test.c)
add_executable(test2 test2.c)
add_executable(tags addCover.c)
add_executable(tags2 addCov.cpp)

target_link_libraries(fuckncm ssl crypto)
target_link_libraries(test2 ssl crypto)
target_link_libraries(test json-c)
target_link_libraries(tags2 tag json-c)


add_library(base64 STATIC otherFun/base64.c)
target_link_libraries(fuckncm base64)
target_link_libraries(test base64)
target_link_libraries(test2 base64)
