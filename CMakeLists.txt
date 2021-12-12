cmake_minimum_required(VERSION 3.16)
project(lab_03)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_03 src/elf_parser.cpp main.cpp src/fsymtab_print.cpp)
include_directories("include")