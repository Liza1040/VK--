cmake_minimum_required(VERSION 3.10.2)
project(test_sum)

set(TEST_SUM_EXECUTABLE)
set(TEST_SUM_INCLUDE_DIRS)

file(GLOB SOURCES *.cpp)

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