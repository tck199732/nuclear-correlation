cmake_minimum_required(VERSION 3.14)
project(UserCorrelation VERSION 1.0 LANGUAGES CXX)
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)

CPMAddPackage(NAME NuclearCorrelation SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
CPMAddPackage(NAME NuclearUtilities SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../util)

find_package(ROOT REQUIRED)

set (
    custom_sources
    readers/custom_reader.cpp
    readers/custom_event.cpp
    cuts/custom_event_cut.cpp
    cuts/custom_track_cut.cpp
    cuts/custom_pair_cut.cpp
    cuts/custom_event_monitor.cpp
    cuts/custom_track_monitor.cpp
    cuts/custom_pair_monitor.cpp
    correlations/custom_correlation.cpp
)

add_library(${PROJECT_NAME} SHARED ${custom_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${PROJECT_NAME}-${PROJECT_VERSION}>
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE
    NuclearCorrelation
    NuclearUtilities
    ${ROOT_LIBRARIES}
)

string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)
packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}
  INCLUDE_DESTINATION ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
  DEPENDENCIES "ROOT ${ROOT_VERSION}" 
)

