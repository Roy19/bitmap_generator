cmake_minimum_required (VERSION 3.0)

project (bitmap_gen)

set (CMAKE_CXX_COMPILER )
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_CFLAGS "-O3")

file (GLOB project_sources src/*.cpp)
file (GLOB project_headers src/*.h src/*.hpp)

add_executable (bitmap_gen ${project_sources} ${project_headers})
