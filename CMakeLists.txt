cmake_minimum_required(VERSION 3.0)
project(dsacpp CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(dsacpp ${SOURCES})

target_include_directories(dsacpp PRIVATE include)
target_link_libraries(dsacpp pthread)