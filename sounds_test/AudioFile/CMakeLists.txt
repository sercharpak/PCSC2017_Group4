cmake_minimum_required(VERSION 3.8)
project(advanced_cmake)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES AudioFile.cpp test_main.cpp)
add_executable(advanced_cmake ${SOURCE_FILES})