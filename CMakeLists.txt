cmake_minimum_required(VERSION 3.10)
project(structures)
add_library(structures INTERFACE)
target_include_directories(structures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
