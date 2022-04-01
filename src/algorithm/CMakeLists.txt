cmake_minimum_required(VERSION 3.10.2)
project(algorithm)

option(MULTIPROCESS "Do you want to run multiprocessing?" OFF)

set(ALGORITHM_LIBRARIES)
set(ALGORITHM_INCLUDE_DIRS)
set(ALGORITHM_SOURCES)

if (MULTIPROCESS)
  file(GLOB SOURCES src/algorithm.c src/parallel.c)
  file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/inc)
  add_library(${PROJECT_NAME} STATIC ${SOURCES})
else()
  file(GLOB SOURCES src/algorithm.c src/naive.c)
  file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/inc)
  add_library(${PROJECT_NAME} SHARED ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

set(ALGORITHM_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(ALGORITHM_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
set(ALGORITHM_SOURCES ${SOURCES} PARENT_SCOPE)