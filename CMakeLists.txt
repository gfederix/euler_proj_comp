cmake_minimum_required(VERSION 3.16)
project(Euler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
# include(GoogleTest)
enable_testing()

find_package(GTest REQUIRED)

add_executable(test1 tests/test_sum_of_digits_254.cpp)
target_link_libraries(test1  GTest::Main)
# target_link_libraries(test1 gtest_main)
gtest_discover_tests(test1)
