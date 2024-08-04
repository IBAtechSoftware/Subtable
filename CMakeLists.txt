cmake_minimum_required(VERSION 3.16)

project(Subtable)

include_directories("include")

add_library(subtable SHARED src/subtable.cpp)
