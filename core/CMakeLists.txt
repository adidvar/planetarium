cmake_minimum_required(VERSION 3.10)
project(Planets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(Boost 1.79.0 REQUIRED)

file(GLOB files
     "*.h"
     "*.cpp"
)

add_library(Core ${files})
target_link_libraries(Core PUBLIC sfml-system PUBLIC sfml-window PUBLIC sfml-graphics PUBLIC Boost::Boost)
target_include_directories(Core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
