cmake_minimum_required(VERSION 3.10)
project(Planets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

file(COPY conanfile.txt DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(core)
add_subdirectory(plugins)

add_executable(Planetarium main.cpp)
target_link_libraries(Planetarium Core)
add_dependencies(Planetarium OldFFormat)