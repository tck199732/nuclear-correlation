cmake_minimum_required(VERSION 3.22...3.28)
project(UnitTests VERSION 1.0 LANGUAGES CXX)

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/util ${CMAKE_BINARY_DIR}/util)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dev ${CMAKE_BINARY_DIR}/dev)
