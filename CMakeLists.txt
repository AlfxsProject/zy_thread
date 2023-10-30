cmake_minimum_required(VERSION 3.26)
project(zy_thread C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_definitions(DO_MUTEX DO_PTHREAD)

include_directories(zy_alloc)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true "zy_alloc/*.h" "zy_alloc/*.c")

set(SOURCES ${SOURCES} zy_thread.h zy_thread.c)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES})