cmake_minimum_required(VERSION 3.24.2)
project(Planetarium LANGUAGES C CXX VERSION 1.0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(COPY_FILE conanfile.txt ${CMAKE_BINARY_DIR}/conanfile.txt)
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR};${CMAKE_PREFIX_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR};${CMAKE_MODULE_PATH}")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(Boost 1.82.0 REQUIRED)

add_subdirectory(src)