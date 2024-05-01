cmake_minimum_required(VERSION 3.27)
project(ElfReader C)

set(CMAKE_C_STANDARD 99)

add_executable(ElfReader
        src/main.c
        src/options.c)

target_include_directories(ElfReader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
