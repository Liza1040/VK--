cmake_minimum_required(VERSION 3.10.2)
project(test_sum)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${NAIVE_INCLUDE_DIRS}) #${FIND_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${NAIVE_LIBRARIES} ${GTEST_LIBRARIES} pthread)# ${FIND_LIBRARIES} pthread)

add_custom_target(
        tests_with_valgrind
        COMMAND valgrind
        --tool=memcheck
        --leak-check=full
        --show-leak-kinds=all
        --error-exitcode=1
        ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME}
)