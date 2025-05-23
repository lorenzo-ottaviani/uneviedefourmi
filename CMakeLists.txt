cmake_minimum_required(VERSION 3.15)
project(ant_life CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the compiler for Windows MSYS2
if (WIN32)
    set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
endif()

# Add G++-specific compilation options
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# === Server ===
file(GLOB SOURCES "src/*.cpp")
add_executable(ant_life ${SOURCES})
include_directories(include)

# Enable detailed build output
set(CMAKE_VERBOSE_MAKEFILE ON)
