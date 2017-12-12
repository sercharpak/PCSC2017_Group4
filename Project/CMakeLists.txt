cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Read.cpp Signal.cpp AudioFile.cpp main.cpp ConfigFileParser.cpp ConfigFileParser.h ConfigFileExecuter.cpp ConfigFileExecuter.h)
add_executable(Project ${SOURCE_FILES})
add_executable(TestFT Read.cpp Signal.cpp AudioFile.cpp TestFT.cpp)
add_executable(TestSong Read.cpp Signal.cpp AudioFile.cpp TestSong.cpp)

file(COPY "Doxyfile" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY "atom_icon_192.ico" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
find_package(Doxygen)
add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
