cmake_minimum_required(VERSION 3.8)
project(PCSC2017_Group4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(PCSC2017_Group4 ${SOURCE_FILES})
add_executable(main2 main2.cpp)

file(COPY "Doxyfile" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
find_package(Doxygen)
add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )

link_directories("/usr/lib/x86_64-linux-gnu/")
target_link_libraries(PCSC2017_Group4 libsndfile.so.1)
target_link_libraries(main2 libsndfile.so.1)
