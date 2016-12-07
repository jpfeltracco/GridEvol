cmake_minimum_required(VERSION 3.1)

project(EvolGrid)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/run)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/run)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(CMAKE_CXX_FLAGS "-fPIC -std=c++1z -g")

add_subdirectory(GridEvol)
add_subdirectory(External/Hippocrates) 
add_subdirectory(External/googletest)

