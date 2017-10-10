cmake_minimum_required(VERSION 3.8)
project(iparam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES iparam.cpp iparam.h)
add_executable(iparam ${SOURCE_FILES})