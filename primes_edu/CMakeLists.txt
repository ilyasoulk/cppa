cmake_minimum_required(VERSION 3.25)
project(prime)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fconcepts-diagnostics-depth=10")

add_subdirectory(prime_lib)

add_executable(primes1 main_1.cpp)
target_include_directories(primes1 BEFORE PUBLIC "prime_lib/include")
target_link_libraries(primes1 prime_lib)

add_executable(primes2 main_2.cpp)
target_include_directories(primes2 BEFORE PUBLIC "prime_lib/include")
target_link_libraries(primes2 prime_lib)
