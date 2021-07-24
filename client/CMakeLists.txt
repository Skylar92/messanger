cmake_minimum_required(VERSION 3.19)
project(messenger)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_SOURCE
        socket/ClientSocketConnector.h
        ../core/socket/SocketConnector.h
        ../core/socket/dto/Message.h
        ../core/socket/utils/SerializationUtils.h

        ../core/socket/SocketConnector.cpp
        socket/ClientSocketConnector.cpp
)

set(BOOST_INCLUDEDIR C:/CPlusPlus/vcpkg/installed/x64-windows/include)
set(BOOST_LIBRARYDIR C:/CPlusPlus/vcpkg/installed/x64-windows/lib)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS serialization REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(clientChat main.cpp ${EXECUTABLE_SOURCE})
target_link_libraries(clientChat ${Boost_LIBRARIES})