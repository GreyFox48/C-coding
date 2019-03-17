cmake_minimum_required(VERSION 3.13)
project(MatthewOlsen4)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(MatthewOlsen4
        src/main.c
        src/scanner.h
        #src/scanner_ad_hoc.c
        src/scanner_nested_cases.c
        CMakeLists.txt
        input.txt
        )
