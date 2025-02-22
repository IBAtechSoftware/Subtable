cmake_minimum_required(VERSION 3.14..3.31 FATAL_ERROR)

project(Subtable)

add_library(subtable SHARED src/subtable.cpp)
add_library(subtable::Subtable ALIAS subtable)

target_include_directories(subtable PUBLIC include)
