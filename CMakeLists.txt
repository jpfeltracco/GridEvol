cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/run)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(CMAKE_CXX_FLAGS "-fPIC -std=c++1z")

add_subdirectory(GridEvol)
add_subdirectory(Hippocrates) 
