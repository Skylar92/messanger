cmake_minimum_required(VERSION 3.19)
project(messenger)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_SOURCE
        socket/ClientSocketConnector.h

        socket/ClientSocketConnector.cpp
        )

add_executable(clientChat main.cpp ${EXECUTABLE_SOURCE})