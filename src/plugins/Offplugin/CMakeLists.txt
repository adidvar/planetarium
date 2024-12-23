cmake_minimum_required(VERSION 3.30)
project(OldFileFormat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB files 
     "*.h"
     "*.cpp"
)

add_library(OldFFormat MODULE ${files})
target_link_libraries(OldFFormat Boost::headers)

install(TARGETS OldFFormat 
    RUNTIME DESTINATION .          
    LIBRARY DESTINATION .           
    ARCHIVE DESTINATION .  
)

