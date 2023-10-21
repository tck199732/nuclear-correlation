cmake_minimum_required(VERSION 3.14)
project(NuclearCorrelation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(ROOT REQUIRED)

# folder name of the source codes
set(custom_folder "custom")
set(util_folder "util")
set(exec_folder "standalone")

enable_testing()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../${util_folder} ${CMAKE_BINARY_DIR}/${util_folder})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../${custom_folder} ${CMAKE_BINARY_DIR}/${custom_folder})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../${exec_folder} ${CMAKE_BINARY_DIR}/${exec_folder})
