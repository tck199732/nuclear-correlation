cmake_minimum_required(VERSION 3.14)
project(UnitTests VERSION 1.0 LANGUAGES CXX)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/util ${CMAKE_BINARY_DIR}/util)
