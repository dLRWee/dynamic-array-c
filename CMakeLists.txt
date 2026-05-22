cmake_minimum_required(VERSION 3.15)
project(DynamicArrayC VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /sdl)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(dynamic_array_project
    main.c
    DynamicArray.c
    DynamicArray.h
    Logger.c
    Logger.h
    Test.c
    Test.h
)

target_include_directories(dynamic_array_project PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})