cmake_minimum_required(VERSION 3.10.2)
project(parallel)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-g -fprofile-arcs -ftest-coverage -fPIC -O0")

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(PARALLEL_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(PARALLEL_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)