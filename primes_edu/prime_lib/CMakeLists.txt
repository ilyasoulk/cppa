cmake_minimum_required(VERSION 3.0)

# Project name
project(prime_lib)


add_library(prime_lib prime.cc include/prime_lib.hh)

target_compile_features(prime_lib PUBLIC cxx_std_20)