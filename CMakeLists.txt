# 
# CMake File.
# Building Configuration

cmake_minimum_required(VERSION 3.21.3)
project(cosmos)

set(CMAKE_CXX_STANDARD 17)
# add_subdirectory(peripherals)
# add_subdirectory(src)


include_directories (${CMAKE_SOURCE_DIR}/include)
# include_directories (${CMAKE_SOURCE_DIR}/include/structs)
link_directories(${CMAKE_SOURCE_DIR}/src/structs)
link_directories(${CMAKE_SOURCE_DIR}/src/integrators)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


# set(SOURCES test.cpp lib1.cpp lib2.cpp)
# file(GLOB Scrs ${CMAKE_SOURCE_DIR}/src/structs/*.cpp ${CMAKE_SOURCE_DIR}/src/integrators/*.cpp)

add_executable(cosmos ${CMAKE_SOURCE_DIR}/src/structs/vec.cpp ${CMAKE_SOURCE_DIR}/src/structs/memo.cpp ${CMAKE_SOURCE_DIR}/src/integrators/euler.cpp main.cpp) #src/structs/vec.cpp src/structs/memo.cpp src/integrators/euler.cpp