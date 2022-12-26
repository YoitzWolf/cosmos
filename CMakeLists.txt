# 
# CMake File.
# Building Configuration

cmake_minimum_required(VERSION 3.21.3)
project(cosmos)

set(CMAKE_CXX_STANDARD 17)
# add_subdirectory(peripherals)
# add_subdirectory(src)


include_directories (${CMAKE_SOURCE_DIR}) #/include
#include_directories (${CMAKE_SOURCE_DIR}/src)

# include_directories (${CMAKE_SOURCE_DIR}/include/structs)
# link_directories(${CMAKE_SOURCE_DIR}/src/structs)
# link_directories(${CMAKE_SOURCE_DIR}/src/integrators)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# include(src/integrators/CMakeLists.txt)
# include(src/structs/CMakeLists.txt)
# include(Src/CMakeLists.txt)

# target_link_libraries (/src/structs structs)

add_executable(cosmos main.cpp #image.png
# ${structs_source} 
    # src/structs/vec.cpp
    # src/structs/memo.cpp
    # src/integrators/euler.cpp
)