cmake_minimum_required(VERSION 3.17)

project(odd VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Doxygen)

add_subdirectory(src)
add_subdirectory(docs)
