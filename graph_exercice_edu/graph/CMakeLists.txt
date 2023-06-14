# CMakeLists.txt

# Must generate the lib graph_lib
cmake_minimum_required(VERSION 3.12)

add_library(graph_lib STATIC
    "include/graph.hh"
    edge.cpp 
    edge_iterator.cpp 
    edge_range.cpp 
    graph.cpp)
