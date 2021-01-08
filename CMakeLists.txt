cmake_minimum_required(VERSION 3.12)
project(tracey)

# Generate a json file with compilation commands for each file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ settings
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# create the tracey library
set(tracey_sources src/event.cpp src/id.cpp src/tracey.cpp src/threads.cpp src/clock.cpp)
add_library(tracey ${tracey_sources})
add_library(trace::tracey ALIAS tracey)

set(tracey_header_path ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(tracey_headers ${tracey_header_path}/tracey/tracey.hpp)

target_include_directories(tracey PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

find_package(fmt REQUIRED)
target_link_libraries(tracey PRIVATE fmt::fmt)

# Installation
#
# I gave up trying to configure CMake to install properly with a .cmake file,
# because CMake docs are no help, and online guides for modern CMake are
# written by suffers of Stockholme syndrome who can't see how crazy they sound.
#
# Instead, use meson to build.
