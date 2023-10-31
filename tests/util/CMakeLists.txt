cmake_minimum_required(VERSION 3.14)
project(UtilityTests LANGUAGES CXX)
include(../../cmake/tools.cmake)
include(../../cmake/CPM.cmake)



CPMAddPackage(NAME NuclearUtilities SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../util)
CPMAddPackage("gh:doctest/doctest@2.4.11")
find_package(ROOT REQUIRED)

set(
    testing_sources
    main.cpp
    test_ame.cpp
    test_physics.cpp
)

add_executable(${PROJECT_NAME} ${testing_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC 
    NuclearUtilities
    ${ROOT_LIBRARIES}
    GenVector
    doctest::doctest
)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ROOT_INCLUDE_DIRS}
)

enable_testing()
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${PROJECT_NAME})