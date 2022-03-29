cmake_minimum_required(VERSION 3.10.2)
project(sum_numbers)

add_subdirectory(naive)

message("NAIVE_INCLUDE_DIRS = ${NAIVE_INCLUDE_DIRS}")
message("NAIVE_LIBRARIES = ${NAIVE_LIBRARIES}")

#add_subdirectory(find)

file(GLOB SOURCES "*.c" "**/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${NAIVE_INCLUDE_DIRS})# ${FIND_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${NAIVE_LIBRARIES})# ${FIND_LIBRARIES})

add_subdirectory(tests)

