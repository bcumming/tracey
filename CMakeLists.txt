cmake_minimum_required(VERSION 3.12)
project(tracey)

# C++ settings
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(examples)

# Generate a json file with compilation commands for each file
set(CMAKE_EXPORT_COMPILE_COMMANDS "YES")
