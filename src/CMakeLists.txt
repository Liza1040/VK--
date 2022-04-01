cmake_minimum_required(VERSION 3.10.2)
project(numbers)

add_subdirectory(algorithm)

message("ALGORITHM_INCLUDE_DIRS = ${ALGORITHM_INCLUDE_DIRS}")
message("ALGORITHM_LIBRARIES = ${ALGORITHM_LIBRARIES}")

#file(GLOB SOURCES "*.c" "**/*.c")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${ALGORITHM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ALGORITHM_LIBRARIES})

add_subdirectory(tests)
