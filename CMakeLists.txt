cmake_minimum_required(VERSION 3.22 ...)
project(NuclearCorrelation VERSION 1.0 LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

include(cmake/CPM.cmake)
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

set(dev_folder_name "dev")
set ( 
    dev_sources 
    base_cut.cpp
    fevent.cpp
    event.cpp
    track.cpp
    analysis.cpp
    manager.cpp
)

List(TRANSFORM dev_sources PREPEND ${CMAKE_CURRENT_LIST_DIR}/${dev_folder_name}/)
add_library(${PROJECT_NAME} SHARED ${dev_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${dev_folder_name}>
    $<INSTALL_INTERFACE:${dev_folder_name}/${PROJECT_NAME}-${PROJECT_VERSION}>
)

string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)
packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}

  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/${dev_folder_name}
  INCLUDE_DESTINATION ${dev_folder_name}/${PROJECT_NAME}-${PROJECT_VERSION}

  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
)
