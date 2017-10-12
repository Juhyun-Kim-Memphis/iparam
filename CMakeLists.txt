cmake_minimum_required(VERSION 3.8)
project(iparam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES catch_include.cpp testcases.cpp IParam.cpp IParam.hpp Module.cpp Module.hpp BufferCache.cpp BufferCache.hpp ModuleFactory.cpp ModuleFactory.hpp)
add_executable(iparam ${SOURCE_FILES})

