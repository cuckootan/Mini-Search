cmake_minimum_required(VERSION 3.5)
project(Mini_Search)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Cache.cc
        src/EchoServer.cc
        src/main.cc
        src/Text.cc
        src/Words.cc)

INCLUDE_DIRECTORIES(include)
LINK_LIBRARIES(echo pthread)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(main ${SOURCE_FILES})