cmake_minimum_required(VERSION 3.10)
project(NuclearCorrelation VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(ROOT REQUIRED)
if (ROOT_FOUND)
    message(STATUS "ROOT FOUND")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/sanitizers-cmake/cmake" ${CMAKE_MODULE_PATH})
find_package(Sanitizers)

# name of the dynamically-linked library
set(dev_name "dev")
set(custom_name "custom")

# folder name of the source codes
set(dev_folder "dev")
set(custom_folder "custom")
set(exec_folder "exec")
# subfolder name of the source codes in $custom_folder
set(reader_folder "readers")
set(cut_folder "cuts")
set(corrfctn_folder "correlations")

add_subdirectory(${dev_folder})
add_subdirectory(${custom_folder})
add_subdirectory(${exec_folder})
