cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB files
     "*.h"
     "*.cpp"
)

include_directories(.)
add_subdirectory(plugins)

add_executable(planetarium ${files})
target_link_libraries(planetarium sfml-system sfml-window sfml-graphics Boost::headers Boost::system Boost::filesystem)
target_include_directories(planetarium PRIVATE .)

install(TARGETS planetarium
    RUNTIME DESTINATION .          
    LIBRARY DESTINATION .           
    ARCHIVE DESTINATION .  
)

