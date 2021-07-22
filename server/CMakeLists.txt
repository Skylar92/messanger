cmake_minimum_required(VERSION 3.19)
project(messenger)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_SOURCE
        ../core/socket/SocketConnector.h
        ../server/socket/TCPServer.h
        ../server/socket/handler/ClientHandler.h
        ../core/socket/dto/Message.h

        ../core/socket/SocketConnector.cpp
        ../server/socket/TCPServer.cpp
        ../server/socket/handler/ClientHandler.cpp
)

add_executable(server main.cpp ${EXECUTABLE_SOURCE})
