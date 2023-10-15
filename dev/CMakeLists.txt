set ( 
    dev_sources 
    fevent.cpp
    event.cpp
    particle.cpp
    track.cpp
    pair.cpp
    analysis.cpp
    manager.cpp
)

add_compile_options(
    -fPIC
    -pipe
    -Wall
    -g
    -Os
)

# for generating ROOT dictionary, not used in this repo.
# root_generate_dictionary(
#     ${dev_name}Dict
#     ${headers}
#     LINKDEF ${dev_name}LinkDef.hh
# )
# add_library(${dev_name} SHARED ${sources} ${dev_name}Dict.cxx)

add_library(${dev_name} SHARED ${dev_sources})
add_sanitizers(${dev_name})

target_include_directories(
    ${dev_name}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(
    ${dev_name} 
    PRIVATE
    ${ROOT_LIBRARIES}
)



