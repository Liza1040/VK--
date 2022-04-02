cmake_minimum_required(VERSION 3.10.2)
project(test_algorithm)

set(TEST_SUM_EXECUTABLE)
set(TEST_SUM_INCLUDE_DIRS)

if(MULTIPROCESS)
  file(GLOB SOURCES test_algorithm.cpp test_parallel.cpp)
else()
  file(GLOB SOURCES test_algorithm.cpp test_naive.cpp)
endif()

#file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR)

option(BUILD_GMOCK "Do you want to build gmonk?" OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${ALGORITHM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ALGORITHM_LIBRARIES} gtest_main)

set(TEST_SUM_EXECUTABLE ${PROJECT_NAME} PARENT_SCOPE)
set(TEST_SUM_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

add_custom_target(
        tests_with_valgrind
        COMMAND valgrind
        --tool=memcheck
        --leak-check=full
        --show-leak-kinds=all
        --error-exitcode=1
        ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME}
)