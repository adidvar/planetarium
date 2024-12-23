cmake_minimum_required(VERSION 3.30)
project(Planetarium LANGUAGES C CXX VERSION 1.0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML COMPONENTS system window graphics REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(src)

file(GLOB DATA_FILES "data/*.oldsystem")

install(FILES ${DATA_FILES} 
        DESTINATION .)