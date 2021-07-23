cmake_minimum_required(VERSION 3.19)

project(messenger)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        ../core/socket/SocketConnector.h
        ../server/socket/TCPServer.h
        ../server/socket/handler/ClientHandler.h
        ../core/socket/dto/Message.h

        ../core/socket/SocketConnector.cpp
        ../server/socket/TCPServer.cpp
        ../server/socket/handler/ClientHandler.cpp
)

set(BOOST_INCLUDEDIR C:/CPlusPlus/vcpkg/installed/x64-windows/include)
set(BOOST_LIBRARYDIR C:/CPlusPlus/vcpkg/installed/x64-windows/lib)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS serialization REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(server main.cpp ${SOURCE_FILES})
target_link_libraries(server ${Boost_LIBRARIES})
