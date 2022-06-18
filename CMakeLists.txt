cmake_minimum_required(VERSION 3.10)
project(Planets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

file(GLOB files 
     "*.h"
     "*.cpp"
)
add_executable(Planetarium ${files})
target_link_libraries(Planetarium sfml-system sfml-window sfml-graphics)
