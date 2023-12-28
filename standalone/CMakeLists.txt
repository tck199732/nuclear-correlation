cmake_minimum_required(VERSION 3.22...3.28)
project(standalone LANGUAGES CXX)
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)

CPMAddPackage(NAME NuclearCorrelation SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
CPMAddPackage(NAME NuclearUtilities SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../util)
CPMAddPackage(NAME UserCorrelation SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../custom)
CPMAddPackage(
    NAME argparse
    GITHUB_REPOSITORY p-ranav/argparse
    VERSION 3.0
)

CPMAddPackage(
    NAME indicators
    GITHUB_REPOSITORY p-ranav/indicators
    VERSION 2.3
)

find_package(ROOT REQUIRED)

set(
    executable_sources
    main.cpp
)

foreach(source ${executable_sources})
    get_filename_component(exec_name ${source} NAME_WE) 
    add_executable(${exec_name}.exe ${source})
    target_link_libraries(
        ${exec_name}.exe 
        PUBLIC 
        NuclearCorrelation
        NuclearUtilities
        UserCorrelation
        argparse
        indicators
        ${ROOT_LIBRARIES} 
    )
    target_include_directories(
        ${exec_name}.exe 
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${ROOT_INCLUDE_DIRS}
    )
endforeach(source)