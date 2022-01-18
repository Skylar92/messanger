cmake_minimum_required(VERSION 3.19)

project(messenger)

set(CMAKE_CXX_STANDARD 20)

include(../build/conanbuildinfo.cmake)
conan_basic_setup()

FILE(GLOB SOURCES main.cpp
        socket/*.h
        socket/*.cpp
        ../core/*/*.cpp
        ../core/*/*.h)

add_executable(clientChat main.cpp ${SOURCES})

target_link_libraries(clientChat ${CONAN_LIBS})