cmake_minimum_required(VERSION 3.14)
project(DevTests LANGUAGES CXX)
include(../../cmake/tools.cmake)
include(../../cmake/CPM.cmake)

CPMAddPackage(NAME NuclearCorrelation SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
CPMAddPackage("gh:doctest/doctest@2.4.11")

set(
    testing_sources
    main.cpp
    test_reader.cpp
    test_track.cpp
    test_property.cpp
)

add_executable(${PROJECT_NAME} ${testing_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC 
    NuclearCorrelation
    ${ROOT_LIBRARIES}
    doctest::doctest
)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

enable_testing()
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${PROJECT_NAME})

if (ENABLE_TEST_COVERAGE)
    target_compile_options(NuclearCorrelation PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
    target_link_options(NuclearCorrelation PUBLIC -fprofile-arcs -ftest-coverage)
endif()
