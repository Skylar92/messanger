cmake_minimum_required(VERSION 3.19)

project(messenger)

set(CMAKE_CXX_STANDARD 20)

include(../build/conanbuildinfo.cmake)
conan_basic_setup()

FILE(GLOB SOURCES main.cpp
        socket/*.h
        socket/*.cpp
        socket/*/*.h
        socket/*/*.cpp
        ../core/socket/*.cpp
        ../core/socket/*.h)

add_executable(server main.cpp ${SOURCES})

target_link_libraries(server ${CONAN_LIBS})
