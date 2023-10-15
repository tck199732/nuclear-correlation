set (
    reader_sources
    custom_reader.cpp
)

set ( 
    cut_sources
    custom_event_cut.cpp
    custom_track_cut.cpp
    custom_pair_cut.cpp
)

set (
    corrfctn_sources
    custom_correlation.cpp
)

List(TRANSFORM reader_sources PREPEND "${reader_folder}/")
List(TRANSFORM cut_sources PREPEND "${cut_folder}/")
List(TRANSFORM corrfctn_sources PREPEND "${corrfctn_folder}/")

add_compile_options(
    -fPIC
    -pipe
    -Wall
    -g
    -Os
)

add_library(${custom_name} SHARED ${reader_sources} ${cut_sources} ${corrfctn_sources})

target_include_directories(
    ${custom_name}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/${custom_folder}/${reader_folder}
    ${PROJECT_SOURCE_DIR}/${custom_folder}/${cut_folder}
    ${PROJECT_SOURCE_DIR}/${custom_folder}/${corrfctn_folder}
    ${PROJECT_SOURCE_DIR}/${dev_folder}
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(
    ${custom_name} 
    PRIVATE
    ${dev_name}
    ${ROOT_LIBRARIES}
)



