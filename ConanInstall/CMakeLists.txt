cmake_minimum_required(VERSION 3.27)
project(compressor C)

find_package(ZLIB REQUIRED)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)