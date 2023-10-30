cmake_minimum_required(VERSION 3.14)
project(NuclearUtilities VERSION 1.0 LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

include(../cmake/CPM.cmake)
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

set (
    util_sources
    ame/ame.cpp
    physics/physics.cpp
)

set(
    util_headers
    ame/ame.hpp
    physics/physics.hpp
)

set( external_folder_name "external" )
file(GLOB_RECURSE external_headers ${CMAKE_CURRENT_LIST_DIR}/${external_folder_name}/**/*.hpp)
file(GLOB_RECURSE external_sources ${CMAKE_CURRENT_LIST_DIR}/${external_folder_name}/**/*.cpp)

add_library(${PROJECT_NAME} SHARED ${util_headers} ${external_headers} ${util_sources} ${external_sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${PROJECT_NAME}-${PROJECT_VERSION}>
)

string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)
packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}
  INCLUDE_DESTINATION ${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
)
