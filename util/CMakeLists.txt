set (
    util_sources
    ame/ame.cpp
    physics/physics.cpp
)


add_compile_options(
    -fPIC
    -pipe
    -Wall
    -g
    -Os
)

add_library(${util_name} SHARED ${util_sources})

target_include_directories(
    ${util_name}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
