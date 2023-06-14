cmake_minimum_required(VERSION 3.25)
project(graph LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(graph)

add_executable(main main.cpp)
target_link_libraries(main graph_lib)