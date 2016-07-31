cmake_minimum_required(VERSION 3.5)
project(argparse)

add_compile_options(-std=c++1y)
enable_testing()
find_package(GTest REQUIRED)

add_library(argparse src/exception.cc src/argument.cc)

if (GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS} src)
    
    add_executable(argparse-test tests/argparse.cc)
    target_link_libraries(argparse-test ${GTEST_BOTH_LIBRARIES} pthread argparse)
    add_test(ArgParseTests argparse-test)
endif()

