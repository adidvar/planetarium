cmake_minimum_required(VERSION 3.10)
project(Planets)

set(SFML_DIR D:/Libs/sfml-64/lib/cmake/SFML/)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(Boost 1.59.0 COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

add_executable(Planets main.cpp dump.cpp init.cpp movement.cpp orbit_queue.cpp planet.cpp ship.cpp vector2f.cpp)
include_directories(${SFML_DIR}/../../../../include .)
include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(Planets ${Boost_LIBRARIES} sfml-system sfml-window sfml-graphics)