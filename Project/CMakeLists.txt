cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Read.cpp Signal.cpp AudioFile.cpp test_main.cpp)
add_executable(Project ${SOURCE_FILES})