cmake_minimum_required(VERSION 3.8)
project(casino)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES casino.c)
add_executable(casino ${SOURCE_FILES})