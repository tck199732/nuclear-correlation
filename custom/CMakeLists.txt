cmake_minimum_required(VERSION 3.14)
project(custom LANGUAGES CXX)
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)

# add main package
set(package_name NuclearCorrelation)
CPMAddPackage(NAME ${package_name} SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
find_package(ROOT REQUIRED)

set (
    reader_sources
    custom_reader.cpp
    custom_event.cpp
)

set ( 
    cut_sources
    custom_event_cut.cpp
    custom_track_cut.cpp
    custom_pair_cut.cpp
    custom_event_monitor.cpp
    custom_track_monitor.cpp
    custom_pair_monitor.cpp
)

set (
    corrfctn_sources
    custom_correlation.cpp
)

List(TRANSFORM reader_sources PREPEND "readers/")
List(TRANSFORM cut_sources PREPEND "cuts/")
List(TRANSFORM corrfctn_sources PREPEND "correlations/")

add_compile_options(
    -fPIC
    -pipe
    -Wall
    -g
    -Os
)

get_filename_component(libutil ${PROJECT_BINARY_DIR}/../util/libutil.so ABSOLUTE)
get_filename_component(util_inc ${CMAKE_CURRENT_LIST_DIR}/../util ABSOLUTE)
add_library(${PROJECT_NAME} SHARED ${reader_sources} ${cut_sources} ${corrfctn_sources})
add_dependencies(${PROJECT_NAME} ${package_name} util)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${util_inc}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE
    ${package_name}
    ${libutil}
    ${ROOT_LIBRARIES}
)
