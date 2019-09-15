cmake_minimum_required(VERSION 3.14)
project(verification)

set(CMAKE_CXX_STANDARD 17)

add_library(verification STATIC userAPI.cpp userAPI.h)