cmake_minimum_required(VERSION 3.14)
project(standalone LANGUAGES CXX)
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)

# add main package
set(package_name NuclearCorrelation)
CPMAddPackage(NAME ${package_name} SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
find_package(ROOT REQUIRED)

set(
    executable_sources
    main.cpp
)

add_compile_options(
    -fPIC
    -pipe
    -Wall
    -g
    -Os
)

get_filename_component(libutil ${PROJECT_BINARY_DIR}/../util/libutil.so ABSOLUTE)
get_filename_component(libcustom ${PROJECT_BINARY_DIR}/../custom/libcustom.so ABSOLUTE)
get_filename_component(util_inc ${CMAKE_CURRENT_LIST_DIR}/../util ABSOLUTE)
get_filename_component(custom_inc ${CMAKE_CURRENT_LIST_DIR}/../custom ABSOLUTE)

foreach(source ${executable_sources})
    get_filename_component(exec_name ${source} NAME_WE) 
    add_executable(${exec_name}.exe ${source})
    add_dependencies(${exec_name}.exe ${package_name} util custom)

    target_link_libraries(
        ${exec_name}.exe 
        PUBLIC 
        ${package_name}
        ${libutil}
        ${libcustom}
        ${ROOT_LIBRARIES} 
    )

    target_include_directories(
        ${exec_name}.exe 
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${util_inc}
        ${custom_inc}
        ${ROOT_INCLUDE_DIRS}
    )
endforeach(source)