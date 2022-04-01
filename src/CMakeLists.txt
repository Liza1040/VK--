cmake_minimum_required(VERSION 3.10.2)
project(numbers)

add_subdirectory(array)

add_subdirectory(naive)

message("NAIVE_INCLUDE_DIRS = ${NAIVE_INCLUDE_DIRS}")
message("NAIVE_LIBRARIES = ${NAIVE_LIBRARIES}")

add_subdirectory(parallel)

file(GLOB SOURCES "*.c" "**/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${ARRAY_INCLUDE_DIRS} ${NAIVE_INCLUDE_DIRS} ${PARALLEL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ARRAY_LIBRARIES} ${NAIVE_LIBRARIES} ${PARALLEL_LIBRARIES})

add_subdirectory(tests)
