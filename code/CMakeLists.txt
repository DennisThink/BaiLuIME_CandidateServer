
cmake_minimum_required(VERSION 3.20)

project(MyService LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyService main.cpp)

target_link_libraries(MyService PRIVATE Advapi32)
add_subdirectory(server)