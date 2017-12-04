cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Signal.cpp AudioFile.cpp main.cpp  )
add_executable(Project ${SOURCE_FILES})

file(COPY "Doxyfile" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY "atom_icon_192.ico" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
find_package(Doxygen)
add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )