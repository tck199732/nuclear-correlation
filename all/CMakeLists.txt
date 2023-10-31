cmake_minimum_required(VERSION 3.14)
project(NuclearCorrelation VERSION 1.0 LANGUAGES CXX)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../standalone ${CMAKE_BINARY_DIR}/standalone)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../tests ${CMAKE_BINARY_DIR}/tests)
