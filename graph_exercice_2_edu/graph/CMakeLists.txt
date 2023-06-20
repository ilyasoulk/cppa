# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

# Project name
project(graph_lib)

set(CMAKE_CXX_STANDARD 23)

# Library source files
set(SOURCES graph.cpp)

# Library header files
set(HEADERS include/graph.hh include/graph_algos.hpp)

# Create the library
add_library(graph_lib STATIC ${SOURCES} ${HEADERS})
