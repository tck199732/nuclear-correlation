cmake_minimum_required(VERSION 3.14)
project(standalone LANGUAGES CXX)
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)

# add main package
CPMAddPackage(NAME NuclearCorrelation SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
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

foreach(source ${executable_sources})
    get_filename_component(exec_name ${source} NAME_WE) 
    add_executable(${exec_name}.exe ${source})
    target_link_libraries(
        ${exec_name}.exe 
        PUBLIC 
        NuclearCorrelation
        ${PROJECT_BINARY_DIR}/../util/libutil.so
        ${PROJECT_BINARY_DIR}/../custom/libcustom.so
        ${ROOT_LIBRARIES} 
    )

    target_include_directories(
        ${exec_name}.exe 
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        # path to source files
        ${CMAKE_CURRENT_LIST_DIR}/../util
        ${CMAKE_CURRENT_LIST_DIR}/../custom
        "${ROOT_INCLUDE_DIRS}"
    )
endforeach(source)