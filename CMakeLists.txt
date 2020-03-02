cmake_minimum_required(VERSION 3.15)
project(fuckncm C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/Cellar/openssl/1.0.2t/include)

link_directories(/usr/local/Cellar/openssl/1.0.2t/lib)



add_executable(fuckncm main.c base64.c WjCryptLib_Rc4.c)
add_executable(test test.c)
#add_executable(base64 base64.c)

target_link_libraries(fuckncm ssl crypto)


add_library(base64 STATIC base64.c)
target_link_libraries(fuckncm base64)
target_link_libraries(test base64)