cmake_minimum_required(VERSION 3.14)
project(util VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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

file(GLOB_RECURSE external_headers external/**/*.hpp)
file(GLOB_RECURSE external_sources external/**/*.cpp)

add_compile_options(
    -fPIC
    -pipe
    -Wall
    -g
    -Os
)

add_library(${PROJECT_NAME} SHARED ${util_headers} ${external_headers} ${util_sources} ${external_sources})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
