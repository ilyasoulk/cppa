# CMakeLists.txt

# Must generate the lib graph_lib
cmake_minimum_required(VERSION 3.12)

project(graph_lib LANGUAGES CXX)

add_library(graph_lib INTERFACE)
target_include_directories(graph_lib INTERFACE include)

# PSC ...
#add_library(graph_lib STATIC
#    "include/graph.hh")
#    edge.cpp
#    edge_iterator.cpp
#    edge_range.cpp
#    graph.cpp)
