cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)
set(DOC_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/doc)
set(SOURCE_FILES Read.cpp Signal.cpp AudioFile.cpp main.cpp ConfigFileParser.cpp ConfigFileExecuter.cpp MedianFilter.cpp)

add_executable(Project ${SOURCE_FILES})
add_executable(TestFT Read.cpp Signal.cpp AudioFile.cpp TestFT.cpp)
add_executable(TestErrorFT Read.cpp Signal.cpp AudioFile.cpp TestErrorFT.cpp)
add_executable(TestSong Read.cpp Signal.cpp AudioFile.cpp TestSong.cpp)
add_executable(TestFrequencyFile Read.cpp Signal.cpp AudioFile.cpp TestReadFrequencyFile.cpp ConfigFileParser.cpp ConfigFileExecuter.cpp MedianFilter.cpp)

#Copies files for Doxygen and test running
file(COPY "run_tests.sh" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY "Doxyfile" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY "atom_icon_192.ico" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY "test-audio"        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(MAKE_DIRECTORY ${DOC_FOLDER})
find_package(Doxygen)
add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
file(COPY ${DOC_FOLDER}      DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



