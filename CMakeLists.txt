cmake_minimum_required(VERSION 3.12)
project(tracey)

# Generate a json file with compilation commands for each file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ settings
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
# spack can be used to install the json library:
#   spack install nlohmann-json
#   spack load nlohmann-json
#   spack install fmt
#   spack load fmt
#find_package(nlohmann_json REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(examples)
