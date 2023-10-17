set(
    executable_sources
    main.cpp
)

add_compile_options(
    -fPIC
    -pipe
    -Wall
    -g
    -Os
)

foreach(source ${executable_sources})
    get_filename_component(exec_name ${source} NAME_WE) 
    add_executable(${exec_name}.exe ${source})
    target_link_libraries(
        ${exec_name}.exe 
        PUBLIC 
        ${custom_name}
        ${dev_name}
        ${ROOT_LIBRARIES} 
    )

    target_include_directories(
        ${exec_name}.exe 
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        # path to lib
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_BINARY_DIR}/${dev_folder}"
        "${PROJECT_BINARY_DIR}/${custom_folder}"
        # path to source files
        "${PROJECT_SOURCE_DIR}/${dev_folder}"
        "${PROJECT_SOURCE_DIR}/${custom_folder}"
        "${PROJECT_SOURCE_DIR}/${custom_folder}/${corrfctn_folder}"
        "${PROJECT_SOURCE_DIR}/${custom_folder}/${reader_folder}"
        "${PROJECT_SOURCE_DIR}/${custom_folder}/${cut_folder}"
        "${ROOT_INCLUDE_DIRS}"
    )
endforeach(source)