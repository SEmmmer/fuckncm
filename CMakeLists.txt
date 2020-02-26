cmake_minimum_required(VERSION 3.15)
project(fuckncm C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/Cellar/openssl/1.0.2t/include)
link_directories(/usr/local/Cellar/openssl/1.0.2t/lib)
add_executable(fuckncm main.c)

target_link_libraries(fuckncm ssl crypto)

