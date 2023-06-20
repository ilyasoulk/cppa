cmake_minimum_required(VERSION 3.25)
project(graph LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(graph)

add_executable(main main.cpp)
target_link_libraries(main graph_lib)
add_executable(main2 main2.cpp)
target_link_libraries(main2 graph_lib)
add_executable(main3 main3.cpp)
target_link_libraries(main3 graph_lib)
