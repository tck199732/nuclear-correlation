cmake_minimum_required(VERSION 3.14)
project(standalone LANGUAGES CXX)
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)

CPMAddPackage(NAME NuclearCorrelation SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
CPMAddPackage(NAME NuclearUtilities SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../util)
CPMAddPackage(NAME UserCorrelation SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../custom)
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
        ${ROOT_LIBRARIES} 
    )
    target_include_directories(
        ${exec_name}.exe 
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${ROOT_INCLUDE_DIRS}
    )
endforeach(source)