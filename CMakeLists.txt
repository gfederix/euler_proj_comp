cmake_minimum_required(VERSION 3.16)
project(Euler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
subdirs(src)

enable_testing()
find_package(GTest REQUIRED)
subdirs(tests)

