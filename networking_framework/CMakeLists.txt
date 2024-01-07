cmake_minimum_required(VERSION 3.12)
project(networking_framework)

set(CMAKE_CXX_STANDARD 11)

# Include directories for header files
include_directories(include)

# Server executable
add_executable(chat_server
        src/server.cpp
        examples/example_server.cpp)

# Client executable
add_executable(chat_client
        src/client.cpp
        examples/example_client.cpp)
