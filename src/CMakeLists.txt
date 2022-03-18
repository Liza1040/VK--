cmake_minimum_required(VERSION 3.10.2)
project(film)

add_subdirectory(list)

message("LIST_INCLUDE_DIRS = ${LIST_INCLUDE_DIRS}")
message("LIST_LIBRARIES = ${LIST_LIBRARIES}")

add_subdirectory(find)

file(GLOB SOURCES "*.c" "**/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${LIST_INCLUDE_DIRS} ${FIND_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIST_LIBRARIES} ${FIND_LIBRARIES})

add_subdirectory(tests)

